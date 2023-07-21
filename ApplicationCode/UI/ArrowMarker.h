#pragma once
#include "Vector2.h"
#include "Sprite.h"

class ArrowMarker
{
public:
	ArrowMarker();
	~ArrowMarker();

	static ArrowMarker* Create(Vector2 pos);

	void Initialize(Vector2 pos);

	void SetPosition(Vector2 pos) { this->pos_ = pos; }

	void SetInvisible(bool isInvisble) { this->isInvisible_ = isInvisble; }

	void Update(Vector2 camera);

	void Draw();

private:
	Vector2 pos_ = {};	
	bool isMarker_ = false;
	bool isInvisible_ = false;
	Sprite* sprite_ = nullptr;
};

