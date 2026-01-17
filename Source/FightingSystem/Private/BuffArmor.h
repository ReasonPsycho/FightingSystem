#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffArmor.generated.h"

UCLASS(Blueprintable)
class FIGHTINGSYSTEM_API UBuffArmor : public UBuffEffect
{
	GENERATED_BODY()

public:
	UBuffArmor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float armor_increase = 50.0f;

	virtual void Apply_Implementation(AActor* Target) override;
};