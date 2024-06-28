#pragma once

#include "sudokuSolver.h"

class NeighborSolver : public SudokuSolver
{
public:
    // Constructor
    explicit NeighborSolver(const vector<vector<int>> & pg)
                            : SudokuSolver(pg) {}

    void generateNewSolution(int & currentScore, int & iterWithoutImprove) override;
};