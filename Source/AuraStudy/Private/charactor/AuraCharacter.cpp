// copyright  D.H.B


#include "Charactor/AuraCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{

	GetMovementComponent()->bSnapToPlaneAtStart=true;
	GetMovementComponent()->bConstrainToPlane=true;
	//GetMovementComponent().borient
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
	
}
