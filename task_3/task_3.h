#ifndef VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_TASK3_H
#define VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_TASK3_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Edit_distance_extended.h"

namespace task3_detail {

	struct Hamming {
		int start = -1;					// start of the adapter in the read, -1 = no match
		std::vector<int> mismatches;	// read positions of the mismatches
	};

	// Mismatch-only matcher.
	// Tries every start s of the adapter in the read (longest overlap first),
	// accepts a start if it has at most floor(e * overlap) mismatches,
	// and keeps the one with the lowest mismatch rate (the longer overlap wins ties).
	inline Hamming hamming_best(const std::string &read, const std::string &adapter,
								const double e, const int minOverlap) {
		const int n = read.length();
		const int m = adapter.length();
		Hamming best;
		double bestRate = 2.0;

		for (int s = std::max(0, n - m); s <= n - minOverlap; ++s) {
			const int len = n - s;
			std::vector<int> pos;
			for (int i = 0; i < len; ++i) {
				if (read[s + i] != adapter[i]) {
					pos.push_back(s + i);
				}
			}
			const double rate = static_cast<double>(pos.size()) / len;
			if (pos.size() <= static_cast<size_t>(e * len) && rate < bestRate) {
				bestRate = rate;
				best.start = s;
				best.mismatches = pos;
			}
		}
		return best;
	}

} // task3_detail

inline void task_3() {
	const auto startTime = std::chrono::steady_clock::now();

	const std::string adapter = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG";
	const double e = 0.10;			// maximum error rate
	const int minOverlap = 15;		// minimum overlap

	const DE::Edit_distance_extended aligner;
	std::ifstream file("dna_files/s_3_sequence_1M.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open file\n";
		return;
	}

	// Read classes
	long exact = 0, mismatchOnly = 0, needsInsertionDeletion = 0, noMatch = 0;

	long alignedBases = 0, errors = 0;
	std::vector<long> errorsPerRead;
	std::vector<long> readCover, readErrors;

	std::string read;
	while (std::getline(file, read)) {
		const int n = read.length();
		if (readCover.size() < static_cast<size_t>(n)) {
			readCover.resize(n, 0);
			readErrors.resize(n, 0);
		}

		const auto h = task3_detail::hamming_best(read, adapter, e, minOverlap);

		if (h.start == -1) {
			// Rejected by the mismatch-only matcher. Does an alignment with insertions/deletions accept it?
			if (aligner.fitsSemiGlobal(read, adapter, e, minOverlap)) {
				++needsInsertionDeletion;
			} else {
				++noMatch;
			}
			continue;
		}

		const size_t k = h.mismatches.size();
		if (k == 0) {
			++exact;
		} else {
			++mismatchOnly;
		}

		alignedBases += n - h.start;
		errors += k;

		if (errorsPerRead.size() <= k) {
			errorsPerRead.resize(k + 1, 0);
		}
		++errorsPerRead[k];

		for (int p = h.start; p < n; ++p) {
			++readCover[p];
		}
		for (const int p : h.mismatches) {
			++readErrors[p];
		}
	}

	const long matched = exact + mismatchOnly;
	const double perNucleotide = static_cast<double>(errors) / alignedBases;

	std::cout << "=== max error rate " << e << ", min overlap " << minOverlap << " ===\n";
	std::cout << "reads with mismatch-only match," << matched << "\n";
	std::cout << "aligned bases," << alignedBases << "\n";
	std::cout << "mismatches," << errors << "\n";
	std::cout << "errors per nucleotide," << perNucleotide << "\n";
	std::cout << "mean errors per read (adapter region)," << static_cast<double>(errors) / matched << "\n";
	std::cout << "errors per read scaled to 50 bases," << perNucleotide * 50 << "\n";

	std::cout << "\nclass,reads\n";
	std::cout << "exact," << exact << "\n";
	std::cout << "mismatch-only," << mismatchOnly << "\n";
	std::cout << "needs insertion/deletion," << needsInsertionDeletion << "\n";
	std::cout << "no match," << noMatch << "\n";

	std::cout << "\nerrors_in_read,reads\n";
	for (size_t k = 0; k < errorsPerRead.size(); ++k) {
		if (errorsPerRead[k] > 0) {
			std::cout << k << "," << errorsPerRead[k] << "\n";
		}
	}

	std::cout << "\nread_position,coverage,errors,error_rate\n";
	for (size_t p = 0; p < readCover.size(); ++p) {
		if (readCover[p] == 0) {
			continue;
		}
		std::cout << p << "," << readCover[p] << "," << readErrors[p] << ","
				  << static_cast<double>(readErrors[p]) / readCover[p] << "\n";
	}

	const auto endTime = std::chrono::steady_clock::now();
	const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "\nTime: " << elapsed.count() << "ms\n";
}

#endif