#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KMER_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KMER_H
#include <string>
#include <unordered_map>
#include <vector>


class Kmer {
private:
	int _line_count;	// number of genomes in file (number of invocations of add_kmer())
	int _ksize;			// length of kmer
	double _threshold;		//
	std::string _seed;	// most common kmer
	std::unordered_map<std::string, int> _map;	// map of all kmers

	double _required_coverage;

	std::string _candidate;
	std::vector<double> _strength;

public:
	Kmer(int ksize, double threshold, double required_coverage);

	void add_kmer(const std::string &dna);
	void find_candidate();
	void print_candidate();
};


#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KMER_H
