// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class USplineComponent;
class UAuraAbilitySystemComponent;
class IEnemyInterface;
/**
 * 
 */
UCLASS()
class AURASTUDY_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:

	void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<class UInputMappingContext> AuraContext;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<class UInputAction> Move;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<class UInputData> InputData;

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	//------自动移动

	FVector3d CachedDestination=FVector3d::Zero();
	float FollowTime=0;
	float ShortPressthreShould=100;
	bool bAutoRun=false;
	bool bTargeting=false;

	UPROPERTY(EditAnywhere,Category="Move")
	float AcceptDistance=50;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Move")
	TObjectPtr<USplineComponent> PathSpline;

	void AutoRun();
	
	
private:

	void InputMove(const FInputActionValue& value);

	//绑定输入配置资产中所有的IA到下列三个函数中
	void BindAction();
	
	void OnInputTagPressed(FGameplayTag Tag);
	void OnInputTagRealse(FGameplayTag Tag);
	void OnInputTagHeld(FGameplayTag Tag);
//----------
	UAuraAbilitySystemComponent* ASC;
	UAuraAbilitySystemComponent* GetASC();
	//-----------------
	IEnemyInterface* LastActor;
	IEnemyInterface* CurrentActor;
	void CursorTrace();
	
};
