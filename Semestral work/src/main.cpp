#include <iostream>
#include <chrono>
#include "randomSolver.h"
#include "neighborSolver.h"
#include "changeWorstSolver.h"
#include "minimizeSolver.h"
#include "unsolvedGrids.h"
#include "solvedGrids.h"

int main()
{
    MinimizeSolver sudoku(sudoku9x9_35);
    auto start = chrono::high_resolution_clock::now();

    sudoku.solve();

    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::nanoseconds>(end - start);
    auto minutes = duration_cast<chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = duration_cast<chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = duration_cast<chrono::milliseconds>(duration);

    cout << "Solving time: "
         << minutes.count() << "m "
         << seconds.count() << "s "
         << milliseconds.count() << "ms" << endl;
    return 0;
}