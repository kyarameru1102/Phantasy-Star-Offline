#pragma once
const enum NightmareAnim {
	enIdle01,               //�ҋ@�P
	enIdle02,               //�ҋ@�Q
	enWalk,                 //����
	enWalkBack,             //������
	enWalkLeft,             //������
	enWalkRight,            //�E����
	enRun,                  //����
	enScream,               //���K
	enJump,                 //�W�����v
	enBasicAttack,          //�ʏ�U��
	enClawAttack,            //�܍U��
	enHornAttack,            //�p�U��
	enGetHit,                //��_��
	enDefend,                //�h��
	enSleep,                 //����
	enDie,                   //���S
	enNightmareAnimClip_num  //�A�j���[�V�����N���b�v�̐�
};

class NightmareAnimation : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	NightmareAnimation();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~NightmareAnimation();
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
	AnimationClip animClip[enNightmareAnimClip_num];//�A�j���[�V�����N���b�v�B

};



