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
	Vector3 toPlayerVecOld = m_toPlayerVec;
	//�J�����̍��W�Ƀv���C���[�̍��W�����B
	m_position = m_player->GetPosition();
	//Y����]�̊p�x���X�V�B
	m_angleAxisY = g_pad[0]->GetRStickXF() * 2.0f;
	//X����]�̊p�x���X�V�B
	m_angleAxisX = g_pad[0]->GetRStickYF() * 2.0f;

	//Y����]���J��������v���C���[�Ɍ������ĐL�т�x�N�g���ɓK��������B
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisY, m_angleAxisY);
	rot.Apply(m_toPlayerVec);

	//Y����m_toPlayerVec�̊O�ς����߂�X�����v�Z����B
	Vector3 AxisX = Vector3::AxisY;
	AxisX.Cross(m_toPlayerVec);
	AxisX.Normalize();
	//X����]���J��������v���C���[�Ɍ������ĐL�т�x�N�g���ɓK��������B
	rot = Quaternion::Identity;
	rot.SetRotationDeg(AxisX, m_angleAxisX);
	rot.Apply(m_toPlayerVec);
	Vector3 toPosDir = m_toPlayerVec;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		m_toPlayerVec = toPlayerVecOld;
	}
	if (toPosDir.y > 0.8f) {
		m_toPlayerVec = toPlayerVecOld;
	}
	//�^�[�Q�b�g���v���C���[�ɂ���B
	m_target = m_player->GetPosition();
	//�^�[�Q�b�g��ݒ�B
	g_camera3D->SetTarget(m_target);
	//���W���X�V�B
	m_position = m_target + m_toPlayerVec;
	//���W��ݒ�B
	g_camera3D->SetPosition(m_position);
	
}