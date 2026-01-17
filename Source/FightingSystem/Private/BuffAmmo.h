#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffAmmo.generated.h"

UCLASS(Blueprintable)
class FIGHTINGSYSTEM_API UBuffAmmo : public UBuffEffect
{
	GENERATED_BODY()

public:
	UBuffAmmo();
	virtual void Apply_Implementation(AActor* Target) override;

};
