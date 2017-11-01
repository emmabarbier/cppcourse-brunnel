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
		//ConnexionSet_.resize(12500, vector<int> (12500));
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

///cette focntion doit remplir le tableau ConnectedTo de chaque neuron
void Network::connect() {
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> exct(0,Ne_-1);
	uniform_int_distribution<> inhb(Ne_,n_neurons_-1);
	
	for (size_t x(0); x< n_neurons_; ++x) {
		
		/// les 12500 neurons recoivent chacun 1000 connexions des neurons exitateurs (les 10000 premiers de l'axe y) choisis aleatoirement a chaque fois
		for (size_t y(0); y< Ce; ++y) {
			size_t Sending_neuron(exct(gen)); ///choix aleatoire du neuron qui envois la connection a x, ici on s'assure que chaque neuron recoit bien 1000 connections exitatrices
			NeuronSet_[Sending_neuron] -> setSendTo(x); ///le tableau SendTo du neuron qui envois (donc sending neuron) est implemente par l'indice de celui a qui il envois, donc x
		}
		
		for (size_t y(0); y< Ci; ++y) { 
			size_t Sending_neuron(inhb(gen));
			NeuronSet_[Sending_neuron] -> setSendTo(x);
		}
	}
}

///la fonction update va iterer sur NeuronSet_. Pour chaque neuron, regarde si il a spike
/// si il a spike, itere sur tous les neurones connectes a celui la
void Network::update(int General_clock) {
	
	int count(0);
	
	for (auto& neuron : NeuronSet_) { ///pour chaque neuron 
		
		
		if (neuron -> update()) {  ///si il a spiké
			
			if ( (count >= 0) and (count<= 9999)) { ///si il est exitateur 
				
				///il doit iterer sur son tableau sendTo et addJexitatory a chacun des neurons compris dans sendTo
				for (auto& receiving_neuron : neuron->getSendTo() ) {
					NeuronSet_[receiving_neuron] -> addJ(Je, General_clock + 15 );
				}
			}
			
			if ( (count >= 10000) and (count <= 12499)) { ///si il est inhibiteur
				
				///il doit iterer sur son tableau sendTo et addJinhibitory a chacun des neurons compris dans sendTo
				for (auto& receiving_neuron : neuron->getSendTo() ) {
					NeuronSet_[receiving_neuron] -> addJ(-g_*Je, General_clock + 15);
				}
	
			
			}
		}
		count += 1;
	} 
	
}


//changer ptr
//enlever num
