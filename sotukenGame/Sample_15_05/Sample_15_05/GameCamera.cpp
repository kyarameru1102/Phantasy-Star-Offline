#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}

void GameCamera::Update()
{
	m_position = m_player->GetPosition() + m_toPlayerVec;

	//�J�����̃^�[�Q�b�g���v���C���[�ɌŒ肷��B
	m_traget = m_player->GetPosition();
	//���W��ݒ�B
	g_camera3D->SetPosition(m_position);
	//�^�[�Q�b�g��ݒ�B
	g_camera3D->SetTarget(m_traget);
}