// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURASTUDY_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;


	
	UPROPERTY(BlueprintReadWrite,Category="GAS")
	TObjectPtr<UAuraAbilitySystemComponent> ASC;
	
};
