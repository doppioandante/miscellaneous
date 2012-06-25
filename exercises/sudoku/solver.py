from copy import deepcopy
from sudoku import Sudoku


class SudokuSolver:
    def __init__(self, sudoku):
        assert isinstance(sudoku, Sudoku)
        
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
