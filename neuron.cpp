#include "neuron.hpp"
#include <fstream>
#include <cmath>
using namespace std;


//======================================================================
//Constructor
//======================================================================


Neuron::Neuron(int time, double I, double D)
	:  V_(0), nb_spikes_(0), time_(time), threshold_(20), isRefractory_(0), tau_(20.), tauRef_(2), h_(0.1), R_(20), J_(0.1), I_(I), spike_(false), buffer_((D/h_)+1, 0), D_(D/0.1) {}

//======================================================================
//getters
//======================================================================

double Neuron::getV() const { return V_; }

double Neuron::getNb_spikes() const { return nb_spikes_; }

double Neuron::getTime_() const { return time_*0.1; } //*0.1 to convert steps to ms

bool Neuron::getStateSpike_() const { return spike_;}

double Neuron::getJ() const {return J_;}

int Neuron::getD() const {return D_; }

vector<int> const& Neuron::getSendTo() const { return SendTo_; }

//======================================================================
//setters
//======================================================================
	
void Neuron::setV (const double& V) { V_= V; }
void Neuron::setSendTo (const double& n) { SendTo_.push_back(n); }


//======================================================================
//Methods
//======================================================================

bool Neuron::update(bool pois) {


	if (isRefractory_ > 0){
		V_ = getValueBuffer();	 //we use this function to set the values of the buffer at 0 during the times it is refractory
		V_= 0;					 //we reset the value of the membrane potential at 0 because the neuron is refractory
		isRefractory_ -=1;
		spike_ = false;
	} else {
		if(pois) { 				//so that our Google tests can work, we have the possibility of using the poisson generator or not
			V_ =  (exp(-h_/tau_)*V_ + I_*R_*(1-exp(-h_/tau_)) + getValueBuffer() + poisson()*J_);
		}
		else {
			V_ =  (exp(-h_/tau_)*V_ + I_*R_*(1-exp(-h_/tau_)) + getValueBuffer());
		}
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


void Neuron::addJ(double J, int D) {
	buffer_[(D)%(buffer_.size())] += J;
}

double Neuron::getValueBuffer() {
	int bufferTime ((time_+1)% buffer_.size()); 	//we access the cell of the buffer we are interested in using the time of the neuron
	double J(buffer_[bufferTime]);					//we access the value of the buffer at t
	buffer_[bufferTime] =0; 						//we reset to 0 the value of the buffer at that time 
	return J;
}

int Neuron::poisson() {
	static random_device rd;
	mt19937 gene(rd());
	double v = (threshold_* eta_ )/(J_ * tau_);
	poisson_distribution<> poisson_generator_(v*0.1);
	return poisson_generator_(gene);
}

