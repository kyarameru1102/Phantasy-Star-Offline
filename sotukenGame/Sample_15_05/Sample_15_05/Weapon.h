#pragma once
#include "Player.h"
#include "DrBoar.h"
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
	/// <summary>
	/// ����ɉe����^����{�[���̔ԍ��B
	/// </summary>
	/// <param name="boneNo">�ԍ��B</param>
	void SetBoneNum(int boneNo)
	{
		m_boneNum = boneNo;
	}
private:
	Player* m_player = nullptr; //�v���C���[�̃C���X�^���X�B
	DrBoar* m_drBoar = nullptr; //�G�̃C���X�^���X�B
	SkinModelRender* m_skimModelRender = nullptr; //�X�L�����f�������_�[�B
	Vector3 m_position = Vector3::Zero;//���W�B
	Quaternion m_rotation = Quaternion::Identity;//��]
	int m_boneNum = 0; //�{�[���̔ԍ��B
	Vector3 m_scale = Vector3::Zero; //�X�P�[���B
};