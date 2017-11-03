#include "neuron.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <memory>

int main () {
	double I;
	int time_start;
	int time_end;
	int General_clock(0);
	double h(0.1);
	
	cout << "Enter external current : ";
	cin >> I;
	
	cout << "Enter start time :  ";
	cin >> time_start;
	
	cout << "Enter end time : ";
	cin >> time_end;

	Neuron n_one(time_start/h,I,1.5);
	Neuron n_two(time_start/h,0,1.5);
	
	// declare the file
	string file_name("MembranePotential.txt");
	
	// open the exit flow
	ofstream exit;
	exit.open("MembranePotential.txt");
	
	// verifies if the file exists
	if (exit.fail()) {
		cerr << "Error : impossible to open the file " << file_name << endl;
	} else {
		while (General_clock < time_end) {
			n_one.update(false);
			n_two.update(false);
			
			General_clock += 1;
			
			if (n_one.getStateSpike_()) {
				exit << "Neuron 1 spiked at time : " << n_one.getTime_() << endl;
				n_two.addJ(n_one.getJ(), (General_clock + n_one.getD()));		///envois au buffer de n_two un J avec un delais
			}
			
			exit << "Membrane potential on neuron 1 : " << n_one.getV() << " at time : " << n_one.getTime_() << endl;
			exit << "Membrane potential on neuron 2 : " << n_two.getV() << " at time : " << n_two.getTime_() << endl;
	
			
		}
	}
	
	exit << "Number of spikes of neuron 1 : " << n_one.getNb_spikes() << endl;
	exit << "Number of spikes of neuron 2 : " << n_two.getNb_spikes() << endl;
	
	exit.close();
	return 0;
}
