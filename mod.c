#include "mod.h"
#include "framework.h"


unsigned int ulGroundCounter = 0;
ACP_tdxBool bPrevOnGround = TRUE;


void * fn_pGetDsgVarFromSpo( HIE_tdstSuperObject *p_stSpo, int idx )
{
	AI_tdstDsgMem *p_stDsgMem = p_stSpo->hLinkedObject.p_stCharacter->hBrain->p_stMind->p_stDsgMem;
	AI_tdstDsgVarInfo *p_stDsgInfos = (*p_stDsgMem->pp_stDsgVar)->a_stDsgVarInfo;

	return &p_stDsgMem->p_cDsgMemBuffer[p_stDsgInfos[idx].ulOffsetInDsgMem];
}

void CALLBACK fn_vRollBoostDisplay( SPTXT_tdstTextInfo *p_stString )
{
	p_stString->X = 10;
	p_stString->Y = 950;
	p_stString->xSize = 6;
	p_stString->bFrame = TRUE;

	HIE_tdstSuperObject *p_stRayman = GAM_g_stEngineStructure->g_hMainActor;

	if ( !p_stRayman || strcmp(XHIE_fn_szGetSuperObjectPersonalName(p_stRayman), "Rayman") != 0 )
		return;

	DNM_tdstDynamics *p_stDynamics = p_stRayman->hLinkedObject.p_stCharacter->hDynam->p_stDynamics;
	ACP_tdxBool bOnGround = !!(p_stDynamics->stDynamicsBase.ulFlags & DNM_C_Flag_OnGround);

	ACP_tdxBool bHovering = (*(unsigned char *)fn_pGetDsgVarFromSpo(p_stRayman, 9) == 15);
	ACP_tdxBool bRollBoostActive = *(ACP_tdxBool *)fn_pGetDsgVarFromSpo(p_stRayman, 33);

	if ( bOnGround )
	{
		if ( !bPrevOnGround )
			ulGroundCounter = 0;

		ulGroundCounter++;
	}

	bPrevOnGround = bOnGround;

	char *szColorFmt = bRollBoostActive ? "/o400:" : "/o200:";
	SPTXT_vPrintFmtLine("Time on ground=:%s%d frames", szColorFmt, ulGroundCounter);
}

void fn_vInitMod( void )
{
	SPTXT_vAddTextCallback(fn_vRollBoostDisplay);
}
