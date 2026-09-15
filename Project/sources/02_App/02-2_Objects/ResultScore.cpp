/*============================================================
*	@file	 : ResultScore.cpp
*	@brief	 : リザルト画面テキスト表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/14
*============================================================*/
#include "ResultScore.h"
#include "GameManager.h"
#include "TextRenderer.h"
#include "Timer.h"
#include <format>

void ResultScore::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 1050.0f, 300.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// レンダラーの設定
	_mRenderer = AddComponent<TextRenderer>(this);
	_mRenderer->SetFont("Kaisotai")
		->SetTextSize(254)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	// タイマーセット
	_mTimer = AddComponent<Timer>(this);
	_mTimer->Start(2.0);
}

void ResultScore::Finalize()
{
	GameObject::Finalize();
}

void ResultScore::Update(double deltaTime)
{
	if (!_mTimer->GetEnable()) {
		mDisplayScore = GameManager::GetScore();
	}
	else {
		// スコアのドラムロール演出
		mDisplayScore = valueDrumRoll();
	}

	// 6桁でゼロ埋めする
	std::string scoreText = std::format("{:06}", mDisplayScore);
	_mRenderer->SetText(scoreText);

	GameObject::Update(deltaTime);
}

void ResultScore::Draw() const
{
	GameObject::Draw();
}

Timer& ResultScore::GetDirectionTimer() const
{
	return *_mTimer;
}

int ResultScore::valueDrumRoll() const
{
	// スコアをランダムで表示する演出用
	int randValue[6]{};

	for (size_t i = 0; i < 6; ++i) {
		randValue[i] = rand() % 10;
	}

	randValue[0] *= 100000;
	randValue[1] *= 10000;
	randValue[2] *= 1000;
	randValue[3] *= 100;
	randValue[4] *= 10;

	int display = randValue[0] + randValue[1] + randValue[2] + randValue[3] + randValue[4] + randValue[5];

	return display;
}
