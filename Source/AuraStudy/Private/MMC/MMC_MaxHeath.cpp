// copyright  D.H.B


#include "MMC/MMC_MaxHeath.h"

#include "Interface/CombatInterface.h"
#include "player/AbilitySystem/AuraAttributeSet.h"



UMMC_MaxHeath::UMMC_MaxHeath()
{
	vigorDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	vigorDef.AttributeToCapture=UAuraAttributeSet::GetvigorAttribute();
	RelevantAttributesToCapture.Add(vigorDef);
	
}

float UMMC_MaxHeath::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//获得捕获的vigor属性值
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	
	AggregatorEvaluateParameters.SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	AggregatorEvaluateParameters.TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	
	float vigor;	
	GetCapturedAttributeMagnitude(vigorDef,Spec,AggregatorEvaluateParameters,vigor);
	vigor=FMath::Max(vigor,0.f);

	int32 level=1;
	if (Spec.GetContext().GetSourceObject())
	{
		ICombatInterface* Soure=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
		level=Soure->GetLevel();
	}
	
	float Result=80+vigor*2.5+level*10;
	
	return Result;
}
