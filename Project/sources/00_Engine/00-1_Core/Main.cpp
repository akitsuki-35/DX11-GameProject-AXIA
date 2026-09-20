/*============================================================
*	@file	 : Main.cpp
*	@brief	 : メイン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/09/20
*============================================================*/
// System
#include "SystemWindow.h"
#include "SystemTimer.h"
#include "AppLoop.h"

#include "ShaderManager.h"
#include "FontManager.h"
#include "FontLoader.h"
#include "Graphics.h"
#include "Transition.h"
#include "Input.h"
#include "AudioPlayer.h"

#include "Application.h"
#include "Title.h"
#include <memory>
#include <d3d11.h>

// フォントロード
// ゲーム起動時に一度だけ呼ぶ
namespace FontSet {
	inline void initialize() {
		FontManager::getInstance().Register("Kaisotai", "assets\\fonts\\Kaisotai-Next-UP-B.ttf");
	}
}

// シェーダー登録
// ゲーム起動時に1度だけ呼ぶ
namespace ShaderSet {
	inline void initialize() {
		ShaderManager::getInstance().Register("UI",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\UnlitPS.cso");

		ShaderManager::getInstance().Register("Font",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\FontPS.cso");

		ShaderManager::getInstance().Register("Unlit",
			"assets\\shaders\\UnlitVS.cso", "assets\\shaders\\UnlitPS.cso");

		ShaderManager::getInstance().Register("PBR",
			"assets\\shaders\\PhongVS.cso", "assets\\shaders\\PBRPS.cso");
	}
}



/*------------------------------------------------------------
	メイン
------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 未使用パラメータ明示（警告を消去）
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// DPIスケーリング対策
	SetProcessDPIAware();

	// ウィンドウ初期化
	System::Window::getInstance().Initialize(hInstance);

	// 各種初期化
	D3D11::Graphics::getInstance().Initialize();

	// シェーダー読み込み
	ShaderSet::initialize();
	FontSet::initialize();

	Transition::getInstance().Initialize("assets\\textures\\white.png", "UI");
	Input::Initialize();
	AudioPlayer::InitializeMaster();

	// 初期シーン設定
	Application::getInstance().Initialize(std::make_unique<Title>());

	// ウィンドウ表示
	System::Window::getInstance().Show(nCmdShow);

	// タイマー初期化
	System::Timer::getInstance().Initialize();

	// ゲームループ
	int isQuit = AppLoop::getInstance().Run();

	timeEndPeriod(1);

	Application::getInstance().Finalize();

	AudioPlayer::FinalizeMaster();
	Input::Finalize();
	D3D11::Graphics::getInstance().Finalize();

	return isQuit;
}