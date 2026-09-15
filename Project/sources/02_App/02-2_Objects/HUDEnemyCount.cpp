/*============================================================
*	@file	 : HUDEnemyCount.cpp
*	@brief	 : ウェーブ数表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/13
*	@updated : 2026/09/13
*============================================================*/
#include "HUDEnemyCount.h"
#include "TextRenderer.h"
#include "Timer.h"
#include "GameManager.h"
#include <format>

void HUDEnemyCount::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 1665.0f, 145.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// テキスト部分レンダラーの設定
	_mTextRenderer = AddComponent<TextRenderer>(this);
	_mTextRenderer->SetFont("Kaisotai")->SetText("Enemy")
		->SetTextSize(32)->SetShadowColor({ 0.0f, 0.5f, 1.0f, 1.0f })->SetColor({ 0.5f, 1.0f, 0.3f, 1.0f })
		->LoadShader("Font");

	// エネミー数レンダラーの設定
	_mEnemyCountRenderer = AddComponent<TextRenderer>(this);
	_mEnemyCountRenderer->SetFont("Kaisotai")->SetOffset({ 100.0f, -10.0f })
		->SetTextSize(48)->SetShadowColor({ 0.0f, 0.5f, 1.0f, 1.0f })->SetColor({ 0.5f, 1.0f, 0.3f, 1.0f })
		->LoadShader("Font");
}

void HUDEnemyCount::Finalize()
{
	GameObject::Finalize();
}

void HUDEnemyCount::Update(double deltaTime)
{
	std::string current = std::format("{:0}", GameManager::GetEnemyCount());
	std::string max = std::format("{:0}", GameManager::GetMaxEnemyCount());
	_mEnemyCountRenderer->SetText(current + " / " + max);

	GameObject::Update(deltaTime);
}

void HUDEnemyCount::Draw() const
{
	GameObject::Draw();
}