#pragma once
#include "ICollider.h"

class MeshCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	MeshCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~MeshCollider();
	/*!
	 * @brief	CModelからメッシュコライダーを生成。
	 *@param[in]	model		スキンモデル。
	 */
	void CreateFromModel(const Model& model, const Matrix* offsetMatrix);
	/*!
	* @brief	tkmファイルからメッシュコライダーを生成。
	*@param[in]	tkmFile		tkmファイル。
	*/
	void CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix);
	btCollisionShape* GetBody() const override
	{
		return m_meshShape.get();
	}
private:
	typedef std::vector<Vector3>		VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>	IndexBuffer;		//インデックスバッファ。
	typedef std::unique_ptr<VertexBuffer>	VertexBufferPtr;
	typedef std::unique_ptr<IndexBuffer>	IndexBufferPtr;
	std::vector<VertexBufferPtr>					m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBufferPtr>						m_indexBufferArray;		//インデックスバッファの配列。
	std::unique_ptr<btBvhTriangleMeshShape>			m_meshShape;				//メッシュ形状。
	std::unique_ptr<btTriangleIndexVertexArray>		m_stridingMeshInterface;
};

