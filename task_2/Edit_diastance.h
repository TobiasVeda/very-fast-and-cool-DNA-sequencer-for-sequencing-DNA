#ifndef VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_Edit_diastance_H
#define VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_Edit_diastance_H
#include <string>

namespace DE {
	class Edit_diastance {

	public:
		Edit_diastance();
		
		struct Match {
		    int suffixStart;
		    int length;
		    int distance;
		};
		
		Match findBestMatch(
		    const std::string& dna,
		    const std::string& adapter,
		    double maxMismatchPercentage
		) const;

		int distance(const std::string &S, const std::string &R) const;
	};
} // DE

#endif //VERY_COOOL_AND_FAST_DNA_SEQUENCER_FOR_SEQUENCING_DNA_KPM_MATCHER_H
