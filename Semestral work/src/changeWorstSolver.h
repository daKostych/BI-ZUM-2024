#pragma once

#include "sudokuSolver.h"

class ChangeWorstSolver : public SudokuSolver
{
public:
    // Constructor
    explicit ChangeWorstSolver(const vector<vector<int>> & pg)
                               : SudokuSolver(pg) {}

    void generateNewSolution(int & currentScore, int & iterWithoutImprove) override;
};