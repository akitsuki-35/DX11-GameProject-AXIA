/*============================================================
*	@file	 : HUDScore.h
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/09/16
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
	// テキスト部分レンダラー
	TextRenderer* _mTextRenderer{ nullptr };

	// スコア数値レンダラー
	TextRenderer* _mScoreRenderer{ nullptr };

public:
	HUDScore() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};