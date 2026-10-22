//
// Created by Tobias on 20.10.2026.
//

#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_2_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_2_H
#include "has_3_adapter_edit.h"


void subtask4_2(const std::string &ADAPTER, const std::string &READ, const std::string &WRITE) {

	auto start = std::chrono::steady_clock::now();
	std::cout <<"Reading file..." <<std::endl;
	std::cout <<"___________________⌄ Full file read" <<std::endl;

	std::string adapter = ADAPTER;

	std::fstream myFile(READ);
	std::string dna;
	std::string file_buffer;
	std::unordered_map<int, int> length_distribution;


	int i = 0;
	while (getline (myFile, dna)) {
		// int match_start = has_3_adapter(dna, adapter, 10);
		int match_start = has_3_adapter_edit(dna, adapter, 10);

		if (match_start == 0) {
			continue;
		}
		if (match_start != -1 && match_start + 4 < dna.length()) {
			dna.erase(match_start);
		}
		file_buffer.append(dna + "\n");
		length_distribution[dna.length()-1] += 1;

		if (i++ % 100000 == 0) {
			std::cout <<"#" <<std::flush;
		}

	}
	std::cout <<std::endl;
	std::cout <<"Length distribution of adapter-stripped sequences" <<std::endl;
	std::cout <<"length,occurrence" <<std::endl;
	for (const auto &[key, value] : length_distribution)	{
		std::cout <<key <<"," <<value <<std::endl;
	}

	std::ofstream myOtherFile(WRITE);
	myOtherFile <<file_buffer;

	myFile.close();
	myOtherFile.close();

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << elapsed.count() << "ms\n";
}

#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_2_H
