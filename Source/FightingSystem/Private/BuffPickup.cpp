#include "BuffPickup.h"
#include "Components/SphereComponent.h"
#include "BuffTrackerComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h" // DODAJ TÊ LINIÊ

ABuffPickup::ABuffPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(80.f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAll"));
    RootComponent = CollisionSphere;

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABuffPickup::OnOverlapBegin);

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    PickupMesh->SetupAttachment(RootComponent);
    // You might want to disable collision on this mesh as the sphere handles pickup
    //PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CurrentBuff = nullptr;

}

void ABuffPickup::BeginPlay()
{
    if (AvailableBuffs.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, AvailableBuffs.Num() - 1);

        if (AvailableBuffs[Index])
        {
            CurrentBuff = NewObject<UBuffEffect>(this, AvailableBuffs[Index]);
        }

        if (CurrentBuff && CurrentBuff->PickupMesh && PickupMesh)
        {
            PickupMesh->SetStaticMesh(CurrentBuff->PickupMesh);
        }
    }

    if (CurrentBuff && GEngine)
    {
        FString BuffName = CurrentBuff->Name.ToString();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Buff: %s"), *BuffName));
    }

	
}

void ABuffPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (Character && CurrentBuff && Character->IsPlayerControlled())
    {
		UBuffTrackerComponent* Tracker = OtherActor->FindComponentByClass<UBuffTrackerComponent>();

		if (Tracker)
		{
			Tracker->ApplyBuff(CurrentBuff);
		}
        else
        {
            CurrentBuff->Apply_Implementation(OtherActor);
        }

        Destroy();
    }
}

// Called every frame
void ABuffPickup::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

}


