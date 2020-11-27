#pragma once
#include "Title.h"

/// <summary>
/// ���j���[��ʃN���X
/// </summary>
class Menu : public IGameObject
{
public:
	Menu();
	~Menu();

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
	const enum {
		en_menuUIMenu,				//���j���[��ʂ�UI�B
		en_menuUIArrowButton,		//����UI�B
		en_menuUIReturnTitle,		//�^�C�g���ɖ߂镶����UI�B
		en_menuUIStatusMoji,		//�X�e�[�^�X������UI�B
		en_menuUINum				//���j���[UI�̐��B
	};

	SpriteRender* m_spriteRender[en_menuUINum] = { nullptr };		//�X�v���C�g�����_�[�B
	Vector3 m_spritePosition[en_menuUINum] = { Vector3::Zero };		//�X�v���C�g�̍��W�B

	Title* m_title = nullptr;
};

