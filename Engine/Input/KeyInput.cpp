#include "KeyInput.h"

void KeyInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	//�L�[�{�[�h�f�o�C�X����
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void KeyInput::Update() {
	HRESULT result;

	//�O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();
	//�S�L�[�̓��͏����擾����
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool KeyInput::PushKey(BYTE keyNumber) {
	//�w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool KeyInput::HoldKey(BYTE keyNumber) {
	if (keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}
	return false;
}

bool KeyInput::TriggerKey(BYTE keyNumber) {
	//�O��͉����Ă��Ȃ��āA����͉����Ă����true��Ԃ�
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

KeyInput* KeyInput::GetIns()
{
	static KeyInput instance;
	return &instance;
}
