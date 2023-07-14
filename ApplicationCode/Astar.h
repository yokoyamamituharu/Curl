#pragma once
#include <vector>
#include <list>

const int Infinity = 100000;

// �폜����
enum EraseResult
{
	NotFound,		// ������
	Erased,			// �폜
	CouldntErased	// �폜�ł��Ȃ�
};

struct Cell
{
	int X{};
	int Y{};

	Cell() :
		X(-1),
		Y(-1)
	{
	}

	Cell(int x, int y)
	{
		X = x;
		Y = y;
	}
};
struct Node {
	Node() :
		Node(0, 0)
	{
	}

	Node(int x, int y) :
		Position(x, y),
		HeuristicCost(Infinity),
		TotalCost(0)
	{
		Edges.clear();
	}

	Cell Position;
	std::vector<Node*> Edges;
	float HeuristicCost;
	float TotalCost;
};

class AStar {
	int MapWidth = 10;
	int MapHeight = 10;

	Node Graph[MapHeight][MapWidth];
	int CostTable[MapHeight][MapWidth];


public:
	AStar(const AStar& astar) = delete;
	AStar& operator=(const AStar& astar) = delete;

	static AStar* GetInstance();

private:
	AStar() = default;
	~AStar() = {};

	std::list<Cell> AStarActivate(Cell& start, Cell& goal);

	//���X�g���̍폜�����ɍ������m�[�h���폜
	int EraseNode(std::list<Node*>& list, Node* newNode, float newCost);

	// �q���[���X�e�B�b�N�R�X�g�v�Z(�m�[�h�ƃS�[���܂ł̋�����Ԃ��Ă���)
	float CalculateHeuristic(const Node* node, const Node* Goal);

	void CreateGraph();

	void InitializeCost();

	//�X�e�[�W�̃R�X�g��ݒ�
	inline void SetTableCost(int cost[][]) { this->CostTable = cost; }
	inline void SetStageWidth(int size) { this->MapWidth = size; }
	inline void SetStageHeight(int size) { this->MapHeight = size; }
};

bool IsCellWithinTheRange(int x, int y);
bool IsEqualCell(const Cell& a, const Cell& b);
bool AddAdjacentNode(std::list<Node*>& openList, std::list<Node*>& closeList, Node* adjacentNode, float cost);
bool Less(Node* a, Node* b);


int CostTable[MapHeight][MapWidth] =
{
	//0  1  2  3  4
	{ 1, 1, 1, 1, 1, }, // 0
	{ 1, 0, 1, 1, 0, }, // 1
	{ 1, 0, 0, 1, 1, }, // 2
	{ 1, 1, 0, 0, 1, }, // 3
	{ 0, 1, 1, 1, 1, }, // 4
};
