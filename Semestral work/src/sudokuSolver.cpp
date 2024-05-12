#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <set>
#include <chrono>
#include "sudokuSolver.h"

#define MAX_ITERATIONS 500000
#define MAX_ITERATIONS_WITHOUT_IMPROVEMENT 1000

int SudokuSolver::checkSubGrids(pair<int, int> ignorePosition)
{
    set<int> digits;
    int score = 0;

    for (size_t subGridX = 0; subGridX < gridSize; subGridX += subGridSize)
    {
        for (size_t subGridY = 0; subGridY < gridSize; subGridY += subGridSize)
        {
            for (size_t i = subGridX; i < subGridX + subGridSize; i++)
                for (size_t j = subGridY; j < subGridY + subGridSize; j++)
                    if (ignorePosition.first != i || ignorePosition.second != j)
                        digits.insert(playGrid[i][j]);

            (ignorePosition.first == -1 && ignorePosition.second == -1)
            ? score += (int)pow(subGridSize, 2) - (int)digits.size()
            : score += ((int)pow(subGridSize, 2) - 1) - (int)digits.size();

            digits.clear();
        }
    }
    return score;
}

int SudokuSolver::calculateScore(pair<int, int> ignorePosition)
{
    int score = 0;
    vector<bool> rowDigits(gridSize + 1, false);
    vector<bool> columnDigits(gridSize + 1, false);

    for (size_t i = 0; i < gridSize; i++)
    {
        for (size_t j = 0; j < gridSize; j++)
        {
            if (ignorePosition.first != i || ignorePosition.second != j)
            {
                if (rowDigits[playGrid[i][j]])
                    score++;
                else
                    rowDigits[playGrid[i][j]] = true;
            }

            if (ignorePosition.first != j || ignorePosition.second != i)
            {
                if (columnDigits[playGrid[j][i]])
                    score++;
                else
                    columnDigits[playGrid[j][i]] = true;
            }
        }
        fill(rowDigits.begin(), rowDigits.end(), false);
        fill(columnDigits.begin(), columnDigits.end(), false);
    }

    score += checkSubGrids(ignorePosition);
    return score;
}

void SudokuSolver::generateFirstSolution()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, (int)gridSize);

    for (size_t i = 0; i < gridSize; i++)
        for (size_t j = 0; j < gridSize; j++)
            if (playGrid[i][j] == 0)
            {
                playGrid[i][j] = distribution(gen);
                isMutable[i][j] = true;
            }
}

void SudokuSolver::regenerateFirstSolution()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, (int)gridSize);

    for (size_t i = 0; i < gridSize; i++)
        for (size_t j = 0; j < gridSize; j++)
            if (isMutable[i][j])
                playGrid[i][j] = distribution(gen);
}

void SudokuSolver::solve()
{
    this->generateFirstSolution();
    int solutionScore = this->calculateScore();
    int iteration = 0, iterWithoutImprove = 0;

    while (solutionScore != 0 && iteration != MAX_ITERATIONS)
    {
        iteration++;
        if (iterWithoutImprove == MAX_ITERATIONS_WITHOUT_IMPROVEMENT)
        {
            cout << "Iterations: " << iteration << '\n';
            this->printGrid();
            cout << "Regenerate first solution...\n";
            cout << "========================================================================================" << endl;
            this->regenerateFirstSolution();
            solutionScore = this->calculateScore();
            iterWithoutImprove = 0;
        }
        this->generateNewSolution(solutionScore, iterWithoutImprove);
    }
    algorithmIterations = iteration;
    this->printGrid(true);
}

void SudokuSolver::printGrid(bool printI)
{
    for (size_t i = 0; i < gridSize; i++)
    {
        for (size_t j = 0; j < gridSize; j++)
        {
            cout << playGrid[i][j] << ' ';
            if (playGrid[i][j] < 10)
                cout << ' ';
        }
        cout << endl;
    }
    cout << "Number of collisions: " << this->calculateScore() << '\n';
    if (printI)
        cout << "Number of algorithm iterations: " << algorithmIterations << '\n';
    cout << "========================================================================================" << endl;
}