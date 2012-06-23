from itertools import product, chain
from copy import deepcopy
import cProfile
import os
from time import sleep


def as2dTuple(t):
    argType = type(t)
    
    if argType is not tuple:
        raise ValueError("Invalid position type, must be a 2d tuple, {0} passed"
                         "instead".format(repr(argType)))

    return t

class Sudoku:
    def __init__(self, values, unitRoot):
        self.values = list(values)
        self.unitRoot = unitRoot
        self.unitSize = self.unitRoot * self.unitRoot
        self.gridSize = self.unitSize * self.unitSize

  
    def __getitem__(self, pos):
        i, j = as2dTuple(pos)

        return self.values[self.unitSize * i + j]                  


    def __setitem__(self, pos, element):
        i, j = as2dTuple(pos)

        self.values[self.unitSize * i + j] = element


    def __str__(self, sep = "| ", invalid = " "):
        result = ""

        for i in range(self.unitSize):
            for j in range(self.unitSize):
                
                element = str(self[i, j] if self[i, j] else invalid)

                result += sep
                result += element

            result += sep
            result += os.linesep

        return result


    def rowAt(self, i):
        pos = self.unitSize * i
        return self.values[pos : pos + self.unitSize]


    def columnAt(self, j):
        return self.values[j : : self.unitSize]


    def regionAt(self, i, j):
        # TODO: use rowAt
        region_i = (i // self.unitRoot) * self.unitRoot * self.unitSize
        region_j = (j // self.unitRoot) * self.unitRoot

        region = []
        for i in range(region_i, region_i + self.unitRoot*self.unitSize,
                       self.unitSize):
            pos = i + region_j
            region.extend(self.values[pos : pos + self.unitRoot])

        return region    

        
class SudokuSolver:
    def __init__(self, sudoku):
        self.sudoku = deepcopy(sudoku)
        self.orig_sudoku = sudoku
        
        self.buildPossibilities()


    def buildPossibilities(self):
        value_set = set(range(1,self.sudoku.unitSize+1))
        
        # rows & columns
        self.rows = []
        self.columns = []
        for i in range(self.sudoku.unitSize):
            self.rows.append(value_set - set(self.sudoku.rowAt(i)))
            self.columns.append(value_set - set(self.sudoku.columnAt(i)))

        # regions
        self.regions = []
        for i in range(0, self.sudoku.unitSize, 3):
            set_list = [] 
            for j in range(0, self.sudoku.unitSize, 3):
                set_list.append(value_set - set(self.sudoku.regionAt(i, j)))

            self.regions.append(set_list)    

                
    def addPossibleValue(self, i, j, value):
        self.rows[i].add(value)
        self.columns[j].add(value)
        self.regions[i//3][j//3].add(value)


    def removePossibleValue(self, i, j, value):
        self.rows[i].remove(value)
        self.columns[j].remove(value)
        self.regions[i//3][j//3].remove(value)


    def getPossibleValues(self, i, j):
        return self.rows[i].intersection(self.columns[j]).intersection(
            self.regions[i//3][j//3])

    
    def solve(self, i=0, j=0):
               
        for i in range(i, 9):
            for j in range(j, 9):
                if self.sudoku[i, j] is None:                        
                    for element in list(self.getPossibleValues(i, j)):
                        self.sudoku[i, j] = element
                        self.removePossibleValue(i, j, element)

                        if self.solve(i, j):
                            return True
                        
                        self.sudoku[i, j] = None
                        self.addPossibleValue(i, j, element)

                    # couldn't find a solution for this cell     
                    if self.sudoku[i, j] is None:
                        return False

                j = 0
    
        return True

##    def solve(self):
##        stack = [(0,0)]
##
##        while len(stack) != 0:
##            doBreak = False
##            i, j = stack.pop()
##            for i in range(i, self.sudoku.unitSize):
##                if doBreak:
##                    break
##                
##                for j in range(j, self.sudoku.unitSize):
##                    sleep(0.5)
##                    print(self.sudoku)                    
##                    if self.sudoku[i, j] is None:
##                        p = self.getPossibleValues(i, j)
##                        print(p)    
##                        if len(p) != 0:                            
##                            value = p.pop()
##                            self.removePossibleValue(i, j, value)
##                            self.sudoku[i, j] = value
##
##                            stack.append((i,j))
##                        else:
##                            doBreak = True
##                            break
##
##                    if self.orig_sudoku[i, j] is None:
##                        print("Rolling back at:", i,j, "=>", self.sudoku[i,j])
##                        self.addPossibleValue(i, j, self.sudoku[i, j])
##                        self.sudoku[i, j] = None
##
##                        doBreak = True
##                        break
##
##                j = 0
##
##        return True        

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
