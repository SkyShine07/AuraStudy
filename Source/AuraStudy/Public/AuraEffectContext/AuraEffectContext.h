#pragma once

#include"GameplayEffectTypes.h"
#include"AuraEffectContext.generated.h"

USTRUCT(BlueprintType)
struct FAuraEffectContext: public  FGameplayEffectContext
{
	GENERATED_USTRUCT_BODY()

public:

	bool GetIsCritial(){return bisCritialHit;};
	
	bool GetIsBlock(){return bisBlock;};

	void SetBlock(bool value){bisBlock=value;};
	void SetCritial(bool value){bisCritialHit=value;};

	//TODO:必须重写的函数
		/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FAuraEffectContext::StaticStruct();
	}
	
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FAuraEffectContext* NewContext = new FAuraEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

		/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	UPROPERTY()
	bool bisBlock=false;

	UPROPERTY()
	bool bisCritialHit=false;
};

template<>
struct TStructOpsTypeTraits< FAuraEffectContext > : public TStructOpsTypeTraitsBase2< FAuraEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};