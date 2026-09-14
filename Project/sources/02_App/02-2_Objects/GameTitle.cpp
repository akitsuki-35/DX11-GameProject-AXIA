/*============================================================
*	@file	 : GameTitle.cpp
*	@brief	 : タイトル表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/14
*============================================================*/
#include "GameTitle.h"
#include "TextRenderer.h"
#include "FontLoader.h"

void GameTitle::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 150.0f, 150.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	std::string title = "Game Title";

	// レンダラーの設定
	auto renderer = AddComponent<TextRenderer>(this);
	renderer->SetFont("Kaisotai")->SetText(title)
		->SetTextSize(254)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");
}

void GameTitle::Finalize()
{
	GameObject::Finalize();
}

void GameTitle::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void GameTitle::Draw() const
{
	GameObject::Draw();
}