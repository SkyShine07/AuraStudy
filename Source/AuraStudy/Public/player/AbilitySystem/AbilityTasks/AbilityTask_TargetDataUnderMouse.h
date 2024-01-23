// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TargetDataUnderMouse.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataUnderMouseSignature,FGameplayAbilityTargetDataHandle,DataHandle);

UCLASS()
class AURASTUDY_API UAbilityTask_TargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,Category="Ability|Task",meta=(BlueprintInternalUseOnly="true",HidePin="ownerAbility",DefaultToSelf="ownerAbility",DisplayName="TargetDataUnderMouse"))
	static UAbilityTask_TargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* ownerAbility);

	UPROPERTY(BlueprintAssignable)
	FTargetDataUnderMouseSignature ValidData;

private:
	virtual void Activate() override;
	void SendTargetData();
};
