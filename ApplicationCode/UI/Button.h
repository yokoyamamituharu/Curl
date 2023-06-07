#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include "MouseInput.h"
#include "Vector2.h"

class Button
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// �{�^���̃C���X�^���X����
	/// </summary>
	/// <param name="imageName">�摜��</param>
	/// <param name="pos">���W</param>
	/// <param name="size">�T�C�Y</param>
	/// <param name="rot">��]</param>
	/// <returns>�C���X�^���X</returns>
	static Button* CreateButton(ImageManager::ImageName imageName, const Vector2& pos, const Vector2& size, const float rot);

	/// <summary>
	/// �{�^���̃C���X�^���X����
	/// </summary>
	/// <param name="imageName">�摜��</param>
	/// <returns>�{�^��</returns>
	static std::unique_ptr<Button> CreateUniqueButton(ImageManager::ImageName imageName, const Vector2& pos, const Vector2& size, const float rot);

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Button() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Button() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(ImageManager::ImageName imageName, const Vector2& pos, const Vector2& size, const float rot);
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���W���Z�b�g
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(const Vector2& pos) { pos_ = pos; }

	/// <summary>
	/// �T�C�Y���Z�b�g
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(const Vector2& size) { size_ = size; }

	/// <summary>
	/// ��]���Z�b�g
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRot(const float rot) { rot_ = rot; }

	/// <summary>
	/// �A���t�@�l���Z�b�g
	/// </summary>
	/// <param name="alpha">�A���t�@�l</param>
	void SetAlpha(const float alpha) { alpha_ = alpha; }

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	Vector2 GetPos() { return pos_; }

	/// <summary>
	/// �T�C�Y���擾
	/// </summary>
	/// <returns></returns>
	Vector2 GetSize() { return size_; }

	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns></returns>
	float GetRot() { return rot_; }

	/// <summary>
	/// �N���b�N���m�t���O���擾
	/// </summary>
	/// <returns>�N���b�N���m�t���O</returns>
	bool GetIsClick() { return isClick_; }

private: //�����o�֐�
	/// <summary>
	/// �}�E�X���������Ă��邩�`�F�b�N
	/// </summary>
	bool MouseHitCheck();

private: //�����o�ϐ�
	//�{�^���X�v���C�g
	std::unique_ptr<Sprite> button_;
	//���W
	Vector2 pos_;
	//�T�C�Y
	Vector2 size_;
	//���T�C�Y
	Vector2 initSize_;
	//��]
	float rot_;
	//�A���t�@�l
	float alpha_;
	//���A���t�@�l
	float initAlpha_;
	//�N���b�N���m�t���O
	bool isClick_;
};