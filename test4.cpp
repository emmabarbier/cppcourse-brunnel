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
	
	cout << "Enter start time :  ";
	cin >> time_start;
	
	cout << "Enter end time : ";
	cin >> time_end;
	
	//creer un network avec ces trois valeurs
	Network network(time_start, time_end, I);
	
	//appeler update de network (lui même appelle update de neuron) avec en argument la general clock
	
	return 0;
}
