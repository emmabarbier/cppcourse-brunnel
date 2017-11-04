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

///The membrane potential should tend to 20 but never reach it if the input is 1.0. Then the neuron never spikes
TEST (NeuronTest, Right_MembranePotential_to20_WithOut_Poisson) {
	Neuron n(0,1.0,1.5);
	for(int i(0); i<9999; ++i) { n.update(false); } //for many updates
	EXPECT_GT(1E-3, std::fabs(19.999 - n.getV()));
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

///We do pretty much the same test, as we know neuron 1 should spike 4 times within 400ms (=4000 steps)
TEST (NeuronTest, Right_number_spikes_WithOut_Poisson) {
	Neuron n(0,1.01,1.5);
	for(int i(0); i<4000; ++i) { n.update(false); }
	EXPECT_EQ(4, n.getNb_spikes());
} 


///We know that the first spike of neuron1 occurs at 92.4ms, with a delay of 1.5ms, neuron2 must receive the spike at time 93.9ms, then it should have a value of 0.1 for its membrane potential
TEST (TwoNeurons, Right_buffer) {
	
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

///We know that after 2 spikes of neuron1, neuron 2 will spike, let's check
TEST (TwoNeurons, SpikeNeuron2) {
	
	int General_clock(0);
	
	Neuron n1(0,1.01,1.5);
	Neuron n2(0,1.0,1.5);
	
	// 2 spikes of neuron1
	for(int i(0); i<1868+15; ++i) { 
		n1.update(false);
		n2.update(false);
		General_clock += 1;
		
		if (n1.getStateSpike_()) { 
			n2.addJ(n1.getJ(), (General_clock + n1.getD()));
			EXPECT_EQ(0, n1.getV());
		}
	}
	EXPECT_EQ(2, n1.getNb_spikes());
	EXPECT_EQ(1, n2.getNb_spikes());
}


//***************************Now let's test the Network******************************************************

///Test if we have well implemented our set of neurons. Thus we test if we have 12 500 neurons.
TEST (NetworkTest, Number_neurons) {
	Network network(0, 100, 0);
	EXPECT_EQ(12500, network.getSize_neuronSet());
}
