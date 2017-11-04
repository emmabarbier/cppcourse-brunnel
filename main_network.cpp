#include "network.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <memory>

int main () {
	double I;
	int time_start;
	int time_end;
	
	cout << "Enter external current : ";
	cin >> I;
	
	cout << "Enter start time (ms):  ";
	cin >> time_start;
	
	cout << "Enter end time (ms) : ";
	cin >> time_end;
	
	Network network(time_start, time_end, I); //We create the network
	
	network.connect(); //We connect the neurons
	network.update();  //We update the network
	
	cout << "End of simulation" << endl;
	return 0;
}
