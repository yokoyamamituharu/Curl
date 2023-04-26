#include "DebugText.h"

DebugText::DebugText() {

}

DebugText::~DebugText() {
	for (int32_t i = 0; i < _countof(spriteDatas); i++) {
		delete spriteDatas[i];
	}
}

void DebugText::Initialize(UINT texnumber) {
	//�S�ẴX�v���C�g�f�[�^�ɂ���
	for (int32_t i = 0; i < _countof(spriteDatas); i++) {
		//�X�v���C�g�𐶐�����
		spriteDatas[i] = Sprite::Create(texnumber, { 0, 0 });
	}
}

void DebugText::Print(const std::string& text, float x, float y, float scale = 1.0f) {
	//�S�Ă̕����ɂ���
	for (int32_t i = 0; i < text.size(); i++) {
		//�ő啶��������
		if (spriteIndex >= maxCharCount) {
			break;
		}

		//1�������o��(ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		int32_t fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int32_t fontIndexY = fontIndex / fontLineCount;
		int32_t fontIndexX = fontIndex % fontLineCount;

		//���W�v�Z
		spriteDatas[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y });
		spriteDatas[spriteIndex]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth, (float)fontHeight });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });

		//������1�i�߂�
		spriteIndex++;
	}
}

void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList) {
	//�S�Ă̕����̃X�v���C�g�ɂ���
	for (int32_t i = 0; i < spriteIndex; i++) {
		//�X�v���C�g�`��
		spriteDatas[i]->Draw();
	}

	spriteIndex = 0;
}