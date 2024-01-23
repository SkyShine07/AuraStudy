// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FInputInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction=nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag Tag;
	
};

UCLASS()
class AURASTUDY_API UInputData : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	const UInputAction* FindInputActionByTag(FGameplayTag& Tag) const ;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FInputInfo> InputDatas;
	
};
