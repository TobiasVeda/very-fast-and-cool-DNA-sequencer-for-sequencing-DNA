#include <string>

// Searches for a 3' adapter in a DNA sequence (naive scan, O(n*m)).
// Returns the start index of the first position where the adapter matches
// exactly, or -1 if there is none.
// The adapter may be cut off by the end of the read: a partial match that runs
// to the end of dna counts as a match (typical for 3' adapters).
int has_3_adapter(const std::string &dna, const std::string &adapter, const int allowed_mismatch_percentage = 0) {

	int global_i = 0;		// Candidate start position of the adapter in dna
	int i = 0;				// Current position in dna during a match attempt
	int j = 0;				// Current position in adapter during a match attempt
	int match_start = -1;	// Start of the current match attempt, or -1 if it failed
	double current_mismatch = 0;	// Current mismatch percentage. Compared against allowed_mismatch

	// Try every position in dna as a possible adapter start
	while (global_i < dna.length()) {

		// Start a new match attempt at global_i
		i = global_i;
		j = 0;
		current_mismatch = 0;

		// Compare until the adapter is fully matched or dna ends
		// (std::string guarantees dna[dna.length()] == '\0')
		while (dna[i] != '\0' && j < adapter.length()) {

			if (dna[i] == adapter[j]) {
				chars_match:
				// Characters match: remember where this attempt began and advance
				match_start = global_i;
				i++;
				j++;
			} else {

				// If within the allowed mismatch percentage we treat it as a char match
				const double char_mismatch_worth = 100.0 / std::min(adapter.length(), (dna.length() - global_i)); // How much one mismatch contribute to percentage
				current_mismatch += char_mismatch_worth; // Iterate the current mismatch
				if (current_mismatch <= allowed_mismatch_percentage) {
					// Treat the mismatch as a match instead
					goto chars_match;
				}
				// Mismatch: this start position fails, abandon the attempt
				match_start = -1;
				break;
			}

		}

		// The attempt did not fail: either the whole adapter matched, or dna ended
		// first (truncated adapter at the 3' end). Both count as a match.
		if (match_start != -1) {
			return match_start;
		}

		// Attempt failed, try the next start position
		global_i++;
	}

	// No position matched
	return -1;
}
