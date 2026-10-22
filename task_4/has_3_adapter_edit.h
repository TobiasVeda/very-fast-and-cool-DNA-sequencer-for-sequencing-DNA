//
// Created by Tobias on 22.10.2026.
//

#ifndef VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_HAS_3_ADAPTER_EDIT_H
#define VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_HAS_3_ADAPTER_EDIT_H
#include <algorithm>
#include <string>
#include <vector>

// Searches for a 3' adapter in a DNA sequence, allowing substitutions,
// insertions and deletions.
// Returns the start index of the first position where the adapter matches
// within the allowed error budget, or -1 if there is none.
// A partial match that runs to the end of dna counts as a match.
// The budget is the same as in has_3_adapter: allowed_mismatch_percentage is
// applied to L = min(adapter.length(), dna.length() - start).
// The alignment must begin with the adapter's first base lined up against
// dna[start] (match or substitution), so the returned index is the true
// adapter start and not one base early because of a leading insertion.
int has_3_adapter_edit(const std::string &dna, const std::string &adapter, const double allowed_mismatch_percentage = 0) {

	const int n = (int)dna.length();
	const int m = (int)adapter.length();
	if (n == 0 || m == 0) {
		return -1;
	}

	const int INF = 1 << 28;
	const double eps = 1e-9;

	// Largest possible budget, used to size the buffers once
	const int k_max = (int)(allowed_mismatch_percentage * std::min(m, n) / 100.0 + eps);
	std::vector<int> prev(2 * k_max + 3);
	std::vector<int> cur(2 * k_max + 3);

	for (int s = 0; s < n; s++) {

		const int rem = n - s;                               // Bases left in dna from s
		const int L = std::min(m, rem);                      // Compared length
		const int k = (int)(allowed_mismatch_percentage * L / 100.0 + eps); // Max edits allowed
		const int width = 2 * k + 3;                         // Band: diagonals -k..k plus a sentinel on each side
		const int center = k + 1;                            // Index of diagonal 0

		// Row 0: only (0,0) is reachable. No leading insertions or deletions.
		std::fill(prev.begin(), prev.begin() + width, INF);
		prev[center] = 0;

		// Row j = adapter chars consumed, column i = dna chars consumed from s.
		// Band index idx corresponds to diagonal d = i - j = idx - center.
		for (int j = 1; j <= m; j++) {

			std::fill(cur.begin(), cur.begin() + width, INF);
			int row_min = INF;
			const char a = adapter[j - 1];

			for (int idx = 1; idx <= 2 * k + 1; idx++) {

				const int i = j + (idx - center);
				if (i < 1 || i > rem) {
					continue;
				}

				int v = prev[idx] + (dna[s + i - 1] != a);   // Match / substitution
				v = std::min(v, prev[idx + 1] + 1);          // Adapter base missing in dna (deletion)
				v = std::min(v, cur[idx - 1] + 1);           // Extra base in dna (insertion)
				if (v > INF) {
					v = INF;
				}
				cur[idx] = v;

				if (v <= k) {
					// Whole adapter consumed (j == m), or dna ran out first (i == rem)
					if (j == m || i == rem) {
						return s;
					}
				}
				if (v < row_min) {
					row_min = v;
				}
			}

			// Costs never decrease along a path, so if the whole row is over budget this start fails
			if (row_min > k) {
				break;
			}
			std::swap(prev, cur);
		}
	}

	return -1;
}
#endif //VERY_FAST_AND_COOL_DNA_SEQUENCER_FOR_SEQUENCING_DNA_HAS_3_ADAPTER_EDIT_H
