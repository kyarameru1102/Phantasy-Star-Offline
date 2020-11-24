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
	/// <summary>
	/// �A�j���[�V�����N���b�v��Ԃ��B
	/// </summary>
	/// <returns></returns>
	AnimationClip* GetAnimationClip()
	{
		return animClip;
	}
private:

	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
};