#include "stdafx.h"
#include "MeshCollider.h"

MeshCollider::MeshCollider()
{
}

MeshCollider::~MeshCollider()
{
}

void MeshCollider::CreateFromModel(const Model& model, const Matrix* offsetMatrix)
{
	CreateFromTkmFile(model.GetTkmFile(), offsetMatrix);
}

void MeshCollider::CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix)
{
	Matrix mBias;
	mBias.MakeRotationX(Math::PI * -0.5f);
	if (offsetMatrix != nullptr) {
		mBias = mBias * (*offsetMatrix);
	}
	m_stridingMeshInterface = std::make_unique<btTriangleIndexVertexArray>();
	int numMesh = 0;

	tkmFile.QueryMeshParts([&numMesh, &mBias](const TkmFile::SMesh& mesh) {
		//���f���̒��_�o�b�t�@����A�����G���W���p�̒��_�o�b�t�@���쐬�B
		VertexBufferPtr vertexBuffer = std::make_unique<VertexBuffer>();
		for (auto& vb : mesh.vertexBuffer) {
			auto pos = vb.pos;
			//�o�C�A�X��������B
			mBias.Apply(pos);
			vertexBuffer->push_back(pos);
		}
		//���f���̃C���f�b�N�X�o�b�t�@����A�����G���W���p�̃C���f�b�N�X�o�b�t�@���쐬�B
		IndexBufferPtr indexBuffer = std::make_unique<IndexBuffer>();
		if (!mesh.indexBuffer16Array.empty()) {
			//16bit�C���f�b�N�X�o�b�t�@����쐬����B
			for (auto& ib : mesh.indexBuffer16Array) {
				for (auto index : ib.indices) {
					indexBuffer->push_back(index);
				}
			}
		}
		else {
			//32bit�C���f�b�N�X�o�b�t�@����쐬����B
			for (auto& ib : mesh.indexBuffer16Array) {
				for (auto index : ib.indices) {
					indexBuffer->push_back(index);
				}
			}
		}

		numMesh++;
		});

	//BulletPhysics�̃C���f�b�N�X���b�V�����쐬�B
	btIndexedMesh indexedMesh;
	IndexBuffer* ib = m_indexBufferArray.back().get();
	VertexBuffer* vb = m_vertexBufferArray.back().get();
	indexedMesh.m_numTriangles = (int)ib->size() / 3;
	indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib->front());
	indexedMesh.m_triangleIndexStride = 12;
	indexedMesh.m_numVertices = (int)vb->size();
	indexedMesh.m_vertexBase = (unsigned char*)(&vb->front());
	indexedMesh.m_vertexStride = sizeof(Vector3);
	m_stridingMeshInterface->addIndexedMesh(indexedMesh);
}
