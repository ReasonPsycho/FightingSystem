#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffHealthRegeneration.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGSYSTEM_API UBuffHealthRegeneration : public UBuffEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float HealAmount = 20.f;

	UBuffHealthRegeneration();
	virtual void Apply_Implementation(AActor* Target) override;
};
