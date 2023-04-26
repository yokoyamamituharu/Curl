#pragma once
#include "DirectXSetting.h"
#include <cstdlib>

class TextDraw
{
private: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(const std::string& textFormatKey, const std::string& solidColorBrushKey, const std::wstring& text, const D2D1_RECT_F& rect);

private: //�ÓI�����o�ϐ�
	//�f�t�H���g�t�H���g�T�C�Y
	static const int32_t defaultFontSize = 32;
	//�f�t�H���g�t�H���g����
	static const int32_t defaultFontWeight = 1000;
	//�f�t�H���g�t�H���g
	static const std::wstring defaultFont;

private: //�����o�ϐ�

};

