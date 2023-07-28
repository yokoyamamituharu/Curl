#pragma once
#include <vector>
#include <list>


const int MapWidth = 52;
const int MapHeight = 43;
const int Infinity = 100000;

// �폜����
enum EraseResult
{
	NotFound,		// ������
	Erased,			// �폜
	CouldntErased	// �폜�ł��Ȃ�
};


class AStar {
public:
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

private:
	Node Graph[MapHeight][MapWidth]{};
	int CostTable[MapHeight][MapWidth]{};


public:
	AStar(const AStar& astar) = delete;
	AStar& operator=(const AStar& astar) = delete;

	static AStar* GetInstance();

	static AStar* Create();

	std::list<Cell> AStarActivate(Cell& start, Cell& goal);
private:
	AStar() = default;
	~AStar() {};


	// �q���[���X�e�B�b�N�R�X�g�v�Z(�m�[�h�ƃS�[���܂ł̋�����Ԃ��Ă���)
	float CalculateHeuristic(const Node* node, const Node* Goal);

	void CreateGraph();

	void InitializeCost();

public:
	//�X�e�[�W�̃R�X�g��ݒ�
	inline void SetTableCost(int cost[MapHeight][MapWidth]) {

		for (int i = 0; i < MapHeight; i++)
		{
			for (int j = 0; j < MapWidth; j++)
			{
				CostTable[i][j] = cost[i][j];
			}
		}
	}
};

//���X�g���̍폜�����ɍ������m�[�h���폜
int EraseNode(std::list<AStar::Node*>& list, AStar::Node* newNode, float newCost);
bool IsCellWithinTheRange(int x, int y);
bool IsEqualCell(const AStar::Cell& a, const AStar::Cell& b);
bool AddAdjacentNode(std::list<AStar::Node*>& openList, std::list<AStar::Node*>& closeList, AStar:: Node* adjacentNode, float cost);
bool Less(AStar::Node* a, AStar::Node* b);