/*============================================================
*	@file	 : HUDGuide.h
*	@brief	 : 操作ガイド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/15
*============================================================*/
#pragma once

#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class TextRenderer;

/*============================================================
*	@class	: HUDGuide
*	@brief	: ウェーブ数表示用HUD
*============================================================*/
class HUDGuide : public GameObject
{
private:
	TextRenderer* _mRenderer{ nullptr };

public:
	HUDGuide() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};