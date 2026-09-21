/*============================================================
*	@file	 : Sky.h
*	@brief	 : スカイドーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Sky
*	@brief	: スカイドーム
*============================================================*/
class Sky : public GameObject
{
public:
	Sky() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};