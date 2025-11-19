// DungeonGenerator.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

UCLASS()
class FIGHTINGSYSTEM_API ADungeonGenerator : public AActor
{
    GENERATED_BODY()

public:
    ADungeonGenerator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Width = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Height = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector RoomOffset = FVector(400, 400, 0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<AActor>> RoomPrefabs;

protected:
    virtual void BeginPlay() override;

private:
    struct FCell
    {
        bool bVisited = false;
        bool Status[4] = { false, false, false, false }; // Up, Down, Right, Left
    };

    TArray<FCell> Board;

    void MazeGenerator();
    void GenerateDungeon();
    TArray<int32> CheckNeighbors(int32 CellIndex) const;
};
