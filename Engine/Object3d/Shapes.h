#pragma once
#include "Object3d.h"
#include "Model.h"

class Shapes
{
public:
	Shapes() = default;
	~Shapes() = default;
	//Shapes(const Shapes& obj) = delete;
	//Shapes& operator=(const Shapes& obj) = delete;

public: //�ÓI�����o�֐�

	/// <summary>
	/// ���ʂ̎O�p�`�𐶐�
	/// </summary>
	/// <param name="vertices_1">���_1</param>
	/// <param name="vertices_2">���_2</param>
	/// <param name="vertices_3">���_3</param>
	/// <returns>���ʂ̎O�p�`</returns>
	static Model* CreateTriangle(const DirectX::XMFLOAT2& vertices_1, const DirectX::XMFLOAT2& vertices_2, const DirectX::XMFLOAT2& vertices_3, const std::string& textureName = "white1x1.png");

	/// <summary>
	/// ���ʂ̎l�p�`�𐶐�
	/// </summary>
	/// <param name="upperLeft">������W</param>
	/// <param name="lowerBottom">�E�����W</param>
	/// <returns>���ʂ̎l�p�`</returns>
	static Model* CreateSquare(DirectX::XMFLOAT2 upperLeft, DirectX::XMFLOAT2 lowerBottom, const std::string& textureName = "white1x1.png");

private: //�����o�ϐ�

};

