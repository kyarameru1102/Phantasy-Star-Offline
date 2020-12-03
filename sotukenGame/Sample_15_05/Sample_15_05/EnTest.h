#pragma once
#include "Player.h"
/// <summary>
/// �G�e�X�g�N���X
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
	enum EnAnimationClip {
		enIdle,
		enWalk,
		enRun,
		enScream,
		enAttack,
		enHornattack,
		enGethit,
		enDie,
		enAnimationClip_num
	};
	int changeTimer = 0;
	int turntimer = 0;
	int turntimer2 = 0;
	bool turnflag = false;
	
	int m_animState = enIdle; //�A�j���[�V�����̏�ԁB
	AnimationClip m_animationClip[enAnimationClip_num];

	Player* m_player = nullptr;
};

