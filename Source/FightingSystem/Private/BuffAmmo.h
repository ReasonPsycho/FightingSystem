#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffAmmo.generated.h"

UCLASS(Blueprintable)
class FIGHTINGSYSTEM_API UBuffAmmo : public UBuffEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	int add_ammo_amount = 30;
	UBuffAmmo();
	virtual void Apply_Implementation(AActor* Target) override;

};
