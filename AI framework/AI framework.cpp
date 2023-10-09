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
	vector<double> weights;
	double bias;
	Neuron(int LastLayerSize, double b) //initialisation of the neuron
	{
		//generate random weights
		for (int i = 0; i < LastLayerSize; i++)
		{
			weights.push_back(distribution(generator));
		}

		bias = b;
		cout << "Neuron created with bias " << b << "\n";
	};

	double Fire(vector<double> inputs)
	{
		//add all the weights and previous outputs into the total function
		double total = 0;
		for (double i : inputs) 
		{
			total += i * weights[i];
		}

		total += bias;

		cout << "Firing neuron with total of " << total << ", and value " << (1 / (1 + exp(-total))) << "\n";
		return (1 / (1 + exp(-total))); //Use a sigmoid function to generate an output.
	}
};

vector<double> Substract(vector<double> first, vector<double> second)
{
	vector<double> result;
	//Per-element substraction
	for (int i = 0; i < first.size(); i++) //Both vectors must be the same
	{
		result[i] = first[i] - second[i];
	}
	return result;
}

class Network
{
public:
	vector<vector<Neuron>> netw;
	Network()
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
	vector<double> GetOutput(vector<double> Input)
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

	void Learn(vector<double> Calculated, vector<double> target)
	{
		//Reverse the network temporarily
		reverse(netw.begin(), netw.end());

		//Output layer
		//Get the derivatives
		vector<double> d_error = Substract(Calculated, target);
		vector<double> d_activation;
		vector<double> d_weights_output;
		vector<double> d_bias_output;

		for (double out : Calculated) //d_activation
		{
			d_activation.push_back(out * (1 - out));
		}

		vector<double> 

		//hidden layers
		bool first = true;
		for (vector<Neuron> CurrentLayer : netw)
		{
			if (first) { first = false; continue; } //skip the first layer, as it is the output layer
		}
	}
};

int main()
{
	cout << "Start\n";
	Network AI;
	vector<double> i;
	//Input custom inut for testing
	int A;
	cin >> A;
	for (int x = 0; x < A + 1; x++)
	{
		double inp;
		cin >> inp;
		i.push_back(inp);
	}
	cout << "\nAI gives output of";
	vector<double> o = AI.GetOutput(i);
	for (double x : o)
	{
		cout << " " << x;
	}
}