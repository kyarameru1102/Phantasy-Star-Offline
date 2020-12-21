#include "stdafx.h"
#include "Title.h"
#include "Game.h"

#include "Fade.h"

Title::Title()
{
	
}

Title::~Title()
{
	//Sprite�̍폜�B
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
}

bool Title::Start()
{
	//0�ԁ�Title1(�w�i)
	//m_titleSprite = NewGO<SpriteRender>(0, "Sprite");
	//m_titleSprite->Init("Assets/image/title/Title_BackGround.DDS", 780.0f, 1280.0f);
	//m_titleSprite->SetPosition({ 0.0f,0.0f,0.0f });
	//m_titleSprite->SetMulColor({ 0.0f,0.0f,0.0f,1.0f });
	//m_spriteRender.push_back(m_titleSprite);
	////1�ԁ�Title2(�w�i)
	//m_titleSprite = NewGO<SpriteRender>(0, "Sprite");
	//m_titleSprite->Init("Assets/image/title/Title_BackGround.DDS", 780.0f, 1280.0f);
	//m_titleSprite->SetPosition({ 1280.0f,0.0f,0.0f });
	//m_titleSprite->SetMulColor({ 0.0f,0.0f,0.0f,1.0f });
	//m_spriteRender.push_back(m_titleSprite);

	m_titleSprite = NewGO<SpriteRender>(0, "Sprite");
	m_titleSprite->Init("Assets/image/title/Title_kari.DDS", 780.0f, 1280.0f);
	m_titleSprite->SetMulColor({ 0.0f,0.0f,0.0f,1.0f });
	m_spriteRender.push_back(m_titleSprite);



	return true;
}
void Title::TitleMoveBackGround()
{
	//�w�i�̈ړ������B
	m_backTexpos1 = m_spriteRender[0]->GetPosition();
	m_backTexpos2 = m_spriteRender[1]->GetPosition();

	m_backTexpos1.x += m_backMove;
	m_backTexpos2.x += m_backMove;

	//���ʒu�ɂȂ�ƈꖇ�ڂ̉E�[�Ɉړ�������B
	//�w�i��Texture���r�؂�Ȃ���I�I
	if (m_backTexpos1.x <= -m_backTexXPos) {
		m_backTexpos1.x = m_backTexXPos;
	}
	else if (m_backTexpos2.x <= -m_backTexXPos) {
		m_backTexpos2.x = m_backTexXPos;
	}

	m_spriteRender[0]->SetPosition(m_backTexpos1);
	m_spriteRender[1]->SetPosition(m_backTexpos2);

}

void Title::TitleFadeIn()
{
	//�t�F�[�h�C���B
	Fade* fadein = NewGO<Fade>(0, "FadeIn");
	fadein->FadeSet(m_spriteRender[0], Fade::Fade_In, 80.0f);

	m_spriteMul = m_spriteRender[0]->GetMulColor();

	//�t�F�[�h�C�������������̂Ŏ��ցB
	if (m_spriteMul.x >= FADEIN_FINISHED.x && m_spriteMul.y >= FADEIN_FINISHED.y && m_spriteMul.z >= FADEIN_FINISHED.z)
	{
		//BGM�̍Đ�
		m_titleState = Title_Select;
	}

}
void Title::TitleFont()
{
	//�^�C�g�����A�{�^���̕\���B

}
void Title::TitleSelect()
{
	//�{�^���I���B
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_titleState = Title_FadeOut;
	}
	////�{�^���I���B
	//if (g_pad[0]->IsTrigger(enButtonStart)) {
	//	m_titleState = Title_FadeOut;
	//}
	//else if (m_buttonState == Button_Load && g_pad[0]->IsTrigger(enButtonLeft)) {
	//	//�u�͂��߂�v��I������B
	//	m_buttonState = Button_Start;
	//}
	//else if (m_buttonState == Button_Start && g_pad[0]->IsTrigger(enButtonRight)) {
	//	//�u�Â���v��I������B
	//	m_buttonState = Button_Load;
	//}

}
void Title::TitleFadeOut()
{
	//�t�F�[�h�A�E�g�B
	Fade* fadeout = NewGO<Fade>(0, "FadeOut");
	fadeout->FadeSet(m_spriteRender[0], Fade::Fade_Out, 80.0f);

	m_spriteMul = m_spriteRender[0]->GetMulColor();

	//�t�F�[�h�A�E�g�����������̂Ŏ��ցB
	if (m_spriteMul.x <= FADEOUT_FINISHED.x && m_spriteMul.y <= FADEOUT_FINISHED.y && m_spriteMul.z <= FADEOUT_FINISHED.z)
	{
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}


}
void Title::Update()
{
	//TitleMoveBackGround();
	switch (m_titleState)
	{
	case Title::Title_FadeIn:
		TitleFadeIn();	//�t�F�[�h�C���B
		break;
	case Title::Title_Font:
		TitleFont();	//�^�C�g�����A�{�^���̕\���B
		break;
	case Title::Title_Select:
		TitleSelect();	//�{�^���I���B
		break;
	case Title::Title_FadeOut:
		TitleFadeOut();	//�t�F�[�h�A�E�g�B
		break;
	}


}
