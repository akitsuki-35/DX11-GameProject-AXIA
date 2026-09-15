/*============================================================
*	@file	 : HUDGuide.cpp
*	@brief	 : 操作ガイド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/15
*	@updated : 2026/09/15
*============================================================*/
#include "HUDGuide.h"
#include "TextRenderer.h"

void HUDGuide::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 1600.0f, 910.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// テキストレンダラーの設定
	auto renderer = AddComponent<TextRenderer>(this);
	renderer->SetFont("Kaisotai")->SetText("       Z : ショット\n       X : スピードアップ\nShift : スピードダウン")
		->SetTextSize(28)->SetShadowColor({ 0.0f, 0.5f, 1.0f, 1.0f })->SetColor({ 0.5f, 1.0f, 0.3f, 1.0f })
		->LoadShader("Font");
}

void HUDGuide::Finalize()
{
	GameObject::Finalize();
}

void HUDGuide::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void HUDGuide::Draw() const
{
	GameObject::Draw();
}