#pragma once
class GameObjectManager;

/// <summary>
/// ゲームオブジェクト。
/// </summary>
/// NewGOしたいものはこれを継承してもろて。
class IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	IGameObject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~IGameObject() {};
	/// <summary>
	/// Updateの直前に呼ばれる開始処理。
	/// </summary>
	/// <returns>
	/// Start関数がtrueを返すとUpdateが呼ばれだす。
	/// </returns>
	virtual bool Start() { return true; }
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() {}
	/// <summary>
	/// 削除されるときに呼ばれる関数。
	/// </summary>
	/// この関数はDeleteGOされた時にすぐに呼ばれるやつ。
	/// DeleteGOで消したフレームで呼ばれるからデストラクタより早く呼ばれるよー。
	/// 必要に応じて使ってもろて。
	virtual void OnDestroy() {}
	///////////////////////////////////////////////////////////////////
	//ここから下は多分使わないかな。
	/// <summary>
	/// 描画関数。
	/// </summary>
	virtual void Render() {}
	/// <summary>
	/// 2D用の描画関数。
	/// </summary>
	virtual void Render2D() {}
	/// <summary>
	/// フォント用の描画関数。
	/// </summary>
	virtual void RenderFont() {}
	///////////////////////////////////////////////////////////////////
	//ここから下は呼ばないで。
	//ゲームオブジェクトマネージャーで使ってるからいじるんじゃねえぞお。
	/// /// <summary>
	/// 優先度を取得。
	/// </summary>
	unsigned char GetPriority() const
	{
		return m_priority;
	}
	/// <summary>
	/// m_isStartにtrueをいれる関数。
	/// </summary>	
	void StartCallEnd()
	{
		m_isStart = true;
	}
	/// <summary>
	/// m_isStartがtrueかfalseかを返す関数。
	/// </summary>
	bool GetStart()
	{
		return m_isStart;
	}
	/// <summary>
	/// 優先度を設定する関数。
	/// </summary>
	void SetPriority(unsigned char prio)
	{
		m_priority = prio;
	}
	/// <summary>
	/// 名前キーを設定する関数。
	/// </summary>
	void SetNameKey(unsigned int nK)
	{
		m_nameKey = nK;
	}
	/// <summary>
	/// 死亡フラグを立てる関数。
	/// </summary>
	void SetIsDead()
	{
		m_isDead = true;
	}
	/// <summary>
	/// 死んでますか？
	/// </summary>
	bool GetIsDead()
	{
		return m_isDead;
	}
	friend class GameObjectManager;
protected:
	unsigned char	m_priority;					//優先度。
	bool			m_isStart = false;			//Start関数が呼ばれたか？
	unsigned int	m_nameKey = 0;				//名前キー。
	bool			m_isDead = false;			//死亡フラグ。
	bool			m_stopUpdate = false;		//trueでアップデートを止める。
};

