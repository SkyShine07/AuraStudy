// copyright  D.H.B


#include "player/AbilitySystem/AuraAbilitySystemComponent.h"

#include "player/AbilitySystem/Abillities/AuraGameplayAbility.h"

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

					//GEngine->AddOnScreenDebugMessage(-12,FColor::Green,Tag.ToString()+"Apply Success");
				}
				
			}
		
		});
}

void UAuraAbilitySystemComponent::AddAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilites)
{
	for (auto Ability : Abilites)
	{
		FGameplayAbilitySpec Spec(Ability);
		
		UAuraGameplayAbility* AuraGameplayAbility= Cast<UAuraGameplayAbility>(Spec.Ability);
		if (AuraGameplayAbility)
		{
			Spec.DynamicAbilityTags.AddTag(AuraGameplayAbility->InputTag);
		}
		
		GiveAbility(Spec);
		
	}
}

void UAuraAbilitySystemComponent::OnInputHeld(FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpec>& Specs=GetActivatableAbilities();
	for (auto Spec : Specs)
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag)&&!Spec.IsActive())
		{
			AbilitySpecInputPressed(Spec);
			TryActivateAbility(Spec.Handle);
		
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,InputTag.ToString());
		}
		
	}
}

void UAuraAbilitySystemComponent::OnInputPressed(FGameplayTag& InputTag)
{
	
		
	
}

void UAuraAbilitySystemComponent::OnInputRelease(FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpec>& Specs=GetActivatableAbilities();
	for (auto Spec : Specs)
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Spec);
			
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,InputTag.ToString());
		}
	}
}
