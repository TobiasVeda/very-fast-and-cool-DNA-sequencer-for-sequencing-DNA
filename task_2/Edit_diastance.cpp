//
// Created by Vetle on 05.10.2026.
//

#include "Edit_diastance.h"

#include <string>

namespace DE {

	Edit_diastance::Edit_diastance() = default;
	
	Edit_diastance::Match Edit_diastance::findBestMatch(
	    const std::string& dna,
	    const std::string& adapter,
	    double maxMismatchPercentage
	) const {
	    int dnaLength = dna.length();
	    int adapterLength = adapter.length();
	
	    int maxLength = dnaLength < adapterLength ? dnaLength : adapterLength;
	
	    Match best = Match{-1, -1, -1};
	
	    for (int length = maxLength; length >= 1; --length) {
	
	        std::string suffix = dna.substr(dnaLength - length, length);
	
	        std::string prefix = adapter.substr(0, length);
	
	        int distance = this->distance(suffix, prefix);
	
	        int threshold = (int)(maxMismatchPercentage * length);
	
	        if (distance <= threshold) {
	            best = Match{dnaLength - length, length, distance};
	            break;
	        }
	    }
	
	    return best;
	}
	

	int Edit_diastance::distance(const std::string &S, const std::string &R) const {
		int s_len = S.length() + 1;
		int r_len = R.length() + 1;

		int *DP = (int*)malloc(r_len * s_len * sizeof(int));

		for (int i = 0; i < s_len; i++)
		{
			DP[i*r_len] = i;
		}

		for (int j = 0; j < r_len; j++)
		{
			DP[j] = j;
		}
		
		for (int j = 1; j < r_len; j++)
		{
			for (int i = 1; i < s_len; i++)
			{
				int top = DP[j + (i-1)*r_len];
				int left = DP[(j-1) + i*r_len];
				int corner = DP[(j-1) + (i-1)*r_len];

				int cross_min = left < top ? left : top;
				int result;
				
				if (cross_min >= corner)
				{
					if (S[i-1] == R[j-1])
					{
						result = corner;
					} else {
						result = corner + 1;
					}
					
				} else {
					 result = cross_min + 1;
				}

				DP[j + i*r_len] = result;
			}
		}
		
		int result = DP[(r_len) * (s_len) - 1];
		free(DP);
		return result;
	}
} // DE
