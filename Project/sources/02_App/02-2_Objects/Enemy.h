/*============================================================
*	@file	 : Enemy.h
*	@brief	 : エネミー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Timer;

/*============================================================
*	@class	: Enemy
*	@brief	: エネミー
*============================================================*/
class Enemy : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

	// 体力
	int mLife{ 3 };

	// ショット間隔
	Timer* _mShotInterval{ nullptr };

	// シェイク用タイマー
	Timer* _mShakeTimer{ nullptr };

	// シェイク強度
	float mShakeIntensity{};

public:
	Enemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// ダメージ
	void Damage();

	// シェイク
	void Shake(float intensity, double shakeTime = 1.0);

private:
	// シェイク更新
	void shakeUpdate(Vector3& position);

	// ショットインターバルをセット
	double setShotInterval(double min = 1.0, double max = 3.0);
};