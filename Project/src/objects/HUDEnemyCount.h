/*============================================================
*	@file	 : HUDEnemyCount.h
*	@brief	 : エネミー数表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/13
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
*	@class	: HUDEnemyCount
*	@brief	: エネミー数表示用HUD
*============================================================*/
class HUDEnemyCount : public GameObject
{
private:
	// テキスト部分レンダラー
	TextRenderer* _mTextRenderer{ nullptr };

	// エネミー数表示レンダラー
	TextRenderer* _mEnemyCountRenderer{ nullptr };

public:
	HUDEnemyCount() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};