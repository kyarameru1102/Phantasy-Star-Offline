#pragma once
#include "Player.h"

/// <summary>
/// �v���C���[�̃X�e�[�^�X�N���X�B
/// </summary>
class PlayerStatus : public IGameObject
{
public:
	PlayerStatus();
	~PlayerStatus();

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
	Player* m_player = nullptr;					//�v���C���[�̃C���X�^���X�B
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[�B
};