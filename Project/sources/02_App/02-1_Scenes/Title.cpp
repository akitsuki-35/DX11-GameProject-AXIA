/*============================================================
*	@file	 : Title.cpp
*	@brief	 : タイトルシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#include "Title.h"
#include "TitleManager.h"
#include "BackGroundTexture.h"
#include "GameTitle.h"
#include "TitleMenu.h"

void Title::Initialize()
{
	_mGameObjects.clear();

	// 背景テクスチャ
	AddGameObject<BackGroundTexture>()->LoadTexture("assets\\textures\\title.jpg");
	AddGameObject<BackGroundTexture>()->LoadTexture("assets\\textures\\white.jpg")->
		SetColor({ 0.0f, 0.0f, 0.0f, 0.25f });

	// テキスト
	AddGameObject<GameTitle>();
	AddGameObject<TitleMenu>();

	// マネージャー（制御用ダミーオブジェクト）
	AddGameObject<TitleManager>();
}

void Title::Finalize()
{
	Scene::Finalize();
}

void Title::Update(double deltaTime)
{
	Scene::Update(deltaTime);
}

void Title::Draw() const
{
	Scene::Draw();
}