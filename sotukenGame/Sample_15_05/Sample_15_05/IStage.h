#pragma once
#include "GameObject.h"

class BackGround;
class Player;
class GameCamera;
class IStage : public IGameObject
{
public:
	/// <summary>
	/// �X�V�֐����Ă΂��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	virtual bool Start()override { return 0; };

	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update()override {};
	bool GetsceanChangeOK() const
	{
		return m_sceanChangeOK;
	}
protected:
	BackGround* m_backGround = nullptr;				//�X�e�[�W�̃C���X�^���X�B
	//Player* m_player = nullptr;
	//GameCamera* m_gameCam = nullptr;
	int m_downEnemy = 0;	//�|�����G�l�~�[�̐��B
	int m_timer = 0;		//�^�C�}�[�B
	bool m_sceanChangeOK = false;	//�V�[����؂�ւ��Ă������ǂ����̃t���O�B
};

