// Game Over Detection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Neuron
{
public:
	Neuron()
	{
		//generate random weight
		weight = rand();
	}
	int weight;
	int GetOutput(int inputs[])
	{
		//calculate wether the neuron will fire or not
		int total = 0;
		//add all the weights into the total function
		for (int i = 0; i < (sizeof(inputs)/sizeof(*inputs)); i++)
		{
			int w = inputs[i];
			total += w;
		}
		//calculate wether the neuron will fire or not
		int result = 0;
		if (total > (RAND_MAX / 2))
		{
			result = weight;
		}
		return result;
	}
private:
};


int main()
{
    cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file