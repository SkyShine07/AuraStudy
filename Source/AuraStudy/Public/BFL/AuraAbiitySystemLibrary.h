// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbiitySystemLibrary.generated.h"


class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURASTUDY_API UAuraAbiitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void ApplyEffectToTarget(AActor* TargetActor,UObject* SourceActor,TSubclassOf<UGameplayEffect>GE,float level);

	 UFUNCTION(BlueprintCallable)
	static void ApplyDynamicInstanceEffectToTarget(AActor* TargetActor, FGameplayAttribute Attribute, UObject* SourceActor,
	 EGameplayModOp::Type ModOp, float Num);
};
