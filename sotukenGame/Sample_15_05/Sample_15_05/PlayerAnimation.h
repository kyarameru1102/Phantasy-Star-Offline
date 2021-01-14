#pragma once
//����U���̃A�j���[�V�����͕������Ă邩��A
//enSpecialAttack_01����enSpecialAttack_03��1�̍U���B
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
	enKaihi_blad,           //�u���C�h��Ԃŉ���B
	enKaihi_sword,          //�\�[�h��Ԃŉ���B
	enHit_blad,           //�u���C�h��Ԃŋ��ށB
	enHit_sword,          //�\�[�h��Ԃŋ��ށB
	enDeath_blad,         //�u���C�h��ԂŎ��S�B
	enDeath_sword,         //�\�[�h��ԂŎ��S�B
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
	enSpecialAttack_01_blad,
	enSpecialAttack_01_sword,
	enSpecialAttack_02_blad,
	enSpecialAttack_02_sword,
	enSpecialAttack_03_blad,
	enSpecialAttack_03_sword,
	enAnimationClipNum, //�A�j���[�V�����N���b�v�̐��B
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
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;

	void InitAnimation();
	
	/// <summary>
	/// �A�j���[�V�����N���b�v��Ԃ��B
	/// </summary>
	/// <returns></returns>
	AnimationClip* GetAnimationClip()
	{
		return animClip;
	}
	/// <summary>
	/// �U���A�j���[�V�����̎��Ԃ�ݒ肷��z���Ԃ��B
	/// </summary>
	/// <returns></returns>
private:
	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
};