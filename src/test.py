# You can use this Python script to test speed of the solution.

import os
import datetime
import random
import string

if __name__ == '__main__':

    program_name = 'ngrams.exe'
    words = 1000
    word_len = (10,15)
    letters = string.ascii_lowercase + string.ascii_uppercase

    with open('test_vocabulary.txt','w') as outfile:
        for _ in range(words):
            rand_len = random.randint(word_len[0],word_len[1])
            word = ''.join(random.choice(letters) for i in range(rand_len))
            outfile.write(word+'\n')

    with open('test_words.txt','w') as outfile:
        for _ in range(words):
            rand_len = random.randint(word_len[0],word_len[1])
            word = ''.join(random.choice(letters) for i in range(rand_len))
            outfile.write(word+'\n')
    

    start = datetime.datetime.now()

    os.system(program_name+' --vocabulary test_vocabulary.txt --words test_words.txt --output output.txt')

    end = datetime.datetime.now()
    print(end - start)