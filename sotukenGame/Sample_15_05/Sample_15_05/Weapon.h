#pragma once
#include "Player.h"
class Weapon : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Weapon();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Weapon();
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
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ肷��B
	/// </summary>
	/// <param name="rot"></param>
	void SetRtation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
private:
	Player* m_player = nullptr; //�v���C���[�̃C���X�^���X�B
	SkinModelRender* m_skimModelRender = nullptr; //�X�L�����f�������_�[�B
	Vector3 m_position = Vector3::Zero;//���W�B
	Quaternion m_rotation = Quaternion::Identity;//��]�B
};