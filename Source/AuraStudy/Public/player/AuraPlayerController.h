// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


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

private:

	void InputMove(const FInputActionValue& value);


	IEnemyInterface* LastActor;
	IEnemyInterface* CurrentActor;
	void CursorTrace();
	
};
