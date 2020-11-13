#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_playerSkinModel);
}
bool Player::Start()
{
	//�A�j���[�V���������[�h�B
	animClip[enStay01].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay02].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enChange01].Load("Assets/animData/player/blad/change_01.tka");
	animClip[enChange02].Load("Assets/animData/player/sword/change_02.tka");
	animClip[attackAndChang01].Load("Assets/animData/player/blad/attackAndChange_01.tka");
	animClip[attackAndChang02].Load("Assets/animData/player/sword/attackAndChange_02.tka");
	animClip[enStay01].SetLoopFlag(true);
	animClip[enStay02].SetLoopFlag(true);
	animClip[enChange01].SetLoopFlag(true);
	animClip[enChange02].SetLoopFlag(true);
	animClip[attackAndChang01].SetLoopFlag(true);
	animClip[attackAndChang02].SetLoopFlag(true);


	//���f���̏������B
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init("Assets/modelData/player/player.tkm", animClip, enAnimationClipNum);
	Quaternion qRot;
	qRot.SetRotationDegX(0.0f);
	m_playerSkinModel->SetRotation(qRot);
	m_charaCon.Init(50.0f, 100.0f, m_position);
	m_gameCam = FindGO<GameCamera>("gameCamera");
	return true;
}
void Player::Update()
{
	Vector3 cameraDir = m_gameCam->GetTarget() - m_gameCam->GetPosition();
	cameraDir.y = 0.0f;
	cameraDir.Normalize();

	Vector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		Vector3::AxisY
	);
	//�v���C���[�̃��[�u�X�s�[�h���X�V�B
	m_moveSpeed = cameraDirX * g_pad[0]->GetLStickXF() * -5.0f +
		cameraDir * g_pad[0]->GetLStickYF() * 5.0f;
	//���W��ݒ�B
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);

	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {
		float rot = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(Vector3::AxisY, rot);
	}
	m_playerSkinModel->SetRotation(m_rotation);


	if (g_pad[0]->IsTrigger(enButtonX)) {
		//����ύX�̃t���O�𗧂Ă�B
		m_changeAnimFlag = true;
		//m_attackAndChangState = enChange01;
	}
	/*else if (g_pad[0]->IsPress(enButtonY)) {
		m_changeAnimFlag = true;
		m_attackAndChangState = attackAndChang01;
	}*/
	if (m_changeAnimFlag != false) {
		//����̏�Ԃɂ���ĕ���ύX�̃A�j���[�V���������߂�B
		if (m_weaponState == enBladState) {
			m_animState = enChange01;
		}
		else if(m_weaponState == enSwordState){
			m_animState = enChange02;
		}
		//�^�C�}�[�����Z�B
		m_changeAnimTimer++;
		if (m_changeAnimTimer > m_changeAnimTime) {
			//����ύX�̃A�j���[�V�������I������B
			//m_weaponState������ύX�O�̏�ԂŁA�ύX��̏�Ԃɂ���B
			if (m_weaponState == enBladState) {
				m_weaponState = enSwordState;
				m_animState = enStay02;
			}
			else if (m_weaponState == enSwordState) {
				m_weaponState = enBladState;
				m_animState = enStay01;
			}
			//�t���O��false�ɂ���B
			m_changeAnimFlag = false;
			//�^�C�}�[�����Z�b�g�B
			m_changeAnimTimer = 0;
		}
	}
	//�A�j���[�V�������Đ��B
	m_playerSkinModel->PlayAnimation(m_animState, 0.0f);
}