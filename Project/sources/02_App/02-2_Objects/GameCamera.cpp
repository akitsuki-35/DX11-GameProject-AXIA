/*============================================================
*	@file	 : GameCamera.cpp
*	@brief	 : ゲーム用カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/21
*	@updated : 2026/09/21
*============================================================*/
#include "GameCamera.h"
#include "Game.h"
#include "GameManager.h"
#include "Timer.h"
#include "Input.h"
#include "Player.h"
#include "BufferManager.h"
#include "Config.h"

using namespace DirectX;

void GameCamera::Initialize()
{
	mTransform.SetPosition({ 0.0f, 5.0f, 5.0f });
	mTarget = Vector3(0.0f, 0.0f, 0.0f);

	// シェイク用タイマー
	_mShakeTimer = AddComponent<Timer>(this);
}

void GameCamera::Finalize()
{
	Camera::Finalize();
}

void GameCamera::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	// プレイヤー座標取得
	Player* player = Game::GetGameObject<Player>();
	Vector3 playerPos = player->GetTransform().GetPosition();

	// カメラ回転行列取得
	Vector3 rotation = mTransform.GetRotation();

	// 左右キーでカメラ回転
	if (!GameManager::IsHitStop()) {
		if (Input::GetKeyPress(VK_LEFT) && !Input::GetKeyPress(VK_RIGHT)) {
			mTransform.SetRotation({ rotation.x, rotation.y -= 3.0f * dt, rotation.z });
		}
		else if (Input::GetKeyPress(VK_RIGHT) && !Input::GetKeyPress(VK_LEFT)) {
			mTransform.SetRotation({ rotation.x, rotation.y += 3.0f * dt, rotation.z });
		}
	}

	// 回転行列をセット
	rotation = mTransform.GetRotation();

	// プレイヤーを追従する
	float t = 0.1f;
	mTarget = mTarget * (1.0f - t) + (playerPos + Vector3(0.0f, 1.25f, 0.0f)) * t;
	mTransform.SetPosition(mTarget + Vector3(-sinf(rotation.y) * 5.0f, 1.25f, -cosf(rotation.y) * 5.0f));
	
	// カメラのシェイク処理
	if (_mShakeTimer->GetEnable()) {
		shakeUpdate();
	}

	Camera::Update(deltaTime);

	//// ビュー行列をセット
	//XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//mViewMatrix = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*)&mTransform.GetPosition()),
	//	XMLoadFloat3((XMFLOAT3*)&mTarget), XMLoadFloat3(&up));

	//GameObject::Update(deltaTime);
}

void GameCamera::Shake(float intensity, double shakeTime)
{
	// 揺れの強さをセット
	mShakeIntensity = intensity;

	// タイマーをセット
	_mShakeTimer->Start(shakeTime);
}

void GameCamera::shakeUpdate()
{
	// 現在位置とターゲットを取得
	Vector3 target = mTarget;
	Vector3 position = mTransform.GetPosition();

	// タイマーの進行度に応じて揺れの強さを算出
	float progress = _mShakeTimer->GetProgress();
	float intensity = mShakeIntensity * progress;
	float angle = static_cast<float>(_mShakeTimer->GetTime()) * 50.0f;
	float shakeX = intensity * cosf(angle);
	float shakeY = intensity * sinf(angle);

	// 座標とターゲットに揺れを加算
	position.x += shakeX;
	position.y += shakeY;
	target.x += shakeX;
	target.y += shakeY;

	// 現在時間が0なら揺れの強さを0にする
	if (_mShakeTimer->IsTimeUp()) {
		mShakeIntensity = 0.0f;
	}

	// 座標とターゲットを差し戻し
	mTransform.SetPosition(position);
	mTarget = target;
}