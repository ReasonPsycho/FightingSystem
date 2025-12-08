

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <BuffEffect.h>
#include "BuffTrackerComponent.generated.h"

USTRUCT(BlueprintType)
struct FActiveBuffData
{
	GENERATED_BODY()

public:
	// The actual buff effect object
	UPROPERTY()
	UBuffEffect* BuffEffect = nullptr;

	// The time remaining until the buff expires
	UPROPERTY()
	float TimeRemaining = 0.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTINGSYSTEM_API UBuffTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffTrackerComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void ApplyBuff(UBuffEffect* NewBuff);

	UPROPERTY()
	TArray<struct FActiveBuffData> ActiveBuffs;

		
	
};
