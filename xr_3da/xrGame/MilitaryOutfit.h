///////////////////////////////////////////////////////////////
// MilitaryOutfit.h
// MilitaryOutfit - �������� ������ ��������
///////////////////////////////////////////////////////////////


#pragma once

#include "CustomOutfit.h"

class CMilitaryOutfit: public CCustomOutfit
{
private:
    typedef	CCustomOutfit inherited;
public:
	CMilitaryOutfit(void);
	virtual ~CMilitaryOutfit(void);
};
