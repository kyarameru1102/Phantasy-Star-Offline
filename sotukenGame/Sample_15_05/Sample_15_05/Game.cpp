#include "stdafx.h"
#include "Game.h"


Game::Game()
{

}

Game::~Game()
{
}

bool Game::Start()
{
    m_ladySkinModelRender = NewGO<SkinModelRender>(0, "UnityChan");
    m_ladySkinModelRender->Init("Assets/modelData/unityChan.tkm");
    return true;
}

void Game::Update()
{
    int a = 0;
}
