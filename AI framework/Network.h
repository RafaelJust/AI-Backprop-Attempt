#include <iostream>
#include <random>
#include <vector>
#include "Vector math.h"

using namespace std;


//Setup of the random generator
default_random_engine generator;
uniform_real_distribution<double> distribution(-1, 1);

class Neuron
{
public:
	vector<double> weights;
	double bias;
	double Last_output;
	Neuron(int LastLayerSize, double b) //initialisation of the neuron
	{
		//generate random weights
		for (int i = 0; i < LastLayerSize; i++)
		{
			weights.push_back(distribution(generator));
		}

		bias = b;
		Last_output = 0;
		cout << "Neuron created with bias " << b << "\n";
	};

	double Fire(vector<double> inputs);
};

double Neuron::Fire(vector<double> inputs)
{
	//add all the weights and previous outputs into the total function
	double total = 0;
	for (double i : inputs)
	{
		total += i * weights[i];
	}

	total += bias;
	Last_output = (1 / (1 + exp(-total)));
	cout << "Firing neuron with total of " << total << ", and value " << Last_output << "\n";
	return Last_output; //Use a sigmoid function to generate an output.
}

vector<double> GetLastActivations(vector<Neuron> neurons)
{
	vector<double> result;
	//Get the last output of all the neurons in the vector and add them to a list
	for (Neuron n : neurons)
	{
		result.push_back(n.Last_output);
	}

	return result;
}

class Network
{
public:
	vector<vector<Neuron>> netw;
	Network(vector<int> layers)
	{
		netw.resize(layers.size());
		//initialize network
		for (int layer = 0; layer < layers.size(); layer++)
		{
			//Create a random value for each neuron
			for (int n = 0; n < layers[layer]; n++)
			{
				netw[layer].push_back(Neuron(distribution(generator), distribution(generator)));
			}
		}
		cout << "Network ready to go!\n";
	};

	vector<double> GetOutput(vector<double> Input);
	void Learn(vector<double> Calculated, vector<double> target);
};

vector<double> Network::GetOutput(vector<double> Input)
{
	vector<double> previous = Input;
	vector<double> Curr;

	for (vector<Neuron> layer : netw)
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

void Network::Learn(vector<double> Calculated, vector<double> target)
{
	//Reverse the network temporarily
	reverse(netw.begin(), netw.end());

	//Output layer
	//Get the derivatives
	vector<double> d_error = Substract(Calculated, target);
	vector<double> d_activation;
	vector<double> d_weights_output;
	vector<double> d_biases_output;

	for (double out : Calculated) //d_activation
	{
		d_activation.push_back(out * (1 - out));
	}

	vector<double> delta_output = Multiply(d_error, d_activation);

	//Calculate the gradients of the weights (d_weights_output) and biases (d_biases_output) of the output layer.
	d_biases_output = delta_output;

	//The gradients are calculated by multiplying the delta_output with the activations of the previous layer (activation_previous_layer)
	vector<double> activation_previous_layer = GetLastActivations(netw[1]);
	d_weights_output = Multiply(delta_output, activation_previous_layer);

	//hidden layers
	bool first = true;
	for (vector<Neuron> CurrentLayer : netw)
	{
		if (first) { first = false; continue; } //skip the first layer, as it is the output layer
	}
}