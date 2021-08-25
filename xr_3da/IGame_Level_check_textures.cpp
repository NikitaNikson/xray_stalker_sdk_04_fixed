#include "stdafx.h"
#include "ResourceManager.h"
#include "IGame_Level.h"

void IGame_Level::LL_CheckTextures()
{
	u32	m_base,c_base,m_lmaps,c_lmaps;
	Device.Resources->_GetMemoryUsage		(m_base,c_base,m_lmaps,c_lmaps);

	Msg	("* t-report - base: %d, %d Kb",	c_base,		m_base/1024);
	Msg	("* t-report - lmap: %d, %d Kb",	c_lmaps,	m_lmaps/1024);
	BOOL	bError	= FALSE;
	// old, rem
	/*
#ifdef DEBUG
	if (m_base>64*1024*1024 || c_base>400)
	{
		LPCSTR msg	= "Too many base-textures (limit: 400 textures or 64 Mb).\n        Reduce number of textures (better) or their resolution (worse).";
		Msg		("***FATAL***: %s",msg);
		bError		= TRUE;
	}
	if (m_lmaps>32*1024*1024 || c_lmaps>8)
	{
		LPCSTR msg	= "Too many lmap-textures (limit: 8 textures or 32 Mb).\n        Reduce pixel density (worse) or use more vertex lighting (better).";
		Msg			("***FATAL***: %s",msg);
		bError		= TRUE;
	}
#endif // DEBUG
	*/
}
