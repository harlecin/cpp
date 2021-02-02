#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::abs;
using std::cout;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;

enum class State
{
    kEmpty,
    kObstacle,
    kClosed,
    kPath,
    kStart,
    kFinish
};

vector<State> ParseLine(string string)
{
    istringstream string_stream(string);
    char c;
    int n;
    vector<State> output;
    while (string_stream >> n >> c && c == ',')
    {
        if (n == 1)
        {
            output.push_back(State::kObstacle);
        }
        else
        {
            output.push_back(State::kEmpty);
        }
    }

    return output;
}

vector<vector<State>> ReadBoardFile(string path)
{
    std::ifstream board_file(path);
    vector<vector<State>> vec_board;

    if (board_file)
    {
        string line;
        int i = 0;
        while (getline(board_file, line))
        {
            vec_board.push_back(ParseLine(line));
        }
    }

    return vec_board;
}
/*
Compare f-values of two cells.
*/
bool Compare(const vector<int> node1, const vector<int> node2)
{

    bool node1_greater_node2 = (node1[2] + node1[3]) > (node2[2] + node2[3]);

    return node1_greater_node2;
}

/*
Sort the two-dimensional vector of ints in descending order.
*/
void CellSort(vector<vector<int>> *v)
{
    sort(v->begin(), v->end(), Compare);
}

int Heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{

    //Check point is on grid
    bool isOnGrid = (0 <= x) && (grid[0].size()) && (0 <= y) && (y <= grid.size());
    //Check if point is empty if on grid
    if (isOnGrid)
    {
        return (grid[x][y] == State::kEmpty);
    }
    return false;
}

void AddToOpen(int x, int y, int g, int h,
               vector<vector<int>> &open_nodes,
               vector<vector<State>> &grid)
{

    vector<int> node{x, y, g, h};

    open_nodes.push_back(node);
    grid[x][y] = State::kClosed;
}

void ExpandNeighbors(
    const vector<int> &current_node,
    int goal[2],
    vector<vector<int>> &open_nodes,
    vector<vector<State>> &grid)
{
    int x = current_node[0];
    int y = current_node[1];
    int g = current_node[2];

    vector<vector<int>> possibleMovements{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (vector<int> movement : possibleMovements)
    {
        int x_test = x + movement[0];
        int y_test = y + movement[1];
        if (CheckValidCell(x_test, y_test, grid))
        {
            int g_test = g + 1;
            int h = Heuristic(x_test, y_test, goal[0], goal[1]);
            AddToOpen(x_test, y_test, g_test, h, open_nodes, grid);
        }
    }
}

vector<vector<State>> Search(
    vector<vector<State>> grid,
    int init[2],
    int goal[2])
{

    vector<vector<int>> open_nodes{};

    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, open_nodes, grid);

    while (open_nodes.size() > 0)
    {
        CellSort(&open_nodes);
        vector<int> current_node = open_nodes.back();

        open_nodes.pop_back(); // remove last element from vector
        x = current_node[0];
        y = current_node[1];
        grid[x][y] = State::kPath;

        if (x == goal[0] && y == goal[1])
        {
            return grid;
        }
        ExpandNeighbors(current_node, goal, open_nodes, grid);
    }

    // We've run out of new nodes to explore and haven't found a path.
    cout << "No path found!"
         << "\n";
    return std::vector<vector<State>>{};
}

string CellString(State state)
{
    switch (state)
    {
    case State::kObstacle:
        return "⛰️   ";
    case State::kPath:
        return "🚗   ";
    case State::kStart:
        return "🚦   ";
    case State::kFinish:
        return "🏁   ";
    default:
        return "0   ";
    }
}

void PrintBoard(vector<vector<State>> board)
{
    //alternatively use `auto`
    for (vector<State> v : board)
    {
        for (State i : v)
        {
            cout << CellString(i) << " ";
        }
        cout << "\n";
    }
}

int main()
{
    int init[2]{0, 0}; //int-array
    int goal[2]{4, 5};

    vector<vector<State>> vec_board = ReadBoardFile("1.board");
    vector<vector<State>> solution = Search(vec_board, init, goal);
    PrintBoard(solution);
    return 0;
}