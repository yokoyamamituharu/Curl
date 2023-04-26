#include "MouseInput.h"

MouseInput* MouseInput::GetIns()
{
	static MouseInput instance;
	return &instance;
}

void MouseInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	//�}�E�X�f�o�C�X����
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (devMouse != nullptr) {
		//���̓f�[�^�`���̃Z�b�g
		result = devMouse->SetDataFormat(&c_dfDIMouse);
		//�r�����䃌�x���̃Z�b�g
		result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

void MouseInput::Update() {
	HRESULT result;

	//�O��̃}�E�X�̃N���b�N��ۑ�
	preMouseState = mouseState;
	//�}�E�X���̍X�V
	if (devMouse != nullptr) {
		result = devMouse->Acquire();
		//�}�E�X�̓��͏����擾����
		result = devMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
		//�}�E�X�J�[�\���̈ʒu���擾
		GetCursorPos(&mousePoint);
		//�擾�����J�[�\���̈ʒu���E�B���h�E��̈ʒu�ɕϊ�
		ScreenToClient(winApp->GetHwnd(), &mousePoint);
	}
}

bool MouseInput::PushClick(BYTE mouseClick) {
	//�w��L�[�������Ă����true��Ԃ�
	if (mouseState.rgbButtons[mouseClick] & (0x80)) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool MouseInput::TriggerClick(BYTE mouseClick) {
	//�O��͉����Ă��Ȃ��āA����͉����Ă����true��Ԃ�
	if (!preMouseState.rgbButtons[mouseClick] && mouseState.rgbButtons[mouseClick]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}