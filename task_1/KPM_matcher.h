#ifndef VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KPM_MATCHER_H
#define VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KPM_MATCHER_H
#include <string>
#include <vector>

namespace KPM {
	class KPM_matcher {
	private:
		std::vector<int> _LPS;
		std::string _pattern;

	public:
		KPM_matcher();

		void construct_LPS(const std::string &pattern);

		int compare(const std::string &text, const double allowed_mismatch = 0) const;


	};
} // KPM

#endif //VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KPM_MATCHER_H
