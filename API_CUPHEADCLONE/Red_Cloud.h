#pragma once
#include "Cloud.h"
class CRed_Cloud :
	public CCloud
{
public:
	CRed_Cloud();
	virtual ~CRed_Cloud();

	virtual void Initialize(void) override;
	virtual void Late_Update(void)override;
	virtual void Release(void) override;
};

