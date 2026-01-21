#include "BuffArmor.h"
#include "Engine/Engine.h"


UBuffArmor::UBuffArmor()
{
	Name = FText::FromString("Armor Buff");
	Description = FText::FromString("Increases Armor by a multiplier.");
}

void UBuffArmor::Apply_Implementation(AActor* Target)
{
}
