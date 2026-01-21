#include "HealthComponent.h"

#include <algorithm>

#include "HealthManagerSubsystem.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* world = GetWorld()) {
		if (UHealthManagerSubsystem* manager = world->GetSubsystem<UHealthManagerSubsystem>())
		{
			manager->RegisterComponent(this);
		}
	}
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::set_health(float health)
{
	health_ = health;
	if (health_ <= 0.0f) {
		if (OnDeath.IsBound()) {
			OnDeath.Broadcast();
		}
	}
}

void UHealthComponent::max_health(float health)
{
	max_health_ = health;
}

void UHealthComponent::DamageFlat(float damage_amount)
{
	check(damage_amount > 0.0f);
	set_health(std::clamp(health() - damage_amount, -1.0f, health()));
	UE_LOG(LogTemp, Warning, TEXT("%f amount of damage taken"), damage_amount);
}

void UHealthComponent::DamageFullHealthPercentage(float percentage)
{
	check(percentage > 0.0f);
	set_health(std::clamp(max_health() * percentage, -1.0f, health()));
}

void UHealthComponent::DamageCurrentHealthPercentage(float percentage)
{
	check(percentage > 0.0f);
	set_health(std::clamp(health() * percentage, -1.0f, health()));
}

void UHealthComponent::HealFlat(float heal_amount)
{
	check(heal_amount > 0.0f);
	set_health(std::clamp(health() + heal_amount, health(), max_health()));
}

void UHealthComponent::HealFullHealthPercentage(float percentage)
{
	check(percentage > 0.0f);
	set_health(std::clamp(max_health() * percentage, health(), max_health()));
}

void UHealthComponent::HealMissingHealthPercentage(float percentage)
{
	check(percentage > 0.0f);
	set_health(std::clamp(health() + (max_health() - health()) * percentage, health(), max_health()));
}

void UHealthComponent::Die() {
	if (!ShouldDie()) {
		return;
	}

	if (UWorld* world = GetWorld()) {
		if (UHealthManagerSubsystem* manager = world->GetSubsystem<UHealthManagerSubsystem>())
		{
			manager->ReportDeath(this);
		}
	}
}
