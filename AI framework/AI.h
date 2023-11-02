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
private:
	vector<double> weights;
	double bias;
public:
	double input;
	double output;

	Neuron(int LastLayerSize, double b) //initialisation of the neuron
	{
		
		//generate random weights
		for (int i = 0; i < LastLayerSize; i++)
		{
			weights.push_back(distribution(generator));
		}

		bias = b;
		output = 0;
		cout << "Neuron created with bias " << b << "\n";
	};

	double Fire(vector<double> inputs);

	vector<double> GetWeights();
	double GetBias();

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
	input = total;
	total += bias;
	output = tanh(total);
	//cout << "Firing neuron with total of " << total << ", and value " << output << "\n";
	return output; //Use a sigmoid function to generate an output.
}

vector<double> Neuron::GetWeights() { return weights; }
double Neuron::GetBias() { return bias; }

void Neuron::SetWaB(vector<double> w, double b) //set the weights and bias of the neuron
{
	weights = w;
	bias = b;
}


class Network
{
public:
	double learningRate;
	vector<vector<Neuron>> netw;
	vector<vector<double>> Outputs;

	Network(vector<int> layers, int InputSize, double lr)
	{
		netw.resize(layers.size());

		//initialize network

		learningRate = lr; //set the current learning rate

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

		cout << "Network ready to go!\n\n\n";
	};

	vector<double> GetOutput(vector<double> Input);
	vector<double> ActivationFunction(vector<double> in);
	void Learn(const vector<double>& input, const vector<double>& expectedOutput);
};

vector<double> Network::GetOutput(vector<double> Input)
{
	Outputs.clear();
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
		Outputs.push_back(Curr); //Add the output of the layer to the outputs vector
		previous = Curr; //use result for next input
	}
	return Curr;
}

vector<double> Network::ActivationFunction(vector<double> input)
{
	vector<double> result;
	//calculates the output of the current layer
	for (double i : input)
	{
		result.push_back(tanh(i));
	}
	return result;
}

void Network::Learn(const vector<double>& input, const vector<double>& expectedOutput) {
	// Backpropagation
	vector<vector<double>> dC_do(netw.size()); //Derivative of the cost function wrt output of the neuron
	vector<vector<double>> dC_di(netw.size()); //Derivative of the cost function wrt input of the neuron
	vector<vector<double>> dC_dW(netw.size()); //Derivative of the cost function wrt weights

	// Calculate derivatives starting from the output layer
	for (int layer = static_cast<int>(netw.size()) - 1; layer >= 0; --layer) { // the -2 is because the last layer is the output layer, so skip it, and 0 is input layer, so ignore it
		auto temp_layer = netw[layer];

		//Calculate dC_do
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
					double CurrW = temp_layer[neuronIdx].GetWeights()[Synapse];
					temp_dC_do += CurrW * dC_di[nxt_l][Synapse];
					dC_dW[neuronIdx].push_back(temp_layer[neuronIdx].output * dC_di[nxt_l][Synapse]);
				}
				dC_do[layer].push_back(temp_dC_do);
			}

			
			dC_di[layer].push_back(da_dz(temp_));
		}
	}
}