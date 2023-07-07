#pragma once
#include <vector>

const int MapWidth = 10;
const int MapHeight = 10;
const int Infinity = 100000;

// 削除結果
enum EraseResult
{
	NotFound,		// 未発見
	Erased,			// 削除
	CouldntErased	// 削除できない
};

class AStar {
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

	AStar() = default;
	~AStar() = default;
	AStar(const AStar& obj) = delete;
	void operator=(const AStar& obj) = delete;


	Node Graph[MapHeight][MapWidth];

	bool IsCellWithinTheRange(int x, int y);
	bool IsEqualCell(const Cell& a, const Cell& b);
	bool AddAdjacentNode(std::list<Node*>& openList, std::list<Node*>& closeList, Node* adjacentNode, float cost);
	bool Less(Node* a, Node* b);

	//リスト内の削除条件に合ったノードを削除
	EraseResult EraseNode(std::list<Node*>& list, Node* newNode, float newCost);

	// ヒューリスティックコスト計算(ノードとゴールまでの距離を返している)
	float CalculateHeuristic(const Node* node, const Node* Goal);

	void CreateGraph();

	void AStarActivate(Cell& start, Cell& goal);

	void InitializeCost();
};

int CostTable[MapHeight][MapWidth] =
{
	//0  1  2  3  4
	{ 1, 1, 1, 1, 1, }, // 0
	{ 1, 0, 1, 1, 0, }, // 1
	{ 1, 0, 0, 1, 1, }, // 2
	{ 1, 1, 0, 0, 1, }, // 3
	{ 0, 1, 1, 1, 1, }, // 4
};
