#include "Astar.h"

AStar* AStar::GetInstance()
{
	static AStar* instance = new AStar();
	return instance;
}

void AStar::Initialize(int cost[MapHeight][MapWidth])
{
	

	//int cost[MapHeight][ MapWidth] = {};
	SetTableCost(cost);

	CreateGraph();

	
}

void AStar::NodeUpdate(int y,int x)
{

	//隣接ノード設定
	Cell adjacent_cells[] = {
		Cell(x,y - 1),
		Cell(x - 1,y),
		Cell(x + 1,y),
		Cell(x,y + 1),
	};

	//隣接ノードの追加
	for (const Cell& cell : adjacent_cells)
	{
		if (IsCellWithinTheRange(cell.X, cell.Y) == true && CostTable[cell.Y][cell.X] == 1) {
			Graph[y][x].Edges.push_back(&Graph[cell.Y][cell.X]);
		}
	}
}

bool IsCellWithinTheRange(int x, int y)
{
	if (x >= 0 && x < MapWidth &&
		y >= 0 && y < MapHeight)
	{
		return true;
	}

	return false;
}

bool IsEqualCell(const Cell& a, const Cell& b)
{
	if (a.X == b.X &&
		a.Y == b.Y)
	{
		return true;
	}

	return false;
}

bool Less(AStar::Node* a, AStar::Node* b)
{
	if (a->TotalCost < b->TotalCost) {
		return true;
	}
	return false;
}

bool AddAdjacentNode(std::list<AStar::Node*>& openList, std::list<AStar::Node*>& closeList, AStar::Node* adjacentNode, float cost)
{
	bool Update = true;

	if (EraseNode(closeList, adjacentNode, cost) == EraseResult::CouldntErased) {
		Update = false;
	}

	if (EraseNode(openList, adjacentNode, cost) == EraseResult::CouldntErased) {
		Update = false;
	}

	if (Update) {
		openList.push_back(adjacentNode);
		return true;
	}

	return false;
}

int EraseNode(std::list<AStar::Node*>& list, AStar::Node* newNode, float newCost)
{
	// クローズリストチェック
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// ノードと同じセルがあるか調べる
		if (IsEqualCell(newNode->Position, (*itr)->Position) == true)
		{
			// コストの比較
			if (newCost < (*itr)->TotalCost)
			{
				list.erase(itr);
				return EraseResult::Erased;
			}
			else
			{
				return EraseResult::CouldntErased;
			}
		}
	}

	return EraseResult::NotFound;
}

float AStar::CalculateHeuristic(const Node* node, const Node* Goal)
{
	float x = fabsf(float(Goal->Position.X) - float(node->Position.X));
	float y = fabsf(float(Goal->Position.Y) - float(node->Position.Y));

	return sqrtf(x * x + y * y);
}

void AStar::CreateGraph()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Graph[y][x].Position.X = x;
			Graph[y][x].Position.Y = y;

			NodeUpdate(y,x);
		}
	}

	printf("aaaaaaaaaaaaaaaaaaaaa");

}

std::list<Cell>& AStar::AStarActivate(Cell& start, Cell& goal)
{
	std::list<Node*> openList;
	std::list<Node*> closeList;

	const Node* goalNode = &Graph[goal.Y][goal.X];

	Cell lastUpdateCell[MapHeight][MapWidth];

	InitializeCost();

	openList.push_back(&Graph[start.Y][start.X]);

	int count = 0;

	while (openList.empty() == false)
	{
		Node* searchNode = (*openList.begin());
		openList.erase(openList.begin());

		if (IsEqualCell(searchNode->Position, goalNode->Position)) {
			closeList.push_back(searchNode);
			break;
		}

		for (Node* adjacentNode : searchNode->Edges)
		{
			//コスト計算
			if (adjacentNode->HeuristicCost == Infinity)
			{
				adjacentNode->HeuristicCost = CalculateHeuristic(adjacentNode, goalNode);
			}
			float edgeCost = float(CostTable[adjacentNode->Position.Y][adjacentNode->Position.X]);
			float totalCost = searchNode->TotalCost;

			float cost = edgeCost + adjacentNode->HeuristicCost + totalCost;

			//ノード追加
			if (AddAdjacentNode(openList, closeList, adjacentNode, cost))
			{
				//トータルコスト更新
				adjacentNode->TotalCost = cost;

				lastUpdateCell[adjacentNode->Position.Y][adjacentNode->Position.X] = searchNode->Position;
			}

			
		}
		bool close = true;

		// クローズリストチェック
		for (auto itr = closeList.begin(); itr != closeList.end(); itr++)
		{
			// ノードと同じセルがあるか調べる
			if (IsEqualCell(searchNode->Position, (*itr)->Position) == true)
			{
				close = false;
				break;
			}
		}

		// 同じノードが無かったので追加
		if (close == true)
		{
			// このノードの探索終了
			closeList.push_back(searchNode);
		}

		openList.sort(Less);
	}

	//ルート復元
	std::list<Cell> routeList;

	routeList.push_back(goal);
	while (!routeList.empty())
	{
		Cell route = routeList.front();

		if (IsEqualCell(route, start)) {

			return routeList;

			for (Cell& cell : routeList)
			{
				printf("X = %d y = %d/n", cell.X, cell.Y);
			}
			break;
		}
		else
		{
			if (IsCellWithinTheRange(route.X, route.Y)) {
				routeList.push_front(lastUpdateCell[route.Y][route.X]);
			}
			else {
				printf("経路は見つからなかった...");
				break;
			}
		}
	}
	return routeList;
}

void AStar::InitializeCost()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Graph[y][x].HeuristicCost = Infinity;
			Graph[y][x].TotalCost = 0;
		}
	}
}
