#include "BuffHealthRegeneration.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

UBuffHealthRegeneration::UBuffHealthRegeneration()
{
	Name = FText::FromString("Health Regeneration");
	Description = FText::FromString("Regenerates a certain amount of health.");
}

void UBuffHealthRegeneration::Apply_Implementation(AActor* Target)
{
    if (!Target) return;

    
}
