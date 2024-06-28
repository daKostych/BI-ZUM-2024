# pragma once

#include <vector>
#include <cmath>

using namespace std;

class SudokuSolver
{
public:
    // Constructor
    SudokuSolver(const vector<vector<int>> & pg)
            : playGrid(pg),
              gridSize(pg.size()),
              subGridSize((size_t)sqrt(pg.size()))
    {
        isMutable = vector<vector<bool>>(gridSize, vector<bool>(gridSize, false));
    }

    void solve();
    virtual void generateNewSolution(int & currentScore, int & iterWithoutImprove) = 0;

protected:
    void printGrid(bool printI = false);
    void generateFirstSolution();
    void regenerateFirstSolution();
    int calculateScore(pair<int, int> ignorePosition = make_pair(-1, -1));
    int checkSubGrids(pair<int, int> ignorePosition);

    size_t gridSize, subGridSize, algorithmIterations = 0;
    vector<vector<int>> playGrid;
    vector<vector<bool>> isMutable;
};