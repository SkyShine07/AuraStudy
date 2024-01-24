#include "AuraAbilitySystemGlobals.h"

#include "AuraEffectContext/AuraEffectContext.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraEffectContext();
}
