#include "network.hpp"
#include <cmath>
#include <random>
#include <fstream>
using namespace std;

//======================================================================
//Constructor
//======================================================================

Network::Network(int time_start, int time_end, double I)
	: time_start_(time_start), time_end_(time_end/0.1), I_(I), Network_clock_(0)
	{
		allocate(n_neurons_);
	}

//======================================================================
//Methods
//======================================================================

void Network::allocate (int nb_neurons) {
	for (int i(0); i<nb_neurons; ++i) {
		Neuron* neuron(new Neuron(time_start_/0.1, I_, 1.5));
		NeuronSet_.push_back(neuron);
	}
}

void Network::connect() {
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> exct(0,Ne_-1);
	uniform_int_distribution<> inhb(Ne_,n_neurons_-1);
	
	
	for (size_t x(0); x< n_neurons_; ++x) {
		
		
		for (size_t y(0); y< Ce; ++y) {
			size_t Sending_neuron(exct(gen));
			NeuronSet_[Sending_neuron] -> setSendTo(x); 
		}
		for (size_t y(0); y< Ci; ++y) { 
			size_t Sending_neuron(inhb(gen));
			NeuronSet_[Sending_neuron] -> setSendTo(x);
		}
	}
}

void Network::update() {
	
	// declare the file
	string file_name("spikes.gdf");
	
	// open the exit flow
	ofstream exit;
	exit.open("spikes.gdf");
	
	while (Network_clock_ < time_end_) {
		int count(0);
		for (auto& neuron : NeuronSet_) {
			
			if (neuron -> update(true)) {
				
				if (exit.fail()) {
					cerr << "Error : impossible to open the file " << file_name << endl;
				} else {
					exit << neuron->getTime_()*10 << '\t' << count+1 << '\n';
				}

				if ( (count >= 0) and (count<= 9999)) { 
					for (auto& receiving_neuron : neuron->getSendTo() ) {
						NeuronSet_[receiving_neuron] -> addJ(Je, Network_clock_ + 15 );
					}
				}
			
				if ( (count >= 10000) and (count <= 12499)) {
					for (auto& receiving_neuron : neuron->getSendTo() ) {
						NeuronSet_[receiving_neuron] -> addJ(-g_*Je, Network_clock_ + 15);
					}
				}
			}
			count += 1;
		} 
		Network_clock_ += 1;
		cout << "general clock = " << Network_clock_*0.1 << endl;
	} 
	exit.close();
}
