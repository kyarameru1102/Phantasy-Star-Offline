#pragma once
class Player;
#include "Player.h"
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameCamera();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameCamera();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// ���W��Ԃ��B
	/// </summary>
	const Vector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �J�����̃^�[�Q�b�g��Ԃ��B
	/// </summary>
	const Vector3 GetTarget()
	{
		return m_target;
	}
	void ResetToPlayerVec()
	{
		m_toPlayerVec = { 0.0f, 200.0f, 400.0f };
	}
private:
	Player* m_player = nullptr;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_target = Vector3::Zero;
	Vector3 m_toPlayerVec = { 0.0f, 200.0f, 400.0f };//�J��������v���C���[�Ɍ������ĐL�т�x�N�g���B
	float m_angleAxisX = 0.0f;//X����]�̊p�x�B
	float m_angleAxisY = 0.0f;//Y����]�̊p�x�B

};

