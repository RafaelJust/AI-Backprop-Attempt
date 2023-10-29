#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <math.h>

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

	total += bias;
	Last_output = tanh(total);
	cout << "Firing neuron with total of " << total << ", and value " << Last_output << "\n";
	return Last_output; //Use a sigmoid function to generate an output.
}

vector<double> Neuron::GetWeights() { return weights; }
double Neuron::GetBias() { return bias; }

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
public:
	double learningRate;
	vector<vector<Neuron>> netw;

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
	// Feedforward
	vector<double> layerOutput = input; // Output of the current layer
	vector<vector<double>> layerOutputs; // Store outputs of all layers
	layerOutputs.push_back(layerOutput);

	for (size_t layer = 0; layer < netw.size(); ++layer) {
		vector<double> layerInput; // Input to the current layer

		// Calculate input to the current layer
		for (Neuron neuron : netw[layer]) {
			// Get weights of the neuron
			vector<double> weights = neuron.GetWeights();

			// Multiply neuron outputs with corresponding weights and add them up
			double neuronInput = inner_product(layerOutput.begin(), layerOutput.end(),
				weights.begin(), 0.0);

			// Add bias
			neuronInput += neuron.GetBias();

			layerInput.push_back(neuronInput);
		}

		// Calculate output of the current layer using activation function
		layerOutput = ActivationFunction(layerInput);
		layerOutputs.push_back(layerOutput);
	}

	// Backpropagation
	vector<double> error; // Error at the output layer
	for (size_t i = 0; i < expectedOutput.size(); ++i) {
		double output = layerOutput[i];
		error.push_back(expectedOutput[i] - output);
	}
	vector<double> nextLayerError = error;

	// Adjust weights and biases of each neuron starting from the output layer
	for (int layer = static_cast<int>(netw.size()) - 1; layer >= 0; --layer) {
		vector<double> delta; // Delta value for weight adjustment

		// Backpropagate the error to the current layer
		vector<double> currentError;
		for (int neuronIdx = 0; neuronIdx < netw[layer].size(); neuronIdx++) {
			double neuronError = 0.0;
			for (int nextNeuronIdx = 0; nextNeuronIdx < netw[layer + 1].size(); nextNeuronIdx++) {
				double weightedError = nextLayerError[nextNeuronIdx] * netw[layer][neuronIdx].GetWeights()[nextNeuronIdx];
				neuronError += weightedError;
			}
			neuronError *= layerOutputs[layer + 1][neuronIdx] * (1 - layerOutputs[layer + 1][neuronIdx]); // Apply the derivative of the activation function
			currentError.push_back(neuronError);
		}

		cout << "Current Layer size: " << netw[layer].size() << "\n";
		for (size_t neuronIdx = 0; neuronIdx < netw[layer].size(); ++neuronIdx) {
			cout << "Busy adjusting values of weight [" << layer << "," << neuronIdx << "]\n";
			// Calculate delta for the current neuron
			double neuronOutput = layerOutputs[layer][neuronIdx];
			double neuronDelta = neuronOutput * (1 - neuronOutput) * currentError[neuronIdx];
			delta.push_back(neuronDelta);

			// Get weights of the current neuron
			vector<double> weights = netw[layer][neuronIdx].GetWeights();
			cout << "weights.size() = " << weights.size() << "\n";

			// Update weights and bias of the current neuron
			vector<double> newWeights;
			for (size_t weightIdx = 0; weightIdx < weights.size(); ++weightIdx) {
				double newWeight = weights[weightIdx] + learningRate * neuronDelta * layerOutputs[layer][weightIdx];
				newWeights.push_back(newWeight);
				cout << "newWeights.size() = " << newWeights.size() << "\n";
			}

			double newBias = netw[layer][neuronIdx].GetBias() + learningRate * neuronDelta;
			netw[layer][neuronIdx].SetWaB(newWeights, newBias);
			cout << "Updated weight and biases! newBias: " << newBias << "\n\n";
		}

		// Calculate error for the previous layer
		error.clear();
		for (size_t neuronIdx = 0; neuronIdx < netw[layer].size(); ++neuronIdx) {
			double neuronError = inner_product(delta.begin(), delta.end(),
				netw[layer][neuronIdx].GetWeights().begin(), 0.0);
			error.push_back(neuronError);
		}

		//save the current error to the nexterror vector fro use in the next layer
		nextLayerError = currentError;
	}
}