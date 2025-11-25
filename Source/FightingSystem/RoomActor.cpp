#include "RoomActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ARoomActor::ARoomActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Root tylko raz, komponenty dodasz w BP
    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // Pocz¹tkowo puste
    DoorUp = DoorDown = DoorRight = DoorLeft = nullptr;
    WallUp = WallDown = WallRight = WallLeft = nullptr;
}

void ARoomActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    FindDoorByName();
    FindWallByName();

    // Upewnij siê, ¿e tablica Doors jest w kolejnoœci Up, Down, Right, Left
    Doors.Empty();
    Doors.Add(DoorUp);
    Doors.Add(DoorDown);
    Doors.Add(DoorRight);
    Doors.Add(DoorLeft);
}

void ARoomActor::FindDoorByName()
{
    TArray<UStaticMeshComponent*> Components;
    GetComponents<UStaticMeshComponent>(Components);

    for (UStaticMeshComponent* Comp : Components)
    {
        if (!Comp) continue;

        FString Name = Comp->GetName();

        if (Name.Equals(TEXT("Door2"))) DoorUp = Comp;
        else if (Name.Equals(TEXT("Door1"))) DoorDown = Comp;
        else if (Name.Equals(TEXT("Door4"))) DoorRight = Comp;
        else if (Name.Equals(TEXT("Door3"))) DoorLeft = Comp;

        if (Name.StartsWith(TEXT("Door")))
        {
            Comp->SetVisibility(false, true);
            Comp->SetHiddenInGame(true, true);
            Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

            UE_LOG(LogTemp, Warning, TEXT("Znaleziono i ukryto drzwi: %s"), *Name);
        }
    }
}

void ARoomActor::FindWallByName()
{
    TArray<UStaticMeshComponent*> Components;
    GetComponents<UStaticMeshComponent>(Components);

    for (UStaticMeshComponent* Comp : Components)
    {
        if (!Comp) continue;

        FString Name = Comp->GetName();

        // Przypisanie do zmiennych
        if (Name.Equals(TEXT("Wall2"))) WallUp = Comp;
        else if (Name.Equals(TEXT("Wall1"))) WallDown = Comp;
        else if (Name.Equals(TEXT("Wall4"))) WallRight = Comp;
        else if (Name.Equals(TEXT("Wall3"))) WallLeft = Comp;

        if (Name.StartsWith(TEXT("Wall")))
        {
            // Ustawiamy wszystkie œciany jako niewidoczne i wy³¹czamy kolizjê
            Comp->SetVisibility(false, true);
            Comp->SetHiddenInGame(true, true);
            Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

            UE_LOG(LogTemp, Warning, TEXT("Znaleziono i ukryto œcianê: %s"), *Name);
        }
    }
}


void ARoomActor::UpdateDoors(const TArray<bool>& Status)
{
    if (Status.Num() < 4) return;

    UStaticMeshComponent* DoorComps[4] = { DoorUp, DoorDown, DoorRight, DoorLeft };
    UStaticMeshComponent* WallComps[4] = { WallUp, WallDown, WallRight, WallLeft };

    for (int32 i = 0; i < 4; ++i)
    {
        bool bOpen = Status[i];

        if (DoorComps[i])
        {
            DoorComps[i]->SetVisibility(bOpen, true);
            DoorComps[i]->SetHiddenInGame(!bOpen, true);
            DoorComps[i]->SetCollisionEnabled(bOpen ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
        }

        if (WallComps[i])
        {
            bool bWallVisible = !bOpen;
            WallComps[i]->SetVisibility(bWallVisible, true);
            WallComps[i]->SetHiddenInGame(!bWallVisible, true);
            WallComps[i]->SetCollisionEnabled(bWallVisible ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
        }
    }
}
