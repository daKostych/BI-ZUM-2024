#pragma once

#include "sudokuSolver.h"

class MinimizeSolver : public SudokuSolver
{
public:
    // Constructor
    explicit MinimizeSolver(const vector<vector<int>> & pg)
            : SudokuSolver(pg) {}

    void generateNewSolution(int & currentScore, int & iterWithoutImprove) override;
};