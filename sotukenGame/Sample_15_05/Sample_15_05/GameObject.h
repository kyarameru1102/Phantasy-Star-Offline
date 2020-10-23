#pragma once
class GameObjectManager;

/// <summary>
/// �Q�[���I�u�W�F�N�g�B
/// </summary>
/// NewGO���������̂͂�����p�����Ă���āB
class IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	IGameObject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~IGameObject() {};
	/// <summary>
	/// Update�̒��O�ɌĂ΂��J�n�����B
	/// </summary>
	/// <returns>
	/// Start�֐���true��Ԃ���Update���Ă΂ꂾ���B
	/// </returns>
	virtual bool Start() { return true; }
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() {}
	/// <summary>
	/// �폜�����Ƃ��ɌĂ΂��֐��B
	/// </summary>
	/// ���̊֐���DeleteGO���ꂽ���ɂ����ɌĂ΂���B
	/// DeleteGO�ŏ������t���[���ŌĂ΂�邩��f�X�g���N�^��葁���Ă΂���[�B
	/// �K�v�ɉ����Ďg���Ă���āB
	virtual void OnDestroy() {}
	///////////////////////////////////////////////////////////////////
	//�������牺�͑����g��Ȃ����ȁB
	/// <summary>
	/// �`��֐��B
	/// </summary>
	virtual void Render() {}
	/// <summary>
	/// 2D�p�̕`��֐��B
	/// </summary>
	virtual void Render2D() {}
	/// <summary>
	/// �t�H���g�p�̕`��֐��B
	/// </summary>
	virtual void RenderFont() {}
	///////////////////////////////////////////////////////////////////
	//�������牺�͌Ă΂Ȃ��ŁB
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�Ŏg���Ă邩�炢����񂶂�˂������B
	/// /// <summary>
	/// �D��x���擾�B
	/// </summary>
	unsigned char GetPriority() const
	{
		return m_priority;
	}
	/// <summary>
	/// m_isStart��true�������֐��B
	/// </summary>	
	void StartCallEnd()
	{
		m_isStart = true;
	}
	/// <summary>
	/// m_isStart��true��false����Ԃ��֐��B
	/// </summary>
	bool GetStart()
	{
		return m_isStart;
	}
	/// <summary>
	/// �D��x��ݒ肷��֐��B
	/// </summary>
	void SetPriority(unsigned char prio)
	{
		m_priority = prio;
	}
	/// <summary>
	/// ���O�L�[��ݒ肷��֐��B
	/// </summary>
	void SetNameKey(unsigned int nK)
	{
		m_nameKey = nK;
	}
	/// <summary>
	/// ���S�t���O�𗧂Ă�֐��B
	/// </summary>
	void SetIsDead()
	{
		m_isDead = true;
	}
	/// <summary>
	/// ����ł܂����H
	/// </summary>
	bool GetIsDead()
	{
		return m_isDead;
	}
	friend class GameObjectManager;
protected:
	unsigned char	m_priority;					//�D��x�B
	bool			m_isStart = false;			//Start�֐����Ă΂ꂽ���H
	unsigned int	m_nameKey = 0;				//���O�L�[�B
	bool			m_isDead = false;			//���S�t���O�B
};

