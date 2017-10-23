#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Network {
	
private :
	vector< vector<int> > NeuronSet_;

public:
	
	//constructors
	Network(vector< vector<int> > ConnexionSet); //default constructor
		
		
};

#endif
