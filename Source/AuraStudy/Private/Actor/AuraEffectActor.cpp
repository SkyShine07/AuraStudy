// copyright  D.H.B


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

}

void AAuraEffectActor::ApplyGameplayEffectToActor(AActor* TargetActor,TSubclassOf<UGameplayEffect> GE_EffectClass)
{
	UAbilitySystemComponent* ASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(ASC);
	if (ASC)
	{
		//利用GEffectContext将自己的数据传递到GE中
		FGameplayEffectContextHandle EffectContextHandle=ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		if (!IsValid(GE_EffectClass)) return ;
	
		FGameplayEffectSpecHandle SpecHandle=ASC->MakeOutgoingSpec(GE_EffectClass,ActorLevel,EffectContextHandle);
		FActiveGameplayEffectHandle ActiveHandle=ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

		if (SpecHandle.Data.Get()->Def->DurationPolicy==EGameplayEffectDurationType::Infinite)
		{
			InfiniteEffectActiveHandles.Add(ActiveHandle,ASC);
		}
		
		
		
	}
}

void AAuraEffectActor::RemoveGameplayInfiniteEffectFromActor(AActor* TargetActor)
{
	UAbilitySystemComponent* ASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(ASC);

	//找到actor对应的GE_ActiveHandle,从ASC中移除效果，并删除TMAp中对应的Pair
	
	for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : InfiniteEffectActiveHandles)
	{
		if (HandlePair.Value==ASC&&HandlePair.Key.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
			InfiniteEffectActiveHandles.FindAndRemoveChecked(HandlePair.Key);
			
		}
		
	}
	
	
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}



