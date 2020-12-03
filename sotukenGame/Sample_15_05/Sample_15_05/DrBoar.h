#pragma once
/// <summary>
/// �h���S���{�A�N���X
/// </summary>
class Player;
class DrBoar : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DrBoar();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DrBoar();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	/// <returns></returns>
	void Update();

	void Move();
	void Turn();

	/// <summary>
	/// �v���C���[�̍��W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	enum EnAnimationClip {
		enIdle,
		enWalk,
		enRun,
		enScream,
		enAttack,
		enHornattack,
		enGethit,
		enDie,
		enAnimationClip_num
	};

	SkinModelRender* m_DrBoarSkinModel = nullptr;
	Vector3 m_position = Vector3::Zero;  //���W
	Vector3 m_scale = Vector3::One;      //�g�嗦
	Quaternion m_rotation = Quaternion::Identity; //��]
	Vector3 m_movespeed = Vector3::Zero;  //�ړ����x
	int changeTimer = 0;       //�A�j���[�V�����ύX�^�C�}�[
	int m_animState = enIdle; //�A�j���[�V�����̏�ԁB
	AnimationClip m_animationClip[enAnimationClip_num];

	Player* m_player = nullptr;
};

