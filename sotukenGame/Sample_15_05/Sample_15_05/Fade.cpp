#include "stdafx.h"
#include "Fade.h"

Fade::Fade(){}
Fade::~Fade(){}

bool Fade::Start(){return true;}
void Fade::FadeIn()
{
	//フェードイン。
	m_mulColor = m_fadeSprite->GetMulColor();

	m_mulColor.x += m_mulColorAddValue;
	m_mulColor.y += m_mulColorAddValue;
	m_mulColor.z += m_mulColorAddValue;
	if (m_mulColor.x > FADEIN_FINISHED &&
		m_mulColor.y > FADEIN_FINISHED &&
		m_mulColor.z > FADEIN_FINISHED)
	{
		//表示完了。
		m_mulColor.x = FADEIN_FINISHED;
		m_mulColor.y = FADEIN_FINISHED;
		m_mulColor.z = FADEIN_FINISHED;
		m_fadeSprite->SetMulColor(m_mulColor);
		//削除する。
		DeleteGO(this);
	}
	else {
		m_fadeSprite->SetMulColor(m_mulColor);
	}

}
void Fade::FadeOut()
{
	//フェードアウト。
	m_mulColor = m_fadeSprite->GetMulColor();

	m_mulColor.x -= m_mulColorAddValue;
	m_mulColor.y -= m_mulColorAddValue;
	m_mulColor.z -= m_mulColorAddValue;
	if (m_mulColor.x < FADEOUT_FINISHED &&
		m_mulColor.y < FADEOUT_FINISHED &&
		m_mulColor.z < FADEOUT_FINISHED)
	{
		//非表示完了。
		m_mulColor.x = FADEOUT_FINISHED;
		m_mulColor.y = FADEOUT_FINISHED;
		m_mulColor.z = FADEOUT_FINISHED;
		m_fadeSprite->SetMulColor(m_mulColor);
		//削除する。
		DeleteGO(this);
	}
	else {
		m_fadeSprite->SetMulColor(m_mulColor);
	}
}
void Fade::DoNothing()
{	
	//フェードが設定されたら、各フェード処理に移る。
	if (m_fadeState == Fade_In) {
		m_fadeState = Fade_In;				//フェードイン。
	}
	if (m_fadeState == Fade_Out) {
		m_fadeState = Fade_Out;				//フェードアウト。
	}
}
void Fade::Update()
{
	switch (m_fadeState)
	{
	case Fade::Fade_In:
		FadeIn();		//フェードイン。
		break;
	case Fade::Fade_Out:
		FadeOut();		//フェードアウト。
		break;
	case Fade::Fade_DoNothing:
		DoNothing();	//何もしない。
		break;
	}
}
