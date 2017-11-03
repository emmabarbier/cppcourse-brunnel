#include "network.hpp"
#include <cmath>
#include <random>
#include <fstream>
using namespace std;

//======================================================================
//Constructors
//======================================================================

Network::Network(int time_start, int time_end, double I)
	: time_start_(time_start), time_end_(time_end/0.1), I_(I), Network_clock_(0)
	{
		allocate(n_neurons_);
	}

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
	
	//int i;
	
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
		//++i;
		//cout << "i= " << i << endl;
		//cout << "taille de sendTo de " << x << ": " << 
	}
}

///la fonction update va iterer sur NeuronSet_. Pour chaque neuron, regarde si il a spike
/// si il a spike, itere sur tous les neurones connectes a celui la
void Network::update(int time_end) {
	
	// declare the file
	string file_name("spikes.gdf");
	
	// open the exit flow
	ofstream exit;
	exit.open("spikes.gdf");
	
	while (Network_clock_ < time_end_) {
		
		int count(0);
		for (auto& neuron : NeuronSet_) { ///pour chaque neuron
			
			if (neuron -> update(true)) {  ///si il a spiké
				
				if (exit.fail()) {
					cerr << "Error : impossible to open the file " << file_name << endl;
				} else {
					exit << neuron->getTime_() << '\t' << count+1 << '\n';
				}

				if ( (count >= 0) and (count<= 9999)) { ///si il est exitateur 
				
					///il doit iterer sur son tableau sendTo et addJexitatory a chacun des neurons compris dans sendTo
					for (auto& receiving_neuron : neuron->getSendTo() ) {
						NeuronSet_[receiving_neuron] -> addJ(Je, Network_clock_ + 15 );
					}
				}
			
				if ( (count >= 10000) and (count <= 12499)) { ///si il est inhibiteur
				
					///il doit iterer sur son tableau sendTo et addJinhibitory a chacun des neurons compris dans sendTo
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
