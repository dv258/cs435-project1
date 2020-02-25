#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector<int> getRandomArray(int n)
{
	vector<int> arr;
	int rnd;

	for (int i = 0; i < n; i++)
	{
		while(true)
		{
			rnd = rand();

			bool found = false;
			for (int j = 0; j < arr.size(); j++)
			{
				if(arr[j] == rnd)
				{
					found = true;
					break;
				}
			}

			if(!found)
				break;
		}

		arr.push_back(rnd);
	}

	return arr;
}

vector<int> getSortedArray(int n)
{
	vector<int> arr;
	for (int i = n; i > 0; i--)
		arr.push_back(i);

	return arr;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	vector<int> arr = getRandomArray(32);

	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;

	arr = getSortedArray(32);

	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}
