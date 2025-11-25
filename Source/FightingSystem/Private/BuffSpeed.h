

#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGSYSTEM_API UBuffSpeed : public UBuffEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float SpeedMultiplier = 1.5f;

	UBuffSpeed();
	
	virtual void Apply_Implementation(AActor* Target) override;
};
