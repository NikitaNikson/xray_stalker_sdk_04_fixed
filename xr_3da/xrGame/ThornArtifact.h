///////////////////////////////////////////////////////////////
// ThornArtifact.h
// ThornArtefact - �������� �������
///////////////////////////////////////////////////////////////

#pragma once
#include "Artifact.h"

class CThornArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CThornArtefact(void);
	virtual ~CThornArtefact(void);

	virtual void Load				(LPCSTR section);

protected:
};