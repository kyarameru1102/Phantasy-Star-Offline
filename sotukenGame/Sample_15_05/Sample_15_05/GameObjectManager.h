#pragma once
#include <vector>		//可変長配列。
#include "GameObject.h"
#include "Util.h"

/// <summary>
/// ゲームオブジェクトを管理するクラス。
/// </summary>
/// GameObjectを継承したやつらがNewGOされたらここでいい感じにされるぜい。
class GameObjectManager
{
private:
	/// <summary>
	/// ゲームオブジェクトの名前キーを作成する関数。
	/// </summary>
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");
		unsigned int hash;
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		else {
			hash = Util::MakeHash(objectName);
		}
		return hash;
	}
	/// <summary>
	/// 事前描画。
	/// </summary>
	void PreRender();
	/// <summar
	/// 3D描画。
	/// </summary>
	void Render3D();
	/// <summary>
	/// 遅延描画。
	/// </summary>
	void PostRender();
	void Render2D();
	/// <summary>
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
public:
	/// <summary>
	/// 初期化関数。
	/// </summary>
	/// <param name="gameObjectPrioMax">
	/// 最大優先順位（255まで）
	/// </param>
	void Init(int gameObjectPrioMax);

	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance;
	}
	void Update();
	void Render();

	/// <summary>
	/// ゲームオブジェクトのnew
	/// </summary>
	/// prio			優先順位。
	/// objectName		オブジェクトの名前。
	template<class T>
	T* NewGameObject(unsigned char prio, const char* objectName)
	{
		if (prio <= m_priorityMax)
		{
			T* NewObject = new T();
			m_gameObjectListArray.at(prio).push_back(NewObject);
			unsigned int hash = MakeGameObjectNameKey(objectName);
			NewObject->SetPriority(prio);
			NewObject->SetNameKey(hash);
			return NewObject;
		}
		else {
			assert(1);
		}
	}
	/// <summary>
	/// ゲームオブジェクトの削除。
	/// </summary>
	/// <param name="gameObject">
	/// ゲームオブジェクト。
	/// </param>
	void DeleteGameObject(IGameObject*& gameObject)
	{
		if (gameObject != nullptr)
		{
			gameObject->OnDestroy();
			gameObject->SetIsDead();
			m_deleteObjectListArray.at(gameObject->GetPriority()).push_back(gameObject);
			gameObject = nullptr;
		}
	}
	/// <summary>
	/// ゲームオブジェクトの検索。
	/// NewGOする際につけた名前で検索をかける。
	/// </summary>
	template<class T>
	T* FindGameObject(const char* objectName)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					T* t = dynamic_cast<T*>(go);
					if (t != nullptr) {
						return t;
					}
				}
			}
		}
		return nullptr;
	}
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					T* t = dynamic_cast<T*>(go);
					if (func(t) == false)
						return;
				}
			}
		}
	}
private:
	std::vector<IGameObject*>			 m_gameObjectList;
	typedef std::list<IGameObject*>		GameObjectList;
	std::vector<GameObjectList>			m_gameObjectListArray;		//ゲームオブジェクトの優先度付きリスト
	std::vector<GameObjectList>			m_deleteObjectListArray;	//削除用のリスト。
	unsigned char						m_priorityMax = 255;		//優先度の最大数。
};

static inline GameObjectManager& gameObjectManager()
{
	return GameObjectManager::Instance();
}
/// <summary>
/// ゲームオブジェクトを生成する関数。
/// </summary>
template<class T>
static inline T* NewGO(int priority, const char* objectName = nullptr)
{
	return gameObjectManager().NewGameObject<T>((unsigned char)priority, objectName);
}
/// <summary>
/// ゲームオブジェクトを削除する関数。
/// </summary>
/// <param name="go">
/// ゲームオブジェクト。
/// </param>
static inline void DeleteGO(IGameObject* go)
{
	gameObjectManager().DeleteGameObject(go);
}
/// <summary>
///ゲームオブジェクト検索用の関数。
/// </summary>
/// <param name="objectName">NewGOのときにオブジェクトにつけた名前。</param>
/// <returns>インスタンス。</returns>
template<class T>
static inline T* FindGO(const char* objectName)
{
	return gameObjectManager().FindGameObject<T>(objectName);
}
/// <summary>
/// ゲームオブジェクト検索用の関数。
/// </summary>
/// <param name="objectName">NewGOのときにオブジェクトにつけた名前。</param>
/// <param name="func">見つかった時に行うコールバック関数。</param>

template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
{
	return gameObjectManager().FindGameObjects<T>(objectName, func);
}

/// <summary>
/// 引数に渡した名前がついているゲームオブジェっくとすべてを削除する関数。
/// </summary>
/// <param name="objectName">NewGOのときにオブジェクトにつけた名前。</param>
static inline void DeleteGOs(const char* objectName)
{
	QueryGOs<IGameObject>(objectName, [](auto go) {
		DeleteGO(go);
		return true;
	});
}
