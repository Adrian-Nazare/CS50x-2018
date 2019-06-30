import re

readpoint = open("US.txt", "r")
writepoint = open("US2.txt", "w")
b = readpoint.read()
c = re.sub('\t\t\t', '\t', b)
writepoint.write(c)