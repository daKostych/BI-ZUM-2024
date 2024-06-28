#pragma once

#include "sudokuSolver.h"

class RandomSolver : public SudokuSolver
{
public:
    // Constructor
    explicit RandomSolver(const vector<vector<int>> & pg)
                          : SudokuSolver(pg) {}

    void generateNewSolution(int & currentScore, int & iterWithoutImprove) override;
};