#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <random>
using namespace std;

//!  The Neuron class. 
/*!
  This class allows the network to create its neurons.
*/ 
 

class Neuron {
	
private:
	
	double V_; ///membrane potential
	int nb_spikes_; ///number of spikes made by the neuron
	int time_; ///internal clock of the neuron (ms)
	double threshold_; /// membrane potential threshold
	double isRefractory_; ///allows us to know if the neuron is refractory or not
	double tau_;
	double tauRef_;
	double h_;
	double R_;
	double J_;
	double I_;
	bool spike_;
	const int Vext_ = 20;
	vector <double> buffer_;
	vector <int> SendTo_;
	int D_; ///delay in ms --> is converted in steps in teh constructor
	poisson_distribution<> poisson_generator_; 
	//faire tableau de temps de spike, a chaque fois qu'il spike pushback ce tableau avec le moment ou il a spiké
	/**
	 * atparam 
	 * at return
	 * 
	 * 
	 */
	
public:
	
	//! Neuron constructor.
    /*!
      Will create a neuron which's life will start a time "time". It will have an electrical input of I.
      * When an other neuron sends him a spike, he will receive it with a delay of D.
    */ 
	Neuron(int time, double I, double D);
	
	//getters
	double getV() const;
	double getNb_spikes() const;
	double getTime_() const;
	bool getStateSpike_() const;
	double getJ() const;
	int getD() const;
	vector<int> const& getSendTo() const;
	
	//setter
	void setV (const double& V);
	void setSendTo (const double& n);
	
	//methods
	bool update(bool poisson);
	void Interact(Neuron &other);
	void addJ(double J, int D);
	double getValueBuffer();
	int poisson();
	
	
	///fct pour regarder la valeur dans le tableau
};


#endif
