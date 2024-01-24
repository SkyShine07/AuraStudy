// copyright  D.H.B


#include "GE_ExecutionCalculation/GE_ExecutionCalculation_Damage.h"
#include "GameplayEffectAttributeCaptureDefinition.h"
#include "AuraEffectContext/AuraEffectContext.h"
#include "player/AbilitySystem/AuraAttributeSet.h"


struct FDamageCaptureDef
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	
	
	FDamageCaptureDef()
	{
		//---TODO:利用宏定义捕获的属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Strength,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);
		
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
	}

	static FDamageCaptureDef  Get();

protected:
	static  FDamageCaptureDef DamageCaptureDef;
	
};

FDamageCaptureDef FDamageCaptureDef::DamageCaptureDef;
FDamageCaptureDef FDamageCaptureDef::Get()
{
	return FDamageCaptureDef::DamageCaptureDef;
};


UGE_ExecutionCalculation_Damage::UGE_ExecutionCalculation_Damage()
{
	
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().ArmorDef);
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().StrengthDef);
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().BlockChanceDef);
	
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(FDamageCaptureDef::Get().CriticalHitResistanceDef);
	
}

void UGE_ExecutionCalculation_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	 const FGameplayEffectSpec OwningSpec=ExecutionParams.GetOwningSpec();

	UAbilitySystemComponent* SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();

	FAggregatorEvaluateParameters  EvaluateParameters;
	EvaluateParameters.SourceTags=OwningSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags=OwningSpec.CapturedTargetTags.GetAggregatedTags();
//TODO:捕获需要计算用的属性值
	
	float Armor=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageCaptureDef::Get().ArmorDef,EvaluateParameters,Armor);
	Armor=FMath::Max(0,Armor);
		
	float BlockChance=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageCaptureDef::Get().BlockChanceDef,EvaluateParameters,BlockChance);
	BlockChance=FMath::Max(0,BlockChance);
	
	float ArmorPenetration=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageCaptureDef::Get().ArmorPenetrationDef,EvaluateParameters,ArmorPenetration);
	ArmorPenetration=FMath::Max(0,ArmorPenetration);

	float CriticalHitChance=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageCaptureDef::Get().CriticalHitChanceDef,EvaluateParameters,CriticalHitChance);
	CriticalHitChance=FMath::Max(0,CriticalHitChance);
		
	float CriticalHitDamage=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageCaptureDef::Get().CriticalHitDamageDef,EvaluateParameters,CriticalHitDamage);
	CriticalHitDamage=FMath::Max(0,CriticalHitDamage);
	
	float TargetCriticalHitResistance=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageCaptureDef::Get().CriticalHitResistanceDef,EvaluateParameters,TargetCriticalHitResistance);
	TargetCriticalHitResistance=FMath::Max(0,TargetCriticalHitResistance);
	
	FGameplayModifierEvaluatedData 	DamageModifierEvaluatedData;
	DamageModifierEvaluatedData.Attribute=UAuraAttributeSet::GetIncomingDamageAttribute();
	DamageModifierEvaluatedData.ModifierOp=EGameplayModOp::Override;

//TODO:计算伤害:格挡伤害减半，穿甲降低百分比护甲,暴击伤害翻倍
	float Damage=0;
	//Damage=OwningSpec.GetModifierMagnitude(0,false);
	Damage=OwningSpec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Damage"));
	
	const float EffectCritialChance=1-TargetCriticalHitResistance*0.15f;
	bool bBlockchance=FMath::RandRange(0,100)<BlockChance;
	bool bCritialchance=FMath::RandRange(0,100)<EffectCritialChance;

	//--TODO:使用自定义的AuraEffectContext
	
	FAuraEffectContext* AuraEffectContext= static_cast<FAuraEffectContext*>(OwningSpec.GetContext().Get());
	 if (AuraEffectContext)
	 {
	 	AuraEffectContext->SetBlock(bBlockchance);
	 	AuraEffectContext->SetCritial(bCritialchance);
	 }
	
	
	Damage=bCritialchance?CriticalHitDamage+Damage*2.f:Damage;
	Damage=bBlockchance?Damage/2.f:Damage;
	
	const float EffectArmor=Armor*(1-ArmorPenetration*0.25f)/100.f;
	Damage*=(100-EffectArmor*0.33f)/100.f;
	

	
	DamageModifierEvaluatedData.Magnitude=Damage;
	
	OutExecutionOutput.AddOutputModifier(DamageModifierEvaluatedData);
}
