/*============================================================
*	@file	 : HUDScore.h
*	@brief	 : スコア表示
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
*	@class	: HUDScore
*	@brief	: スコア表示用HUD
*============================================================*/
class HUDScore : public GameObject
{
private:
	TextRenderer* _mTextRenderer{ nullptr };
	TextRenderer* _mScoreRenderer{ nullptr };

public:
	HUDScore() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};