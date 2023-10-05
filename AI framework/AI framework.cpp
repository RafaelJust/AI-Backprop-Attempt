#include <iostream>
#include <random>
#include <vector>
using namespace std;

vector<int> layers {8,20,32,64,64,64,32,4}; //last layer is output layer
float Alpha; //The discount factor, used to determine


//Setup of the random generator
default_random_engine generator;
uniform_real_distribution<double> distribution(-1, 1);

class Neuron
{
public:
	double weight;
	Neuron(double w) //initialisation of the neuron
	{
		weight = w;
		cout << "Neuron created with weight " << w << "\n";
	};

	double Fire(vector<double> inputs)
	{
		//calculate wether the neuron will fire or not
		double total = 0;
		//add all the weights into the total function
		for (double i : inputs)
		{
			total += i;
		}
		if (total >= 1)
		{
			return weight;
		}
		else
		{
			return 0;
		}
	}
};

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
				neurons[layer].push_back(Neuron(distribution(generator)));
			}
		}
		cout << "Network ready to go!\n";
	};
	vector<double> GetOutput(vector<double> Input)
	{
		vector<double> previous = Input;
		vector<double> Curr;

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

	void Learn(vector<int> Error)
	{

	}
};

int main()
{
	cout << "Start\n";
	Network AI;
	vector<double> i;
	for (int x = 0; x < 20; x++)
	{
		i.push_back(distribution(generator));
		cout << " " << i.back();
	}
	cout << "\nAI gives output of";
	vector<double> o = AI.GetOutput(i);
	for (double x : o)
	{
		cout << " " << x;
	}
}