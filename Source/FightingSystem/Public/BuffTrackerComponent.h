

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <BuffPickup.h>
#include "BuffTrackerComponent.generated.h"

USTRUCT(BlueprintType)
struct FActiveBuffData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBuffEffect* BuffEffect = nullptr;

	UPROPERTY()
	float Duration = 0.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTINGSYSTEM_API UBuffTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffTrackerComponent();

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void HandleGlobalDeath(FVector DeathLocation);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Buffs")
	TSubclassOf<class ABuffPickup> _buffClass;

	void SpawnDelayedPickup(FVector SpawnLocation);


	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void ApplyBuff(TSubclassOf<UBuffEffect> BuffClass);

	UPROPERTY()
	TArray<struct FActiveBuffData> ActiveBuffs;

		
	
};
