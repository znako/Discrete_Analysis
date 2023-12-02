import random 
import sys    
import os

A_LETTER = 97
LETTERS_AMOUNT = 26
MAX_KEY_LENGTH = 255
MAX_VALUE = (2 ** 64) - 1

pushFile = open('pushTest.txt', 'w')
popFile = open('popTest.txt', 'w')
findFile = open('findTest.txt', 'w')
saveFile = open('saveTest.txt', 'w')
loadFile = open('loadTest.txt', 'w')

amount = int(sys.argv[1])
for i in range(0, amount):
    key = ''
    keyLength = random.randrange(1, MAX_KEY_LENGTH)
    value = random.randrange(0, MAX_VALUE)
    for i in range(0, keyLength):
        key += chr(random.randrange(A_LETTER, A_LETTER + LETTERS_AMOUNT))
    pushFile.write(key + ' ' + str(value) + '\n')
    findFile.write(key + '\n')
    popFile.write(key + ' ' + str(value) + '\n')
    saveFile.write('! Save save.txt' + '\n')
    loadFile.write('! Load save.txt'  + '\n')

pushFile.write('! Save output.txt' + '\n')
pushFile.close()
findFile.close()
popFile.close()
saveFile.close()
loadFile.close()

filenames = ['pushTest.txt', 'findTest.txt', 'popTest.txt', 'saveTest.txt', 'loadTest.txt']
with open('test.txt', 'w') as outfile:
    outfile.write(str(amount) + '\n')
    for fname in filenames:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)

for x in filenames:
    os.remove(x)