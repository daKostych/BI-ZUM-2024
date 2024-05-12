#include <random>
#include "randomSolver.h"

void RandomSolver::generateNewSolution(int & currentScore, int & iterWithoutImprove)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, (int)gridSize);

    int X, Y;
    while (true)
    {
        X = distribution(gen) - 1;
        Y = distribution(gen) - 1;
        if (isMutable[Y][X])
            break;
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