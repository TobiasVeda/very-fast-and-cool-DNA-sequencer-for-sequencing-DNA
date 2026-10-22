
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>

#include "has_3_adapter.h"
#include "Edit_diastance.h"

void task_2() {
	auto start = std::chrono::steady_clock::now();
	std::cout <<"Reading file..." <<std::endl;
	std::cout <<"__________⌄ Full file read" <<std::endl;

	std::string adapter = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG";

	std::fstream myFile("dna_files/s_3_sequence_1M.txt");
	std::string dna;
	std::string cout_buffer;
	int count = 0;
	std::map<int, int> histogram;

	auto matcher = DE::Edit_diastance();

	int i = 0;
	while (getline (myFile, dna)) {
		// int match_start = has_3_adapter(dna, adapter, 25);
		auto tmp = matcher.findBestMatch(dna, adapter, 0.1);
		int match_start = tmp.suffixStart;

		if (i++ % 100000 == 0) {
			std::cout <<"#" <<std::flush;
		}
		if (match_start != -1) {

			histogram[match_start] += 1;
			++count;
			cout_buffer.append("Match at position " + std::to_string(match_start) + " for: " + dna + "\n");
		}
	}
	std::cout <<std::endl;



	cout_buffer.append("\n");
	cout_buffer.append("length,occurrence\n");
	for (auto [key, value] : histogram) {
		// std::cout <<"Stripped length " <<key <<" occurs " <<value <<" number of times\n";
		cout_buffer.append(std::to_string(key) + "," + std::to_string(value) + "\n");
	}

	std::cout <<cout_buffer <<std::endl;
	std::cout <<"Found " <<count <<" matches (including complete matches/overlaps)" <<std::endl;

	myFile.close();

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << elapsed.count() << "ms\n";

}
