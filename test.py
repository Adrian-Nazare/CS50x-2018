import time
s1 = "Mari"
s2 = "Bal"



def distances(a, b):
    """Calculate edit distance from a to b"""

    matrix = [[(0, 0) for j in range(len(b) + 1)] for i in range (len(a) + 1)]
    print(matrix)
    for j in range (1, len(b) + 1):
        matrix[0][j] = (matrix[0][j-1][0] + 1, 2)
    for i in range (1, len(a) + 1):
        matrix[i][0] = (matrix[i-1][0][0] + 1, 1)
    print(matrix)
    for j in range (1, len(b) + 1):
        for i in range (1, len(a) + 1):

            dele = matrix [i-1][j][0] + 1
            ins = matrix[i][j-1][0] + 1
            sub = matrix [i-1][j-1][0] + int(not (a[i-1] == b[j-1]))

            if dele <= ins and dele <= sub:
                matrix[i][j] = (dele, 1)
            elif ins <= dele and ins <= sub:
                matrix[i][j] = (ins, 2)
            else:
                matrix[i][j] = (sub, 3)
    return matrix

matrix = distances(s1, s2)

    # Extract operations from table
operations = []
talpici = []
i, j = len(s1), len(s2)
print("i = len(s1) ={}".format(i))
print("j = len(s2) ={}".format(j))

while True:
    talpica, operation = matrix[i][j]
    print("talpica = {}".format(talpica))
    print("Operation = {}".format(operation))
    print("i inainte ={}".format(i))
    print("j inainte ={}".format(j))

    if not operation:
        break
    if operation == 2:
        j -= 1
        print("j={}".format(j))
    elif operation == 1:
        i -= 1
        print("i={}".format(i))
    else:
        i -= 1
        j -= 1
        print("j={}".format(j))
        print("j={}".format(j))
    operations.append(operation)
    talpici.append(talpica)
print("Talpici = {}".format(talpici))
print("Operations = {}".format(operations))
#while True:
#    print(i)
#    print(matrix[i])
#    time.sleep(1)
#    i = i+1
i = 0
#while True:
#    print(i)
#    print("talpica = {}".format(talpici[i]))
#    print("Operation = {}".format(operations[i]))
#    time.sleep(1)
#    i = i+1