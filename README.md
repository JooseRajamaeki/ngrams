This repository implements computing n-grams and matching words using them.
The function <number_of_common_ngrams> computes all unique n-grams of the given two words (up to a given maximum n) and counts how many of the unique n-grams are present in both of the provided words.

The application files are in the folder "src". The application has no outside dependencies apart from the standard library of C++. The application consists of the files:
ngrams.cpp
ngrams.hpp
main.cpp

The application is run on command line using the following syntax.
```
program_name --vocabulary vocabulary.txt --words word_list.txt --output output.txt
```
Each line of word_list.txt is matched to a line in vocabulary.txt using number of common ngrams divided by the number of total ngrams in both words. The outputs are written to output.txt.