#pragma once
#include "GameObject.h"


class SpriteRender : public IGameObject
{
public:
	/// <summary>
	/// �������֐��B
	/// </summary>
	/// <param name="dds">dds�t�@�C���̃t�@�C���p�X</param>
	/// <param name="height">����</param>
	/// <param name="width">��</param>
	/// <param name="fx">�g�p����V�F�[�_�[�̃t�@�C���p�X</param>
	/// ��4�����̓V�F�[�_�[��ύX���Ȃ��ꍇ�����Ȃ��Ă悢�B
	void Init(const char* dds,float height, float width, const char* fx = "Assets/shader/sprite.fx");
	/// <summary>
	/// sprite��\��������W��ݒ肷��֐��B
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
	/// �s�{�b�g��ݒ肷��֐��B
	/// </summary>
	/// <param name="pivot">Vector2 pivot</param>
	void SetPivot(const Vector2& pivot)
	{
		m_pivot = pivot;
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
	void Render2D() override;
private:
	SpriteInitData		m_spriteInitData;
	Sprite				m_sprite;
	Vector3				m_position = Vector3::Zero;
	Quaternion			m_rotation = Quaternion::Identity;
	Vector3				m_scale = Vector3::One;
	Vector2				m_pivot = { 0.5f, 0.5f };
};

