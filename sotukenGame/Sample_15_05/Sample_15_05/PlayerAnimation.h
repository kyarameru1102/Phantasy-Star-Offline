#pragma once
const enum PlayerAnim {
	enStay_blad,            //�u���C�h��ԁB
	enStay_sword,            //�\�[�h��ԁB
	enWalk_blad,           //�u���C�h��Ԃŕ����B
	enWalk_sword,           //�\�[�h��Ԃŕ����B
	enRun_blad,            //�u���C�h��Ԃő���B
	enRun_sword,            //�\�[�h��Ԃő���B
	enJumpStart_blad,       //�u���C�h��ԂŃW�����v����B
	enJumpStart_sword,      //�\�[�h��ԂŃW�����v����B
	enStayInTheAir_blad,   //�u���C�h��Ԃő؋�B
	enStayInTheAir_sword,  //�\�[�h��Ԃő؋�B
	enChange_blad,          //�u���C�h����\�[�h�ɕύX�B
	enChange_sword,         //�\�[�h����u���C�h�ɕύX�B
	enAttack01_blad,         //�u���C�h��Ԃ̍U��1
	enAttack01_sword,        //�\�[�h��Ԃ̍U��1
	enAttack02_blad,         //�u���C�h��Ԃ̍U��2
	enAttack02_sword,         //�\�[�h��Ԃ̍U��2
	enAttack03_blad,         //�u���C�h��Ԃ̍U��3
	enAttack03_sword,         //�\�[�h��Ԃ̍U��3
	enAttack04_blad,         //�u���C�h��Ԃ̍U��4
	enAttack04_sword,         //�\�[�h��Ԃ̍U��4
	enAttack05_blad,         //�u���C�h��Ԃ̍U��5
	enAttack05_sword,         //�\�[�h��Ԃ̍U��5
	enAttack06_blad,         //�u���C�h��Ԃ̍U��6
	enAttack06_sword,         //�\�[�h��Ԃ̍U��6
	enAttack07_blad,         //�u���C�h��Ԃ̍U��7
	enAttack07_sword,         //�\�[�h��Ԃ̍U��7
	enAttack08_blad,         //�u���C�h��Ԃ̍U��8
	enAttack08_sword,         //�\�[�h��Ԃ̍U��8
	enAttack09_blad,         //�u���C�h��Ԃ̍U��9
	enAttack09_sword,         //�\�[�h��Ԃ̍U��9
	enAnimationClipNum, //�A�j���[�V�����N���b�v�̐��B
};
const enum AttackAnimTime {
	enAttackTime01_blad,
	enAttackTime02_blad,
	enAttackTime03_blad,
	enAttackTime04_blad,
	enAttackTime05_blad,
	enAttackTime06_blad,
	enAttackTime07_blad,
	enAttackTime08_blad,
	enAttackTime09_blad,
	enAttackTime01_sword,
	enAttackTime02_sword,
	enAttackTime03_sword,
	enAttackTime04_sword,
	enAttackTime05_sword,
	enAttackTime06_sword,
	enAttackTime07_sword,
	enAttackTime08_sword,
	enAttackTime09_sword,
	enAttackTimeNum
};
class PlayerAnimation : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	PlayerAnimation();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PlayerAnimation();
	/// <summary>
	/// �U���A�j���[�V�����̎��Ԃ�ݒ�B
	/// </summary>
	void SetAttackAnimationTime();
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
	int* GetAttackAnimationTime()
	{
		return m_attackAnimationTime;
	}
private:
	int m_attackAnimationTime[enAttackTimeNum];//�U���A�j���[�V�����̎��Ԃ�ݒ肷��z��B
	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
};