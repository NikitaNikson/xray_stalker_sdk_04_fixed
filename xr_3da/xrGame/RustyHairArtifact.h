///////////////////////////////////////////////////////////////
// RustyHairArtifact.h
// RustyHairArtefact - �������� ������ ������
///////////////////////////////////////////////////////////////

#pragma once
#include "Artifact.h"

class CRustyHairArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CRustyHairArtefact(void);
	virtual ~CRustyHairArtefact(void);

	virtual void Load				(LPCSTR section);

protected:
};