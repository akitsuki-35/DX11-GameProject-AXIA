/*============================================================
*	@file	 : BackGroundTexture.h
*	@brief	 : 背景テクスチャ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/10
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "GameObject.h"
#include "Vector2.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class UIRenderer;

/*============================================================
*	@class	: BackGroundTexture
*	@brief	: 背景テクスチャ
*============================================================*/
class BackGroundTexture : public GameObject
{
private:
	// レンダラー
	UIRenderer* _mRenderer{ nullptr };

public:
	BackGroundTexture() = default;
	virtual ~BackGroundTexture() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// テクスチャ読み込み
	BackGroundTexture* LoadTexture(const char* fileName);

	// テクスチャサイズ設定
	BackGroundTexture* SetSize(const Vector2& size);

	// カラー設定
	BackGroundTexture* SetColor(const DirectX::XMFLOAT4& color);
};