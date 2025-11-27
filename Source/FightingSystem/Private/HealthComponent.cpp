#include "HealthComponent.h"
#include <algorithm>

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::set_health(float health)
{
	health_ = health;
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
	if (health() < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroyed!"));
		GetOwner()->Destroy();
	}
}

void UHealthComponent::DamageFullHealthPercentage(float percentage)
{
	check(percentage > 0.0f);
	set_health(std::clamp(max_health() * percentage, -1.0f, health()));
	if (health() < 0.0f)
	{
		GetOwner()->Destroy();
	}
}

void UHealthComponent::DamageCurrentHealthPercentage(float percentage)
{
	check(percentage > 0.0f);
	set_health(std::clamp(health() * percentage, -1.0f, health()));
	if (health() < 0.0f)
	{
		GetOwner()->Destroy();
	}
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
