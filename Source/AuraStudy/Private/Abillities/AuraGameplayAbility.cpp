// copyright  D.H.B


#include "player/AbilitySystem/Abillities/AuraGameplayAbility.h"

#include "Kismet/KismetSystemLibrary.h"


UGameplayEffect* UAuraGameplayAbility::GetCooldownGameplayEffect() const
{
	UGameplayEffect* GE_CoolDown=NewObject<UGameplayEffect>(GetTransientPackage());
	GE_CoolDown->DurationPolicy=EGameplayEffectDurationType::HasDuration;
	GE_CoolDown->DurationMagnitude=CoolDown;

	UKismetSystemLibrary::PrintString(this,
		FString::Printf(TEXT("GE_CoolDown DurationMagnitude: %s"), *GE_CoolDown->DurationMagnitude.GetValueForEditorDisplay().ToString()));
	return GE_CoolDown;
}

UGameplayEffect* UAuraGameplayAbility::GetCostGameplayEffect() const
{
	UGameplayEffect* GE_Cost=NewObject<UGameplayEffect>(GetTransientPackage());
	GE_Cost->DurationPolicy=EGameplayEffectDurationType::Instant;

	for (const auto Cost : costs)
	{
		FGameplayModifierInfo ModifierInfo;
		ModifierInfo.ModifierOp= EGameplayModOp::Additive;
		ModifierInfo.Attribute=Cost.Key;
		ModifierInfo.ModifierMagnitude=Cost.Value;
		GE_Cost->Modifiers.Add(ModifierInfo);

	}
	UKismetSystemLibrary::PrintString(this,
		FString::Printf(TEXT("GE_Cost MOdfiers: %d"),GE_Cost->Modifiers.Num()));
	return GE_Cost;
}
