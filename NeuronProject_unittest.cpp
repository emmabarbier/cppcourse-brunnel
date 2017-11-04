#include <iostream>
#include <cmath>
#include "neuron.hpp"
#include "network.hpp"
#include "gtest/gtest.h"

///Test if we have the right equation for the membrane potential
TEST (NeuronTest, Right_MembranePotential_WithOut_Poisson) {
	Neuron n(0,1.0,1.5);
	
	//First update test
	n.update(false);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), n.getV());
}

///We know that the spikes times are 92.4ms, 186.8ms, 281.2ms, 375.6ms, we will test for 2 spikes and assume that the program works afterward
TEST (NeuronTest, Right_SpikeTimes_WithOut_Poisson) {
	Neuron n(0,1.01,1.5);
	
	//first spike
	for(int i(0); i<923; ++i) { n.update(false); }
	EXPECT_EQ(0, n.getNb_spikes());
	n.update(false);
	EXPECT_EQ(1, n.getNb_spikes());
	EXPECT_EQ(0.0, n.getV());
	
	//second spike
	for(int i(0); i<943; ++i) { n.update(false); }
	EXPECT_EQ(1, n.getNb_spikes());
	n.update(false);
	EXPECT_EQ(2, n.getNb_spikes());
} 

///We know that the first spike of neuron1 occurs at 92.4ms, with a delay of 1.5ms, neuron2 must receive the spike at time 93.9ms, then it should have a value of 0.1 for its membrane potential
TEST (NeuronTest, Right_buffer) {
	
	int General_clock(0);
	
	Neuron n1(0,1.01,1.5);
	Neuron n2(0,0,1.5);
	
	//spike of neuron1
	for(int i(0); i<939; ++i) { 
		n1.update(false);
		n2.update(false);
		General_clock += 1;
		
		if (n1.getStateSpike_()) {
			n2.addJ(n1.getJ(), (General_clock + n1.getD()));
		}
	}
	EXPECT_EQ(1, n1.getNb_spikes());
	EXPECT_EQ(0.1, n2.getV());
}


//***************************Now let's test the Network******************************************************

///Test if we have well implemented our set of neurons. Thus we test if we have 12 500 neurons.
TEST (NeuronTest, Number_neurons) {
	Network network(0, 100, 0);
	EXPECT_EQ(12500, network.getSize_neuronSet());
}
