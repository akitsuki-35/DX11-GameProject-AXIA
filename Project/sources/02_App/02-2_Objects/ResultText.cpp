/*============================================================
*	@file	 : ResultText.cpp
*	@brief	 : リザルト画面テキスト表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/14
*============================================================*/
#include "ResultText.h"
#include "TextRenderer.h"

void ResultText::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 120.0f, 100.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	// レンダラーの設定
	auto renderer = AddComponent<TextRenderer>(this);
	renderer->SetFont("Kaisotai")->SetText("Result")
		->SetTextSize(128)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");
}

void ResultText::Finalize()
{
	GameObject::Finalize();
}

void ResultText::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void ResultText::Draw() const
{
	GameObject::Draw();
}