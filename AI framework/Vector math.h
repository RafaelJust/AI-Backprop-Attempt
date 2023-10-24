#include <vector>
using namespace std;

vector<double> Substract(vector<double> first, vector<double> second)
{
	vector<double> result;
	//Per-element substraction
	for (int i = 0; i < first.size(); i++) //Both vectors must be the same
	{
		result.push_back(first[i] - second[i]);
	}

	return result;
}

vector<double> Multiply(vector<double> first, vector<double> second)
{
	cout << "Vector Math!";
	vector<double> result;
	if (first.size() == second.size())
	{
		//use Per-element multiplication for faster calculation
		for (int i = 0; i < first.size(); i++)
		{
			result.push_back(first[i] * second[i]);
		}
	}
	else //vectors are not the same
	{
		vector<vector<double>> operands = { first,second }; //Use for easier handling
		int smaller;
		smaller = (min(first.size(), second.size()) == second.size()); //get the smallest vector

		//multiply each value of the larger vector with all the values of the smaller ones
		for (double a : operands[!smaller])
		{
			for (double product : operands[smaller]) // !smaller changes 0 to 1, and 1 to 0
			{
				a *= product;
			}
		}

		result = operands[!smaller]; //make the multiplicated vector the result
	}

	return result;
}