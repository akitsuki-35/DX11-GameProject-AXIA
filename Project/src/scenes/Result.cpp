/*============================================================
*	@file	 : Result.cpp
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#include "Result.h"

// マネージャー
#include "ResultManager.h"

// オブジェクト群
#include "BackGroundTexture.h"
#include "ResultText.h"
#include "ResultScore.h"
#include "ResultMenu.h"

void Result::Initialize()
{
	_mGameObjects.clear();

	// 背景テクスチャ
	AddGameObject<BackGroundTexture>()->LoadTexture("assets\\textures\\result.jpg");
	AddGameObject<BackGroundTexture>()->LoadTexture("assets\\textures\\white.jpg")->SetColor({ 0.0f, 0.0f, 0.0f, 0.25f });

	// テキスト
	AddGameObject<ResultText>();
	AddGameObject<ResultScore>();
	AddGameObject<ResultMenu>();

	// マネージャー（制御用ダミーオブジェクト）
	AddGameObject<ResultManager>();
}

void Result::Finalize()
{
	Scene::Finalize();
}

void Result::Update(double deltaTime)
{
	Scene::Update(deltaTime);
}

void Result::Draw() const
{
	Scene::Draw();
}