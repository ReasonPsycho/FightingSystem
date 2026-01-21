#include "BuffPickup.h"
#include "Components/SphereComponent.h"
#include "BuffTrackerComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"

ABuffPickup::ABuffPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(80.f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAll"));
    RootComponent = CollisionSphere;

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABuffPickup::OnOverlapBegin);

    //PickupMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PickupMesh"));
    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));

    PickupMesh->SetupAttachment(RootComponent);
    // You might want to disable collision on this mesh as the sphere handles pickup
    PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABuffPickup::BeginPlay()
{
    Super::BeginPlay();
    if (AvailableBuffs.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, AvailableBuffs.Num() - 1);

        CurrentBuffClass = AvailableBuffs[Index];

        const UBuffEffect* DefaultBuff = CurrentBuffClass.GetDefaultObject();

        if (DefaultBuff && PickupMesh)
        {
            PickupMesh->SetStaticMesh(DefaultBuff->PickupMesh);

            /*PickupMesh->SetSkeletalMesh(DefaultBuff->PickupSkeletalMesh);

            if (DefaultBuff->IdleAnimation)
            {
                PickupMesh->PlayAnimation(DefaultBuff->IdleAnimation, true);
            }*/

            if (GEngine)
            {
                FString BuffName = DefaultBuff->Name.ToString();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Buff: %s"), *BuffName));
            }
        }
        if (!PickupMesh)
        {
            UE_LOG(LogTemp, Error, TEXT("PickupMesh is null in BeginPlay for %s!"), *GetName());
            return;
        }
    }	
}

void ABuffPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (Character && CurrentBuffClass && Character->IsPlayerControlled())
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("bububububffff"));
        }

		UBuffTrackerComponent* Tracker = OtherActor->FindComponentByClass<UBuffTrackerComponent>();

		if (Tracker)
		{
            Tracker->ApplyBuff(CurrentBuffClass);
		}
        else
        {
            UBuffEffect* TempBuff = NewObject<UBuffEffect>(OtherActor, CurrentBuffClass);
            if (TempBuff)
            {
                TempBuff->Apply_Implementation(OtherActor);
            }
        }

        SetActorEnableCollision(false);
        Destroy();        
    }
}

// Called every frame
void ABuffPickup::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

}


