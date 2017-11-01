#include "network.hpp"
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
	
	//creer un network avec ces trois valeurs
	Network network(time_start, time_end, I);
	
	network.connect();
	 
	
	//appeler update de network (lui même appelle update de neuron) avec en argument la general clock
	while (General_clock < time_end/h) {
		network.update(General_clock);
		General_clock += 1;
		cout << "general clock = " << General_clock*0.1 << endl;
	}
	cout << "End of simulation" << endl;
	return 0;
}
