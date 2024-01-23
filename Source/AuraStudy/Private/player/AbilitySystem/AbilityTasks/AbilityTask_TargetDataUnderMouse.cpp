// copyright  D.H.B


#include "player/AbilitySystem/AbilityTasks/AbilityTask_TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouse(
	UGameplayAbility* ownerAbility)
{
	UAbilityTask_TargetDataUnderMouse* obj=NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(ownerAbility);

	return obj;
	
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		//TODO：将客户端数据发送到服务器
		
		SendTargetData();

		return;
	}

//TODO:非本地控制，等待TargetData发送过来,如果数据已经到达，调用绑定的回调函数，如果没有到达，等待。

	AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddLambda(
		[this](const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag Tag)
		{
			AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
			ValidData.Broadcast(DataHandle);
		});
	
	bool bcalled=AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (bcalled)
	{
			SetWaitingOnRemotePlayerData();
	}

	return ;
}

void UAbilityTask_TargetDataUnderMouse::SendTargetData()
{
	//---创建一个新的预测键
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC=Ability->GetCurrentActorInfo()->PlayerController.Get();

	FHitResult HitResult;
	bool bHit=PC->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	
	FGameplayAbilityTargetData_SingleTargetHit* TargetHit=new FGameplayAbilityTargetData_SingleTargetHit();
	TargetHit->HitResult=HitResult;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(TargetHit);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),	
									GetActivationPredictionKey(),
													DataHandle,FGameplayTag(),
													AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
