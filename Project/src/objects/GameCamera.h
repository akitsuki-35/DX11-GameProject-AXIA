/*============================================================
*	@file	 : GameCamera.h
*	@brief	 : ゲーム用カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/21
*	@updated : 2026/09/21
*============================================================*/
#pragma once

#include "Camera.h"
#include <DirectXMath.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Timer;

/*============================================================
*	@class	: GameCamera
*	@brief	: ゲーム用カメラオブジェクト
*============================================================*/
class GameCamera final : public Camera
{
protected:
	// カメラシェイク用タイマー
	Timer* _mShakeTimer{ nullptr };

	// シェイク強度
	float mShakeIntensity{};

public:
	virtual ~GameCamera() = default;
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;

	// カメラシェイク
	void Shake(float intensity, double shakeTime = 1.0);

private:
	// シェイク更新
	void shakeUpdate();
};