#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>

struct Point
{
    int x, y;

    bool operator==(const Point &second) { return x == second.x && y == second.y; };
};

class Maze
{
public:
    Maze(std::ifstream &inputFile)
    {
        if (!inputFile.is_open())
        {
            std::cout << "Error: Unable to open the file." << std::endl;
        }

        std::string line, keyword, comma;

        while (std::getline(inputFile, line))
        {
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

    void Solve(const std::string &algorithm)
    {
        if (start == destination)
            std::cout << "\nStart and Destination are the same point!\n"
                      << std::endl;
        else if (algorithm == "BFS")
            BFS();
        else if (algorithm == "DFS")
            DFS();
        else if (algorithm == "RS")
            RandomSearch();
        else
            std::cout << "Error: Invalid algorithm." << std::endl;
    };

    void PrintStep(size_t step, bool flag)
    {
        /*
        if (flag)
            std::cout << "Final path!!!" << '\n'
                      << std::endl;
        else
            std::cout << "Step " << step << '\n'
                      << std::endl;
        */

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
                else if (distance[i][j] > 0)
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
        std::cout << '\n';
        for (size_t i = 0; i < print.size(); i++)
        {
            for (size_t j = 0; j < print[i].size(); j++)
            {
                std::cout << print[i][j];
            }
            std::cout << std::endl;
        }
        /*
        if (flag)
            std::cout << "\nLength of the path (o): " << distance[destination.y][destination.x] << std::endl;
        */
        std::cout << "--------------------------------------------------------------------------------------------------\n"
                  << "S Start\nE End\n# Opened node\no Path\nX Wall\nspace Fresh node\n"
                  << "--------------------------------------------------------------------------------------------------\n"
                  << "Nodes expanded: " << expandedNodes << "\n"
                  << "Path length: " << distance[destination.y][destination.x]
                  << std::endl;
        print.clear();
    };

    void Clean()
    {
        distance.clear();
        parent.clear();
    };

private:
    bool isValidMove(const int &x, const int &y) { return x >= 0 && y >= 0 && maze[y][x] != 'X'; };

    void BFS()
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
                        expandedNodes++;
                        distance[nextY][nextX] = distance[currentPoint.y][currentPoint.x] + 1;
                        parent[nextY][nextX] = currentPoint;

                        if (destination.x == nextX && destination.y == nextY)
                        {
                            PrintStep(step++, true);
                            return;
                        }
                        // PrintStep(step++, false);
                    }
                }
            }
        }
    };

    void DFS()
    {
        distance = std::vector<std::vector<int>>(maze.size(), std::vector<int>(maze[0].size(), -1));
        parent = std::vector<std::vector<Point>>(maze.size(), std::vector<Point>(maze[0].size(), {-1, -1}));

        std::vector<Point> open;
        open.push_back(start);
        distance[start.y][start.x] = 0;
        std::vector<Point> closed;

        int moveX[] = {1, -1, 0, 0};
        int moveY[] = {0, 0, 1, -1};

        while (!open.empty())
        {
            Point currentPoint = open.front();
            open.erase(open.begin());

            if (currentPoint.x == destination.x && currentPoint.y == destination.y)
            {

                PrintStep(step++, true);
                return;
            }
            else
            {
                std::vector<Point> currentIteration;
                for (int i = 0; i < 4; i++)
                {
                    int nextX = currentPoint.x + moveX[i];
                    int nextY = currentPoint.y + moveY[i];
                    Point nextPoint = {nextX, nextY};

                    if (isValidMove(nextX, nextY) &&
                        ((std::find_if(open.begin(), open.end(), [&](const Point &p)
                                       { return p.x == nextX && p.y == nextY; })) == open.end()) &&
                        ((std::find_if(closed.begin(), closed.end(), [&](const Point &p)
                                       { return p.x == nextX && p.y == nextY; })) == closed.end()) &&
                        ((std::find_if(currentIteration.begin(), currentIteration.end(), [&](const Point &p)
                                       { return p.x == nextX && p.y == nextY; })) == currentIteration.end()))
                    {
                        currentIteration.push_back(nextPoint);
                        expandedNodes++;
                        distance[nextY][nextX] = distance[currentPoint.y][currentPoint.x] + 1;
                        parent[nextY][nextX] = currentPoint;
                        // PrintStep(step++, false);
                    }
                }
                currentIteration.insert(currentIteration.end(), open.begin(), open.end());
                open = currentIteration;
                closed.push_back(currentPoint);
                currentIteration.clear();
            }
        }
    };

    void RandomSearch()
    {
        distance = std::vector<std::vector<int>>(maze.size(), std::vector<int>(maze[0].size(), -1));
        parent = std::vector<std::vector<Point>>(maze.size(), std::vector<Point>(maze[0].size(), {-1, -1}));

        std::vector<Point> open;
        open.push_back(start);
        distance[start.y][start.x] = 0;
        std::vector<Point> closed;

        int moveX[] = {1, -1, 0, 0};
        int moveY[] = {0, 0, 1, -1};

        while (!open.empty())
        {
            std::random_device rd;
            std::mt19937 rng(rd());

            std::uniform_int_distribution<int> distribution(0, open.size() - 1);
            int random_index = distribution(rng);

            Point currentPoint = open[random_index];
            open.erase(open.begin() + random_index);

            if (currentPoint.x == destination.x && currentPoint.y == destination.y)
            {
                PrintStep(step++, true);
                return;
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    int nextX = currentPoint.x + moveX[i];
                    int nextY = currentPoint.y + moveY[i];
                    Point nextPoint = {nextX, nextY};

                    if (isValidMove(nextX, nextY) &&
                        ((std::find_if(open.begin(), open.end(), [&](const Point &p)
                                       { return p.x == nextX && p.y == nextY; })) == open.end()) &&
                        ((std::find_if(closed.begin(), closed.end(), [&](const Point &p)
                                       { return p.x == nextX && p.y == nextY; })) == closed.end()))
                    {
                        open.push_back(nextPoint);
                        expandedNodes++;
                        distance[nextY][nextX] = distance[currentPoint.y][currentPoint.x] + 1;
                        parent[nextY][nextX] = currentPoint;
                        // PrintStep(step++, false);
                    }
                }
                closed.push_back(currentPoint);
            }
        }
    };

    std::vector<std::vector<char>> maze;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<Point>> parent;
    Point start, destination;
    size_t step = 1, expandedNodes = 0;
    bool flag = false;
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Error: Mismatch number of CLI parametrs." << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    // std::ifstream input("dataset/4.txt");

    Maze maze = Maze(input);
    maze.Solve(argv[2]);

    // Maze maze = Maze(input);
    // maze.Solve("DFS");

    maze.Clean();

    return 0;
}