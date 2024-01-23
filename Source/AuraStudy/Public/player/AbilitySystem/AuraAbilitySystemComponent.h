// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayAssetTag,const FGameplayTag&, Tag);

UCLASS()
class AURASTUDY_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	UPROPERTY(BlueprintAssignable)
	FGameplayAssetTag OnMessageTag;

	UFUNCTION(BlueprintCallable)
	void AddAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilites);

	//响应输入的InputTag函数
	void OnInputHeld(FGameplayTag& InputTag);
	void OnInputPressed(FGameplayTag& InputTag);
	void OnInputRelease(FGameplayTag& InputTag);
};
