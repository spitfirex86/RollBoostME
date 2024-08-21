#include "framework.h"
#include "mod.h"


__declspec(dllexport)
int ModMain(BOOL bInit)
{
	if ( bInit )
	{
		fn_vInitMod();
	}
	else
	{
		fn_vDesInitMod();
	}

	return 0;
}
