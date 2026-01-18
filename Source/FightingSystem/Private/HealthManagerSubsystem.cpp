#include "HealthManagerSubsystem.h"
#include "HealthComponent.h"

void UHealthManagerSubsystem::RegisterComponent(UHealthComponent* component)
{
    if (component)
    {
        UE_LOG(LogTemp, Warning, TEXT("[%s] HealthComponent was registered ain HealthComponentManager."), *component->GetOwner()->GetName());
        ActiveHealthComponents.AddUnique(component);
    }
}

void UHealthManagerSubsystem::UnregisterComponent(UHealthComponent* component)
{
    if (component)
    {
        UE_LOG(LogTemp, Warning, TEXT("[%s] HealthComponent was deregistered in HealthComponentManager."), *component->GetOwner()->GetName());
        ActiveHealthComponents.Remove(component);
    }
}

void UHealthManagerSubsystem::ReportDeath(UHealthComponent* component) {
    if (component && 
        ActiveHealthComponents.Contains(component) && 
        component->GetOwner()) {

        UnregisterComponent(component);

        if (OnActorDied.IsBound()) {
            OnActorDied.Broadcast(component->GetOwner()->GetActorLocation());
        }
    }
}