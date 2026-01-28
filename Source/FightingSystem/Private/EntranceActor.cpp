#include "EntranceActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

AEntranceActor::AEntranceActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Tworzymy trigger box
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetBoxExtent(FVector(200.f, 200.f, 200.f));
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Event
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEntranceActor::OnOverlapBegin);

    // Tutaj ustawiasz domyœlny level
    LevelName = "TestLevel";
}


void AEntranceActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEntranceActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor) return;

	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn) return;

	if (LevelName.IsNone()) return;

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
