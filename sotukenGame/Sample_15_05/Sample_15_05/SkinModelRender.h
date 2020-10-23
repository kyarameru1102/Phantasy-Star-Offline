#pragma once
#include "GameObject.h"

/// <summary>
/// �X�L�����f�������_�[�B
/// </summary>
/// ���f����\�����₷������N���X�B
/// GameObject���p�����Ă��邩��NewGO�ŃC���X�^���X���쐬����K�v������您�������B
class SkinModelRender : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	SkinModelRender();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~SkinModelRender();
	/// <summary>
	/// �������֐��B
	/// </summary>
	/// <param name="tkm">tkm�t�@�C��</param>
	/// <param name="fx">�g�p����V�F�[�_�[</param>
	/// �V�F�[�_�[�������ւ������ꍇ�̂ݑ�������ύX���Ă��������B
	/// �V�F�[�_�[��ς���C���Ȃ��̂ł���Α������͂�����Ȃ��Ă����B
	void Init(const char *tkm,const char *fx = "Assets/shader/model.fx");
	/// <summary>
	/// ���f����\��������W��ݒ肷��֐��B
	/// </summary>
	/// <param name="position">Vector3 position</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// �����Ă��������ݒ肷��֐��B
	/// </summary>
	/// <param name="rotation">Quaternion rotation</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �傫����ݒ肷��֐��B
	/// </summary>
	/// <param name="scale">Vector3 scale</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ���f���������_�����O���邩�ǂ����̊֐��B
	/// </summary>
	/// <param name="on">true �����_�����O����B
	/// false �����_�����O���Ȃ��B</param>
	/// �v����ɂ��̊֐��̈�����false�������SkinModelRender�̃C���X�^���X���B
	/// �f���[�g���邱�ƂȂ����f�����������Ƃ��ł���B
	/// �K�v�ɉ����Ďg���Ă���āB
	void SetRenderOn(bool on)
	{
		m_renderOn = on;
	}
private:
	/// <summary>
	/// �J�n�֐��B
	/// </summary>
	/// <returns>true</returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`��֐��B
	/// </summary>
	void Render() override;
private:
	ModelInitData	m_modelInitData;						//�������p�f�[�^�B
	Model			m_model;								//���f���B
	Vector3			m_position = Vector3::Zero;				//���W�B
	Quaternion		m_rotation = Quaternion::Identity;		//��]�B
	Vector3			m_scale = Vector3::One;					//�g�嗦�B
	bool			m_renderOn = true;						//�`�悳��邩�ǂ����B
	bool            m_renderOK = false;						//Update�̌�Ƀ����_�[���Ă΂��悤�ɂ���t���O�B
};

