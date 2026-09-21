/*============================================================
*	@file	 : HUDWave.h
*	@brief	 : ウェーブ数表示
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
class TextRenderer;

/*============================================================
*	@class	: HUDWave
*	@brief	: ウェーブ数表示用HUD
*============================================================*/
class HUDWave : public GameObject
{
private:
	// テキスト部分レンダラー
	TextRenderer* _mTextRenderer{ nullptr };

	// ウェーブ数値レンダラー
	TextRenderer* _mWaveRenderer{ nullptr };

public:
	HUDWave() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};