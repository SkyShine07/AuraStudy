// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_ExecutionCalculation_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURASTUDY_API UGE_ExecutionCalculation_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:

	
	
	UGE_ExecutionCalculation_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
