#pragma once
const enum BoarAnim {
	enIdle,                    //�ҋ@
	enWalk,                    //����
	enRun,                     //����
	enScream,                  //���K
	enAttack,                  //�U��
	enHornattack,              //�p�U��
	enGethit,                  //��_��
	enDie,                     //���S
	enAnimationClip_num        //�A�j���[�V�����N���b�v�̐�
};
class EnemyAnimation : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EnemyAnimation();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnemyAnimation();
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
	/// �A�j���[�V�����N���b�v��Ԃ��B
	/// </summary>
	/// <returns></returns>
	AnimationClip* GetAnimationClip()
	{
		return animClip;
	}
private:
	AnimationClip animClip[enAnimationClip_num];//�A�j���[�V�����N���b�v�B
};

