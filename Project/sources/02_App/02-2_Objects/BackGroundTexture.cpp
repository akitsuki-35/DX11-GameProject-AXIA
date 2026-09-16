/*============================================================
*	@file	 : BackGroundTexture.cpp
*	@brief	 : 背景テクスチャ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/10
*	@updated : 2026/09/16
*============================================================*/
#include "BackGroundTexture.h"
#include "UIRenderer.h"
#include "Config.h"

void BackGroundTexture::Initialize()
{
	// レンダラー設定
	_mRenderer = AddComponent<UIRenderer>(this);
	_mRenderer->GetCanvas().CreateCanvas(UIStyle::Pivot::LeftTop);

	// トランスフォーム初期化
	// デフォルトではスクリーンサイズで初期化
	mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	mTransform.SetScale({ Screen::WIDTH, Screen::HEIGHT, 0.0f });

	// シェーダー読み込み
	_mRenderer->LoadShader("UI");
}

void BackGroundTexture::Finalize()
{
	GameObject::Finalize();
}

void BackGroundTexture::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void BackGroundTexture::Draw() const
{
	GameObject::Draw();
}

BackGroundTexture* BackGroundTexture::LoadTexture(const char* fileName)
{
	// テクスチャ読み込み
	_mRenderer->LoadTexture(fileName);
	return this;
}

BackGroundTexture* BackGroundTexture::SetSize(const Vector2& size)
{
	// サイズ設定
	mTransform.SetScale({ size.x, size.y, 0.0f });
	return this;
}

BackGroundTexture* BackGroundTexture::SetColor(const DirectX::XMFLOAT4& color)
{
	// カラー設定
	_mRenderer->SetColor(color);
	return this;
}
