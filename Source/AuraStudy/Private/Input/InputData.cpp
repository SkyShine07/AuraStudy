// copyright  D.H.B


#include "Input/InputData.h"



const UInputAction* UInputData::FindInputActionByTag(FGameplayTag& Tag) const 
{
	for (auto Element : InputDatas)
	{
		if (Element.Tag==Tag&&Element.InputAction)
		{
			return Element.InputAction;
		}
	}

	return nullptr;
}
