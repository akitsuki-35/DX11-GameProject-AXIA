/*============================================================
*	@file	 : Player.cpp
*	@brief	 : プレイヤー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/09/06
*============================================================*/
#include "Player.h"
#include "Game.h"
#include "GameManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Input.h"
#include "ModelRenderer.h"
#include "Timer.h"

void Player::Initialize()
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

	// モデル・シェーダー読み込み
	AddComponent<ModelRenderer>(this)->LoadModel("assets\\models\\Player.fbx")->
		LoadTexture("Roughness.jpg", ModelRenderer::TextureType::Roughness)->
		LoadTexture("Metalness.jpg", ModelRenderer::TextureType::Metalness)->
		SetParameter({ 0.2f, 0.8f, 1.0f, 0.0f })->
		LoadShader("PBR");

	// タイマーのセット
	_mShotInterval = AddComponent<Timer>(this);
	_mShakeTimer = AddComponent<Timer>(this);
}

void Player::Finalize()
{
	GameObject::Finalize();
}

void Player::Update(double deltaTime)
{
	if (IsDestroy()) return;

	if (GameManager::IsHitStop()) return;

	mIsDamage = false;

	// dtをfloatに変換
	float dt = static_cast<float>(deltaTime);

	// 抵抗力
	float r = 5.0f;

	// 現在の座標と回転を取得
	Vector3 position = mTransform.GetPosition();
	Vector3 rotation = mTransform.GetRotation();

	// オブジェクト正面を取得
	Camera* camera = Game::GetGameObject<Camera>();
	Vector3 forward = camera->GetForward();

	// yの値は使わないので0に
	forward.y = 0.0f;
	forward.Normalize();

	// 自動で正面に前進
	mVelocity += forward * 100.0f * dt;

	// キー入力で旋回
	if (Input::GetKeyPress(VK_RIGHT) && !Input::GetKeyPress(VK_LEFT)) {
		rotation.z = std::max(rotation.z - 2.0f * dt, -1.0f);
	}
	else if (Input::GetKeyPress(VK_LEFT) && !Input::GetKeyPress(VK_RIGHT)) {
		rotation.z = std::min(rotation.z + 2.0f * dt, 1.0f);
	}
	else {
		// 入力がない時は傾きを戻す
		if (rotation.z > 0.0f) rotation.z = std::max(rotation.z - 2.0f * dt, 0.0f);
		else if (rotation.z < 0.0f) rotation.z = std::min(rotation.z + 2.0f * dt, 0.0f);
	}

	// SHIFTキーでスピードダウン・Xキーでスピードアップ
	if (Input::GetKeyPress(VK_SHIFT)) {
		mVelocity -= forward * 50.0f * dt;
	}
	if (Input::GetKeyPress('X')) {
		mVelocity += forward * 105.0f * dt;
	}

	// カメラ方向にプレイヤーを向ける
	float yaw = atan2f(mVelocity.x, mVelocity.z);
	rotation.y = yaw;

	// 摩擦抵抗
	mVelocity.x += -mVelocity.x * r * dt;
	mVelocity.z += -mVelocity.z * r * dt;

	// 移動処理
	position += mVelocity * dt;

	// 敵との衝突処理
	GameManager::EnemyCollision(*this, position, dt);

	// 座標クランプ
	GameManager::ClampPosition(position);

	// 弾の発射
	if (!_mShotInterval->GetEnable() && !GameManager::IsTransition()) {
		if (Input::GetKeyPress('Z')) {
			GameManager::AudioPlay("Shot");
			Bullet* bullet = Game::AddGameObject<Bullet>();
			bullet->SetPosition(mTransform.GetPosition());
			bullet->SetVelocity(forward * 100.0f);

			// インターバルのセット
			_mShotInterval->Start(0.2);
		}
	}

	// 座標と回転をセット
	mTransform.SetPosition(position);
	mTransform.SetRotation(rotation);

	GameObject::Update(deltaTime);
}

void Player::Draw() const
{
	GameObject::Draw();
}

void Player::Damage(int damage)
{
	mLife -= damage;
	mIsDamage = true;

	if (mLife < 0) {
		mLife = 0;
	}
}

void Player::Shake(float intensity, double shakeTime)
{
	// 揺れの強さをセット
	mShakeIntensity = intensity;

	// タイマーをセット
	_mShakeTimer->Start(shakeTime);
}

void Player::shakeUpdate(Vector3& position)
{
	// タイマーの進行度に応じて揺れの強さを算出
	float progress = _mShakeTimer->GetProgress();
	float intensity = mShakeIntensity * progress;
	float angle = static_cast<float>(_mShakeTimer->GetTime()) * 50.0f;
	float shakeX = intensity * cosf(angle);
	float shakeY = intensity * sinf(angle);

	// 座標に揺れを加算
	position.x += shakeX;
	position.y += shakeY;

	// 現在時間が0なら揺れの強さを0にする
	if (_mShakeTimer->IsTimeUp()) {
		mShakeIntensity = 0.0f;
	}
}