#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "PlayerStatusUI.h"
const float MAX_SPEED_Y = 40.0f; //Y�����̃X�s�[�h�̍ő�l�B
const float FLAME_NUM = 30.0f;  //�t���[�����B
const float FLUCTUATION_VALUE_Y = MAX_SPEED_Y / FLAME_NUM; //Y�����̃X�s�[�h�̕ϓ��l�B
                                                           //Y�����̃X�s�[�h�̍ő�l���t���[�����Ŋ����āA
                                                           //1�t���[��������̕ϓ��l�����߂�B
const float MAX_ANGLE = 360.0f;//�ő�̊p�x�B
const float HALF_ANGLE = 180.0f;//�����̊p�x�B
const float ROTATION_AMOUNT = 10.0f;//��]�ʁB
Player::Player()
{
}
Player::~Player()
{
	if (m_playerSkinModel != nullptr) {
		DeleteGO(m_playerSkinModel);
	}
	if (m_weapon[0] != nullptr) {
		DeleteGO(m_weapon[0]);
	}
	if (m_weapon[1] != nullptr) {
		DeleteGO(m_weapon[1]);
	}
	if (m_playerStatusUI != nullptr) {
		DeleteGO(m_playerStatusUI);
	}
	if (m_playerAnim != nullptr) {
		DeleteGO(m_playerAnim);
	}
}
void Player::GetExperiencePoint(const float experiencePoint)
{
	//�o���l�ɓ|�����G�̌o���l�����Z����B
	m_experiencePoint += experiencePoint;
	//���ɕK�v�Ȍo���l��荡�̌o���l�������Ԃ̓��x�������Z����B
	while (m_experiencePoint >= m_nextExperiencePoint)
	{
		//���x�������Z�B
		m_playerLevel++;
		//���ɕK�v�ȃ��x����1.1�{�ɑ��₷�B
		m_nextExperiencePoint *= 1.1f;
		if (m_playerLevel > 1) {
			ATTACK_ANIM_NUM_X = 4;
			ATTACK_ANIM_NUM_Y = 3;
		}
	}
}
void Player::AttackFlag(int attackTime01_blad, int attackAnimNum, int attackTime01_sword)
{
	m_attackAnimationFlag = true;
	if (attackTimer <= 0) {
		//�U���^�C����0�ȉ��B
		m_attackAnimationTimeNum = attackTime01_blad;
		m_attackAnimNum = attackAnimNum;
		if (m_weaponState == enSwordState) {
			//�\�[�h���
			m_attackAnimationTimeNum = attackTime01_sword;
		}
		//�^�C���ɍŏ��̍U�����Ԃ�����B
		m_totalAttackAnimationTime = m_playerAnim->GetAttackAnimationTime()[m_attackAnimationTimeNum];
		//�A���^�C���Ƀ^�C��������B
		m_continuousAttackTime = m_totalAttackAnimationTime;
		//�A���^�C������50�����B
		m_continuousAttackTime = m_playerAnim->GetSwitchAttackTime()[m_attackAnimationTimeNum];

		m_attackFlag = true;
	}
	if (attackTimer >= m_continuousAttackTime && m_attackNum < m_attackAnimNum) {
		//�A���^�C���ȍ~
		m_attackNum++;
		m_attackAnimationTimeNum++;
		//�U���A�j���[�V�����̍��v���ԂɎ��̍U���A�j���[�V�����̎��Ԃ����Z����B
		m_totalAttackAnimationTime = attackTimer + m_playerAnim->GetAttackAnimationTime()[m_attackAnimationTimeNum];
		m_continuousAttackTime = attackTimer + m_playerAnim->GetSwitchAttackTime()[m_attackAnimationTimeNum];;
		//�t���O�𗧂ĂāA���̎��͍U�����ł�������ς����悤�ɂ���B
		m_attackAngleFlag = false;

		//m_attackFlag = true;
	}
}
void Player::AttackEnd()
{
	if (m_attackAnimationTimeNum == enAttackTime09_blad ||
		m_attackAnimationTimeNum == enAttackTime09_sword) {
		//����`�F���W�̍U���A�j���[�V�����������B
		//����̏�Ԃ�ύX����B
		if (m_weaponState == enBladState) {
			m_weaponState = enSwordState;
		}
		else if (m_weaponState == enSwordState) {
			m_weaponState = enBladState;
		}
	}
	m_attackAnimationFlag = false;
	attackTimer = 0;
	m_attackNum = 0;
	m_totalAttackAnimationTime = 0;
	m_animState = enStay_blad;
	m_attackAngleFlag = false;
}
void Player::Attack()
{
	if (m_attackAnimationFlag != false) {
		m_attackAngleFlag = true;
		if (attackTimer >= m_continuousAttackTime) {
			m_moveSpeed = Vector3::Zero;

			m_attackFlag = false;
		}
		else {
			m_moveSpeed = m_dir * 5.0f;
			m_attackFlag = true;
		}
		//�U���^�C�}�[�����Z�B
		attackTimer++;
		//X�{�^����Y�{�^���ŏ����U���A�j���[�V���������߂�B
		if (m_attackAnimNum == ATTACK_ANIM_NUM_X) {
			m_animState = enAttack01_blad;
		}
		else {
			m_animState = enAttack06_blad;
		}
		//m_attackNum�~2�����Z�����ԍ��̃A�j���[�V�����𗬂��B
		m_animState += m_attackNum * 2;
		if (attackTimer > m_totalAttackAnimationTime) {
			//�U���A�j���[�V�����I���B
			AttackEnd();
		}
	}
}

