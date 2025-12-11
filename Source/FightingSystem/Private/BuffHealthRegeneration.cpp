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

    TArray<UActorComponent*> Components;
    Target->GetComponents(UActorComponent::StaticClass(), Components);

    for (UActorComponent* Comp : Components)
    {
        if (Comp && Comp->GetName().Contains("Damagable"))
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Got the Damagable component")));

            FName FuncName = TEXT("AddHP_Event");
            UFunction* Func = Comp->FindFunction(FuncName);
            if (Func)
            {
                struct FAddHealthParams
                {
                    float Amount;
                };
                FAddHealthParams Params;
                Params.Amount = HealAmount;
                Comp->ProcessEvent(Func, &Params);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health buff AddHP_Event")));
				
            }
        }
    }
}
