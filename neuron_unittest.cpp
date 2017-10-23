#include <iostream>
#include <cmath>
#include "neuron.hpp"
#include "gtest/gtest.h"

///Test if we have the right equation for the membrane potential
TEST (NeuronTest, MembranePotential) {
	Neuron n(0,1.0,1.5);
	
	//First update test
	n.update();
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), n.getV());
}

///We know that the spikes times are 92.4ms, 186.8ms, 281.2ms, 375.6ms, we will test for 2 spikes and assume that the program works afterward
TEST (NeuronTest, SpikeTimes) {
	Neuron n(0,1.01,1.5);
	
	//first spike
	for(int i(0); i<923; ++i) { n.update(); }
	EXPECT_EQ(0, n.getNb_spikes());
	n.update();
	EXPECT_EQ(1, n.getNb_spikes());
	EXPECT_EQ(0.0, n.getV());
	
	//second spike
	for(int i(0); i<943; ++i) { n.update(); }
	EXPECT_EQ(1, n.getNb_spikes());
	n.update();
	EXPECT_EQ(2, n.getNb_spikes());
} 
