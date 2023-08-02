#include "ParticleManager2d.h"

ParticleManager2d* ParticleManager2d::Create()
{
	ParticleManager2d* instance = new ParticleManager2d();
	return instance;
}

std::unique_ptr<ParticleManager2d> ParticleManager2d::UniquePtrCreate()
{
	std::unique_ptr<ParticleManager2d> instance = std::make_unique<ParticleManager2d>();
	return std::move(instance);
}

std::unique_ptr<ParticleManager2d::Particle2d> ParticleManager2d::ParticleCreate()
{
	std::unique_ptr<Particle2d> instance = std::make_unique<Particle2d>();
	return std::move(instance);
}

void ParticleManager2d::Update()
{

	//�����̐s�����p�[�e�B�N����S����
	particleList_.remove_if([](Particle2d& particle) {
		return particle.nowFrame_ >= particle.endFrame_;
		});

	for (std::forward_list<Particle2d>::iterator it = particleList_.begin(); it != particleList_.end(); it++) {

		// �o�߃t���[�������J�E���g
		it->nowFrame_++;
		// �i�s�x��0�`1�͈̔͂Ɋ��Z
		float f = (float)it->endFrame_ / it->nowFrame_;

		// ���x�ɉ����x�����Z
		it->velocity_ = it->velocity_ + it->accel_;

		// ���x�ɂ��ړ�
		it->pos_ = it->pos_ + it->velocity_;

		// �J���[�̐��`���
		it->color_ = it->start_Color_ + (it->end_Color_ - it->start_Color_) / f;

		// �X�P�[���̐��`���
		it->size_ = it->start_Size_ + (it->end_Size_ - it->start_Size_) / f;

		// �X�P�[���̐��`���
		it->rot_ = it->start_Rot_ + (it->end_Rot_ - it->start_Rot_) / f;

		//�A���t�@�l�̐��`���
		it->alpha_ = it->start_Alpha_ + (it->end_Alpha_ - it->start_Alpha_) / f;

		//�p�[�e�B�N���X�V
		it->particle_->SetPosition(it->pos_);
		it->particle_->SetColor(it->color_);
		it->particle_->SetSize(it->size_);
		it->particle_->SetRotation(it->rot_);
		it->particle_->SetAlpha(it->alpha_);
	}

}

void ParticleManager2d::Draw()
{
	for (Particle2d& particle : particleList_) {
		particle.particle_->Draw();
	}
}

void ParticleManager2d::Add(int32_t life, Vector2 position, Vector2 velocity, Vector2 accel, Vector2 start_scale, Vector2 end_scale, Vector3 start_color, Vector3 end_color, float start_alpha, float end_alpha)
{
	// ���X�g�ɗv�f��ǉ�
	particleList_.emplace_front();
	// �ǉ������v�f�̎Q��
	Particle2d& p = particleList_.front();
	p.pos_ = position;
	p.velocity_ = velocity;
	p.accel_ = accel;
	p.start_Size_ = start_scale;
	p.end_Size_ = end_scale;
	p.start_Color_ = start_color;
	p.end_Color_ = end_color;
	p.start_Alpha_ = start_alpha;
	p.end_Alpha_ = end_alpha;
	p.endFrame_ = life;

	p.particle_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::particleCircle, position);
}
