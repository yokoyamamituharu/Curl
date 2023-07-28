#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include "TextDraw.h"
#include "Vector2.h"
#include <sstream>

class MessageWindow
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static MessageWindow* Create();
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X����</returns>
	static std::unique_ptr<MessageWindow> UniquePtrCreate();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(Vector2 playerPos, float playerRadius);
	/// <summary>
	/// �X�v���C�g�`�揈��
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// �e�L�X�g�`��
	/// </summary>
	void TextMessageDraw();
	/// <summary>
	/// �R�}���h���̓`�F�b�N
	/// </summary>
	void CommandCheck();
	/// <summary>
	/// �|�C���g�ړ��`�F�b�N
	/// </summary>
	void PointMoveCheck(Vector2 playerPos, float playerRadius);
	/// <summary>
	/// �J�E���^�[���Z�b�g
	/// </summary>
	/// <param name="counter">�J�E���^�[</param>
	void SetCounter(float counter) { counter_ = counter; }
	/// <summary>
	/// �J�E���g��������
	/// </summary>
	/// <param name="count">�J�E���g</param>
	void AddCounter(float count) { counter_ += count; }
	/// <summary>
	/// �J�E���^�[�̗ʂ��`�F�b�N
	/// </summary>
	void CounterCheck();
	/// <summary>
	/// �ǂݍ��ݏI���t���O�擾
	/// </summary>
	/// <returns>�ǂݍ��ݏI���t���O</returns>
	bool GetIsLoadEnd() { return isLoadEnd_; }
	/// <summary>
	/// �e�L�X�g���b�Z�[�W�f�[�^�ǂݍ���
	/// </summary>
	/// <param name="fileName">�ǂݍ��ރt�@�C����</param>
	void LoadTextMessageData(const std::string& fileName);
	/// <summary>
	/// �J�E���g�Ώێ擾
	/// </summary>
	/// <returns>�J�E���g�Ώ�</returns>
	std::wstring GetCountTarget() { return countTarget_; }

private: //�ÓI�����o�ϐ�
	//�E�B���h�E�J������
	static const int32_t windowOpenTime = 120;
	//�E�B���h�E������
	static const int32_t windowCloseTime = 120;

private: //�����o�ϐ�
	//�e�L�X�g�`��N���X
	std::unique_ptr<TextDraw> textDraw_;
	//�e�L�X�g�E�B���h�E�X�v���C�g
	std::unique_ptr<Sprite> textWindow_;
	//�e�L�X�g�E�B���h�E�T�C�Y
	Vector2 textWindowSize_;
	//���b�Z�[�W�f�[�^�X�V�ҋ@�t���O
	bool isMessageUpdateWait_;
	//���b�Z�[�W�f�[�^�ҋ@�^�C�}�[
	int32_t messageWaitTimer_;
	//���b�Z�[�W�f�[�^�`�抮���t���O
	bool isTextDrawComplete_;
	//���b�Z�[�W�f�[�^�i�[�p������
	std::stringstream textData_;
	//���b�Z�[�W�o�͗p������
	std::wstring drawMessage_;
	//���b�Z�[�W�i�[�p������
	std::wstring message_;
	//�v�b�V���R�}���h�i�[�p������
	std::wstring command_;
	//�J�E���g�^�[�Q�b�g�i�[�p������
	std::wstring countTarget_;
	//�E�B���h�E�J���^�C�}�[
	int32_t windowOpenTimer_;
	//�E�B���h�E���^�C�}�[
	int32_t windowCloseTimer_;
	//�e�L�X�g�X�s�[�h
	int32_t textSpeed_;
	//�e�L�X�g��
	int32_t textCount_;
	//�e�L�X�g�ǉ�����
	int32_t textAddTimer_;
	//�E�B���h�E�J�t���O
	bool isOpen_;
	//�R�}���h���͑ҋ@�t���O
	bool isCommand_;
	//�|�C���g�ړ��t���O
	bool isPointMove_;
	//�J�E���^�[�`�F�b�N�t���O
	bool isCountCheck_;
	//�ǂݍ��ݏI���t���O
	bool isLoadEnd_;
	//�ړ��|�C���g
	Vector2 movePoint_;
	//�ړ��|�C���g���a
	float movePointRadius_;
	//�J�E���^�[
	float counter_;
	//�}�b�N�X�J�E���g
	float maxCount_;
};
