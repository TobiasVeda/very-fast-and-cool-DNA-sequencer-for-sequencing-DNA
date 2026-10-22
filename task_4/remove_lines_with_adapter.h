//
// Created by Tobias on 22.10.2026.
//

#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_REMOVE_LINES_WITH_ADAPTER_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_REMOVE_LINES_WITH_ADAPTER_H
#include "has_3_adapter_edit.h"


void remove_lines_with_adapter(const std::string &ADAPTER, const std::string &READ, const std::string &WRITE) {

	auto start = std::chrono::steady_clock::now();
	std::cout <<"Reading file..." <<std::endl;
	std::cout <<"___________________⌄ Full file read" <<std::endl;

	std::string adapter = ADAPTER;

	std::fstream myFile(READ);
	std::string dna;
	std::string file_buffer;


	int i = 0;
	while (getline (myFile, dna)) {
		// int match_start = has_3_adapter(dna, adapter, 10);
		int match_start = has_3_adapter_edit(dna, adapter, 10);

		if (match_start == -1) {
			file_buffer.append(dna + "\n");
		}

		if (i++ % 100000 == 0) {
			std::cout <<"#" <<std::flush;
		}

	}
	std::cout <<std::endl;

	std::ofstream myOtherFile(WRITE);
	myOtherFile <<file_buffer;

	myFile.close();
	myOtherFile.close();

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << elapsed.count() << "ms\n";
}


#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_REMOVE_LINES_WITH_ADAPTER_H
