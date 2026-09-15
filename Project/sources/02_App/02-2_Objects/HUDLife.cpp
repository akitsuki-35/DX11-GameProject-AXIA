/*============================================================
*	@file	 : HUDLife.cpp
*	@brief	 : 体力表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/09/13
*============================================================*/
#include "HUDLife.h"
#include "TextRenderer.h"
#include "Game.h"
#include "Player.h"
#include <format>

using namespace DirectX;

void HUDLife::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 100.0f, 900.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 2.0f, 2.0f,  1.0f }
	);

	// HP数値レンダラー設定
	_mLifeRenderer = AddComponent<TextRenderer>(this);
	_mLifeRenderer->SetFont("Kaisotai")
		->SetTextSize(100)->SetShadowColor({ 0.5f, 1.0f, 1.0f, 1.0f })->SetColor({ 0.3f, 0.7f, 1.0f, 1.0f })
		->LoadShader("Font");

	// テキスト部分レンダラー設定
	_mTextRenderer = AddComponent<TextRenderer>(this);
	_mTextRenderer->SetFont("Kaisotai")->SetText("HP")->SetOffset({ 140.0f, 30.0f })
		->SetTextSize(60)->SetShadowColor({ 0.5f, 1.0f, 1.0f, 1.0f })->SetColor({ 0.3f, 0.7f, 1.0f, 1.0f })
		->LoadShader("Font");
}

void HUDLife::Finalize()
{
	GameObject::Finalize();
}

void HUDLife::Update(double deltaTime)
{
	int life = Game::GetGameObject<Player>()->GetLife();
	std::string lifeText = std::format("{:0}", life);

	_mLifeRenderer->SetText(lifeText);

	// 文字オフセット変更
	if (life != 100 && life >= 10) {
		_mLifeRenderer->SetOffset({ 30.0f, 0.0f });
	}
	else if(life < 10) {
		_mLifeRenderer->SetOffset({ 60.0f, 0.0f });
	}

	// 残りライフに応じて文字色変更
	if (life != 100) {
		if (life > 60) {
			XMFLOAT4 color = { 0.5f, 1.0f, 0.3f, 1.0f };
			XMFLOAT4 shadowColor = { 0.0f, 0.5f, 1.0f, 1.0f };
			_mLifeRenderer->SetShadowColor(shadowColor)->SetColor(color);
			_mTextRenderer->SetShadowColor(shadowColor)->SetColor(color);
		}
		else if (life > 30) {
			XMFLOAT4 color = { 1.0f, 0.8f, 0.0f, 1.0f };
			XMFLOAT4 shadowColor = { 1.0f, 0.0f, 0.0f, 1.0f };
			_mLifeRenderer->SetShadowColor(shadowColor)->SetColor(color);
			_mTextRenderer->SetShadowColor(shadowColor)->SetColor(color);
		}
		else {
			XMFLOAT4 color = { 1.0f, 0.2f, 0.5f, 1.0f };
			XMFLOAT4 shadowColor = { 1.0f, 0.5f, 0.0f, 1.0f };
			_mLifeRenderer->SetShadowColor(shadowColor)->SetColor(color);
			_mTextRenderer->SetShadowColor(shadowColor)->SetColor(color);
		}
	}

	GameObject::Update(deltaTime);
}

void HUDLife::Draw() const
{
	GameObject::Draw();
}