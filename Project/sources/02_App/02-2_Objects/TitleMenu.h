/*============================================================
*	@file	 : TitleMenu.h
*	@brief	 : タイトルメニュー
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
*	@class	: TitleMenu
*	@brief	: タイトルメニュー
*============================================================*/
class TitleMenu : public GameObject
{
private:
	TextRenderer* _mStartRenderer{ nullptr };
	TextRenderer* _mQuitRenderer{ nullptr };

public:
	TitleMenu() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

private:
	float flashCalc(double deltaTime);
};