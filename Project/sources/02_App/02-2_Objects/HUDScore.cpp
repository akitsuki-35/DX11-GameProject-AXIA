/*============================================================
*	@file	 : HUDScore.cpp
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/09/13
*============================================================*/
#include "HUDScore.h"
#include "TextRenderer.h"
#include "FontLoader.h"
#include "Timer.h"
#include <format>

void HUDScore::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 75.0f, 60.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// テキスト部分レンダラーの設定
	_mTextRenderer = AddComponent<TextRenderer>(this);
	_mTextRenderer->SetFont("Kaisotai")->SetText("Score")
		->SetTextSize(54)->SetShadowColor({0.0f, 0.5f, 1.0f, 1.0f})->SetColor({0.5f, 1.0f, 0.3f, 1.0f})
		->LoadShader("Font");

	// スコア数値レンダラーの設定
	_mScoreRenderer = AddComponent<TextRenderer>(this);
	_mScoreRenderer->SetFont("Kaisotai")->SetOffset({ 150.0f, -10.0f })
		->SetTextSize(64)->SetShadowColor({ 0.0f, 0.5f, 1.0f, 1.0f })->SetColor({ 0.5f, 1.0f, 0.3f, 1.0f })
		->LoadShader("Font");
}

void HUDScore::Finalize()
{
	GameObject::Finalize();
}

void HUDScore::Update(double deltaTime)
{
	// 6桁でゼロ埋めする
	std::string score = std::format("{:06}", mScore);
	_mScoreRenderer->SetText(score);

	GameObject::Update(deltaTime);
}

void HUDScore::Draw() const
{
	GameObject::Draw();
}