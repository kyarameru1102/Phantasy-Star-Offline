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
	//�`�揈���B

	Render();

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
}

void GameObjectManager::Render()
{
	//���O�`��B
	PreRender();
	//�RD���f���`��B
	Render3D();
	//�x���`��B
	PostRender();
	//�QD�n�̕`��B
	Render2D();
}

void GameObjectManager::PreRender()
{
}

void GameObjectManager::Render3D()
{
	//3D���f����`��B
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
	//2D��`��B
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		for (auto go : m_gameObjectListArray[i]) {
			if (go->GetIsDead() == false) {
				go->Render2D();
			}
		}
	}
	//�t�H���g��`��B
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		for (auto go : m_gameObjectListArray[i]) {
			if (go->GetIsDead() == false) {
				go->RenderFont();
			}
		}
	}
}