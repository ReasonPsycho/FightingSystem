#include "BuffAmmo.h"
#include "Engine/Engine.h"


UBuffAmmo::UBuffAmmo()
{
	Name = FText::FromString("Ammo Buff");
	Description = FText::FromString("Increases Ammo by a multiplier.");
}

void UBuffAmmo::Apply_Implementation(AActor* Target)
{
}
