/*============================================================
*	@file	 : ResultMenu.cpp
*	@brief	 : タイトルメニュー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/16
*============================================================*/
#include "ResultMenu.h"
#include "TextRenderer.h"
#include "ResultManager.h"
#include "Timer.h"
#include "Input.h"
#include "Utility.h"
#include "Easing.h"

using namespace DirectX;

void ResultMenu::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 175.0f, 750.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// レンダラーの設定
	_mTitleRenderer = AddComponent<TextRenderer>(this);
	_mTitleRenderer->SetFont("Kaisotai")->SetText("タイトルへ")
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	_mRetryRenderer = AddComponent<TextRenderer>(this);
	_mRetryRenderer->SetFont("Kaisotai")->SetText("リトライ")->SetOffset({ 0.0f, 125.0f })
		->SetTextSize(80)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	// タイマーの設定
	_mEaseTimer = AddComponent<Timer>(this);
}

void ResultMenu::Finalize()
{
	GameObject::Finalize();
}

void ResultMenu::Update(double deltaTime)
{
	int currentItem = ResultManager::GetCurrentItem();
	XMFLOAT4 color = { 0.0f, 1.0f, 1.0f, 1.0f };

	// イージング
	if (_mEaseTimer->GetEnable()) {
		float ease = static_cast<float>(Utility::Easing::CalculateEase(_mEaseTimer->GetTime(), 0.25,
			EaseInOutBack));

		if (currentItem == 0) {
			easeItem(_mTitleRenderer, ease, true);
			easeItem(_mRetryRenderer, ease, false);
		}
		else if (currentItem == 1) {
			easeItem(_mTitleRenderer, ease, false);
			easeItem(_mRetryRenderer, ease, true);
		}
	}

	// 選択項目を点滅させる
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

void ResultMenu::SetEaseTimer(double time)
{
	// イージング用タイマーをセット
	_mEaseTimer->Start(time);
}

float ResultMenu::flashCalc(double deltaTime)
{
	// 点滅スピード計算
	float flashSpeed = 5.0f;

	static float time = 0.0f;
	time += static_cast<float>(deltaTime) * flashSpeed;

	float value = (sinf(time) + 1.0f) / 2.0f;

	return value;
}

void ResultMenu::easeItem(TextRenderer* renderer, float ease, bool isCurrent)
{
	// 選択項目のイージング
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

	// オフセット移動
	renderer->SetOffset(itemOffset);
}
