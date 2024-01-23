// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CharcrorClassInfo.generated.h"

/**
 * 
 */

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharactorType :uint8
{
	Warrior,
	Ranger,
	Elementalist
};

USTRUCT(BlueprintType)
struct FCharactorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="defaultCharatorClass")
	TSubclassOf<UGameplayEffect> PrimarryAttributes;
	

	
};
UCLASS()
class AURASTUDY_API UDA_CharcrorClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharactorType ,FCharactorInfo> Infos;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> SencondaryAttributes;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> vitalAttributes;

	UFUNCTION(BlueprintCallable)
	FCharactorInfo& FindCharactorInfo(ECharactorType& characterClass);

	
};
