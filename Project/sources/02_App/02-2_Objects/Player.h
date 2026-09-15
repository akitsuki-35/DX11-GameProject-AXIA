/*============================================================
*	@file	 : Player.h
*	@brief	 : プレイヤークラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/09/13
*============================================================*/
#pragma once

#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class AudioPlayer;
class Timer;

/*============================================================
*	@class	: Player
*	@brief	: プレイヤー
*============================================================*/
class Player : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

	// ショット間隔
	Timer* _mShotInterval{ nullptr };

	// 体力
	int mLife{ 100 };

	// そのフレームでダメージを受けたか
	bool mIsDamage{ false };

	Timer* _mShakeTimer{ nullptr }; // シェイク用タイマー
	float mShakeIntensity{}; // シェイク強度

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// ダメージ
	void Damage(int damage);

	// シェイク
	void Shake(float intensity, double shakeTime = 1.0);

	// HP取得
	int GetLife() const { return mLife; }
	
	// 生死取得
	// オブジェクトそのものを消さないためHPで判定
	const bool IsDestroy() const override { return mLife == 0; }

	// ダメージ判定
	const bool IsDamage() const { return mIsDamage; }

private:
	void shakeUpdate(Vector3& position);
};