// DungeonGenerator.cpp
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "RoomActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

ADungeonGenerator::ADungeonGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADungeonGenerator::BeginPlay()
{
    Super::BeginPlay();
    MazeGenerator();
}

/*
=====================================================
    FUNKCJA FILTRUJĄCA DOPUSZCZALNE POZIOMY Z DLA CELLI
=====================================================
*/
TArray<int32> ADungeonGenerator::FilterZValuesForCell(int32 CellIndex, const TArray<int32>& Candidates) const
{
    TArray<int32> Out;

    for (int32 Value : Candidates)
    {
        bool bValid = true;

        TArray<int32> Adjacent;

        // Up
        if (CellIndex - Width >= 0)
            Adjacent.Add(CellIndex - Width);

        // Down
        if (CellIndex + Width < Width * Height)
            Adjacent.Add(CellIndex + Width);

        // Right
        if ((CellIndex + 1) % Width != 0)
            Adjacent.Add(CellIndex + 1);

        // Left
        if (CellIndex % Width != 0)
            Adjacent.Add(CellIndex - 1);

        for (int32 Neighbor : Adjacent)
        {
            if (!Board[Neighbor].bVisited) continue;

            int32 NeighborZLevel = CellZLevel[Neighbor];

            if (FMath::Abs(NeighborZLevel - Value) > 1)
            {
                bValid = false;
                break;
            }
        }

        if (bValid)
            Out.Add(Value);
    }

    return Out;
}

/*
=====================================================
                MAZE GENERATOR
=====================================================
*/
void ADungeonGenerator::MazeGenerator()
{
    Board.SetNum(Width * Height);
    CellZLevel.Init(0, Width * Height); // domyślnie wszystkie = 0

    for (int32 i = 0; i < Board.Num(); ++i)
    {
        Board[i].bVisited = false;
        Board[i].Status.Init(false, 4);
    }

    int32 CurrentCell = 0;
    TArray<int32> Path;

    int32 Iterations = 0;
    const int32 MaxIterations = Width * Height * 10;

    while (Iterations++ < MaxIterations)
    {
        if (!Board.IsValidIndex(CurrentCell)) break;

        Board[CurrentCell].bVisited = true;

        if (CurrentCell == Board.Num() - 1)
            break;

        TArray<int32> Neighbors = CheckNeighbors(CurrentCell);

        if (Neighbors.Num() == 0)
        {
            if (Path.Num() == 0) break;
            CurrentCell = Path.Pop();
        }
        else
        {
            Path.Push(CurrentCell);

            int32 NewCell = Neighbors[FMath::RandRange(0, Neighbors.Num() - 1)];

            // ---------------------------------------
            // Otwieranie drzwi symetryczne
            // ---------------------------------------
            if (NewCell == CurrentCell + 1)
            {
                Board[CurrentCell].Status[2] = true;
                Board[NewCell].Status[3] = true;
            }
            else if (NewCell == CurrentCell - 1)
            {
                Board[CurrentCell].Status[3] = true;
                Board[NewCell].Status[2] = true;
            }
            else if (NewCell == CurrentCell + Width)
            {
                Board[CurrentCell].Status[1] = true;
                Board[NewCell].Status[0] = true;
            }
            else if (NewCell == CurrentCell - Width)
            {
                Board[CurrentCell].Status[0] = true;
                Board[NewCell].Status[1] = true;
            }

            // ---------------------------------------
            // GENEROWANIE ZLEVEL DLA NEWCELL
            // ---------------------------------------

            int32 CurrentZ = CellZLevel[CurrentCell];

            TArray<int32> Possible;
            Possible.Add(CurrentZ - 1);
            Possible.Add(CurrentZ);
            Possible.Add(CurrentZ + 1);

            Possible = FilterZValuesForCell(NewCell, Possible);

            if (Possible.Num() > 0)
            {
                CellZLevel[NewCell] = Possible[FMath::RandRange(0, Possible.Num() - 1)];
            }
            else
            {
                CellZLevel[NewCell] = CurrentZ; // fallback
            }

            CurrentCell = NewCell;
        }
    }

    GenerateDungeon();
}

/*
=====================================================
           SPRAWDZANIE SĄSIADÓW W LABIRYNCIE
=====================================================
*/
TArray<int32> ADungeonGenerator::CheckNeighbors(int32 CellIndex) const
{
    TArray<int32> Neighbors;

    const int32 Total = Board.Num();
    if (!Board.IsValidIndex(CellIndex)) return Neighbors;

    if (CellIndex - Width >= 0 && !Board[CellIndex - Width].bVisited)
        Neighbors.Add(CellIndex - Width);

    if (CellIndex + Width < Total && !Board[CellIndex + Width].bVisited)
        Neighbors.Add(CellIndex + Width);

    if ((CellIndex + 1) % Width != 0 && !Board[CellIndex + 1].bVisited)
        Neighbors.Add(CellIndex + 1);

    if (CellIndex % Width != 0 && !Board[CellIndex - 1].bVisited)
        Neighbors.Add(CellIndex - 1);

    return Neighbors;
}

