/*============================================================
*	@file	 : ResultManager.cpp
*	@brief	 : リザルトシーン制御用ダミーオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/07
*	@updated : 2026/09/07
*============================================================*/
#include "ResultManager.h"
#include "SceneManager.h"
#include "Transition.h"
#include "ResultScore.h"
#include "ResultMenu.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Input.h"

void ResultManager::Initialize()
{
	// トランジション処理
	Transition::getInstance().Start(1.0, true);
	
	_mResultAudios.clear();

	mResultItem = -1;

	// BGM読み込み
	mBGMVolume = 0.1f;
	AudioPlayer* bgm = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\Result.ogg")->SetVolume(mBGMVolume);
	_mResultAudios.emplace("BGM", bgm);

	// SE読み込み
	AudioPlayer* cursor = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\Cursor.mp3")->SetVolume(0.3f);
	_mResultAudios.emplace("Cursor", cursor);

	AudioPlayer* start = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\GameStart.ogg")->SetVolume(0.15f);
	_mResultAudios.emplace("GameStart", start);

	AudioPlayer* decision = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\Decision.ogg")->SetVolume(0.15f);
	_mResultAudios.emplace("Decision", decision);

	_mResultAudios["BGM"]->Play(true);
}

void ResultManager::Finalize()
{
	GameObject::Finalize();
}

void ResultManager::Update(double deltaTime)
{
	auto& directionTimer = Result::GetGameObject<ResultScore>()->GetDirectionTimer();

	// スコア表示演出が終わったら操作可能にする
	if (directionTimer.IsTimeUp()) {
		mResultItem = 0;
		Result::GetGameObject<ResultMenu>()->SetEaseTimer(0.25);
	}

	// 上下キーで項目選択
	if (!Transition::getInstance().GetTransitionActive()) {
		if (Input::GetKeyTrigger(VK_UP) && mResultItem == 1) {
			_mResultAudios["Cursor"]->Play();
			Result::GetGameObject<ResultMenu>()->SetEaseTimer(0.25);
			mResultItem = 0;
		}
		if (Input::GetKeyTrigger(VK_DOWN) && mResultItem == 0) {
			_mResultAudios["Cursor"]->Play();
			Result::GetGameObject<ResultMenu>()->SetEaseTimer(0.25);
			mResultItem = 1;
		}
	}

	bool isInput = false;

	// 決定
	if (Input::GetKeyTrigger('Z')) {
		isInput = true;

		if (mResultItem == 0) {
			_mResultAudios["Decision"]->Play();
		}
		else if (mResultItem == 1) {
			_mResultAudios["GameStart"]->Play();
		}
	}

	// シーン遷移処理
	if (!Transition::getInstance().GetTransitionActive() && isInput) {
		Transition::getInstance().Start(1.0, false);
		mTransitionWait = true;
	}

	if (mTransitionWait && !Transition::getInstance().GetTransitionActive()) {
		mTransitionWait = false;

		if (mResultItem == 0) {
			SceneManager::getInstance().SceneChange<Title>();
		}
		else if (mResultItem == 1) {
			SceneManager::getInstance().SceneChange<Game>();
		}
	}

	// BGMのフェードアウト処理
	if (mTransitionWait) {
		float volume = mBGMVolume * Transition::getInstance().GetTransitionProgress();
		_mResultAudios["BGM"]->SetVolume(volume);
	}

	GameObject::Update(deltaTime);
}

void ResultManager::Draw() const
{
	GameObject::Draw();
}

void ResultManager::AudioPlay(std::string key)
{
	// キーから登録オーディオを検索して再生する
	auto it = _mResultAudios.find(key);

	if (it != _mResultAudios.end()) {
		_mResultAudios[key]->Play();
	}
}