// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AURASTUDY_API UMyGameInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
};
