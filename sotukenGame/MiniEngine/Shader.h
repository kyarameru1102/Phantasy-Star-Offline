#pragma once


class Shader {
public:
	/// <summary>
	/// �s�N�Z���V�F�[�_�[�����[�h�B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	/// <param name="entryFuncName">�G���g���[�|�C���g�̊֐����B</param>
	void LoadPS(const wchar_t* filePath, const char* entryFuncName);
	/// <summary>
	/// ���_�V�F�[�_�[�����[�h�B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="entryFuncName">�G���g���[�|�C���g�̊֐����B</param>
	void LoadVS(const wchar_t* filePath, const char* entryFuncName);
	/// <summary>
	/// �R���s���[�g�V�F�[�_�[�����[�h�B
	/// </summary>
	/// <param name="filePath"></param>
	/// <param name="entryFuncName"></param>
	void LoadCS(const wchar_t* filePath, const char* entryFuncName);
	/// <summary>
	/// �R���p�C���ς݃V�F�[�_�[�f�[�^���擾�B
	/// </summary>
	/// <returns></returns>
	ID3DBlob* GetCompiledBlob() const
	{
		return m_blob;
	}

private:
	/// <summary>
	/// �V�F�[�_�[�����[�h�B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="entryFuncName">�G���g���[�|�C���g�̊֐����B</param>
	/// <param name="shaderModel">�V�F�[�_�[���f��</param>
	void Load(const wchar_t* filePath, const char* entryFuncName, const char* shaderModel);
private:
	ID3DBlob*	m_blob = nullptr;	//�R���p�C���ς݂̃V�F�[�_�[�f�[�^�B
};

