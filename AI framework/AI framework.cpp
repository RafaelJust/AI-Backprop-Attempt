#include <iostream>
#include "Network.h"
using namespace std;


int main()
{
	cout << "Start\n";
	Network AI;
	vector<double> i;
	//Input custom input for testing
	int A;
	cin >> A;
	for (int x = 0; x < A + 1; x++)
	{
		double inp;
		cin >> inp;
		i.push_back(inp);
	}
	cout << "\nAI gives output of";
	vector<double> o = AI.GetOutput(i);
	for (double x : o)
	{
		cout << " " << x;
	}
}