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
	if (Target)
	{
		UHealthComponent* HealthComp = Target->FindComponentByClass<UHealthComponent>();

		if (HealthComp)
		{
			
			HealthComp->HealFullHealthPercentage(HealAmount);

			UE_LOG(LogTemp, Warning, TEXT("Uleczono gracza o: %f"), HealAmount);
		}
	}
}
