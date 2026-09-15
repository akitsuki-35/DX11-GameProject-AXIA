/*============================================================
*	@file	 : TitleManager.cpp
*	@brief	 : タイトルシーン制御用ダミーオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/07
*	@updated : 2026/09/07
*============================================================*/
#include "TitleManager.h"
#include "SceneManager.h"
#include "Transition.h"
#include "Title.h"
#include "Game.h"
#include "TitleMenu.h"
#include "Input.h"
#include "SystemWindow.h"

void TitleManager::Initialize()
{
	// トランジション処理
	Transition::getInstance().Start(1.0, true);

	_mTitleAudios.clear();

	// BGM読み込み
	mBGMVolume = 0.1f;
	AudioPlayer* bgm = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\Title.ogg")->SetVolume(mBGMVolume);
	_mTitleAudios.emplace("BGM", bgm);

	// SE読み込み
	AudioPlayer* cursor = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\Cursor.mp3")->SetVolume(0.3f);
	_mTitleAudios.emplace("Cursor", cursor);

	AudioPlayer* start = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\GameStart.ogg")->SetVolume(0.15f);
	_mTitleAudios.emplace("GameStart", start);

	AudioPlayer* decision = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\Decision.ogg")->SetVolume(0.15f);
	_mTitleAudios.emplace("Decision", decision);

	_mTitleAudios["BGM"]->Play(true);

	Title::GetGameObject<TitleMenu>()->SetEaseTimer(0.25);
}

void TitleManager::Finalize()
{
	GameObject::Finalize();
}

void TitleManager::Update(double deltaTime)
{
	// 上下キーで項目選択
	if (!Transition::getInstance().GetTransitionActive()) {
		if (Input::GetKeyTrigger(VK_UP) && mTitleItem == 1) {
			_mTitleAudios["Cursor"]->Play();
			Title::GetGameObject<TitleMenu>()->SetEaseTimer(0.25);
			mTitleItem = 0;
		}
		if (Input::GetKeyTrigger(VK_DOWN) && mTitleItem == 0) {
			_mTitleAudios["Cursor"]->Play();
			Title::GetGameObject<TitleMenu>()->SetEaseTimer(0.25);
			mTitleItem = 1;
		}
	}

	bool isInput = false;

	// 決定
	if (Input::GetKeyTrigger('Z') && !Transition::getInstance().GetTransitionActive()) {
		isInput = true;

		if (mTitleItem == 0) {
			_mTitleAudios["GameStart"]->Play();
		}
		else if (mTitleItem == 1) {
			_mTitleAudios["Decision"]->Play();
		}
	}

	// シーン遷移処理
	if (!Transition::getInstance().GetTransitionActive() && isInput) {
		Transition::getInstance().Start(1.0, false);
		mTransitionWait = true;
	}

	if (mTransitionWait && !Transition::getInstance().GetTransitionActive()) {
		mTransitionWait = false;

		if (mTitleItem == 0) {
			SceneManager::getInstance().SceneChange<Game>();
		}
		else if (mTitleItem == 1) {
			System::Window::getInstance().GameQuit();
		}
	}

	// BGMのフェードアウト処理
	if (mTransitionWait) {
		float volume = mBGMVolume * Transition::getInstance().GetTransitionProgress();
		_mTitleAudios["BGM"]->SetVolume(volume);
	}

	GameObject::Update(deltaTime);
}

void TitleManager::Draw() const
{
	GameObject::Draw();
}

void TitleManager::AudioPlay(std::string key)
{
	// キーから登録オーディオを検索して再生する
	auto it = _mTitleAudios.find(key);

	if (it != _mTitleAudios.end()) {
		_mTitleAudios[key]->Play();
	}
}