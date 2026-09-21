/*============================================================
*	@file	 : Game.cpp
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/09/16
*============================================================*/
#include "Game.h"

// マネージャー
#include "GameManager.h"

// オブジェクト群
#include "GameCamera.h"
#include "Grid.h"
#include "Player.h"
#include "Bullet.h"
#include "Sky.h"
#include "ScreenFilter.h"
#include "HUDScore.h"
#include "HUDLife.h"
#include "HUDWave.h"
#include "HUDEnemyCount.h"
#include "HUDGuide.h"

void Game::Initialize()
{
	// 配列を初期化
	_mGameObjects.clear();

	// カメラ
	AddGameObject<GameCamera>();

	// スカイドーム
	AddGameObject<Sky>();

	// グリッド（フィールド）
	AddGameObject<Grid>()->SetPosition({ 0.0f, 0.0f, 0.0f });

	// オブジェクト
	AddGameObject<Player>();

	// 2Dオブジェクト群
	AddGameObject<ScreenFilter>();
	AddGameObject<HUDScore>();
	AddGameObject<HUDLife>();
	AddGameObject<HUDWave>();
	AddGameObject<HUDEnemyCount>();
	AddGameObject<HUDGuide>();

	// マネージャー（制御用ダミーオブジェクト）
	AddGameObject<GameManager>();
}

void Game::Finalize()
{
	Scene::Finalize();
}

void Game::Update(double deltaTime)
{
	// スロー中は通常の半分の時間で更新
	if (mSlow) {
		deltaTime *= 0.5;
	}

	Scene::Update(deltaTime);
}

void Game::Draw() const
{
	Scene::Draw();
}