// copyright  D.H.B


#include "charactor/AuraCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//添加武器
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weapon"));
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return  ASC;
}


FVector AAuraCharacterBase::GetProjectileLocation()
{
	if (IsValid(Weapon))
	{
		return  Weapon->GetSocketLocation(WeaponProjectileSocket);
	}
	return FVector::Zero();
}



void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAttributesByGE()
{
	AAuraGameModeBase* GM=Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->InitCharactorAttribute(GetAbilitySystemComponent(),CharactorType,GetLevel());
	}
	
}


