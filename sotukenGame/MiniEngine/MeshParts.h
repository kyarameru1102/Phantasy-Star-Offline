/// <summary>
/// ���b�V���p�[�c�N���X�B
/// </summary>

#pragma once

#include "tkFile/TkmFile.h"
#include "StructuredBuffer.h"
#include "RenderMode.h"

class RenderContext;
class Skeleton;
class Material;
class IShaderResource;


/// <summary>
/// ���b�V��
/// </summary>
struct SMesh {
	VertexBuffer m_vertexBuffer;						//���_�o�b�t�@�B
	std::vector< IndexBuffer* >		m_indexBufferArray;	//�C���f�b�N�X�o�b�t�@�B
	std::vector< Material* >		m_materials;			//�}�e���A���B
	std::vector<int>				skinFlags;				//�X�L���������Ă��邩�ǂ����̃t���O�B
};

/// <summary>
/// ���b�V���p�[�c�B
/// </summary>
class MeshParts {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~MeshParts();
	/// <summary>
	/// tkm�t�@�C�����珉����
	/// </summary>
	/// <param name="tkmFile">tkm�t�@�C���B</param>
	/// /// <param name="fxFilePath">fx�t�@�C���̃t�@�C���p�X</param>
	/// <param name="vsEntryPointFunc">���_�V�F�[�_�[�̃G���g���[�|�C���g�̊֐���</param>
	/// <param name="psEntryPointFunc">�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�̊֐���</param>
	void InitFromTkmFile(
		const TkmFile& tkmFile,
		const wchar_t* fxFilePath,
		const char* vsEntryPointFunc,
		const char* psEntryPointFunc,
		void* expandData,
		int expandDataSize,
		IShaderResource* expandShaderResourceView
	);
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="rc">�����_�����O�R���e�L�X�g</param>
	/// <param name="mWorld">���[���h�s��</param>
	/// <param name="mView">�r���[�s��</param>
	/// <param name="mProj">�v���W�F�N�V�����s��</param>
	/// <param name="light">���C�g</param>
	void Draw(RenderContext& rc, const Matrix& mWorld, const Matrix& mView, const Matrix& mProj, EnRenderMode renderMode, int shadowMapNumber);
	/// <summary>
	/// �X�P���g�����֘A�t����B
	/// </summary>
	/// <param name="skeleton">�X�P���g��</param>
	void BindSkeleton(Skeleton& skeleton);
	/// <summary>
	/// ���b�V���ɑ΂��Ė₢���킹���s���B
	/// </summary>
	/// <param name="queryFunc">�N�G���֐�</param>
	void QueryMeshs(std::function<void(const SMesh& mesh)> queryFunc)
	{
		for (const auto& mesh : m_meshs) {
			queryFunc(*mesh);
		}
	}
	/*void QueryMeshAndDescriptorHeap(std::function<void(const SMesh& mesh, const DescriptorHeap& ds)> queryFunc)
	{
		for( int i = 0; i < m_meshs.size(); i++ ){
			queryFunc(*m_meshs[i], m_descriptorHeap[i]);
		}
	}*/
	Skeleton* GetSkeleton()
	{
		return m_skeleton;
	}
private:
	/// <summary>
	/// tkm���b�V�����烁�b�V�����쐬�B
	/// </summary>
	/// <param name="mesh">���b�V��</param>
	/// <param name="meshNo">���b�V���ԍ�</param>
	/// <param name="fxFilePath">fx�t�@�C���̃t�@�C���p�X</param>
	/// <param name="vsEntryPointFunc">���_�V�F�[�_�[�̃G���g���[�|�C���g�̊֐���</param>
	/// <param name="psEntryPointFunc">�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�̊֐���</param>
	void CreateMeshFromTkmMesh(
		const TkmFile::SMesh& mesh, 
		int meshNo,
		const wchar_t* fxFilePath,
		const char* vsEntryPointFunc,
		const char* psEntryPointFunc );

	/// <summary>
	/// �f�B�X�N���v�^�q�[�v���쐬�B
	/// </summary>
	void CreateDescriptorHeaps();
private:
	//�g��SRV���ݒ肳��郌�W�X�^�̊J�n�ԍ��B
	const int EXPAND_SRV_REG__START_NO = 10;
	/// <summary>
	/// �萔�o�b�t�@�B
	/// </summary>
	/// <remarks>
	/// ���̍\���̂�ύX������ASimpleModel.fx��CB���ύX����悤�ɁB
	/// </remarks>
	struct SConstantBuffer {
		Matrix mWorld;		//���[���h�s��B
		Matrix mView;		//�r���[�s��B
		Matrix mProj;		//�v���W�F�N�V�����s��B
		Matrix mLightView;		//���C�g�r���[�s��
		Matrix mLightProj;		//���C�g�v���W�F�N�V�����s��
		Matrix mLightViewProj[CascadeShadowMap::SHADOWMAP_NUM];	//���C�g�r���[�v���W�F�N�V�����s��
		Vector4 mFarList[CascadeShadowMap::SHADOWMAP_NUM];
		int isShadowReciever;	//�V���h�E���V�[�o�[�̃t���O
		int shadowMapNumber = 0;	//���Ԗڂ̃V���h�E�}�b�v�Ƀ����_�����O���邩
	};
	ConstantBuffer m_commonConstantBuffer[CascadeShadowMap::SHADOWMAP_NUM + 1];					//���b�V�����ʂ̒萔�o�b�t�@�B
	ConstantBuffer m_expandConstantBuffer;					//���[�U�[�g���p�̒萔�o�b�t�@
	IShaderResource* m_expandShaderResourceView = nullptr;	//���[�U�[�g���V�F�[�_�[���\�[�X�r���[�B
	StructuredBuffer m_boneMatricesStructureBuffer;			//�{�[���s��̍\�����o�b�t�@�B
	std::vector< SMesh* > m_meshs;							//���b�V���B
	typedef std::vector<DescriptorHeap> DescriptorHeapList;		//�f�B�X�N���v�^�q�[�v�B
	DescriptorHeapList m_descriptorHeapList[CascadeShadowMap::SHADOWMAP_NUM + 1];					//�ʏ�`��ƃJ�X�P�[�h�V���h�E�p�Ƀf�B�X�N���v�^�q�[�v��p�ӂ���
	Skeleton* m_skeleton = nullptr;								//�X�P���g���B
	void* m_expandData = nullptr;								//���[�U�[�g���f�[�^�B
	bool m_isInitDescriptorHeap = false;	//�f�B�X�N���v�^�q�[�v���������������H
	bool m_isShadowReciever = true;		//�V���h�E���V�[�o�[�̃t���O
};