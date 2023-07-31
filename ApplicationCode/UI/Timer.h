#pragma once
#include "Sprite.h"

class Timer
{
public: //�����o�֐�
    Timer() = default;
    ~Timer() = default;
    /// <summary>
    /// ������
    /// </summary>
    void Initialize(const int32_t maxTime);
    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();
    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw();
    /// <summary>
    /// ���v�J���t���O���Z�b�g
    /// </summary>
    /// <param name="isOpen">���v�J���t���O</param>
    void SetIsWatchOpen(bool isOpen) { isWatchOpen_ = isOpen; }

    /// <summary>
    /// �^�C�}�[�X�^�[�g
    /// </summary>
    /// <param name="isTimerStart"></param>
    void SetIsTimerStart(bool isTimerStart) { isTimerStart_ = isTimerStart; }
    /// <summary>
    /// ���݂̃^�C���̊������擾
    /// </summary>
    int32_t GetTimeRange() { return nowTime_ / maxTime_; }

private: //�����o�֐�
    /// <summary>
    /// ���Ԃ����]�p�����߂�
    /// </summary>
    void RotCulc();

private: //�ÓI�����o�ϐ�
    //�A�j���[�V�����^�C�}�[
    int32_t animationTime = 6;

private: //�����o�ϐ�
    //���ݎ���
    int32_t nowTime_;
    //�ő厞��
    int32_t maxTime_;
    //���v
    std::unique_ptr<Sprite> watch_[7];
    //���j
    std::unique_ptr<Sprite> bigHand_;
    //���j��]
    float bigHandRot_;
    //���v�A�j���[�V������
    int32_t watchAnimeCount_;
    //���v�J���t���O
    bool isWatchOpen_;
    //�^�C�}�[�X�^�[�g�t���O
    bool isTimerStart_;
    //���v�J�A�j���[�V�����^�C�}�[
    int32_t animationTimer_;
};