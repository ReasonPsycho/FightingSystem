#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaterVisibilityController.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTINGSYSTEM_API UWaterVisibilityController : public UActorComponent
{
	GENERATED_BODY()

public:
	UWaterVisibilityController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	UPROPERTY(EditAnywhere, Category = "Water")
	FName WaterTag = "Water";

	// Referencje do obiektów wody na scenie
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Water")
	TArray<AActor*> WaterActors;

	// Offset wysokoœci (¿eby nie migota³o)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Water")
	float ZOffset = 0.0f;
	// Odleg³oœæ aktywacji wody (w cm)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Water")
	float ActivationDistance = 2000.0f;


private:
	APawn* PlayerPawn;
};
