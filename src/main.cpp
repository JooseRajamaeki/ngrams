//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0.If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "ngrams.hpp"

int main(int argc, char* argv[])
{

	std::string output_file_name = "";
	std::string vocabulary_file_name = "";
	std::string word_list_file_name = "";

	std::string previous_string = "";

	for (int i = 0; i < argc; i++)
	{
		std::string current_string(argv[i]);

		if (previous_string.compare("--output") == 0)
		{
			output_file_name = current_string;
		}

		if (previous_string.compare("--vocabulary") == 0)
		{
			vocabulary_file_name = current_string;
		}

		if (previous_string.compare("--words") == 0)
		{
			word_list_file_name = current_string;
		}

		previous_string = current_string;
	}

	if (output_file_name.size() > 0 && vocabulary_file_name.size() > 0 && word_list_file_name.size() > 0)
	{
		std::vector<std::string> vocabulary = load_words(vocabulary_file_name);
		std::vector<std::string> word_list = load_words(word_list_file_name);

		std::vector<std::string> vocabulary_no_duplicates;
		// Remove duplicates
		for (unsigned int i = 0; i < vocabulary.size(); i++)
		{
			bool duplicate_found = false;
			for (unsigned int j = 0; j < vocabulary_no_duplicates.size(); j++)
			{
				if (vocabulary[i] == vocabulary_no_duplicates[j])
				{
					duplicate_found = true;
					break;
				}
			}

			if (!duplicate_found)
			{
				vocabulary_no_duplicates.push_back(vocabulary[i]);
			}

		}

		vocabulary.clear();

		write_closest_to_file(output_file_name, word_list, vocabulary_no_duplicates);
	}

}