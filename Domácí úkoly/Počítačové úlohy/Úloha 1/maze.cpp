#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

struct Point
{
    int x, y;
};

class Maze
{
public:
    Maze(std::ifstream &inputFile, const std::string &algorithm)
    {
        if (!inputFile.is_open())
        {
            std::cout << "Unable to open the file" << std::endl;
        }

        std::string line, keyword, comma;

        while (std::getline(inputFile, line))
        {
            // std::cout << line << std::endl;
            if (!line.find("start"))
            {
                std::istringstream in(line);
                in >> keyword >> start.x >> comma >> start.y;
                in.clear();
            }
            else if (!line.find("end"))
            {
                std::istringstream in(line);
                in >> keyword >> destination.x >> comma >> destination.y;
                in.clear();
            }
            else
            {
                std::vector<char> row;
                for (char symbol : line)
                    row.push_back(symbol);
                maze.push_back(row);
            }
        }

        inputFile.close();
    };

    void Solve()
    {
        distance = std::vector<std::vector<int>>(maze.size(), std::vector<int>(maze[0].size(), -1));
        parent = std::vector<std::vector<Point>>(maze.size(), std::vector<Point>(maze[0].size(), {-1, -1}));

        std::queue<Point> Q;
        Q.push(start);
        distance[start.y][start.x] = 0;

        int moveX[] = {1, -1, 0, 0};
        int moveY[] = {0, 0, 1, -1};

        while (!Q.empty())
        {
            Point currentPoint = Q.front();
            Q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nextX = currentPoint.x + moveX[i];
                int nextY = currentPoint.y + moveY[i];

                if (isValidMove(nextX, nextY))
                {
                    if (distance[nextY][nextX] == -1)
                    {
                        Q.push({nextX, nextY});
                        distance[nextY][nextX] = distance[currentPoint.y][currentPoint.x] + 1;
                        parent[nextY][nextX] = currentPoint;

                        if (destination.x == nextX && destination.y == nextY)
                        {
                            PrintStep(step++, true);
                            return;
                        }
                    }
                }
            }
            PrintStep(step++, false);
        }
    };

    void PrintStep(size_t step, bool flag)
    {
        if (flag)
            std::cout << "The shortest path!!!" << '\n'
                      << std::endl;
        else
            std::cout << "Step " << step << '\n'
                      << std::endl;

        std::vector<std::vector<char>> print(maze.size(), std::vector<char>(maze[0].size(), ' '));
        for (int i = 0; i < (int)maze.size(); i++)
        {
            for (int j = 0; j < (int)maze[i].size(); j++)
            {
                if (maze[i][j] == 'X')
                    print[i][j] = 'X';
                else if (distance[i][j] == 0)
                    print[i][j] = 'S';
                else if (destination.y == i && destination.x == j)
                    print[i][j] = 'E';
                else if (distance[i][j] > 0 /*&& !flag*/)
                    print[i][j] = '#';
                else
                    print[i][j] = ' ';
            }
        }
        if (flag)
        {
            Point point = {parent[destination.y][destination.x].x, parent[destination.y][destination.x].y};
            while (true)
            {
                if (point.x == start.x && point.y == start.y)
                    break;

                print[point.y][point.x] = 'o';
                point = {parent[point.y][point.x].x, parent[point.y][point.x].y};
            }
        }
        for (size_t i = 0; i < print.size(); i++)
        {
            for (size_t j = 0; j < print[i].size(); j++)
            {
                std::cout << print[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------------------------------------------------------------------------------------------------------\n\n";
        print.clear();
    };

    void Clean()
    {
        distance.clear();
        parent.clear();
    };

private:
    bool isValidMove(const int &x, const int &y) { return x >= 0 && y >= 0 && maze[y][x] != 'X'; };

    std::vector<std::vector<char>> maze;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<Point>> parent;
    Point start, destination;
    size_t step = 1;
    bool flag = false;
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    // std::ifstream input("dataset/6.txt");

    Maze maze = Maze(input, argv[2]);
    // Maze maze = Maze(input, "BFS");
    maze.Solve();
    maze.Clean();

    return 0;
}