/*============================================================
*	@file	 : ResultMenu.h
*	@brief	 : リザルトメニュー
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
*	@class	: ResultMenu
*	@brief	: リザルトメニュー
*============================================================*/
class ResultMenu : public GameObject
{
private:
	TextRenderer* _mTitleRenderer{ nullptr };
	TextRenderer* _mRetryRenderer{ nullptr };

public:
	ResultMenu() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

private:
	float flashCalc(double deltaTime);
};