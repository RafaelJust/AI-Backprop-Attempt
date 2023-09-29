#include <iostream>
#include <vector>
using namespace std;

int layers[] = {3,5,5,3};

class Neuron
{
public:
	int weight;
	Neuron(int w) //initialisation of the neuron
	{
		weight = w;
		cout << "Neuron created with weight " << w << "\n";
	};

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
};

int getLargestNumber(int list[])
{
	//Go through every entry in an array and return the index of the largest one
	int Largest = 0;
	for (int i = 0; i < sizeof(list); i++)
	{
		if (list[i] > list[Largest])
		{
			Largest = i;
		}
	}
	return Largest;
}

class Network
{
public:
	vector<vector<Neuron>> neurons;
	Network()
	{
		//initialize network
		neurons.resize(sizeof(layers));
		for (int i = 0; i < neurons.size(); i++)
		{
			cout << "[" << i << "]";
			neurons[i].assign(layers[i], Neuron(rand())); //Create a single layer with random weights
		}
	};
};

int main()
{
	cout << "Start\n";
	Network AI;
}