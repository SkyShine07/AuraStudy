// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"


//角色的抽象基类，玩家控制角色和AI派生于此

UCLASS(Abstract)
class AURASTUDY_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();

protected:
	
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon;


};
