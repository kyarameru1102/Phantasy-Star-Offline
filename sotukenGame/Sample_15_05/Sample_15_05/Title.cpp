#include "stdafx.h"
#include "Title.h"
#include "Game.h"

#include "Fade.h"

Title::Title()
{
	
}

Title::~Title()
{
	//Spriteの削除。
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
}

bool Title::Start()
{
	//0番→Title1(背景)
	//m_titleSprite = NewGO<SpriteRender>(0, "Sprite");
	//m_titleSprite->Init("Assets/image/title/Title_BackGround.DDS", 780.0f, 1280.0f);
	//m_titleSprite->SetPosition({ 0.0f,0.0f,0.0f });
	//m_titleSprite->SetMulColor({ 0.0f,0.0f,0.0f,1.0f });
	//m_spriteRender.push_back(m_titleSprite);
	////1番→Title2(背景)
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
	//背景の移動処理。
	m_backTexpos1 = m_spriteRender[0]->GetPosition();
	m_backTexpos2 = m_spriteRender[1]->GetPosition();

	m_backTexpos1.x += m_backMove;
	m_backTexpos2.x += m_backMove;

	//一定位置になると一枚目の右端に移動させる。
	//背景のTextureが途切れないよ！！
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
	//フェードイン。
	Fade* fadein = NewGO<Fade>(0, "FadeIn");
	fadein->FadeSet(m_spriteRender[0], Fade::Fade_In, 80.0f);

	m_spriteMul = m_spriteRender[0]->GetMulColor();

	//フェードインが完了したので次へ。
	if (m_spriteMul.x >= FADEIN_FINISHED.x && m_spriteMul.y >= FADEIN_FINISHED.y && m_spriteMul.z >= FADEIN_FINISHED.z)
	{
		//BGMの再生
		m_titleState = Title_Select;
	}

}
void Title::TitleFont()
{
	//タイトル名、ボタンの表示。

}
void Title::TitleSelect()
{
	//ボタン選択。
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_titleState = Title_FadeOut;
	}
	////ボタン選択。
	//if (g_pad[0]->IsTrigger(enButtonStart)) {
	//	m_titleState = Title_FadeOut;
	//}
	//else if (m_buttonState == Button_Load && g_pad[0]->IsTrigger(enButtonLeft)) {
	//	//「はじめる」を選択する。
	//	m_buttonState = Button_Start;
	//}
	//else if (m_buttonState == Button_Start && g_pad[0]->IsTrigger(enButtonRight)) {
	//	//「つづける」を選択する。
	//	m_buttonState = Button_Load;
	//}

}
void Title::TitleFadeOut()
{
	//フェードアウト。
	Fade* fadeout = NewGO<Fade>(0, "FadeOut");
	fadeout->FadeSet(m_spriteRender[0], Fade::Fade_Out, 80.0f);

	m_spriteMul = m_spriteRender[0]->GetMulColor();

	//フェードアウトが完了したので次へ。
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
		TitleFadeIn();	//フェードイン。
		break;
	case Title::Title_Font:
		TitleFont();	//タイトル名、ボタンの表示。
		break;
	case Title::Title_Select:
		TitleSelect();	//ボタン選択。
		break;
	case Title::Title_FadeOut:
		TitleFadeOut();	//フェードアウト。
		break;
	}


}
