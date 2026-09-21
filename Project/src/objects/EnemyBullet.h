/*============================================================
*	@file	 : EnemyBullet.h
*	@brief	 : 敵の弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/13
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "GameObject.h"
#include <memory>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class ParticleEmitter;
class Player;

/*============================================================
*	@class	: EnemyBullet
*	@brief	: 敵の弾
*============================================================*/
class EnemyBullet : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

	// 弾が消えるまでの時間
	double mLifeTime{ 2.0 };

	// 軌跡用パーティクル
	ParticleEmitter* _mEmitter{};

public:
	EnemyBullet() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// 速度をセット
	void SetVelocity(const Vector3& velocity) { mVelocity = velocity; }

private:
	// ヒット演出
	void hitEffect(Player* enemy);
};