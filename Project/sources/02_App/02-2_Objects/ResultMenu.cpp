/*============================================================
*	@file	 : ResultMenu.cpp
*	@brief	 : タイトルメニュー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/15
*============================================================*/
#include "ResultMenu.h"
#include "TextRenderer.h"
#include "ResultManager.h"
#include "Input.h"

using namespace DirectX;

void ResultMenu::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 200.0f, 750.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// レンダラーの設定
	_mTitleRenderer = AddComponent<TextRenderer>(this);
	_mTitleRenderer->SetFont("Kaisotai")->SetText("タイトルへ")
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	_mRetryRenderer = AddComponent<TextRenderer>(this);
	_mRetryRenderer->SetFont("Kaisotai")->SetText("リトライ")->SetOffset({ 100.0f, 125.0f })
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");
}

void ResultMenu::Finalize()
{
	GameObject::Finalize();
}

void ResultMenu::Update(double deltaTime)
{
	int currentItem = ResultManager::GetCurrentItem();
	XMFLOAT4 color = { 0.0f, 1.0f, 1.0f, 1.0f };

	if (currentItem == 0) {
		color.x = flashCalc(deltaTime);
		_mTitleRenderer->SetColor({ color });
		_mRetryRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
	else if (currentItem == 1) {
		color.x = flashCalc(deltaTime);
		_mRetryRenderer->SetColor({ color });
		_mTitleRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	GameObject::Update(deltaTime);
}

void ResultMenu::Draw() const
{
	GameObject::Draw();
}

float ResultMenu::flashCalc(double deltaTime)
{
	float flashSpeed = 5.0f;

	static float time = 0.0f;
	time += static_cast<float>(deltaTime) * flashSpeed;

	float value = (sinf(time) + 1.0f) / 2.0f;

	return value;
}
