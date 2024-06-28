#include <climits>
#include <random>
#include "minimizeSolver.h"

void MinimizeSolver::generateNewSolution(int & currentScore, int & iterWithoutImprove)
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

    int score = this->calculateScore();
    int newScore;
    int difference = 0;
    int originNumber = playGrid[Y][X];
    int newNumber;

    for (int i = 1; i < gridSize + 1; i++)
    {
        if (i == originNumber)
            continue;

        playGrid[Y][X] = i;
        int tmpScore = this->calculateScore();
        if (score - tmpScore > difference)
        {
            difference = score - tmpScore;
            newNumber = i;
            newScore = tmpScore;
        }
    }

    if (difference > 0)
    {
        playGrid[Y][X] = newNumber;
        currentScore = newScore;
        iterWithoutImprove = 0;
    }
    else
    {
        iterWithoutImprove++;
        playGrid[Y][X] = originNumber;
    }
}