/*
=====================================================
        WYBÓR PRZYPADKOWEGO POKOJU WG WAG
=====================================================
*/
TSubclassOf<ARoomActor> ADungeonGenerator::GetRandomWeightedRoom() const
{
    float TotalWeight = 0.f;
    for (const auto& Entry : WeightedRooms)
        TotalWeight += Entry.Weight;

    float RandomValue = FMath::RandRange(0.f, TotalWeight);
    float Accumulated = 0.f;

    for (const auto& Entry : WeightedRooms)
    {
        Accumulated += Entry.Weight;
        if (RandomValue <= Accumulated)
            return Entry.RoomClass;
    }

    return nullptr;
}

/*
=====================================================
            POKOJE STARTOWE / KOŃCOWE / LOSOWE
=====================================================
*/
TSubclassOf<ARoomActor> ADungeonGenerator::GetForcedOrRandomRoom(int32 Index) const
{
    int32 TotalCells = Width * Height;

    if (Index < NumForcedStartRooms && StartRooms.Num() > 0)
    {
        int32 ForcedIndex = FMath::Clamp(Index, 0, StartRooms.Num() - 1);
        return StartRooms[ForcedIndex];
    }

    int32 EndStartIndex = TotalCells - NumForcedEndRooms;
    if (Index >= EndStartIndex && EndRooms.Num() > 0)
    {
        int32 EndIndex = Index - EndStartIndex;
        EndIndex = FMath::Clamp(EndIndex, 0, EndRooms.Num() - 1);
        return EndRooms[EndIndex];
    }

    return GetRandomWeightedRoom();
}

/*
=====================================================
                GENEROWANIE DUNGEONU W ŚWIECIE
=====================================================
*/
void ADungeonGenerator::GenerateDungeon()
{
    UWorld* World = GetWorld();
    if (!World) return;
    if (WeightedRooms.Num() == 0) return;

    for (int32 x = 0; x < Width; x++)
    {
        for (int32 y = 0; y < Height; y++)
        {
            int32 Index = x + y * Width;
            if (!Board.IsValidIndex(Index)) continue;

            if (Board[Index].bVisited)
            {
                // rzeczywisty Z na podstawie poziomu ZLevel
                float ZLevel = CellZLevel[Index] * lowerBound;

                FVector Location(x * RoomOffset.X, y * RoomOffset.Y, ZLevel);
                FRotator Rot = FRotator::ZeroRotator;
                TSubclassOf<ARoomActor> RoomClass = GetForcedOrRandomRoom(Index);
                if (!RoomClass) continue;

                FActorSpawnParameters SpawnParams;
                ARoomActor* NewRoom = World->SpawnActor<ARoomActor>(RoomClass, Location, Rot, SpawnParams);

                if (NewRoom)
                {
                    //NewRoom->SetActorLabel(FString::Printf(TEXT("%d-%d"), x, y));

                    // Przygotuj ZDiff PRZED wywołaniem UpdateDoors
                    // Przygotuj ZDiff PRZED wywołaniem UpdateDoors
                    TArray<int32> ZDiff;
                    ZDiff.Init(0, 4);

                    // Obliczamy różnicę w RZECZYWISTYCH Z (world Z = level * lowerBound)
                    float CurrentWorldZ = CellZLevel[Index] * lowerBound;

                    // UP = index - Width
                    if (Index - Width >= 0)
                    {
                        float NeighborWorldZ = CellZLevel[Index - Width] * lowerBound;
                        ZDiff[0] = FMath::RoundToInt(NeighborWorldZ - CurrentWorldZ); // <0 => sąsiad niżej
                    }

                    // DOWN = index + Width
                    if (Index + Width < Width * Height)
                    {
                        float NeighborWorldZ = CellZLevel[Index + Width] * lowerBound;
                        ZDiff[1] = FMath::RoundToInt(NeighborWorldZ - CurrentWorldZ);
                    }

                    // RIGHT = index + 1
                    if ((Index + 1) % Width != 0)
                    {
                        float NeighborWorldZ = CellZLevel[Index + 1] * lowerBound;
                        ZDiff[2] = FMath::RoundToInt(NeighborWorldZ - CurrentWorldZ);
                    }

                    // LEFT = index - 1
                    if (Index % Width != 0)
                    {
                        float NeighborWorldZ = CellZLevel[Index - 1] * lowerBound;
                        ZDiff[3] = FMath::RoundToInt(NeighborWorldZ - CurrentWorldZ);
                    }

                    // Przypisz ZDiff zanim zaktualizujesz drzwi/platformy
                    NewRoom->NeighborZDiff = ZDiff;


                    // Teraz przekaż status drzwi — UpdateDoors użyje już poprawnego NeighborZDiff
                    TArray<bool> StatusCopy = Board[Index].Status;
                    if (StatusCopy.Num() != 4)
                        StatusCopy.Init(false, 4);

                    NewRoom->UpdateDoors(StatusCopy);
                }
            }
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Dungeon generated."));
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSys)
    {
        NavSys->Build();
    }
    UE_LOG(LogTemp, Warning, TEXT("Navigation mesh rebuit."));
}

