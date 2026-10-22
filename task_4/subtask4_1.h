//
// Created by Tobias on 20.10.2026.
//

#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_H


void subtaks4_1(const std::string &READ) {
	auto start = std::chrono::steady_clock::now();

	std::cout << "4_1: Reading file..." << std::endl;
	std::cout << "___________________⌄ Full file read" << std::endl;

	const int KSIZE = 15;
	const double THRESHOLD = 0.8;
	const double REQUIRED_COVERAGE = 0.5;
	auto kmer = Kmer(KSIZE, THRESHOLD, REQUIRED_COVERAGE);

	std::fstream myFile(READ);
	// std::fstream myFile("dna_files/task4/stripped_adapter.txt");
	// std::fstream myFile("dna_files/task4/unique_sequences.txt");
	std::string dna;

	int i = 0;
	int size = -1;
	while (getline(myFile, dna)) {
		kmer.add_kmer(dna);

		if (i % 100000 == 0) {
			std::cout << "#" << std::flush;
		}

		if (++i > size & size != -1) {
			break;
		}
	}
	std::cout << "\nDone reading file" << std::endl;

	kmer.find_candidate();
	kmer.print_candidate();
	std::cout <<
		"AGATCGGAAGAGCACACGTCTGAACTCCAGTCACGTAGAGATCTCGTATGCCGTCTTCTGCTTGAA <- Likely correct, found by \"cheating\"" <<
		std::endl;


	myFile.close();
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << elapsed.count() << "ms\n";
}

#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_SUBTASK4_H
