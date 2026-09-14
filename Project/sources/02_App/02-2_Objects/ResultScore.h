/*============================================================
*	@file	 : ResultScore.h
*	@brief	 : リザルトスコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/14
*============================================================*/
#pragma once

#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class TextRenderer;
class Timer;

/*============================================================
*	@class	: ResultScore
*	@brief	: リザルトスコア表示
*============================================================*/
class ResultScore : public GameObject
{
private:
	int mDisplayScore{};
	TextRenderer* _mRenderer{ nullptr };
	Timer* _mTimer{ nullptr };

public:
	ResultScore() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

private:
	// 表示演出
	int valueDrumRoll() const;
};