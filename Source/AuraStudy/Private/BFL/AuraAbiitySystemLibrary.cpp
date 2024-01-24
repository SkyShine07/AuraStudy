// copyright  D.H.B


#include "BFL/AuraAbiitySystemLibrary.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


void UAuraAbiitySystemLibrary::ApplyEffectToTarget(AActor* TargetActor,UObject* SourceActor, TSubclassOf<UGameplayEffect> GE, float level)
{
	UAbilitySystemComponent* ASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!ASC) return ;

	FGameplayEffectContextHandle ContextHandle=ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceActor);
	FGameplayEffectSpecHandle GEhandle=ASC->MakeOutgoingSpec(GE,level,ContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*GEhandle.Data);
	
    return;
    
    
   
}

void UAuraAbiitySystemLibrary::ApplyDynamicInstanceEffectToTarget(AActor* TargetActor, FGameplayAttribute Attribute, UObject* SourceActor,
	EGameplayModOp::Type ModOp, float Num)
{
	UGameplayEffect* InstanceGE=NewObject<UGameplayEffect>();

	InstanceGE->DurationPolicy=EGameplayEffectDurationType::Instant;
	
	FGameplayModifierInfo ModifierInfo ;
	ModifierInfo.Attribute=Attribute;
	ModifierInfo.ModifierOp=ModOp;
	ModifierInfo.ModifierMagnitude=FScalableFloat(Num);

	InstanceGE->Modifiers.Add(ModifierInfo);

	UAbilitySystemComponent* ASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!ASC) return ;
	FGameplayEffectContextHandle Handle=ASC->MakeEffectContext();
	Handle.AddSourceObject(SourceActor);	
	ASC->ApplyGameplayEffectToSelf(InstanceGE,1,Handle);

	return ;
}

FGameplayEffectSpecHandle UAuraAbiitySystemLibrary::MakeGESpecWithSourcebjectApplyTargetViaSetByCaller(TSubclassOf<UGameplayEffect> GEClass,
	AActor* SourceActor, AActor* TargetActor,float level,FGameplayTag Tag,float Num)
{
	if (!SourceActor||!GEClass) return nullptr;

	UAbilitySystemComponent* ASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!ASC) return nullptr;
	FGameplayEffectContextHandle ContextHandle=ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceActor);
	FGameplayEffectSpecHandle SpecHandle= ASC->MakeOutgoingSpec(GEClass,level,ContextHandle);
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(Tag,Num);
	
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

	return SpecHandle;
	
}
