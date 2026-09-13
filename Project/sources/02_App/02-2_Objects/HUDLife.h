/*============================================================
*	@file	 : HUDLife.h
*	@brief	 : 体力表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/09/13
*============================================================*/
#pragma once

#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Timer;
class TextRenderer;

/*============================================================
*	@class	: HUDLife
*	@brief	: プレイヤーHP表示用HUD
*============================================================*/
class HUDLife : public GameObject
{
private:
	TextRenderer* _mTextRenderer{ nullptr };
	TextRenderer* _mLifeRenderer{ nullptr };

public:
	HUDLife() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};