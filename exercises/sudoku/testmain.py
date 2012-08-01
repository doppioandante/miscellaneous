from itertools import chain
from sudoku import Sudoku
from solver import SudokuSolver

sudoku = Sudoku(
    chain.from_iterable([
        [   9, None, None, None, None, None,    6, None,   8],
        [None, None,    7, None, None, None, None, None, None],
        [None,    1, None,    8,    6,    2, None, None, None],
        [None, None, None, None,    4, None,    5, None,    1],
        [   4, None, None, None,    5, None, None, None,    6],
        [   5, None,    9, None,    8, None, None, None, None],
        [None, None, None,    6,    1,    7, None,    9, None],
        [None, None, None, None, None, None,    4, None, None],
        [   1, None,    8, None, None, None, None, None,    3]
    ]), 3)


solver = SudokuSolver(sudoku)
if solver.solve():
    print(solver.sudoku)
else:
    print("Impossible sudoku")
