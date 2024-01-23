// copyright  D.H.B


#include "DA/DA_CharcrorClassInfo.h"

FCharactorInfo& UDA_CharcrorClassInfo::FindCharactorInfo(ECharactorType& characterClass)
{
	
	return *Infos.Find(characterClass);
}
