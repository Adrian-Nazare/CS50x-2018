from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    # initialize matrix
    matrix = [[(0, 0) for j in range(len(b) + 1)] for i in range(len(a) + 1)]

    # complete the costs and operations for the first row and column
    for j in range(1, len(b) + 1):
        matrix[0][j] = (matrix[0][j-1][0] + 1, 2)
    for i in range(1, len(a) + 1):
        matrix[i][0] = (matrix[i-1][0][0] + 1, 1)

    # complete the costs and operations for the rest of the table
    for j in range(1, len(b) + 1):
        for i in range(1, len(a) + 1):

            dele = matrix[i-1][j][0] + 1
            ins = matrix[i][j-1][0] + 1
            sub = matrix[i-1][j-1][0] + int(not (a[i-1] == b[j-1]))

            if dele <= ins and dele <= sub:
                matrix[i][j] = (dele, Operation.DELETED)
            elif ins <= dele and ins <= sub:
                matrix[i][j] = (ins, Operation.INSERTED)
            else:
                matrix[i][j] = (sub, Operation.SUBSTITUTED)
    return matrix
