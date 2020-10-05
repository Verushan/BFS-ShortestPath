#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int numRows, numCols;

class point
{
public:
    int row = -1, col = -1; // Members of this structure

    point() {} // Default constructor

    point(int row, int col) // Additional constructor
    {
        this->row = row;
        this->col = col;
    }

    bool operator!=(point &other) // Used for comparisions
    {
        return row != other.row || col != other.col;
    }

    bool operator==(point &other)
    {
        return row == other.row && col == other.col;
    }
};

class node // Combines the two properties (parent array and visited array) into one type
{
public:
    point parent;
    bool visited = false;

    node(){};
};

void Display(vector<vector<char>> &maze)
{
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
            cout << maze[r][c];

        cout << endl;
    }
}

bool isValid(vector<vector<char>> &maze, point &curr)
{
    if (curr.row < 0 || curr.row >= numRows || curr.col < 0 || curr.col >= numCols || maze[curr.row][curr.col] == 'x')
        return false;

    return true;
}

void BFS(point &source, point &goal, vector<vector<char>> &maze)
{
    point invalid = point();
    vector<vector<node>> nodes(numRows, vector<node>(numCols, node()));     // Will track our visits and update values as we go
    vector<pair<int, int>> neighbours = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // Used to traverse cell neighbours

    queue<point> toVisit;
    toVisit.push(source);

    while (!toVisit.empty() && !nodes[goal.row][goal.col].visited)
    {
        point curr = toVisit.front();
        toVisit.pop();

        for (pair<int, int> &offset : neighbours)
        {
            point currCell = point(curr.row + offset.first, curr.col + offset.second);

            if (isValid(maze, currCell) && nodes[currCell.row][currCell.col].visited == false)
            {
                toVisit.push(currCell);
                nodes[currCell.row][currCell.col].parent = curr;
                nodes[currCell.row][currCell.col].visited = true;
            }
        }
    }

    if (toVisit.empty() && !nodes[goal.row][goal.col].visited)
        cout << "No Path" << endl;
    else
    {
        point curr = nodes[goal.row][goal.col].parent;

        while (curr != source)
        {
            maze[curr.row][curr.col] = '*';
            curr = nodes[curr.row][curr.col].parent;
        }

        Display(maze);
    }
}

int main()
{
    string inp;
    point source, goal;

    cin >> numRows >> numCols;

    vector<vector<char>> maze(numRows, vector<char>(numCols));

    cin.ignore(); // Ignore remaining whitespace and \n

    for (int i = 0; i < numRows; i++)
    {
        getline(cin, inp);

        for (int j = 0; j < numCols; j++)
        {
            maze[i][j] = inp[j];

            if (maze[i][j] == 'S')
                source = point(i, j);
            else if (maze[i][j] == 'G')
                goal = point(i, j);
        }
    }

    BFS(source, goal, maze);
    return 0;
}