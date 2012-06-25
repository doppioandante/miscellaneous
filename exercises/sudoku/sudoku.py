import os # for linesep


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
