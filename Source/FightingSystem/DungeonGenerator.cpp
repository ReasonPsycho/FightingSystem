// DungeonGenerator.cpp
#include "DungeonGenerator.h"
#include "Engine/World.h"

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
    Board.SetNum(Width * Height);

    int32 CurrentCell = 0;
    TArray<int32> Path;

    int32 Iterations = 0;
    while (Iterations++ < 1000)
    {
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

            if (NewCell > CurrentCell)
            {
                // Down or Right
                if (NewCell - 1 == CurrentCell)
                {
                    Board[CurrentCell].Status[2] = true; // Right
                    CurrentCell = NewCell;
                    Board[CurrentCell].Status[3] = true; // Left
                }
                else
                {
                    Board[CurrentCell].Status[1] = true; // Down
                    CurrentCell = NewCell;
                    Board[CurrentCell].Status[0] = true; // Up
                }
            }
            else
            {
                // Up or Left
                if (NewCell + 1 == CurrentCell)
                {
                    Board[CurrentCell].Status[0] = true; // Up
                    CurrentCell = NewCell;
                    Board[CurrentCell].Status[1] = true; // Down
                }
                else
                {
                    Board[CurrentCell].Status[3] = true; // Left
                    CurrentCell = NewCell;
                    Board[CurrentCell].Status[2] = true; // Right
                }
            }
        }
    }

    GenerateDungeon();
}

TArray<int32> ADungeonGenerator::CheckNeighbors(int32 CellIndex) const
{
    TArray<int32> Neighbors;

    // Up
    if (CellIndex - Width >= 0 && !Board[CellIndex - Width].bVisited)
        Neighbors.Add(CellIndex - Width);

    // Down
    if (CellIndex + Width < Board.Num() && !Board[CellIndex + Width].bVisited)
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

    for (int32 i = 0; i < Width; i++)
    {
        for (int32 j = 0; j < Height; j++)
        {
            int32 Index = i + j * Width;
            if (Board[Index].bVisited)
            {
                int32 RoomIndex = FMath::RandRange(0, RoomPrefabs.Num() - 1);
                FVector Location(i * RoomOffset.X, j * RoomOffset.Y, 0);
                AActor* NewRoom = World->SpawnActor<AActor>(RoomPrefabs[RoomIndex], Location, FRotator::ZeroRotator);
                if (NewRoom)
                {
                    NewRoom->SetActorLabel(FString::Printf(TEXT("%d-%d"), i, j));
                    // Tutaj mo¿esz dodaæ funkcjê UpdateRoom(Board[Index].Status) jeœli Room ma w³asny komponent
                }
            }
        }
    }
}
