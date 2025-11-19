#include "RoomActor.h"

ARoomActor::ARoomActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARoomActor::UpdateDoors(const TArray<bool>& Status)
{
    for (int i = 0; i < 4; i++)
    {
        bool bOpen = Status.IsValidIndex(i) ? Status[i] : false;

        if (Doors.IsValidIndex(i) && Walls.IsValidIndex(i))
        {
            Doors[i]->SetActorHiddenInGame(!bOpen);
            Doors[i]->SetActorEnableCollision(bOpen);

            Walls[i]->SetActorHiddenInGame(bOpen);
            Walls[i]->SetActorEnableCollision(!bOpen);
        }
    }
}
