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
		for (int i = 0; i < sizeof(inputs); i++)
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