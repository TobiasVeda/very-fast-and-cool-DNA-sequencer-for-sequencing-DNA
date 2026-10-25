#include "Edit_distance_extended.h"

#include <algorithm>
#include <vector>

namespace DE {

	bool Edit_distance_extended::fitsSemiGlobal(
		const std::string &read,
		const std::string &adapter,
		const double e,
		const int minOverlap
	) const {
		const int n = read.length();
		const int m = adapter.length();

		// Row i of the table D. Only the previous row is needed.
		// Row 0: D[0][j] = j. The first column is always 0 (free start in the read).
		std::vector<int> prev(m + 1);
		std::vector<int> cur(m + 1);
		for (int j = 0; j <= m; ++j) {
			prev[j] = j;
		}

		for (int i = 1; i <= n; ++i) {
			cur[0] = 0;
			for (int j = 1; j <= m; ++j) {
				const int cost = read[i - 1] == adapter[j - 1] ? 0 : 1;
				cur[j] = std::min({prev[j - 1] + cost, prev[j] + 1, cur[j - 1] + 1});
			}
			std::swap(prev, cur);
		}

		// prev now holds row n: prev[j] = errors when the end of the read is aligned to a[0..j-1]
		for (int j = std::max(minOverlap, 1); j <= m; ++j) {
			if (prev[j] <= static_cast<int>(e * j)) {
				return true;
			}
		}
		return false;
	}

} // DE