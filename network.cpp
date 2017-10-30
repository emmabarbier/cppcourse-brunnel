#include "network.hpp"
#include <cmath>
#include <random>
using namespace std;

//======================================================================
//Constructors
//======================================================================

Network::Network(int time_start, int time_end, double I)
	: time_start_(time_start), time_end_(time_end), I_(I)
	{
		allocate(n_neurons_);
		ConnexionSet_.resize(12500, vector<int>(2500));
	}

//======================================================================
//getters
//======================================================================


//======================================================================
//setters
//======================================================================
	


//======================================================================
//Methods
//======================================================================

/// cette fonction ajoute a notre tableau neuronSet 12 500 neurons
void Network::allocate (int nb_neurons) {
	for (int i(0); i<nb_neurons; ++i) {
		Neuron* neuron(new Neuron(time_start_/0.1, I_, 1.5));
		NeuronSet_.push_back(neuron);
	}
}

///cette focntion doit remplir le tableau conection set
void Network::connect() {
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> exct(0,9999);
	uniform_int_distribution<> inhb(10000,12499);
	
	for (size_t x(0); x< n_neurons_; ++x) {
		
		/// les 12500 neurons sur l'axe x recoivent chacun 1000 connexions des neurons exitateurs (les 10000 premiers de l'axe y) choisis aleatoirement a chaque fois
		for (size_t y(0); y< Ce; ++y) {
			size_t target_neuron(exct(gen));
			ConnexionSet_[x][target_neuron] +=1;
		}
		
		for (size_t y(0); y< Ci; ++y) { 
			size_t target_neuron(inhb(gen));
			ConnexionSet_[x][target_neuron] +=1;
		}
	}
}

void Network::update() {
	

}
