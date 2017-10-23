#include "neuron.cpp"
#include <string>
#include <fstream>

int main () {

	double I;
	double time_start;
	double time_end;
	
	cout << "Enter external current : ";
	cin >> I;
	
	cout << "Enter start time :  ";
	cin >> time_start;
	
	cout << "Enter end time : ";
	cin >> time_end;

	Neuron n_one(time_start);
	
	// declare the file
	string file_name("MembranePotential.txt");
	
	// open the exit flow
	ofstream exit;
	exit.open("MembranePotential.txt", ios::out|ios::app);
	
	// verifies if the file exists
	if (exit.fail()) {
		cerr << "Error : impossible to open the file " << file_name << endl;
	} else {
		while (n.getTime_() < time_end) {
			n.update(I);
			exit << "Membrane potential : " << n.getV() << " at time : " << n.getTime_() << endl;
		}
	}
	
	exit << "Number of spikes : "<< n.getNb_spikes();
	
	exit.close();
	return 0;
}
