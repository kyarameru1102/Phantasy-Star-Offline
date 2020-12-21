#include "stdafx.h"
#include "Fade.h"

Fade::Fade(){}
Fade::~Fade(){}

bool Fade::Start(){return true;}
void Fade::FadeIn()
{
	//�t�F�[�h�C���B
	m_mulColor = m_fadeSprite->GetMulColor();

	m_mulColor.x += m_mulColorAddValue;
	m_mulColor.y += m_mulColorAddValue;
	m_mulColor.z += m_mulColorAddValue;
	if (m_mulColor.x > FADEIN_FINISHED &&
		m_mulColor.y > FADEIN_FINISHED &&
		m_mulColor.z > FADEIN_FINISHED)
	{
		//�\�������B
		m_mulColor.x = FADEIN_FINISHED;
		m_mulColor.y = FADEIN_FINISHED;
		m_mulColor.z = FADEIN_FINISHED;
		m_fadeSprite->SetMulColor(m_mulColor);
		//�폜����B
		DeleteGO(this);
	}
	else {
		m_fadeSprite->SetMulColor(m_mulColor);
	}

}
void Fade::FadeOut()
{
	//�t�F�[�h�A�E�g�B
	m_mulColor = m_fadeSprite->GetMulColor();

	m_mulColor.x -= m_mulColorAddValue;
	m_mulColor.y -= m_mulColorAddValue;
	m_mulColor.z -= m_mulColorAddValue;
	if (m_mulColor.x < FADEOUT_FINISHED &&
		m_mulColor.y < FADEOUT_FINISHED &&
		m_mulColor.z < FADEOUT_FINISHED)
	{
		//��\�������B
		m_mulColor.x = FADEOUT_FINISHED;
		m_mulColor.y = FADEOUT_FINISHED;
		m_mulColor.z = FADEOUT_FINISHED;
		m_fadeSprite->SetMulColor(m_mulColor);
		//�폜����B
		DeleteGO(this);
	}
	else {
		m_fadeSprite->SetMulColor(m_mulColor);
	}
}
void Fade::DoNothing()
{	
	//�t�F�[�h���ݒ肳�ꂽ��A�e�t�F�[�h�����Ɉڂ�B
	if (m_fadeState == Fade_In) {
		m_fadeState = Fade_In;				//�t�F�[�h�C���B
	}
	if (m_fadeState == Fade_Out) {
		m_fadeState = Fade_Out;				//�t�F�[�h�A�E�g�B
	}
}
void Fade::Update()
{
	switch (m_fadeState)
	{
	case Fade::Fade_In:
		FadeIn();		//�t�F�[�h�C���B
		break;
	case Fade::Fade_Out:
		FadeOut();		//�t�F�[�h�A�E�g�B
		break;
	case Fade::Fade_DoNothing:
		DoNothing();	//�������Ȃ��B
		break;
	}
}
