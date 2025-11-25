#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" // <-- potrzebne dla UStaticMeshComponent
#include "RoomActor2.generated.h"

UCLASS()
class FIGHTINGSYSTEM_API ARoomActor2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomActor2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Tutaj deklarujesz zmienn¹, któr¹ powi¹¿esz w Blueprint
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	UStaticMeshComponent* CubeComponent;
};
