#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include <iostream>
#include <vector>
using namespace std;

/**  The Network class. 
 * This class allows us to implement a set of communicating neurons.
*/ 

class Network {
	
	
	/**************************************************************************************
	 * 										VARIABLES
	 * *************************************************************************************/
	
private :
	int time_start_;						//!< Time at which the simulation starts (ms).
	int time_end_;							//!< Time at which the simulation ends (ms).
	int I_;									//!< External current
	const unsigned int n_neurons_ = 12500;  //!< Number of neurons
	const int Ne_ = 10000;					//!< Number of excitatory neurons
	const int Ni_ = 2500;					//!< Number of inhibitory neurons
	const int g_= 5;						//!< Weight of the connection
	const unsigned int Ce = 1000;			//!< Number of excitatory connexions a neuron receives
	const unsigned int Ci = 250;			//!< Number of inhibitory connexions a neuron receives
	double Je = 0.1;						//!< Current added to the neurons the neurons send spikes to when they are excitatory
	int Network_clock_;						//!< Clock of the simulation (ms)
	vector < Neuron*> NeuronSet_; 			//!< Vector of neurons

public:

	/**************************************************************************************
	 * 										CONSTRUCTOR
	 * *************************************************************************************/
	
	//! Network constructor.
    /*!
      Will create a network which life starts a time "time_start" and end at time "time_end".
      * Each of its neuron has an input of I.
    */ 
	Network(int time_start, int time_end, double I);
	
	
	/**************************************************************************************
	 * 										GETTER
	 * *************************************************************************************/
	 
	
	/**
	@brief useful for the google test on the network
	@return The size of the NeuronSet
	 */
	int getSize_neuronSet() const;
	
	
	/**************************************************************************************
	 * 										METHODS
	 * *************************************************************************************/
	 
	/**
	@brief Creates the 1000 random excitatory connexions and 250 random inhibitory connexions each neuron receives. Also sets the vector SendTo of each neuron.
	 */
	void connect();
	
	/**
	@brief Sets our set of 12 500 neurons
	@param The number of neurons of the network
	 */
	void allocate(int nb_neurons);
	
	/**
	@brief Updates the network
	 */
	void update();
		
};

#endif
