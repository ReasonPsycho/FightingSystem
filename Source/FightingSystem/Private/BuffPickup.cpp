#include "BuffPickup.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

ABuffPickup::ABuffPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(80.f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAll"));
    RootComponent = CollisionSphere;

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABuffPickup::OnOverlapBegin);

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
    if (OtherActor && CurrentBuff)
    {
        CurrentBuff->Apply_Implementation(OtherActor);
        Destroy();
    }
}

// Called every frame
void ABuffPickup::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

}


