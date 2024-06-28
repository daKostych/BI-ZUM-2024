#include <random>
#include "neighborSolver.h"

void NeighborSolver::generateNewSolution(int & currentScore, int & iterWithoutImprove)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, (int)gridSize);

    int X, Y;
    vector<int> shiftX = {1, -1, 0, 0};
    vector<int> shiftY = {0, 0, 1, -1};

    bool stop = false;
    int iteration = 0;
    while (!stop && iteration < pow(gridSize, 2))
    {
        X = distribution(gen) - 1;
        Y = distribution(gen) - 1;
        if (!isMutable[Y][X])
            continue;

        for (int i = 0; i < 4; i++)
        {
            if (Y + shiftY[i] == (int)gridSize || Y + shiftY[i] == -1 ||
                X + shiftX[i] == (int)gridSize || X + shiftX[i] == -1)
                continue;
            if (playGrid[Y][X] == playGrid[Y + shiftY[i]][X + shiftX[i]])
            {
                stop = true;
                break;
            }
        }
        iteration++;
    }

    int originNumber = playGrid[Y][X];
    playGrid[Y][X] = distribution(gen);

    int newScore = this->calculateScore();
    if (newScore < currentScore)
    {
        currentScore = newScore;
        iterWithoutImprove = 0;
    }
    else
    {
        iterWithoutImprove++;
        playGrid[Y][X] = originNumber;
    }
}