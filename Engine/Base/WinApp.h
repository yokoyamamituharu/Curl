#pragma once
#include <Windows.h>

class WinApp
{
public: //�ÓI�����o�ϐ�
	// �E�B���h�E�T�C�Y
	static const int window_width = 1280;  // ����
	static const int window_height = 720;  // �c��
public: //�ÓI�����o�֐�
	/// <summary>
	/// �E�B���h�E�v���V�[�W��
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">���b�Z�[�W�ԍ�</param>
	/// <param name="wparam">���b�Z�[�W���</param>
	/// <param name="lparam">���b�Z�[�W���</param>
	/// <returns>����</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// ���b�Z�[�W�̏���
	/// </summary>
	/// <returns></returns>
	bool ProcessMessage();
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();
	/// <summary>
	/// �E�B���h�E�X�^�C���̎w��
	/// </summary>
	void SetWindowStyle(LONG windowStyle);
	/// <summary>
	/// �E�B���h�E�n���h���̎擾
	/// </summary>
	/// <returns></returns>
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetInstance() { return w.hInstance; }

private: //�����o�ϐ�
	HWND hwnd = nullptr;
	WNDCLASSEX w;
	LONG windowStyle; //�E�B���h�E�X�^�C��
};

