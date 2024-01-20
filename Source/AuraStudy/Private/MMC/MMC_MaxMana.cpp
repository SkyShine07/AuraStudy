// copyright  D.H.B


#include "MMC/MMC_MaxMana.h"

#include "Interface/CombatInterface.h"
#include "player/AbilitySystem/AuraAttributeSet.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelDef.bSnapshot=false;
	IntelDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	IntelDef.AttributeToCapture=UAuraAttributeSet::GetIntelligenceAttribute();

	RelevantAttributesToCapture.Add(IntelDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();

	float intel;
	GetCapturedAttributeMagnitude(IntelDef,Spec,EvaluateParameters,intel);

	intel=FMath::Max(intel,0.f);

	int32 level=1;
	if (Spec.GetContext().GetSourceObject())
	{
		ICombatInterface* Soure=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
		level=Soure->GetLevel();
	}
	
	float Result=50+intel*2.5+level*15;
	
	return Result;
	
}
