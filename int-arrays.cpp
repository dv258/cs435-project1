#include <iostream>
#include <set>
#include <vector>

#include <time.h>

using namespace std;

vector<int> getRandomArray(int n)
{
	set<int> s;
	int rnd;

	while(s.size() < n)
		s.insert(rand());
	
	vector<int> arr(s.begin(), s.end());
	return arr;
}

vector<int> getSortedArray(int n)
{
	vector<int> arr;
	for (int i = n; i > 0; i--)
		arr.push_back(i);

	return arr;
}
