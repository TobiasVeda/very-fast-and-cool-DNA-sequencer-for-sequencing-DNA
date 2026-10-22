#include "Kmer.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

Kmer::Kmer(const int ksize, const double threshold, const double required_coverage) {
	_ksize = ksize;
	_line_count = 0;
	_threshold = threshold;
	_strength.resize(ksize, 1.0);
	_required_coverage = required_coverage;
}

void Kmer::add_kmer(const std::string& dna) {
	_unique_sequences[dna] += 1;
	++_line_count;

	for (int i = 0; i < dna.length(); ++i) {
		if (i + _ksize > dna.length()) {
			return;
		}
		std::string kmer = dna.substr(i, _ksize);
		_map[kmer] += 1;
	}
}

void Kmer::find_candidate() {
	const auto max = std::ranges::max_element(_map.begin(), _map.end(),
		[](const auto &comp1, const auto &comp2) {
			return comp1.second < comp2.second;
		});

	std::string seed = max->first;
	int seed_count = max->second;
	_candidate = seed;

	for (int i = 1; i < 9999; ++i) {
		const std::string A = _candidate.substr(i).append("A");
		const std::string T = _candidate.substr(i).append("T");
		const std::string G = _candidate.substr(i).append("G");
		const std::string C = _candidate.substr(i).append("C");

		std::string best_key = A;
		int occurrences = _map[A];
		int total = occurrences;

		for (const auto &key : {T, C, G}) {
			total += _map[key];
			if (_map[best_key] < _map[key]) {
				occurrences = _map[key];
				best_key = key;
			}
		}

		const double fraction = static_cast<double>(occurrences) / total;
		if (fraction <= _threshold || total < _required_coverage * seed_count) {
			break;
		}
		if (best_key == _candidate.substr(_candidate.size() - _ksize)) {
			break; // Best next k-mer is the current k-mer: self-loop
		}
		_candidate.push_back(best_key.back());
		_strength.push_back(fraction);
	}

	for (int i = 0; i < 9999; ++i) {
		const std::string A = _candidate.substr(0, _ksize -1).insert(0, 1, 'A');
		const std::string T = _candidate.substr(0, _ksize -1).insert(0, 1, 'T');
		const std::string G = _candidate.substr(0, _ksize -1).insert(0, 1, 'G');
		const std::string C = _candidate.substr(0, _ksize -1).insert(0, 1, 'C');

		std::string best_key = A;
		int occurrences = _map[A];
		int total = occurrences;

		for (const auto &key : {T, C, G}) {
			total += _map[key];
			if (_map[best_key] < _map[key]) {
				occurrences = _map[key];
				best_key = key;
			}
		}

		const double fraction = static_cast<double>(occurrences) / total;
		if (fraction <= _threshold || total < _required_coverage * seed_count) {
			break;
		}
		if (best_key == _candidate.substr(0, _ksize)) {
			break; // Best next k-mer is the current k-mer: self-loop
		}
		_candidate.insert(0, 1, best_key[0]);
		_strength.insert(_strength.begin(), fraction);
	}



}

void Kmer::print_candidate() {

	for (int i = 0; i < _candidate.length(); ++i) {
		std::cout <<_candidate[i] <<" - "  <<std::setprecision(9) <<_strength[i] <<std::endl;
	}

	std::cout <<_candidate <<std::endl;
}

void Kmer::print_sequence_distribution() {

	// Collect only the entries that pass the threshold
	std::vector<std::pair<std::string, int>> entries;
	for (const auto &[key, value] : _unique_sequences)
	{
		if (value < 1000)
		{
			continue;
		}
		entries.emplace_back(key, value);
	}

	// Sort by occurrence descending, then by sequence ascending for ties
	std::sort(entries.begin(), entries.end(),
			  [](const auto &a, const auto &b)
			  {
				  if (a.second != b.second)
				  {
					  return a.second > b.second;
				  }
				  return a.first < b.first;
			  });

	std::cout << "occurrence,sequence\n";
	for (const auto &[key, value] : entries)
	{
		std::cout << value << "," << key << "\n";
	}
}

void Kmer::print_unique_sequences_to_file(const std::string& file) {
	std::ofstream myFile(file);

	if (!myFile.is_open()) {
		std::cerr << "Could not open file\n";
		return;
	}
	for (const auto &[key, value] : _unique_sequences)	{
		myFile <<key <<"\n";
	}
	myFile.close();
}
