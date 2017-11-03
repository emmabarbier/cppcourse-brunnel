#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include <iostream>
#include <vector>
using namespace std;

//!  The Network class. 
/*!
  This class allows us to implement a set of communicating neurons.
*/

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
	int Network_clock_;
	
	
	//vector < vector<int> > ConnexionSet_ = 	vector < vector<int> > (12500, vector<int> (12500)); //comment initialiser la taille a 12500 par 12500
	vector < Neuron*> NeuronSet_; 

public:
	
	//! Network constructor.
    /*!
      Will create a network which life starts a time "time_start" and end at time "time_end".
      * Each of its neuron has an input of I.
    */ 
	Network(int time_start, int time_end, double I);
	
	//methods
	void connect();
	void allocate(int nb_neurons);
	void update(int time_end);
		
};

#endif
