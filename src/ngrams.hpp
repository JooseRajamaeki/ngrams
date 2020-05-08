//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0.If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NGRAMS_HPP
#define NGRAMS_HPP

#include <string>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <omp.h>

std::pair<unsigned,unsigned> number_of_common_ngrams(const std::string& string1, const std::string& string2, unsigned n_max = 3);
std::vector<int> find_closest(const std::vector<std::string>& words, const std::vector<std::string>& vocabulary);

std::vector<std::string> load_words(const std::string& filename);
void write_closest_to_file(const std::string filename, const std::vector<std::string>& words, const std::vector<std::string>& vocabulary);

#endif

