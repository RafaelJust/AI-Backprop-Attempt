#include <iostream>
#include <vector>
using namespace std;

vector<int> layers {3,5,5,3,4}; //last layer is output layer

class Neuron
{
public:
	int weight;
	Neuron(int w) //initialisation of the neuron
	{
		weight = w;
		cout << "Neuron created with weight " << w << "\n";
	};

	int Fire(vector<int> inputs)
	{
		//calculate wether the neuron will fire or not
		int total = 0;
		//add all the weights into the total function
		for (int i : inputs)
		{
			total += i;
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
		neurons.resize(layers.size());
		//initialize network
		for (int layer = 0; layer < layers.size(); layer++)
		{
			//Create a random value for each neuron
			for (int n = 0; n < layers[layer]; n++)
			{
				neurons[layer].push_back(Neuron(rand()));
			}
		}
		cout << "Network ready to go!\n";
	};
	vector<int> GetOutput(vector<int> Input)
	{
		vector<int> previous = Input;
		vector<int> Curr;

		for (vector<Neuron> layer : neurons)
		{
			//fill in the current vector with the outputs of the neurons in that layer
			Curr.clear();
			for (Neuron n : layer)
			{
				Curr.push_back(n.Fire(previous));
			}
			previous = Curr; //use result for next input
		}
		return Curr;
	}
};

int main()
{
	cout << "Start\n";
	Network AI;
	vector<int> i {1,2,3,7,4,34536,8934};
	cout << "AI gives output of";
	vector<int> o = AI.GetOutput(i);
	for (int x : o)
	{
		cout << " " << x;
	}
}