// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "player/AbilitySystem/Abillities/AuraGameplayAbility.h"
#include "ProjectileSpellAbility.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class AURASTUDY_API UProjectileSpellAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	AAuraProjectile* SpawnProjectile(FVector TargetLocation);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GA")
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
