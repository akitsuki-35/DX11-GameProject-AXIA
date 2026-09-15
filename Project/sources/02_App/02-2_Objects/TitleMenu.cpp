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
#include "Timer.h"
#include "Input.h"
#include "Utility.h"
#include "Easing.h"

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
	_mQuitRenderer->SetFont("Kaisotai")->SetText("ゲーム終了")->SetOffset({ 0.0f, 125.0f })
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	// タイマーのセット
	_mEaseTimer = AddComponent<Timer>(this);
}

void TitleMenu::Finalize()
{
	GameObject::Finalize();
}

void TitleMenu::Update(double deltaTime)
{
	int currentItem = TitleManager::GetCurrentItem();
	XMFLOAT4 color = { 0.0f, 1.0f, 1.0f, 1.0f };

	// イージング
	if (_mEaseTimer->GetEnable()) {
		float ease = static_cast<float>(Utility::Easing::CalculateEase(_mEaseTimer->GetTime(), 0.25,
			EaseInOutBack));

		if (currentItem == 0) {
			easeItem(_mStartRenderer, ease, true);
			easeItem(_mQuitRenderer, ease, false);
		}
		else if (currentItem == 1) {
			easeItem(_mStartRenderer, ease, false);
			easeItem(_mQuitRenderer, ease, true);
		}
	}

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

void TitleMenu::SetEaseTimer(double time)
{
	_mEaseTimer->Start(time);
}

float TitleMenu::flashCalc(double deltaTime)
{
	float flashSpeed = 5.0f;

	static float time = 0.0f;
	time += static_cast<float>(deltaTime) * flashSpeed;

	float value = (sinf(time) + 1.0f) / 2.0f;

	return value;
}

void TitleMenu::easeItem(TextRenderer* renderer, float ease, bool isCurrent)
{
	Vector2 itemOffset = renderer->GetOffset();
	float startX = itemOffset.x;
	float baseX = 0.0f;

	if (isCurrent) {
		float targetX = baseX + 100.0f;
		itemOffset.x = startX + (targetX - startX) * ease;
	}
	else {
		float targetX = baseX;

		itemOffset.x = startX + (targetX - startX) * ease;

		if (itemOffset.x < baseX) {
			itemOffset.x = baseX;
		}
	}

	renderer->SetOffset(itemOffset);
}