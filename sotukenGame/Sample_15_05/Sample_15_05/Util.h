#pragma once
#include <string.h>

class Util {
public:
	/*!
	 * @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	 */
	static int MakeHash(const char* string)
	{
		int hash = 0;
		int l = (int)strlen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}

	/*!
	* @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	*/
	static int MakeHash(const wchar_t* string)
	{
		int hash = 0;
		int l = (int)wcslen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}
};