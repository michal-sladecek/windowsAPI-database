#pragma once
#include "stdafx.h"
#include <string>
#include <vector>

template<class T>
UINT editDist(T str1, T str2)
{
	size_t l1 = str1.length(), l2 = str2.length();
	std::vector<std::vector<int> > dp(l1 + 1, std::vector<int>(l2 + 1, 0));
	for (size_t i = 0; i <= l1; i++) {
		for (size_t j = 0; j <= l2; j++) {
			if (i == 0)dp[i][j] = j;
			else if (j == 0)dp[i][j] = i;
			else if (str1[i - 1] == str2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
		}
	}
	return dp[l1][l2];
}
