// copyright  D.H.B


#include "player/AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[&]( UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle handle)
		{
			FGameplayTagContainer OutTagContainer;
			GameplayEffectSpec.GetAllAssetTags(OutTagContainer);
			FGameplayTag MessageTag=FGameplayTag::RequestGameplayTag(FName("Message"));
			
			for (const FGameplayTag& Tag : OutTagContainer)
			{
				//"Message.healthPosition" "message" true;
				if (Tag.MatchesTag(MessageTag))
				{
					OnMessageTag.Broadcast(Tag);

					GEngine->AddOnScreenDebugMessage(-1,
						2,FColor::Green,Tag.ToString()+"Apply Success");
				}
				
			}
		
		});
}
