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
private:
	vector<double> weights;
	double bias;
public:

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
	vector<double> GetWeights();
	void SetWaB(vector<double> w, double b);
};

double Neuron::Fire(vector<double> inputs)
{
	//add all the weights and previous outputs into the total function
	double total = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		total += inputs[i] * weights[i];
	}

	total += bias;
	Last_output = (1 / (1 + exp(-total)));
	cout << "Firing neuron with total of " << total << ", and value " << Last_output << "\n";
	return Last_output; //Use a sigmoid function to generate an output.
}

vector<double> Neuron::GetWeights() { return weights; }

void Neuron::SetWaB(vector<double> w, double b) //set the weights and bias of the neuron
{
	weights = w;
	bias = b;
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
private:
	double LearningRate;
	bool reversed = false;

public:
	vector<vector<Neuron>> netw;
	void SetReversed(bool rev);

	Network(vector<int> layers, double e, int InputSize)
	{
		netw.resize(layers.size());

		//initialize network

		//Create a random value for each input layer neuron
		for (int n = 0; n < layers[0]; n++)
		{
			netw[0].push_back(Neuron(InputSize, distribution(generator)));
		}

		//Hidden layers & output layer
		for (int layer = 1; layer < layers.size(); layer++)
		{
			//Create a random value for each hidden layer neuron
			for (int n = 0; n < layers[layer]; n++)
			{
				netw[layer].push_back(Neuron(layers[layer - 1], distribution(generator)));
			}
		}

		LearningRate = e;

		cout << "Network ready to go!\n\n\n";
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

void Network::Learn(vector<double> inputs, vector<double> target)
{
	//Set up vecotrs
	vector<double> Calculated;
	vector<double> d_error;
	vector<double> d_activation;
	vector<double> d_weights_output;
	vector<double> d_biases_output;
	vector<double> delta_output;
	vector<double> activation_previous_layer;

	SetReversed(true);

	//Calculate gradients and adjust values
	int i = 0;
	for (vector<Neuron> CurrentLayer : netw)
	{
		SetReversed(false);
		Calculated = GetOutput(inputs); //Forward propagation
		cout << Calculated[0] << "\n";

		//get the derivative of the activation (d_activation)
		for (double out : Calculated)
		{
			d_activation.push_back(out * (1 - out));
		}

		//get the derivative of the error, and multipy it to get the delta of the output
		d_error = Substract(Calculated, target);
		delta_output = Multiply(d_error, d_activation);

		//Calculate the gradients of the weights (d_weights_output) and biases (d_biases_output) of the Current layer
		d_biases_output = delta_output;

		SetReversed(true); //Makes sure the network is reversed, so that the loop goes from the output layer to the input one.

		//get the activation values of the previous layer
		activation_previous_layer = GetLastActivations(netw[i + 1]);

		//apply the deltas to the current neuron
		for (int neur = 0; neur < CurrentLayer.size(); neur++)
		{
			Neuron CurrNeur = CurrentLayer[neur]; //Get the current neuron

			d_weights_output = Multiply(delta_output, Multiply(activation_previous_layer, CurrNeur.GetWeights()));

			// multiply the biases and weights with the learning rate to make sure to have all the layes adjusted
			// and apply it to the neuron.
			CurrNeur.SetWaB(Multiply(d_weights_output, (vector<double>)LearningRate), d_biases_output[neur] * LearningRate);
		}

		i++;
	}

	SetReversed(false);
}

void Network::SetReversed(bool rev)
{
	//Reverse the network if it is the wrong way
	if (reversed != rev)
	{
		reverse(netw.begin(), netw.end());
		reversed = rev;
	}
}