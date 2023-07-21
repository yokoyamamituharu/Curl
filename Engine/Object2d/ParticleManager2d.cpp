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
	//�S�p�[�e�B�N���̍X�V����
	for (Particle2d& particle : particleList_) {
		particle.nowFrame_++;
		particle.velocity_ += particle.accel_;
		particle.pos_ += particle.velocity_;
	}
	//�����̐s�����p�[�e�B�N����S����
	particleList_.remove_if([](Particle2d & particle) {
		return particle.nowFrame_ >= particle.endFrame_;
	});
}

void ParticleManager2d::Draw()
{
	for (Particle2d& particle : particleList_) {
		//particle.particle_->Draw();
	}
}

void ParticleManager2d::Add(const Particle2d& particle)
{
	//particleList_.emplace_front(particle);
}
