
#include "Kmer.h"

//https://academic.oup.com/bioinformaticsadvances/article/3/1/vbac085/6835406
void task_4() {
	auto start = std::chrono::steady_clock::now();
	std::cout <<"Reading file..." <<std::endl;
	std::cout <<"___________________⌄ Full file read" <<std::endl;

	const int KSIZE = 15;
	const double THRESHOLD = 0.8;
	const double REQUIRED_COVERAGE = 0.5;
	auto kmer = Kmer(KSIZE, THRESHOLD, REQUIRED_COVERAGE);

	std::fstream myFile("dna_files/tdt4287-unknown-adapter.txt");
	std::string dna;

	int i = 0;
	int size = -1;
	while (getline (myFile, dna)) {
		kmer.add_kmer(dna);

		if (i % 100000 == 0) {
			std::cout <<"#" <<std::flush;
		}

		if (++i > size & size != -1) {
			break;
		}
	}
	std::cout <<"\nDone reading file" <<std::endl;

	kmer.find_candidate();
	kmer.print_candidate();
	std::cout <<"AGATCGGAAGAGCACACGTCTGAACTCCAGTCACGTAGAGATCTCGTATGCCGTCTTCTGCTTGAA <- Likely correct, found by \"cheating\"" <<std::endl;

	myFile.close();

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << elapsed.count() << "ms\n";
}