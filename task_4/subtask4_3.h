//
// Created by Tobias on 22.10.2026.
//

#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_3_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_3_H
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


void subtask4_3(const std::string &READ, const std::string &WRITE) {

	std::cout << "Reading file..." << std::endl;
	std::cout << "___________________⌄ Full file read" << std::endl;

	std::fstream myFile(READ);
	std::ofstream myOtherFile(WRITE);
	std::string dna;

	std::unordered_map<std::string, int> counts;
	std::vector<std::string> firstSeenOrder;

	int i = 0;
	while (getline(myFile, dna)) {

		auto [it, inserted] = counts.try_emplace(dna, 0);
		if (inserted) {
			firstSeenOrder.push_back(dna);
		}
		++it->second;

		if (++i % 100000 == 0) {
			std::cout << "#" << std::flush;
		}
	}
	std::cout << std::endl;

	// Write deduplicated version (first-seen order)
	for (const std::string& line : firstSeenOrder) {
		myOtherFile << line << "\n";
	}

	// Sort by frequency, descending (ties broken alphabetically for stable output)
	std::vector<std::pair<std::string, int>> sorted(counts.begin(), counts.end());
	std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
		if (a.second != b.second) {
			return a.second > b.second;
		}
		return a.first < b.first;
	});

	std::cout <<"Frequency distribution of stripped sequences" <<std::endl;
	std::cout <<"frequency,sequence" <<std::endl;
	for (const auto& [line, count] : sorted) {
		if (count < 1000) {
			continue;
		}
		std::cout <<count <<"," <<line <<std::endl;
	}

	myFile.close();
	myOtherFile.close();
}



#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_3_H
