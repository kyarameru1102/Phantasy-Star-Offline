#pragma once
#include "Player.h"
#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
/// <summary>
/// 敵テストクラス
/// </summary>
class Player;
class EnTest : public IGameObject
{
public:
	EnTest();
	~EnTest();
	bool Start() override;
	void Update() override;
	
	void Move();
	void Turn();
	void Attack();
private:
	enum {
		Idle_state,
		Attack_state
	};
	int m_status = Attack_state;    //状態
	SkinModelRender* m_EnTestSkinModel = nullptr;
	Quaternion m_rotation = Quaternion::Identity;
	Quaternion m_addrot = Quaternion::Identity;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_movespeed = Vector3::Zero;
	//Vector3 playerLen = Vector3::Zero;
	
	int changeTimer = 0;
	int turntimer = 0;
	int turntimer2 = 0;
	float m_speedY = 0.0f;//Y方向のスピード。
	bool turnflag = false;
	
	int m_animState = enIdle; //アニメーションの状態。
	
	int m_appearcolor = 0;
	Player* m_player = nullptr;
	CharacterController m_charaCon;//キャラコン。
	EnemyAnimation* m_enemyAnim = nullptr;
	std::vector<int> boarcolor = { 1,2,3,4 };
};

