
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>

#include "KPM_matcher.h"

int task_1() {
	auto start = std::chrono::steady_clock::now();
	std::cout <<"❈ Thinking..." <<std::endl;

	std::string adapter = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG";

	auto matcher = new KPM::KPM_matcher();
	matcher->construct_LPS(adapter);

	std::fstream myFile("dna_files/s_3_sequence_1M.txt");
	std::string dna;
	std::string cout_buffer;
	int count = 0;
	std::map<int, int> histogram;

	while (getline (myFile, dna)) {
		int match_start = matcher->compare(dna);
		if (match_start != -1) {

			histogram[match_start] += 1;
			++count;
			cout_buffer.append("Match at position " + std::to_string(match_start) + " for: " + dna + "\n");
		}
	}

	cout_buffer.append("\n");
	for (auto [key, value] : histogram) {
		// std::cout <<"Stripped length " <<key <<" occurs " <<value <<" number of times\n";
		cout_buffer.append("Stripped length " + std::to_string(key) + " occurs " + std::to_string(value) + " number of times\n");
	}

	std::cout <<cout_buffer <<std::endl;
	std::cout <<"Found " <<count <<" matches (including complete matches/overlaps)" <<std::endl;

	delete matcher;
	myFile.close();

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << elapsed.count() << "ms\n";

}