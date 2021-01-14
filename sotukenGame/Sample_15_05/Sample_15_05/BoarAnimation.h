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
	enBoarAnimClip_num        //�A�j���[�V�����N���b�v�̐�
};

class BoarAnimation : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	BoarAnimation();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~BoarAnimation();
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
	AnimationClip animClip[enBoarAnimClip_num];//�A�j���[�V�����N���b�v�B
};



