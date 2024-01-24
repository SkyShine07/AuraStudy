// copyright  D.H.B


#include "charactor/AuraCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
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

void AAuraCharacterBase::Die()
{
	SetLifeSpan(3);
	
	Weapon->K2_DetachFromComponent();
	MultCastDie();
	
}


void AAuraCharacterBase::MultCastDie_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//TODO:溶解
	Disslove();
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


