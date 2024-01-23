// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Charactor/AuraCharacterBase.h"
#include "Interface/CombatInterface.h"
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

	AAuraEnemy();

	//--接口

	virtual int32 GetLevel() override {return level;};

	//初始化ASC的ActorInfo
	virtual void BeginPlay() override;
	
	//继承的高亮描边接口函数
	virtual  void HighLightActor() override;
	virtual  void UnHighLightActor() override;

protected:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetIsHightLight(){return bHightLight;};

	
	
private:

	bool bHightLight;
	
};
