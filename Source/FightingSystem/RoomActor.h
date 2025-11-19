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

    // Drzwi w kolejnoœci: 0-Up, 1-Down, 2-Right, 3-Left
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<AActor*> Doors;

    // Œciany w tej samej kolejnoœci
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<AActor*> Walls;

    // Ustawia drzwi w zale¿noœci od po³¹czeñ
    UFUNCTION(BlueprintCallable)
    void UpdateDoors(const TArray<bool>& Status);
};
