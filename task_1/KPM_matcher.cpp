
#include "KPM_matcher.h"

#include <string>

namespace KPM {

	KPM_matcher::KPM_matcher() = default;

	void KPM_matcher::construct_LPS(const std::string& pattern) {
		_pattern = pattern;
		_LPS.resize(pattern.length());
		_LPS[0] = 0;
		int len = 0;

		for (int i = 1; i < pattern.length(); ++i) {

			// Case 1: increment len and store it at lps[i]
			if (pattern[i] == pattern[len]) {
				_LPS[i] = ++len;
				continue;
			}
			// Case 2: No previous matches, and no new matches. Set lps[i] = 0
			if (pattern[i] != pattern[len] && len == 0) {
				_LPS[i] = 0;
				continue;
			}
			// Case 3: Current i doesnt match/cant extend lps. Might be a smaller prefix that matches current suffix.
			// Walk backwards to find a smaller prefix that matches current suffix.
			if (pattern[i] != pattern[len] && len > 0) {
				while (true) {
					if (pattern[i] == pattern[len]) {
						_LPS[i] = ++len;
						break;
					}
					if (len == 0) {
						break; // check for zero before it might be assigned
					}
					_LPS[i] = 0;
					len = _LPS[len - 1];

				}
			}
		}
	}


	// Searches for the first occurrence of _pattern in text using the Knuth-Morris-Pratt algorithm (KMP).
	// Returns the starting index of the match, or -1 if there is none.
	// _LPS is the precomputed "longest proper prefix which is also a suffix" table for the pattern.
	// Allows the pattern to not be completely matched, as long as there are no chars in the text after the pattern is cut off
	int KPM_matcher::compare(const std::string& text, const double allowed_mismatch) const {

		int i = 0;						// Current position in text
		int j = 0;						// Current position in pattern (= number of chars matched so far)
		int match_start = -1;			// Candidate start index of the match in text
		double current_mismatch = 0;	// Current mismatch percentage. Compared against allowed_mismatch

		while (i < text.length()) {
			// The current match attempt began j characters before i
			match_start = i - j; // match_start + j is the number of currently matched chars


			if (text[i] == _pattern[j]) {
				chars_match:
				// Characters match: advance in both text and pattern
				++i;
				++j;

				// The whole pattern has been matched, so report where it started
				if (j == _pattern.length()) {
					return match_start;
				}

				// Reached the end of the text, report where match started.
				if (i == text.length()) {
					return match_start;
				}

			} else {


				// If within the allowed mismatch percentage we treat it as a char match
				const double char_mismatch_worth = 100.0 / std::min(_pattern.length(), (text.length() - match_start)); // How much one mismatch contribute to percentage
				current_mismatch += char_mismatch_worth; // Iterate the current mismatch
				if (current_mismatch <= allowed_mismatch) {
					// Treat the mismatch as a match instead
					goto chars_match;
				}

				if (j != 0) {
					// Mismatch after a partial match
					// Fall back in the pattern to the "longest prefix that is also a suffix" of the matched part.
					// i is not moved, so no text characters are re-examined.
					j = _LPS[j - 1];
					current_mismatch = 0;

				} else {
					// Mismatch with nothing matched yet: move on to the next text character
					++i;
					current_mismatch = 0;
				}
			}

		}

		// The text was exhausted without finding the pattern
		match_start = -1;
		return match_start;
	}



} // KPM