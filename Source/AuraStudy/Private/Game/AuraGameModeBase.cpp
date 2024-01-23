// copyright  D.H.B


#include "Game/AuraGameModeBase.h"

#include "AbilitySystemComponent.h"

void AAuraGameModeBase::InitCharactorAttribute(UAbilitySystemComponent*ASC,ECharactorType& Type, int32 Level)
{
	if (!CharactorClassInfo) return ;
	
	TSubclassOf<UGameplayEffect> GE=CharactorClassInfo->FindCharactorInfo(Type).PrimarryAttributes;
	FGameplayEffectContextHandle ContextHandle= ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(ASC->GetAvatarActor());
	
	FGameplayEffectSpecHandle PrimarryGEHandle=ASC->MakeOutgoingSpec(GE,Level,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarryGEHandle.Data);
	
	FGameplayEffectSpecHandle SencondaryGEHandle=ASC->MakeOutgoingSpec(CharactorClassInfo->SencondaryAttributes,Level,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SencondaryGEHandle.Data);

	FGameplayEffectSpecHandle vitalGEHandle=ASC->MakeOutgoingSpec(CharactorClassInfo->vitalAttributes,Level,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*vitalGEHandle.Data);
}
