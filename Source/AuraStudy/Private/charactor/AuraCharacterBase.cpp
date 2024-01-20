// copyright  D.H.B


#include "charactor/AuraCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


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


void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAttributesByGE()
{
	if(!IsValid(ASC)||!IsValid(GE_DefaultPrimaryAttribute)||!IsValid(GE_DefaultSencondaryAttribute)) return;
	
	FGameplayEffectContextHandle ContextHandle=ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	//----初始化基础属性，派生属性
	 FGameplayEffectSpecHandle PrimarySpecHandle = ASC->MakeOutgoingSpec(GE_DefaultPrimaryAttribute,1,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data);

	FGameplayEffectSpecHandle SecendarySpecHandle = ASC->MakeOutgoingSpec(GE_DefaultSencondaryAttribute,1,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SecendarySpecHandle.Data);

	FGameplayEffectSpecHandle VitalSpecHandle = ASC->MakeOutgoingSpec(GE_DefaultVitalAttribute,1,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*VitalSpecHandle.Data);
	
}


