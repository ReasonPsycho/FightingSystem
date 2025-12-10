#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"

UCLASS()
class FIGHTINGSYSTEM_API ARoomActor : public AActor
{
    GENERATED_BODY()

public:
    ARoomActor();

    // Komponenty drzwi
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorUp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorUp_LowerPlatform;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorDown;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorDown_LowerPlatform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorRight;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorRight_LowerPlatform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorLeft;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* DoorLeft_LowerPlatform;

    // Komponenty œcian
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallUp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallDown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallRight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallLeft;

    // Tablica drzwi: Up, Down, Right, Left
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    TArray<UStaticMeshComponent*> Doors;

    UFUNCTION(BlueprintCallable)
    void UpdateDoors(const TArray<bool>& Status);

    void FindDoorByName();
    void FindWallByName();
    void FindPlatformByName();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
};
