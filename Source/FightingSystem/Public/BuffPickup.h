

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffEffect.h"
#include "BuffPickup.generated.h"

UCLASS()
class FIGHTINGSYSTEM_API ABuffPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuffPickup();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TArray<TSubclassOf<UBuffEffect>> AvailableBuffs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff")
	UBuffEffect* CurrentBuff;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* CollisionSphere;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
