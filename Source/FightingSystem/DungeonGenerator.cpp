// DungeonGenerator.cpp
#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "RoomActor.h"
#include "Kismet/KismetMathLibrary.h"

ADungeonGenerator::ADungeonGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADungeonGenerator::BeginPlay()
{
    Super::BeginPlay();
    MazeGenerator();
}

void ADungeonGenerator::MazeGenerator()
{
    // Upewniamy siê, ¿e plansza ma odpowiedni rozmiar i ka¿da komórka jest zainicjalizowana
    Board.SetNum(Width * Height);
    for (int32 i = 0; i < Board.Num(); ++i)
    {
        Board[i].bVisited = false;
        Board[i].Status.Init(false, 4); // 4 kierunki: Up, Down, Right, Left
    }

    int32 CurrentCell = 0;
    TArray<int32> Path;

    int32 Iterations = 0;
    const int32 MaxIterations = Width * Height * 10; // limit bezpieczeñstwa
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

            // Symetryczne otwieranie drzwi w obu pokojach
            if (NewCell == CurrentCell + 1) // Right
            {
                Board[CurrentCell].Status[2] = true; // Right
                Board[NewCell].Status[3] = true;     // Left
            }
            else if (NewCell == CurrentCell - 1) // Left
            {
                Board[CurrentCell].Status[3] = true; // Left
                Board[NewCell].Status[2] = true;     // Right
            }
            else if (NewCell == CurrentCell + Width) // Down
            {
                Board[CurrentCell].Status[1] = true; // Down
                Board[NewCell].Status[0] = true;     // Up
            }
            else if (NewCell == CurrentCell - Width) // Up
            {
                Board[CurrentCell].Status[0] = true; // Up
                Board[NewCell].Status[1] = true;     // Down
            }

            CurrentCell = NewCell;
        }
    }

    GenerateDungeon();
}


TArray<int32> ADungeonGenerator::CheckNeighbors(int32 CellIndex) const
{
    TArray<int32> Neighbors;

    const int32 Total = Board.Num();
    if (!Board.IsValidIndex(CellIndex)) return Neighbors;

    // Up
    if (CellIndex - Width >= 0 && !Board[CellIndex - Width].bVisited)
        Neighbors.Add(CellIndex - Width);

    // Down
    if (CellIndex + Width < Total && !Board[CellIndex + Width].bVisited)
        Neighbors.Add(CellIndex + Width);

    // Right
    if ((CellIndex + 1) % Width != 0 && !Board[CellIndex + 1].bVisited)
        Neighbors.Add(CellIndex + 1);

    // Left
    if (CellIndex % Width != 0 && !Board[CellIndex - 1].bVisited)
        Neighbors.Add(CellIndex - 1);

    return Neighbors;
}

void ADungeonGenerator::GenerateDungeon()
{
    UWorld* World = GetWorld();
    if (!World) return;
    if (RoomPrefabs.Num() == 0) return;

    for (int32 x = 0; x < Width; x++)
    {
        for (int32 y = 0; y < Height; y++)
        {
            int32 Index = x + y * Width;
            if (!Board.IsValidIndex(Index)) continue;

            if (Board[Index].bVisited)
            {
                int32 RoomIndex = FMath::RandRange(0, RoomPrefabs.Num() - 1);
                FVector Location(x * RoomOffset.X, y * RoomOffset.Y, 0.f);
                FRotator Rot = FRotator::ZeroRotator;

                TSubclassOf<ARoomActor> RoomClass = RoomPrefabs[RoomIndex];
                if (!RoomClass) continue;

                FActorSpawnParameters SpawnParams;
                ARoomActor* NewRoom = World->SpawnActor<ARoomActor>(RoomClass, Location, Rot, SpawnParams);

                if (NewRoom)
                {
                    NewRoom->SetActorLabel(FString::Printf(TEXT("%d-%d"), x, y));

                    // Upewniamy siê, ¿e Status ma 4 elementy
                    TArray<bool> StatusCopy = Board[Index].Status;
                    if (StatusCopy.Num() != 4)
                        StatusCopy.Init(false, 4);

                    // Wywo³anie UpdateDoors po przypisaniu drzwi i œcian
                    NewRoom->UpdateDoors(StatusCopy);
                }

            }
        }
    }
}
