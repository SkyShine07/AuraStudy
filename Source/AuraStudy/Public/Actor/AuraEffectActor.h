// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;

class UGameplayEffect;

UCLASS()
class AURASTUDY_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraEffectActor();

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToActor(AActor* TargetActor,TSubclassOf<UGameplayEffect> GE_EffectClass);

	UFUNCTION(BlueprintCallable)	
	void RemoveGameplayInfiniteEffectFromActor(AActor* TargetActor);
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="EffectClass")
	float ActorLevel;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="EffectClass")
	TSubclassOf<UGameplayEffect> InstanceEffectClass;


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="EffectClass")
	TSubclassOf<UGameplayEffect> DuringEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="EffectClass")
	TSubclassOf<UGameplayEffect> InfiniteEffectClass;

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> InfiniteEffectActiveHandles;
	
};
