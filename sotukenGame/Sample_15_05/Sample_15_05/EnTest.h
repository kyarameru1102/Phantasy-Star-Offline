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
private:
	SkinModelRender* m_EnTestSkinModel = nullptr;
	Quaternion m_rotation = Quaternion::Identity;
	Quaternion m_addrot = Quaternion::Identity;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_movespeed = Vector3::Zero;
	//Vector3 playerLen = Vector3::Zero;
	/*enum EnAnimationClip {
		enIdle,
		enWalk,
		enRun,
		enScream,
		enAttack,
		enHornattack,
		enGethit,
		enDie,
		enAnimationClip_num
	};*/
	int changeTimer = 0;
	int turntimer = 0;
	int turntimer2 = 0;
	float m_speedY = 0.0f;//Y方向のスピード。
	bool turnflag = false;
	
	int m_animState = enIdle; //アニメーションの状態。
	//AnimationClip m_animationClip[enAnimationClip_num];

	Player* m_player = nullptr;
	CharacterController m_charaCon;//キャラコン。
	EnemyAnimation* m_enemyAnim = nullptr;
};

