#include <climits>
#include <random>
#include "changeWorstSolver.h"

void ChangeWorstSolver::generateNewSolution(int & currentScore, int & iterWithoutImprove)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, (int)gridSize);

    pair<int, int> tmpIgnorePosition, ignorePosition;
    int score = this->calculateScore();
    int difference = INT_MIN;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (isMutable[i][j])
            {
                tmpIgnorePosition = make_pair(i, j);
                int ignoreScore = this->calculateScore(tmpIgnorePosition);
                if (score - ignoreScore > difference)
                {
                    difference = score - ignoreScore;
                    ignorePosition = tmpIgnorePosition;
                }
            }
        }
    }

    int originNumber = playGrid[ignorePosition.first][ignorePosition.second];
    playGrid[ignorePosition.first][ignorePosition.second] = distribution(gen);

    int newScore = this->calculateScore();
    if (newScore < currentScore)
    {
        currentScore = newScore;
        iterWithoutImprove = 0;
    }
    else
    {
        iterWithoutImprove++;
        playGrid[ignorePosition.first][ignorePosition.second] = originNumber;
    }
}