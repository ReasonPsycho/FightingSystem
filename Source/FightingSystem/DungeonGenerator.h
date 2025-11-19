#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
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

    // Ka¿dy prefab MUSI byæ pochodn¹ ARoomActor
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<ARoomActor>> RoomPrefabs;

protected:
    virtual void BeginPlay() override;

private:

    struct FCell
    {
        bool bVisited = false;

        // Up, Down, Right, Left
        TArray<bool> Status = { false, false, false, false };
    };

    TArray<FCell> Board;

    void MazeGenerator();
    void GenerateDungeon();
    TArray<int32> CheckNeighbors(int32 CellIndex) const;
};
