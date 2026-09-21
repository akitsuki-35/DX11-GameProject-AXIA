/*============================================================
*	@file	 : GameTitle.h
*	@brief	 : ゲームタイトル表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/14
*	@updated : 2026/09/17
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: GameTitle
*	@brief	: ゲームタイトル表示
*============================================================*/
class GameTitle : public GameObject
{
public:
	GameTitle() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};