void Player::YDirMove()
{
	if (m_charaCon.IsOnGround() != false) {
		//�n�ʂ̏�ɂ���B
		if (g_pad[0]->IsTrigger(enButtonA) && m_doNothingFlag != true) {
			//A�{�^�����������B
			//�U���A�j���[�V���������Ă�����A�~�߂�B
			if (m_attackAnimationFlag != false) {
				m_attackAnimationFlag = false;
				AttackEnd();
			}
			//�W�����v�t���O�𗧂Ă�B
			m_jumpFlag = true;
			//Y�X�s�[�h���ő�l�ɂ���B
			m_speedY = MAX_SPEED_Y;
			jumpStartTimer = 0;
			m_doNothingFlag = true;
		}
		else {
			//�t���O�������B
			m_jumpFlag = false;
			//Y�X�s�[�h��0�ɂ���B
			m_speedY = 0.0f;
		}
	}
	if (m_jumpFlag != false) {
		//�W�����v�������A�A�j���[�V�����𗬂��B
		jumpStartTimer++;
		if (jumpStartTimer <= 40) {
			m_animState = enJumpStart_blad;
		}
	}
	if (m_charaCon.IsOnGround() != true) {
		//�W�����v���Ă���܂��́A�������Ă���B
		m_speedY -= FLUCTUATION_VALUE_Y;
		m_doNothingFlag = true;
		if (jumpStartTimer >= 40) {
			m_animState = enStayInTheAir_blad;
		}
	}

	if (m_speedY <= -MAX_SPEED_Y) {
		//Y�X�s�[�h�̍Œ�l���Œ肷��B
		m_speedY = -MAX_SPEED_Y;
	}
	//���[�u�X�s�[�h��Y�X�s�[�h�����Z�B
	m_moveSpeed.y += m_speedY;

}
void Player::WeaponChange()
{
	if (m_changeAnimFlag != false) {
		m_animState = enChange_blad;
		//����ύX���͓����Ȃ��B
		m_moveSpeed = Vector3::Zero;
		//�^�C�}�[�����Z�B
		m_changeAnimTimer++;
		if (m_changeAnimTimer > m_changeAnimTime) {
			//����ύX�̃A�j���[�V�������I������B
			//m_weaponState������ύX�O�̏�ԂŁA�ύX��̏�Ԃɂ���B
			if (m_weaponState == enBladState) {
				m_weaponState = enSwordState;
			}
			else if (m_weaponState == enSwordState) {
				m_weaponState = enBladState;
			}
			//�t���O��false�ɂ���B
			m_changeAnimFlag = false;
			//�^�C�}�[�����Z�b�g�B
			m_changeAnimTimer = 0;
		}
	}
}
void Player::SetSpeed()
{
	//�J�������l�������v���C���[�̈ړ��������v�Z����B
	Vector3 cameraDir = m_gameCam->GetTarget() - m_gameCam->GetPosition();
	cameraDir.y = 0.0f;
	cameraDir.Normalize();

	Vector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		Vector3::AxisY
	);
	//�v���C���[�̃��[�u�X�s�[�h���v�Z�B
	m_moveSpeed = cameraDirX * g_pad[0]->GetLStickXF() * -m_magnificationSpeed +
		cameraDir * g_pad[0]->GetLStickYF() * m_magnificationSpeed;

	if (fabs(m_moveSpeed.x) > 0.0f || fabs(m_moveSpeed.z) > 0.0f) {
		//�ړ����Ă���B
		if (g_pad[0]->IsPress(enButtonRB1)) {
			m_magnificationSpeed = 10.0f;
			m_animState = enRun_blad;
		}
		else {
			m_magnificationSpeed = 5.0f;
			m_animState = enWalk_blad;
		}
	}
}
void Player::Rotation()
{
	if (
		fabsf(m_moveSpeed.z) > 0.0f ||
		fabsf(m_moveSpeed.x) > 0.0f) {
		if (
			m_attackFlag != true &&
			m_kaihiFlag != true &&
			m_attackAngleFlag != true &&
			m_changeAnimFlag != true &&
			m_playerHP >= m_beforeHp &&
			m_playerHP > 0.0f
			) {
			//�X�e�B�b�N�̌����Ă�������̊p�x�����߂�B
			m_dir = m_moveSpeed;
			m_dir.Normalize();
			float sita = atan2f(m_moveSpeed.x, m_moveSpeed.z);
			sita = sita * HALF_ANGLE / M_PI;
			if (sita <= 0.0f) {
				sita += MAX_ANGLE;
			}

			//�������Ă�������̊p�x�����߂�B
			Vector3 nowDir = Vector3::AxisZ;
			nowDir.Normalize();
			m_rotation.Apply(nowDir);
			m_angle = atan2f(nowDir.x, nowDir.z);
			m_angle = m_angle * HALF_ANGLE / M_PI;
			if (m_angle <= 0.0f) {
				m_angle += MAX_ANGLE;
			}

			//�������Ă�������̊p�x����X�e�B�b�N�̌����Ă�������̊p�x�������āA
			//�������߂�B
			float angleDifference = m_angle - sita;
			//��ŋ��߂��p�x�̌덷����]�ʈȓ��܂��́A�U���A�j���[�V�������Ȃ�
			if (
				angleDifference <= ROTATION_AMOUNT && angleDifference >= -ROTATION_AMOUNT ||
				m_attackAnimationFlag != false
				) {
				//�������Ă�������̊p�x�ɃX�e�B�b�N�̌����Ă�������̊p�x��������B
				m_angle = sita;
			}
			else if (m_angle <= sita) {
				//�������Ă�������̊p�x���X�e�B�b�N�̌����Ă�������̊p�x���A
				//�������B
				if (angleDifference <= -HALF_ANGLE) {
					//�p�x�̍���-180�ȉ��B
					//�p�x���}�C�i�X����B
					m_angle -= ROTATION_AMOUNT;
				}
				else {
					//�p�x���v���X����B
					m_angle += ROTATION_AMOUNT;
				}
			}
			else if (m_angle >= sita) {
				//�������Ă�������̊p�x���X�e�B�b�N�̌����Ă�������̊p�x���A
				//�傫���B
				if (angleDifference >= HALF_ANGLE) {
					//�p�x�̍���180�ȏ�B
					//�p�x���v���X����B
					m_angle += ROTATION_AMOUNT;
				}
				else {
					//�p�x���}�C�i�X����B
					m_angle -= ROTATION_AMOUNT;
				}

			}
		}
		m_rotation.SetRotationDeg(Vector3::AxisY, m_angle);
	}
	m_playerSkinModel->SetRotation(m_rotation);
}
bool Player::Start()
{
	//����̃C���X�^���X�쐬�B
	m_weapon[0] = NewGO<Weapon>(0, "weapon_01");
	m_weapon[1] = NewGO<Weapon>(0, "weapon_02");
	//�v���C���[�̃A�j���[�V�����̃C���X�^���X�쐬�B
	m_playerAnim = NewGO<PlayerAnimation>(0, "playerAnim");
	//���f���̏������B
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init(
		"Assets/modelData/player/player.tkm",
		m_playerAnim->GetAnimationClip(),
		enAnimationClipNum,
		"Assets/shader/model.fx",
		SkinModelRender::YUp
	);
	m_position.y += 100.0f;
	m_playerSkinModel->SetPosition(m_position);
	//�L�����R���������B
	m_charaCon.Init(50.0f, 100.0f, m_position);
	//����̍��W�A��]��K��������{�[���̔ԍ��������B
	m_weapon[0]->SetBoneNum(m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_r"));
	m_weapon[1]->SetBoneNum(m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_l"));
	//�v���C���[��UI�̃C���X�^���X���쐬�B
	m_playerStatusUI = NewGO<PlayerStatusUI>(0, "playerStatusUI");
	//GameCamera�̃C���X�^���X�������B
	m_gameCam = FindGO<GameCamera>("gameCamera");

	m_beforeHp = m_playerHP;
	return true;
}
void Player::Update()
{
	//�A�j���[�V������ҋ@��Ԃɐݒ�B
	m_animState = enStay_blad;

	//�����ƈړ��X�s�[�h��ݒ�B
	SetSpeed();

	if (m_changeAnimFlag != true &&//����ύX���Ă��Ȃ�
		m_charaCon.IsOnGround() != false &&//�n�ʂ̏�ɂ���
		m_kaihiFlag != true &&//������Ă��Ȃ��B
		m_attackFlag != true &&//�U�����łȂ��B
		m_playerHP >= m_beforeHp &&
		m_playerHP > 0.0f
		) {
		m_doNothingFlag = false;
	}
	//Y�����̈ړ��B
	YDirMove();

	//����ύX�̃t���O�B
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_doNothingFlag != true) {
		//����ύX�̃t���O�𗧂Ă�B
		m_changeAnimFlag = true;
		m_doNothingFlag = true;
		//�U���A�j���[�V���������Ă�����A�~�߂�B
		if (m_attackAnimationFlag != false) {
			m_attackAnimationFlag = false;
			AttackEnd();
		}
	}

	if (m_changeAnimFlag != true && m_kaihiFlag != true && m_charaCon.IsOnGround() != false) {
		if (g_pad[0]->IsTrigger(enButtonX)) {
			m_doNothingFlag = true;
			AttackFlag(enAttackTime01_blad, ATTACK_ANIM_NUM_X, enAttackTime01_sword);
		}
		else if (g_pad[0]->IsTrigger(enButtonY)) {
			m_doNothingFlag = true;
			AttackFlag(enAttackTime06_blad, ATTACK_ANIM_NUM_Y, enAttackTime06_sword);
		}
	}
	//�v���C���[����]������B
	Rotation();
	
	//����̃t���O
	if (g_pad[0]->IsTrigger(enButtonB) && m_doNothingFlag != true) {
		//B�{�^�����������B
		m_kaihiFlag = true;
		m_animState = enKaihi_blad;
		m_doNothingFlag = true;
		//�U���A�j���[�V���������Ă�����A�~�߂�B
		if (m_attackAnimationFlag != false) {
			m_attackAnimationFlag = false;
			AttackEnd();
		}
	}

	//����B
	if (m_kaihiFlag != false) {
		//�^�C�}�[�����Z�B
		m_kaihiTimer++;
		m_animState = enKaihi_blad;
		//��𒆂͐i�s�����ɐi�ށB
		m_moveSpeed = m_dir * 10.0f;
		if (m_kaihiTimer >= 50) {
			//�^�C�}�[��50�ȏ�ɂȂ�����~�܂�B
			m_moveSpeed = Vector3::Zero;
		}
		if (m_kaihiTimer >= 60) {
			//�^�C�}�[��60�ȏ�ɂȂ��������I���B
			m_kaihiTimer = 0;
			m_kaihiFlag = false;
		}
	}
	//����ύX�B
	WeaponChange();
	//�U���B
	Attack();

	if (m_playerHP < m_beforeHp) {
		m_animState = enHit_blad;
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		if (!m_playerSkinModel->GetisAnimationPlaing()) {
			m_beforeHp = m_playerHP;
		}
	}

	if (m_playerHP <= 0.0f) {
		m_animState = enDeath_blad;
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		if (!m_playerSkinModel->GetisAnimationPlaing()) {
			m_deathFlag = true;
		}
	}


	if (m_weaponState == enSwordState) {
		//�\�[�h��ԂȂ�1�����ă\�[�h��Ԃ̃A�j���[�V�����𗬂��B
		m_animState++;
	}
	//�A�j���[�V�������Đ��B
	//�A�j���[�V�����⊮���ԁB
	float complementaryTime = m_complementaryFlame / 60.0f;
	m_playerSkinModel->PlayAnimation(m_animState, complementaryTime);

	//�Ƃ肠�����v���C���[��Y���W��-500�ȉ��ɂȂ�����߂�悤�ɂ���B
	if (m_charaCon.GetPosition().y <= -500.0f || m_deathFlag != false) {
		m_charaCon.SetPosition({ 0.0f, 500.0f, 0.0f });
		m_playerHP = 100.0f;
		m_beforeHp = m_playerHP;
		m_deathFlag = false;
	}

	//���W��ݒ�B
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);
	//�O�̃t���[���̍��W���猻�݂̃t���[���̍��W��
	//�������ĐL�т�x�N�g�������߂�B
	m_weaponMoveSpeed = m_position - m_oldPosition;
	//�O�̍��W�����̍��W�ɒu��������B
	m_oldPosition = m_position;
	//HP��ݒ�B
	m_playerStatusUI->SetCurrentPlayerHP(m_playerHP);
}