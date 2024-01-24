#pragma once
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

UCLASS()
class UAuraAbilitySystemGlobals:public  UAbilitySystemGlobals
{


	GENERATED_BODY()

public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
