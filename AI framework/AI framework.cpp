#include <iostream>
#include "Network.h"
using namespace std;

vector<int> layers{ 8,20,32,64,64,64,32,4 }; //last layer is output layer

int main()
{
	cout << "Start\n";
	Network AI(layers);
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