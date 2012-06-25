from itertools import chain
from sudoku import Sudoku
from solver import SudokuSolver

sudoku = Sudoku(
    chain.from_iterable([
        [7, 5, 6, 8, None, None, None, None, None],
        [None, 9, 2, None, None, None, None, None, None],
        [4, None, 3, None, 6, 7, None, 5, 2],
        [None, 8, 9, 6, None, None, None, 3, None],
        [None, None, None, 5, 9, 3, None, None, None],
        [None, 7, None, None, None, 2, 9, 1, None],
        [5, 2, None, 1, 3, None, 4, None, 9],
        [None, None, None, None, None, None, 1, 2, None],
        [None, None, None, None, None, 8, 7, 6, 5]
    ]), 3)


solver = SudokuSolver(sudoku)
if solver.solve():
    print(solver.sudoku)
else:
    print("Impossible sudoku")
