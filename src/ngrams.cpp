//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0.If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "ngrams.hpp"

void erase_duplicates(std::vector<std::string>& vec)
{
	for (unsigned i = 0; i < vec.size(); i++)
	{
		for (unsigned j = vec.size() - 1; j > i; j--)
		{
			if (vec[i] == vec[j])
			{
				vec.erase(vec.begin() + j);
			}
		}
	}
}

std::vector<std::string> get_ngrams(const std::string& string, unsigned n_max)
{
	std::vector<std::string> ngrams;

	for (unsigned n = 1; n <= n_max; n++)
	{
		for (unsigned i = 0; i + n <= string.size(); i++)
		{
			std::string substring = string.substr(i, n);
			ngrams.push_back(substring);
		}
	}

	erase_duplicates(ngrams);

	return ngrams;
}



std::pair<unsigned, unsigned> number_of_common_ngrams(const std::string& string1, const std::string& string2, unsigned n_max, std::vector<std::string> ngrams)
{

	if (ngrams.size() == 0)
	{
		ngrams = get_ngrams(string2, n_max);
	}

	{
		std::vector<std::string> tmp = get_ngrams(string1,n_max);
		ngrams.insert(ngrams.end(), tmp.begin(), tmp.end());
		erase_duplicates(ngrams);
	}

	unsigned found = 0;
	for (const std::string& ngram : ngrams)
	{
		bool found1 = string1.find(ngram) != std::string::npos;
		bool found2 = string2.find(ngram) != std::string::npos;

		if (found1 && found2)
		{
			found++;
		}
	}

	return std::make_pair(found, ngrams.size());

}

std::vector<int> find_closest(const std::vector<std::string>& words, const std::vector<std::string>& vocabulary, unsigned n_max)
{
	std::vector<int> idx_vocabulary(words.size(), -1);

	std::map<std::string, int> already_processed;

	const int words_len = words.size();
	const int vocabulary_len = vocabulary.size();

#pragma omp parallel for
	for (int i = 0; i < words_len; i++)
	{
		float best_match = -1.0f;
		int idx_closest = -1;

#pragma omp critical
		{
			if (already_processed.count(words[i])) {
				idx_closest = already_processed[words[i]];
			}
		}

		if (idx_closest < 0)
		{
			for (int j = 0; j < vocabulary_len; j++)
			{
				std::pair<unsigned,unsigned> ngrams = number_of_common_ngrams(words[i], vocabulary[j], n_max);
				float match = (float)ngrams.first / (float)ngrams.second;
				if (match > best_match)
				{
					best_match = match;
					idx_closest = j;
				}
			}
		}

#pragma omp critical
		{
			already_processed[words[i]] = idx_closest;
		}

		idx_vocabulary[i] = idx_closest;
	}

	return idx_vocabulary;
}

std::vector<std::string> load_words(const std::string & filename)
{

	std::vector<std::string> lines;

	std::string line;
	std::ifstream input_file(filename);
	for (std::string line; std::getline(input_file, line); )
	{
		lines.push_back(line);
	}

	return lines;
}

void write_closest_to_file(const std::string filename, const std::vector<std::string>& words, const std::vector<std::string>& vocabulary)
{

	std::vector<int> vocabulary_idxs = find_closest(words, vocabulary);

	std::ofstream output_file;
	output_file.open(filename);
	for (unsigned int i = 0; i < words.size(); i++)
	{
		output_file << words[i] << " " << vocabulary[vocabulary_idxs[i]] << std::endl;
	}
	output_file.close();
}
