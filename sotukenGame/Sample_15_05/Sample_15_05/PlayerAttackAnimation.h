#pragma once
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
class Player;
class PlayerAnimation;
class PlayerAttackAnimation : public IGameObject
{
public:
	PlayerAttackAnimation();
	~PlayerAttackAnimation();
	/// <summary>
	/// �U���A�j���[�V�����̎��Ԃ�ݒ�B
	/// </summary>
	void SetAttackAnimationTime();
	/// <summary>
	/// �ʏ�U���B
	/// </summary>
	void NormalAttack();
	/// <summary>
	/// �u���C�h��Ԃ̓���U���B
	/// </summary>
	void SpecialAttackStateBlad();
	/// <summary>
	/// �\�[�h��Ԃ̓���U���B
	/// </summary>
	void SpecialAttackStateSword();
	/// <summary>
	/// ����U���̏I���B
	/// </summary>
	void SpecialAttackEnd();
	void AttackFlag(int attackTime01_blad, int* attackAnimNum, int attackTime01_sword);
	/// �U���I���֐��B
	/// </summary>
	void AttackEnd();
	/// <summary>
	/// �U���B
	/// </summary>
	void Attack();

	bool Start() override;

	void Update() override;

	/// <summary>
	/// �U���ԍ���Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetAttackNum() const
	{
		return m_attackNum;
	}
private:
	Player* m_player = nullptr;
	PlayerAnimation* m_playerAnim = nullptr;
	int attackTimer = 0;
	int m_attackAnimNum = 0; //X�{�^����Y�{�^���̍U���A�j���[�V�����̐��B
	int m_attackAnimationTimeNum = 0; //�U���A�j���[�V�����̎��Ԃ���ꂽ�z��̔ԍ��B
	int m_totalAttackAnimationTime = 0; //�U���A�j���[�V�����̍��v�̎��ԁB
	int m_continuousAttackTime = 0;  //�A������ۂ̃A�j���[�V�����̍��v�̎��ԁB
	int m_attackNum = 0; //�U���ԍ��B
	int m_attackAnimationTime[enAttackTimeNum];//�U���A�j���[�V�����̎��Ԃ�ݒ肷��z��B
	int m_switchAttackTime[enAttackTimeNum];//�U���̐؂�ւ��̎��Ԃ�ݒ肷��z��B
	bool m_specialAttackStartFlag = false;//����U���̃X�^�[�g�t���O�B
	float m_speed = 50.0f;
	int m_timer = 0;
	
};

