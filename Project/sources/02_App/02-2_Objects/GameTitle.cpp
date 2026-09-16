/*============================================================
*	@file	 : GameTitle.cpp
*	@brief	 : ゲームタイトル表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/17
*============================================================*/
#include "GameTitle.h"
#include "TextRenderer.h"

void GameTitle::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 150.0f, 150.0f, 0.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 1.0f, 1.0f,  1.0f }
	);

	std::string title = "A.X.I.A";

	// タイトル表示テキスト
	auto renderer = AddComponent<TextRenderer>(this);
	renderer->SetFont("Kaisotai")->SetText(title)
		->SetTextSize(254)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
		->LoadShader("Font");

	// バージョン表示テキスト
	renderer = AddComponent<TextRenderer>(this);
	renderer->SetFont("Kaisotai")->SetText("@akitsuki-35      v1.0.0")->SetOffset({ 1475.0f, 875.0f })
		->SetTextSize(32)->SetShadowColor({ 0.0f, 0.0f, 0.0f, 1.0f })->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f })
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