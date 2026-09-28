/*============================================================
*	@file	 : GameCamera.h
*	@brief	 : ゲーム用カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/21
*	@updated : 2026/09/28
*============================================================*/
#pragma once

#include "Camera.h"
#include <DirectXMath.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Shaker;

/*============================================================
*	@class	: GameCamera
*	@brief	: ゲーム用カメラオブジェクト
*============================================================*/
class GameCamera final : public Camera
{
private:
	// シェイクコンポーネント
	Shaker* _mShaker{ nullptr };

public:
	virtual ~GameCamera() = default;
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;

	// カメラシェイク
	void Shake(float power, double shakeTime = 1.0);
};