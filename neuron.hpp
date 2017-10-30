#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <random>
using namespace std;

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
	const int Vext = 20;
	vector <double> buffer_;
	vector <int>SendTo_;
	int D_; ///delay in ms --> is converted in steps in teh constructor
	static random device rd;
	mt19937 gene(rd());
	poisson_distribution<> poisson_generator_; 
	
	
public:
	
	//constructors
	Neuron(int time, double I, double D);
	
	//getters
	double getV() const;
	double getNb_spikes() const;
	double getTime_() const;
	bool getStateSpike_() const;
	double getJ() const;
	int getD() const;
	vector<int> &getSendTo() const;
	
	//setter
	void setV (const double& V);
	void setSendTo (const double& n);
	//void setI (const double& I);
	
	//methods
	bool update();
	void Interact(Neuron &other);
	void addJ(double J, int D);
	double getValueBuffer();
	
	
	///fct pour regarder la valeur dans le tableau
};


#endif
