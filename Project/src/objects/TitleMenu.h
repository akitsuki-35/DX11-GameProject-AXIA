/*============================================================
*	@file	 : TitleMenu.h
*	@brief	 : タイトルメニュー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/17
*============================================================*/
#pragma once

#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class TextRenderer;
class Timer;

/*============================================================
*	@class	: TitleMenu
*	@brief	: タイトルメニュー
*============================================================*/
class TitleMenu : public GameObject
{
private:
	// ゲーム開始テキスト
	TextRenderer* _mStartRenderer{ nullptr };

	// ゲーム終了テキスト
	TextRenderer* _mQuitRenderer{ nullptr };

	// テキストイージング用タイマー
	Timer* _mEaseTimer{ nullptr };

public:
	TitleMenu() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// イージング計算用タイマーのセット
	// メニュー側ではカーソルが動いた瞬間を検知しないので、外部から指定する
	void SetEaseTimer(double time);

private:
	// 選択中項目の点滅
	float flashCalc(double deltaTime);

	// カーソル選択時のイージング
	void easeItem(TextRenderer* renderer, float ease, bool isCurrent);
};