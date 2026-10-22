//
// Created by Tobias on 22.10.2026.
//

#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_COUNT_ADAPTER_OCCURRENCE_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_COUNT_ADAPTER_OCCURRENCE_H
#include <fstream>
#include <iosfwd>

#include "has_3_adapter_edit.h"

void count_adapter_occurrence(const std::string &ADAPTER, const std::string &READ) {


	std::string adapter = ADAPTER;

	std::fstream myFile(READ);
	std::string dna;
	int count = 0;


	while (getline (myFile, dna)) {
		int match_start = has_3_adapter_edit(dna, adapter, 10);

		if (match_start != -1 && match_start + 4 < dna.length()) {
			++count;
		}
	}
	std::cout <<"Adapter occurs " <<count <<" times with 10% error margin" <<std::endl;

	myFile.close();

}


#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_COUNT_ADAPTER_OCCURRENCE_H
