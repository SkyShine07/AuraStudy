// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURASTUDY_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()



public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	FGameplayTag InputTag;

	virtual UGameplayEffect* GetCooldownGameplayEffect() const override;
	virtual UGameplayEffect* GetCostGameplayEffect() const override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="CoolDown")
	FScalableFloat CoolDown;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="cost")
	TMap<FGameplayAttribute,FScalableFloat> costs;
	
};
