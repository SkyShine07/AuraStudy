// copyright  D.H.B


#include "Actor/AuraProjectile.h"
#include	"Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


AAuraProjectile::AAuraProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	bReplicates=true;
	
}


void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}






