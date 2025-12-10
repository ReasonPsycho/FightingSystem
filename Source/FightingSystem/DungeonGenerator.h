#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "DungeonGenerator.generated.h"
USTRUCT(BlueprintType)
struct FRoomEntry {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ARoomActor> RoomClass;
    // Szansa/waga pojawienia się pokoju (np. 1–100)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;
};
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
    TArray<FRoomEntry> WeightedRooms;

    // Ile pierwszych pokoi ma być specjalnych
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NumForcedStartRooms = 3;

    // Lista prefabsów dla startowych pokoi
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<ARoomActor>> StartRooms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NumForcedEndRooms = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoomActor>> EndRooms;
    float LastZLevel = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    float lowerBound = -200.f;
    UPROPERTY()
    TArray<float> CellZLevel;



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
    TSubclassOf<ARoomActor> GetRandomWeightedRoom() const;
    TSubclassOf<ARoomActor> GetForcedOrRandomRoom(int32 Index) const;
    TArray<int32> FilterZValuesForCell(int32 CellIndex, const TArray<int32>& Candidates) const;
    float GetNextZLevel();
    void GenerateDungeon();
    TArray<int32> CheckNeighbors(int32 CellIndex) const;
};
