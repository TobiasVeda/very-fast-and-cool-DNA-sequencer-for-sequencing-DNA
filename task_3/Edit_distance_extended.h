#ifndef VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_EDIT_DISTANCE_EXTENDED_H
#define VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_EDIT_DISTANCE_EXTENDED_H
#include <string>

namespace DE {
	class Edit_distance_extended {

	public:
		Edit_distance_extended() = default;

		// Semi-global edit distance check.
		// The start in the read is free, and the alignment ends at the last base of the read.
		// Returns true if some prefix of the adapter with length j >= minOverlap
		// can be aligned to the end of the read with at most floor(e * j) errors.
		bool fitsSemiGlobal(
			const std::string &read,
			const std::string &adapter,
			double e,
			int minOverlap
		) const;
	};
} // DE

#endif