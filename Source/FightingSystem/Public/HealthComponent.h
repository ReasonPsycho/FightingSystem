#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTINGSYSTEM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "HealthComponent")
	float health() const { return health_; };

	UFUNCTION(BlueprintPure, Category = "HealthComponent")
	float max_health() const { return max_health_; };

	UFUNCTION(BlueprintPure, Category = "HealthComponent")
	float GetCurrentHealthPercentage() const { return health_ / max_health_; }

	UFUNCTION(BlueprintPure, Category = "HealthComponent")
	bool ShouldDie() const { return health_ <= 0.0f; }

	UFUNCTION(BlueprintPure, Category = "HealthComponent")
	bool Dying() const { return dying_; }

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void SetDying(bool value) { dying_ = value; }

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void DamageFlat(float damage_amount);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void DamageFullHealthPercentage(float percentage);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void DamageCurrentHealthPercentage(float percentage);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void HealFlat(float heal_amount);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void HealFullHealthPercentage(float percentage);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void HealMissingHealthPercentage(float percentage);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void Die();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void set_health(float health);

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void set_max_health(float health);

	float health_ = 1.0f;
	float max_health_ = 1.0f;
	bool dying_ = false;

protected:
	virtual void BeginPlay() override;
};
