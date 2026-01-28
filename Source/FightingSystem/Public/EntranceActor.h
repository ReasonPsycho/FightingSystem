#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"  // <-- dodane
#include "EntranceActor.generated.h"

UCLASS()
class FIGHTINGSYSTEM_API AEntranceActor : public AActor
{
	GENERATED_BODY()

public:
	AEntranceActor();

protected:
	virtual void BeginPlay() override;

public:
	// Trigger Box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* TriggerBox;

	// Nazwa levelu do za³adowania
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TestLevel")
	FName LevelName;

private:
	// Funkcja wywo³ywana po wejœciu w trigger
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
