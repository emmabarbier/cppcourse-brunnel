#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <random>
using namespace std;

/**  The Neuron class. 
 * This class implements a neuron.
*/ 
class Neuron {
	
	/**************************************************************************************
	 * 										VARIABLES
	 * *************************************************************************************/
	 
private:
	
	double V_; 				 //!< Membrane potential.
	int nb_spikes_;			 //!< Number of spikes made by the neuron.
	int time_; 				 //!< Internal clock of the neuron (ms)
	double threshold_; 		 //!< Membrane Potential's threshold
	double isRefractory_; 	 //!< allows us to know if the neuron is refractory or not
	double tau_;			 //!< A constant for the membrane equation
	double tauRef_;			 //!< Time (ms) during wich the neuron is refractory
	double h_;				 //!< Time step of our simulation : every h, we update the neuron
	double R_;				 //!< Resistance of the neuron
	double J_;				 //!< 
	double I_;				 //!< External current
	bool spike_;			 //!< True if the neuron spiked, false if it did not
	const int Vext_ = 20;	 //!< 
	vector <double> buffer_; //!< Buffer of the neuron, stores the incoming spikes with a delay
	vector <int> SendTo_;	 //!< IDs of the neurons to which the neuron sends spikes
	int D_; 				 //!< Delay of reception of a spike from an other neuron (ms)
	poisson_distribution<> poisson_generator_;  //!< poisson generator
	
	
public:
	
	/**************************************************************************************
	 * 										CONSTRUCTOR
	 * *************************************************************************************/
	 
	//! Neuron constructor.
    /*!
      Will create a neuron which's life will start a time "time". It will have an electrical input of I.
      * When an other neuron sends him a spike, he will receive it with a delay of D.
    */ 
	Neuron(int time, double I, double D);
	
	
	/**************************************************************************************
	 * 										GETTERS
	 * *************************************************************************************/
	 
	
	/**@return The membrane potential
	 */
	double getV() const;
	
	/**@return The nb of spikes of the neuron
	 */
	double getNb_spikes() const;
	
	/**@return The time of the neuron
	 */
	double getTime_() const;
	
	/**@return The number of spikes of the neuron
	 */
	bool getStateSpike_() const;
	
	/**@return The external input
	 */
	double getJ() const;
	
	/**@return The delay
	 */
	int getD() const;
	
	/**@return The vector containing the IDs of the neurons to which the neuron sends spikes
	 */
	vector<int> const& getSendTo() const;
	
	
	/**************************************************************************************
	 * 										SETTERS
	 * *************************************************************************************/
	
	/**
	@brief Gives the Membrane potentiel a new value
	@param new value of V
	 */
	void setV (const double& V);
	
	/**
	@brief Adds a value (ID of a neuron) to the vector SendTo
	@param Additional value to the vector SenTo_
	 */
	void setSendTo (const double& n);


	/**************************************************************************************
	 * 										METHODS
	 * *************************************************************************************/
	
	/**
	@brief Updates the neuron
	@param Boolean telling if we use the poisson distribution or not
	@return true if the neuron spike, false if it did not
	 */
	bool update(bool poisson);
	
	/**
	@brief When we only had two neurons, allowed us to connect them
	@param The Neuron sending the spike
	 */
	void Interact(Neuron &other);
	
	/**
	@brief Adds the value J to the buffer of the neuron with a delay D.
	@param J = value of current to implement in the buffer. D = delay to add J in the buffer.
	 */
	void addJ(double J, int D);
	
	/**
	@brief Gives back the value of the buffer at a certain time
	@return The value of the buffer at the time of the neuron
	 */
	double getValueBuffer();
	
	/**
	@brief Generates a random number of spikes
	@return the random number
	 */
	int poisson();
};


#endif
