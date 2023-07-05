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

private: //�����o�֐�
    /// <summary>
    /// ���Ԃ����]�p�����߂�
    /// </summary>
    void RotCulc();

private: //�����o�ϐ�
    //���ݎ���
    int32_t nowTime_;
    //�ő厞��
    int32_t maxTime_;
    //���v
    std::unique_ptr<Sprite> watch_;
    //���j
    std::unique_ptr<Sprite> bigHand_;
    //�Z�j
    std::unique_ptr<Sprite> littleHand_;
    //���j��]
    float bigHandRot_;
    //�Z�j��]
    float littleHandRot_;
};