/*============================================================
*	@file	 : GameCamera.cpp
*	@brief	 : ゲーム用カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/21
*	@updated : 2026/09/28
*============================================================*/
#include "GameCamera.h"
#include "Game.h"
#include "GameManager.h"
#include "Shaker.h"
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
	_mShaker = AddComponent<Shaker>(this);
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
	if (_mShaker->IsSeeking()) {
		// シェイク座標オフセット取得
		Vector3 shake = _mShaker->GetShakeOffset();

		// カメラ座標にシェイクを適用
		Vector3 position = mTransform.GetPosition();
		position += shake;
		mTransform.SetPosition(position);

		// 注視点にシェイクを適用
		Vector3 target = mTarget;
		target += shake;
		mTarget = target;
	}

	Camera::Update(deltaTime);
}

void GameCamera::Shake(float power, double shakeTime)
{
	// 揺れの強さとタイマーをセット
	_mShaker->Shake(power, shakeTime);
}