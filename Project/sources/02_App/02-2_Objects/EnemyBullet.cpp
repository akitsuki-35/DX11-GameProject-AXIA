/*============================================================
*	@file	 : EnemyBullet.cpp
*	@brief	 : 敵の弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/13
*	@updated : 2026/09/16
*============================================================*/
#include "EnemyBullet.h"
#include "Game.h"
#include "GameManager.h"
#include "Player.h"
#include "Camera.h"
#include "ParticleEmitter.h"
#include "ModelRenderer.h"

void EnemyBullet::Initialize()
{
	// トランスフォームの初期化
	mTransform = Transform(
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	);

	// 移動量と加速度の初期化
	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 0.0f, 0.0f, 0.0f };
	
	// 軌跡用パーティクルのセット
	_mEmitter = Game::AddGameObject<ParticleEmitter>();
	_mEmitter->LoadCSV("assets\\csv\\EnemyBullet.csv");

	// モデル・シェーダー読み込み
	AddComponent<ModelRenderer>(this)->LoadModel("assets\\models\\bullet.obj")->LoadShader("Unlit");
}

void EnemyBullet::Finalize()
{
	GameObject::Finalize();
}

void EnemyBullet::Update(double deltaTime)
{
	// 削除フラグが有効・ヒットストップ中は処理しない
	if (mDestroy) return;
	if (GameManager::IsHitStop()) return;

	// dtをfloatに変換
	float dt = static_cast<float>(deltaTime);

	// 現在の座標を取得
	Vector3 position = mTransform.GetPosition();
	 
	// 弾の直進
	position += mVelocity * dt;

	// オブジェクト背面取得
	Vector3 back = -mTransform.GetForward();

	// オブジェクト背面に向けてパーティクル発射
	_mEmitter->SetPosition(position);
	_mEmitter->SetAccel(back * 10.0f);
	_mEmitter->SetVelocity({ -mVelocity.x * 0.1f, -mVelocity.y * 0.1f, -mVelocity.z * 0.1f });

	// 敵との衝突判定
	auto player = Game::GetGameObject<Player>();

	// 距離計算
	Vector3 dir = player->GetPosition() - position;
	float length = dir.Length();

	// 距離がオブジェクト半径より小さい
	if (length < 2.0f && !player->IsDestroy()) {
		player->Damage(3 + rand() % 5);

		// 弾とパーティクルエミッタを削除
		SetDestroy();
		_mEmitter->SetDestroy();

		// ヒット演出
		hitEffect(player);
	}

	// 一定時間経過で弾を削除
	// パーティクルエミッタも同時に削除する
	mLifeTime -= deltaTime;
	if (mLifeTime <= 0.0) {
		SetDestroy();
		_mEmitter->SetDestroy();
	}

	// 座標のセット
	mTransform.SetPosition(position);

	GameObject::Update(deltaTime);
}

void EnemyBullet::Draw() const
{
	GameObject::Draw();
}

void EnemyBullet::hitEffect(Player* player)
{
	// 再生SEキー
	std::string audio = "Hit";

	// エミッタ寿命
	double emitterLife = 0.5;

	// エミッタ発生座標
	Vector3 effectPosition = mTransform.GetPosition();

	// シェイクの強さ
	float shake = 0.3f;

	// ヒットストップの長さ
	double hitStop = 0.025;

	// 死亡時は演出を強化
	if (player->IsDestroy()) {
		audio = "Destroy";
		emitterLife = 3.0;
		effectPosition = player->GetPosition();
		shake = 0.5f;
		hitStop = 0.75;
	}

	// ヒットSE
	GameManager::AudioPlay(audio);

	effectPosition.y += 1.0f;

	// 爆発エフェクト
	Game::AddGameObject<ParticleEmitter>()->LoadCSV("assets\\csv\\Explosion.csv")->SetEmitterLife(emitterLife)->
		SetPosition(effectPosition);

	// シェイク
	player->Shake(shake);
	auto camera = Game::GetGameObject<Camera>();
	camera->Shake(shake);

	// ヒットストップ
	GameManager::SetHitStop(hitStop);
}