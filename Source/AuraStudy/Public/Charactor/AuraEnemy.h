// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Charactor/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"

#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class AURASTUDY_API AAuraEnemy : public AAuraCharacterBase,public  IEnemyInterface
{
	GENERATED_BODY()

public:

	//继承的高亮描边接口函数
	virtual  void HighLightActor() override;
	virtual  void UnHighLightActor() override;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetIsHightLight(){return bHightLight;};

private:

	bool bHightLight;
	
};
