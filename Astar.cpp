#include "Astar.h"

bool IsCellWithinTheRange(int x, int y)
{
	if (x >= 0 && x < MapWidth &&
		y >= 0 && y < MapHeight)
	{
		return true;
	}
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

bool Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost) {
		return true;
	}
	return false;
}

bool AddAdjacentNode(std::list<Node*>& openList, std::list<Node*>& closeList, Node* adjacentNode, float cost)
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

int EraseNode(std::list<Node*>& list, Node* newNode, float newCost)
{
	// �N���[�Y���X�g�`�F�b�N
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// �m�[�h�Ɠ����Z�������邩���ׂ�
		if (IsEqualCell(newNode->Position, (*itr)->Position) == true)
		{
			// �R�X�g�̔�r
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

float CalculateHeuristic(const Node* node, const Node* Goal)
{
	float x = fabsf(float(Goal->Position.X) - float(node->Position.X));
	float y = fabsf(float(Goal->Position.Y) - float(node->Position.Y));

	return sqrtf(x * x + y * y);
}

void CreateGraph()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Graph[y][x].Position.X = x;
			Graph[y][x].Position.Y = y;

			//�אڃm�[�h�ݒ�
			Cell adjacent_cells[] = {
				Cell(x,y - 1),
				Cell(x - 1,y),
				Cell(x + 1,y),
				Cell(x,y + 1),
			};

			//�אڃm�[�h�̒ǉ�
			for (const Cell& cell : adjacent_cells)
			{
				if (IsCellWithinTheRange(cell.X, cell.Y) == true && CostTable[cell.Y][cell.X]) {
					Graph[y][x].Edges.push_back(&Graph[cell.Y][cell.X]);
				}
			}
		}
	}
}

std::list<Cell> AStarActivate(Cell& start, Cell& goal)
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
			//�R�X�g�v�Z
			if (adjacentNode->HeuristicCost == Infinity)
			{
				adjacentNode->HeuristicCost = CalculateHeuristic(adjacentNode, goalNode);
			}
			float edgeCost =float(CostTable[adjacentNode->Position.Y][adjacentNode->Position.X]);
			float totalCost = searchNode->TotalCost;

			float cost = edgeCost + adjacentNode->HeuristicCost + totalCost;

			//�m�[�h�ǉ�
			if (AddAdjacentNode(openList, closeList, adjacentNode, cost)) 
			{
				//�g�[�^���R�X�g�X�V
				adjacentNode->TotalCost = cost;

				lastUpdateCell[adjacentNode->Position.Y][adjacentNode->Position.X] = searchNode->Position;
			}

			closeList.push_back(searchNode);

			openList.sort(Less);
		}
	}

	//���[�g����
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
				printf("�o�H�͌�����Ȃ�����...");
				break;
			}
		}
	}
}

void InitializeCost()
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
