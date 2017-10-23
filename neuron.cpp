#include "neuron.hpp"
#include <fstream>
#include <cmath>
using namespace std;


//======================================================================
//Constructors
//======================================================================

//default constructor
Neuron::Neuron(int time, double I, double D)
	:  V_(0), nb_spikes_(0), time_(time), threshold_(20), isRefractory_(0), tau_(20.), tauRef_(2), h_(0.1), R_(20), J_(0.1), I_(I), spike_(false), buffer_(16, 0), D_(D/0.1)  {}
	//:  V_(0), nb_spikes_(0), time_(time), threshold_(20), isRefractory_(0), tau_(20.), tauRef_(2), h_(0.1), R_(20), J_(0.1), I_(I), spike_(false), buffer_(((D/h_) +1)	, 0), D_(D/0.1)  {}
	
//D/h +1
//======================================================================
//getters
//======================================================================

double Neuron::getV() const { return V_; }

double Neuron::getNb_spikes() const { return nb_spikes_; }

double Neuron::getTime_() const { return time_*0.1; } 

bool Neuron::getStateSpike_() const { return spike_;}

double Neuron::getJ() const {return J_;}

int Neuron::getD() const {return D_; }

//double Neuron::getI() const { return I_;}

//======================================================================
//setters
//======================================================================
	
void Neuron::setV (const double& V) { V_= V; }

//void Neuron::setI (const double& I) { I_ = I}

//======================================================================
//Methods
//======================================================================

bool Neuron::update() {

	if (isRefractory_ > 0){
		V_= 0;
		isRefractory_ -=1;
		spike_ = false;
		//to do :clear the buffer at the times where the neuron is refractory (copy the fct getValue buffer without a return)
	} else {
		V_ =  (exp(-h_/tau_)*V_ + I_*R_*(1-exp(-h_/tau_)) + getValueBuffer()); ///ici on va ajouter le nombre de J qu'il y a dans le buffer du neuron au temps actuel
	}
			
	if (V_ > threshold_ ) {
		nb_spikes_+=1;
		isRefractory_ = tauRef_/h_;
		V_=0;
		spike_ = true;
	}
		
	time_ += 1;
	return spike_;
}

void Neuron::Interact(Neuron &other) {
	if (other.spike_ == true) {
		other.V_ += J_;
	}
}

///on ajoute un J au buffer avec un delais du temps actuel + delais
void Neuron::addJ(double J, int D) {
	buffer_[(D)%(buffer_.size())] += J;
}

double Neuron::getValueBuffer() {
	int bufferTime ((time_+1)% buffer_.size()); ///ici on accede a la cellule du buffer qui nous interesse a partir du temps du neuron
	double J(buffer_[bufferTime]);
	buffer_[bufferTime] =0; ///on reinitialise la cellule du buffer qu'on vient de lire a 0
	return J;
}

