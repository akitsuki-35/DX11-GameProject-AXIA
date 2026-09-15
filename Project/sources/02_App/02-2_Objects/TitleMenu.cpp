/*============================================================
*	@file	 : TitleMenu.cpp
*	@brief	 : タイトルメニュー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/15
*============================================================*/
#include "TitleMenu.h"
#include "TextRenderer.h"
#include "TitleManager.h"
#include "Input.h"

using namespace DirectX;

void TitleMenu::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 200.0f, 750.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// レンダラーの設定
	_mStartRenderer = AddComponent<TextRenderer>(this);
	_mStartRenderer->SetFont("Kaisotai")->SetText("ゲーム開始")
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	_mQuitRenderer = AddComponent<TextRenderer>(this);
	_mQuitRenderer->SetFont("Kaisotai")->SetText("ゲーム終了")->SetOffset({ 100.0f, 125.0f })
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");
}

void TitleMenu::Finalize()
{
	GameObject::Finalize();
}

void TitleMenu::Update(double deltaTime)
{
	int currentItem = TitleManager::GetCurrentItem();
	XMFLOAT4 color = { 0.0f, 1.0f, 1.0f, 1.0f };

	if (currentItem == 0) {
		color.x = flashCalc(deltaTime);
		_mStartRenderer->SetColor({ color });
		_mQuitRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
	else if (currentItem == 1) {
		color.x = flashCalc(deltaTime);
		_mQuitRenderer->SetColor({ color });
		_mStartRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	GameObject::Update(deltaTime);
}

void TitleMenu::Draw() const
{
	GameObject::Draw();
}

float TitleMenu::flashCalc(double deltaTime)
{
	float flashSpeed = 5.0f;

	static float time = 0.0f;
	time += static_cast<float>(deltaTime) * flashSpeed;

	float value = (sinf(time) + 1.0f) / 2.0f;

	return value;
}
