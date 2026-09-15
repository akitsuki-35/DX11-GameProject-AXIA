/*============================================================
*	@file	 : ResultText.h
*	@brief	 : リザルト画面テキスト表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/14
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: ResultText
*	@brief	: リザルト画面テキスト表示
*============================================================*/
class ResultText : public GameObject
{
public:
	ResultText() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};