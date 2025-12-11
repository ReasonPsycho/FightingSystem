

#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffSpeed.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIGHTINGSYSTEM_API UBuffSpeed : public UBuffEffect
{
	GENERATED_BODY()

public:
	UBuffSpeed();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float SpeedMultiplier = 1.5f;

	
	virtual void Apply_Implementation(AActor* Target) override;
};
