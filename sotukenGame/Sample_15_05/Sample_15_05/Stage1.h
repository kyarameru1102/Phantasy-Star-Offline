#pragma once
#include "Game.h"
#include "BackGround.h"
#include "DrBoar.h"
#include "Title.h"

class Stage1 : public IGameObject
{
public:
	Stage1();
	~Stage1();

	/// <summary>
	/// �X�V�֐����Ă΂��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start()override;

	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update()override;

private:
	enum {
		ENEMY_NUM = 2		//�G�l�~�[�̐��B
	};

	Game* m_game = nullptr;
	BackGround* m_backGround = nullptr;				//�X�e�[�W�̃C���X�^���X�B
	DrBoar* m_drBoar[ENEMY_NUM] = { nullptr };		//�h���S���{�A(�G)�̃C���X�^���X�B
	Title* m_title = nullptr;						//�^�C�g���̃C���X�^���X�B

	int m_downEnemy = 0;	//�|�����G�l�~�[�̐��B
	int m_timer = 0;		//�^�C�}�[�B
};

