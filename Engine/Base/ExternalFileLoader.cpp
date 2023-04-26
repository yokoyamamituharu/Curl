#include "ExternalFileLoader.h"
#include "DirectXSetting.h"
#include <fstream>

const std::string ExternalFileLoader::defaultDirectory = "Engine/Resources/GameData/";

ExternalFileLoader* ExternalFileLoader::GetIns()
{
	static ExternalFileLoader instance;
	return &instance;
}

std::stringstream ExternalFileLoader::ExternalFileOpen(const std::string& fileName)
{
	//�t�@�C���X�g���[��
	std::ifstream file;
	std::stringstream fileData;
	fileData.str("");
	fileData.clear(std::stringstream::goodbit);

	file.open(defaultDirectory + fileName);
	if (file.fail()) {
		assert(0);
	}

	fileData << file.rdbuf();

	file.close();

	return fileData;
}

std::wstring ExternalFileLoader::StringToWstring(const std::string& text)
{
	//�����T�C�Y���擾
	int32_t iBufferSize = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, (wchar_t*)NULL, 0);
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	//SJIS����wstring�ɕϊ�
	MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, cpUCS2, iBufferSize);
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	delete[] cpUCS2;

	return oRet;
}
