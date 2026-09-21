/*============================================================
*	@file	 : HUDGuide.h
*	@brief	 : 操作ガイド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: HUDGuide
*	@brief	: 操作ガイド表示用HUD
*============================================================*/
class HUDGuide : public GameObject
{
public:
	HUDGuide() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};