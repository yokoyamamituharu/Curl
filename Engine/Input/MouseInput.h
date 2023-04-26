#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class MouseInput final
{
public: //enum
	enum MouseState {
		LEFT_CLICK,
		RIGHT_CLICK,
		WHEEL_CLICK
	};

private: //�G�C���A�X
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MouseInput() = default;

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~MouseInput() = default;

	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	MouseInput(const MouseInput& obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	MouseInput& operator=(const MouseInput& obj) = delete;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �N���b�N���m
	/// </summary>
	bool PushClick(BYTE mouseClick);

	/// <summary>
	/// �N���b�N�����u�Ԃ̂݌��m
	/// </summary>
	bool TriggerClick(BYTE mouseClick);

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static MouseInput* GetIns();

	/// <summary>
	/// �}�E�X�|�C���^�̈ʒu�擾
	/// </summary>
	/// <returns></returns>
	const POINT& GetMousePoint() { return mousePoint; }

	/// <summary>
	/// �}�E�X�|�C���^��1�t���[���ł̈ړ��ʎ擾(X��)
	/// </summary>
	/// <returns>1�t���[���ł̈ړ���</returns>
	float GetMouseXVelocity() { return (float)mouseState.lX; }

	/// <summary>
	/// �}�E�X�|�C���^��1�t���[���ł̈ړ��ʎ擾(Y��)
	/// </summary>
	/// <returns>1�t���[���ł̈ړ���</returns>
	float GetMouseYVelocity() { return (float)mouseState.lY; }

private: //�����o�ϐ�
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> dinput;
	//�}�E�X�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devMouse;
	//�}�E�X�̏��
	DIMOUSESTATE mouseState;
	DIMOUSESTATE preMouseState;
	POINT mousePoint;
	//WindowsAPI
	WinApp* winApp = nullptr;
};

