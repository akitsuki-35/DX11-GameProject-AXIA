/*============================================================
*	@file	 : HUDWave.cpp
*	@brief	 : ウェーブ数表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/13
*	@updated : 2026/09/13
*============================================================*/
#include "HUDWave.h"
#include "TextRenderer.h"
#include "FontLoader.h"
#include "Timer.h"
#include "GameManager.h"
#include <format>

void HUDWave::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 1650.0f, 70.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// テキスト部分レンダラーの設定
	_mTextRenderer = AddComponent<TextRenderer>(this);
	_mTextRenderer->SetFont("Kaisotai")->SetText("Wave")
		->SetTextSize(48)->SetShadowColor({0.0f, 0.5f, 1.0f, 1.0f})->SetColor({0.5f, 1.0f, 0.3f, 1.0f})
		->LoadShader("Font");

	// ウェーブ数値レンダラーの設定
	_mWaveRenderer = AddComponent<TextRenderer>(this);
	_mWaveRenderer->SetFont("Kaisotai")->SetOffset({ 125.0f, -20.0f })
		->SetTextSize(72)->SetShadowColor({ 0.0f, 0.5f, 1.0f, 1.0f })->SetColor({ 0.5f, 1.0f, 0.3f, 1.0f })
		->LoadShader("Font");
}

void HUDWave::Finalize()
{
	GameObject::Finalize();
}

void HUDWave::Update(double deltaTime)
{
	std::string wave = std::format("{:0}", GameManager::GetWave());
	_mWaveRenderer->SetText(wave);

	GameObject::Update(deltaTime);
}

void HUDWave::Draw() const
{
	GameObject::Draw();
}