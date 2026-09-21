/*============================================================
*	@file	 : Camera.cpp
*	@brief	 : カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/26
*	@updated : 2026/09/16
*============================================================*/
#include "Camera.h"
#include "Game.h"
#include "GameManager.h"
#include "Timer.h"
#include "Input.h"
#include "Player.h"
#include "BufferManager.h"
#include "Config.h"

using namespace DirectX;

void Camera::Initialize()
{
	mTransform.SetPosition({ 0.0f, 5.0f, 5.0f });
	mTarget = Vector3(0.0f, 0.0f, 0.0f);

	// シェイク用タイマー
	_mShakeTimer = AddComponent<Timer>(this);
}

void Camera::Finalize()
{
	GameObject::Finalize();
}

void Camera::Update(double deltaTime)
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

	// ビュー行列をセット
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	mViewMatrix = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*)&mTransform.GetPosition()),
		XMLoadFloat3((XMFLOAT3*)&mTarget), XMLoadFloat3(&up));

	GameObject::Update(deltaTime);
}

Vector3 Camera::GetForward() const
{
	// カメラ前方取得
	Vector3 forward = mTarget - mTransform.GetPosition();
	forward.Normalize();

	return forward;
}

Vector3 Camera::GetRight() const
{
	// カメラ右方向取得
	Vector3 forward = GetForward();
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 right = Vector3::Cross(up, forward);
	right.Normalize();

	return right;
}

void Camera::SetMatrix() const
{
	// プロジェクション行列設定
	XMMATRIX projection = XMMatrixPerspectiveFovLH(1.0f,
		static_cast<float>(Screen::WIDTH) / static_cast<float>(Screen::HEIGHT), 1.0f, 1000.0f);
	D3D11::BufferManager::getInstance().SetProjectionMatrix(projection);

	// ビュー行列設定
	D3D11::BufferManager::getInstance().SetViewMatrix(mViewMatrix);
}

void Camera::Shake(float intensity, double shakeTime)
{
	// 揺れの強さをセット
	mShakeIntensity = intensity;

	// タイマーをセット
	_mShakeTimer->Start(shakeTime);
}

void Camera::shakeUpdate()
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