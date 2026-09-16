/*============================================================
*	@file	 : Camera.h
*	@brief	 : カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/26
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "GameObject.h"
#include <DirectXMath.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Timer;

/*============================================================
*	@class	: Camera
*	@brief	: カメラオブジェクト
*============================================================*/
class Camera : public GameObject
{
protected:
	// 注視点
	Vector3 mTarget{};

	// ビュー行列
	DirectX::XMMATRIX mViewMatrix{};

	// カメラシェイク用タイマー
	Timer* _mShakeTimer{ nullptr };

	// シェイク強度
	float mShakeIntensity{};

public:
	virtual ~Camera() = default;
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;

	// ビュー行列取得
	DirectX::XMMATRIX GetViewMatrix() const { return mViewMatrix; }

	// カメラ前方取得
	Vector3 GetForward() const;

	// カメラ右方向取得
	Vector3 GetRight() const;

	// カメラ行列のセット
	void SetMatrix() const;

	// カメラシェイク
	void Shake(float intensity, double shakeTime = 1.0);

private:
	// シェイク更新
	void shakeUpdate();
};