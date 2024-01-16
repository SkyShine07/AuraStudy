// copyright  D.H.B


#include "charactor/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//添加武器
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weapon"));
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}


void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


