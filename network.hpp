#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Network {
	
private :
	int time_start_;
	int time_end_;
	int I_;
	const unsigned int n_neurons_ = 12500;
	const int Ne_ = 10000;
	const int Ni_ = 2500;
	const int g_= 5;
	const unsigned int Ce = 1000;
	const unsigned int Ci = 250;
	double Je = 0.1;
	
	
	//vector < vector<int> > ConnexionSet_ = 	vector < vector<int> > (12500, vector<int> (12500)); //comment initialiser la taille a 12500 par 12500
	vector < Neuron*> NeuronSet_; 

public:
	
	//constructors
	Network(int time_start, int time_end, double I); //default constructor
	
	//methods
	void connect();
	void allocate(int nb_neurons);
	void update(int General_clock);
		
		
};

#endif
