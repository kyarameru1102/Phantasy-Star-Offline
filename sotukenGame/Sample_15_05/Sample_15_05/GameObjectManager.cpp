#include "stdafx.h"
#include "GameObjectManager.h"



void GameObjectManager::Init(int gameObjectPrioMax)
{
	if (gameObjectPrioMax <= 255)
	{
		m_priorityMax = static_cast<unsigned char>(gameObjectPrioMax);
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectListArray.resize(gameObjectPrioMax);
	}
}

void GameObjectManager::Update()
{

	for (auto& deleteList : m_deleteObjectListArray) {
		for (IGameObject* go : deleteList) {
			if (go->GetIsDead() == true)
			{
				unsigned char prio = go->GetPriority();
				GameObjectList& goList = m_gameObjectListArray.at(prio);
				auto it = std::find(goList.begin(), goList.end(), go);
				if (it != goList.end())
				{
					delete(*it);
				}
				goList.erase(it);
			}
		}
		deleteList.clear();
	}

	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		for (auto go : m_gameObjectListArray[i]) {
			if (go->GetStart() == false) {
				if (go->Start())
					go->StartCallEnd();
			}
			else {
				if (go->GetIsDead() == false) {
					go->Update();
				}
			}
		}
	}
	//•`‰æˆ—B
	Render();
}

void GameObjectManager::Render()
{
	g_graphicsEngine->RendertoShadow();
	g_graphicsEngine->BeginDeferredRender();
	//–‘O•`‰æB
	PreRender();
	//‚RDƒ‚ƒfƒ‹•`‰æB
	Render3D();
	g_graphicsEngine->EndModelDraw();
	g_graphicsEngine->RendertoPostEffect();
	////’x‰„•`‰æB
	//PostRender();
	//‚QDŒn‚Ì•`‰æB
	Render2D();
}

void GameObjectManager::PreRender()
{
}

void GameObjectManager::Render3D()
{
	//3Dƒ‚ƒfƒ‹‚ğ•`‰æB
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		for (auto go : m_gameObjectListArray[i]) {
			if (go->GetIsDead() == false) {
				go->Render();
			}
		}
	}
}

void GameObjectManager::PostRender()
{
}

void GameObjectManager::Render2D()
{
	//2D‚ğ•`‰æB
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		for (auto go : m_gameObjectListArray[i]) {
			if (go->GetIsDead() == false) {
				go->Render2D();
			}
		}
	}
	//ƒtƒHƒ“ƒg‚ğ•`‰æB
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		for (auto go : m_gameObjectListArray[i]) {
			if (go->GetIsDead() == false) {
				go->RenderFont();
			}
		}
	}
}