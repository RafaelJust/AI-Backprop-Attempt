#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <math.h>

// Sym: i -> input in neuron; o -> output of neuron; C -> Cost function; W -> weights
// Sym: delta -> dC/dz

using namespace std;

//Setup of the random generator
default_random_engine generator;
uniform_real_distribution<double> distribution(-1, 1);

double da_dz(double z)
{
	return tanh(z) * (1.0f - tanh(z));
}

class Neuron
{
public:
	vector<double> weights;
	double bias;
	double input;
	double output;

	Neuron(int NextLayerSize, double b) //initialisation of the neuron
	{
		
		//generate random weights
		for (int weight = 0; weight < NextLayerSize; weight++)
		{
			weights.push_back(distribution(generator));
		}

		bias = b;
		output = 0;
		cout << "Neuron created with " << weights.size() << " weights\n";
	};

	double Fire(vector<double> inputs, int neuronIdx, vector<Neuron> prevNeur);
};

double Neuron::Fire(vector<double> inputs, int neuronIdx, vector<Neuron> prevNeur)
{
	//add all the weights and previous outputs into the total function
	double total = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		total += inputs[i] * prevNeur[i].weights[neuronIdx];
	}
	input = total;
	total += bias;
	output = tanh(total); //use a tanh function to generate an output
	return output;
}


class Network
{
public:
	double learningRate;
	vector<vector<Neuron>> netw;
	vector<vector<double>> Outputs;

	Network(vector<int> layers, double lr)
	{
		netw.resize(layers.size());

		//initialize network

		learningRate = lr; //set the current learning rate

		//Input & Hidden layers
		for (int layer = 0; layer < layers.size() - 1; layer++)
		{
			cout << "Layer " << layer << " with size = " <<  layers[layer] << "and weight amount " << layers[layer + 1] << ":\n";
			//Create a random value for each hidden layer neuron
			for (int n = 0; n < layers[layer]; n++)
			{
				netw[layer].push_back(Neuron(layers[layer + 1], distribution(generator)));
			}
			cout << " \n";
		}

		//Output neurons
		for (int n = 0; n < layers[layers.size() - 1]; n++)
		{
			netw[layers.size() - 1].push_back(Neuron(0, distribution(generator)));
		}

		cout << "Network ready to go!\n\n\n";
	};

	vector<double> GetOutput(vector<double> Input);
	void Learn(const vector<double>& input, const vector<double>& expectedOutput);
};

vector<double> Network::GetOutput(vector<double> Input)
{
	Outputs.clear();
	vector<double> previous = Input;
	vector<Neuron> previousLayer = netw[Input[0]];
	vector<double> Curr;

	for (vector<Neuron> layer : netw)
	{
		//fill in the current vector with the outputs of the neurons in that layer
		Curr.clear();
		for (int neuronIdx = 0; neuronIdx < layer.size(); ++neuronIdx)
		{
			Curr.push_back(layer[neuronIdx].Fire(previous, neuronIdx, previousLayer));
		}
		Outputs.push_back(Curr); //Add the output of the layer to the outputs vector
		//use result and layer for next input
		previous = Curr;
		previousLayer = layer;
	}
	return Curr;
}

void Network::Learn(const vector<double>& input, const vector<double>& expectedOutput) {
	// Backpropagation
	vector<vector<double>> dC_do(netw.size()); //Derivative of the cost function wrt output of the neuron
	vector<vector<double>> dC_di(netw.size()); //Derivative of the cost function wrt input of the neuron
	vector<vector<vector<double>>> dC_dW(netw.size()); //Derivative of the cost function wrt weights

	// Calculate derivatives starting from the output layer
	for (int layer = static_cast<int>(netw.size()) - 1; layer >= 0; --layer) { // the -2 is because the last layer is the output layer, so skip it, and 0 is input layer, so ignore it
		auto temp_layer = netw[layer];
		vector<vector<double>> temp_dC_dW;
		//Calculate dC_do and dC_dW
		for (size_t neuronIdx = 0; neuronIdx < netw[layer].size(); ++neuronIdx) {
			if (layer == netw.size() - 1) //Output layer
			{
				dC_do[layer].push_back(temp_layer[neuronIdx].output - expectedOutput[neuronIdx]);
			}
			else { //Hidden and input layers
				double temp_dC_do = 0;
				int nxt_l = layer + 1;

				for (int Synapse = 0; Synapse < netw[nxt_l].size(); ++Synapse)
				{
					//Multiply all weights with the derivative of the output from the next layer.
					double CurrW = temp_layer[neuronIdx].weights[Synapse];
					temp_dC_do += CurrW * dC_di[nxt_l][Synapse];

					//multiply the neurons output with the input of the neuron connected to it to get dC_dW
					temp_dC_dW[neuronIdx].push_back(temp_layer[neuronIdx].output * dC_di[nxt_l][Synapse]);
				}

				//Apply the fnal values
				dC_do[layer].push_back(temp_dC_do);
				dC_dW.push_back(temp_dC_dW);
			}

			
			dC_di[layer].push_back(da_dz(temp_layer[neuronIdx].input) * dC_do[layer][neuronIdx]);
		}
	}

	 //Adjust the weights
	for (int layer = 0; layer < netw.size() - 1; ++layer)
	{
		for (int neuronIdx = 0; neuronIdx < netw[layer].size(); ++neuronIdx)
		{
			for (int synapse = 0; synapse < netw[layer + 1].size(); synapse++)
			{
				netw[layer][neuronIdx].weights[synapse] -= learningRate * dC_dW[layer][neuronIdx][synapse];
			}
		}
	}
}