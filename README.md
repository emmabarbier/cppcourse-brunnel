# cppcourse-brunnel

I- INTRODUCTION
In this README, you will find a brief description of the NeuronProject, and everything you need to know to make it run on your computer, using the files presented in this GitHub repository.

II- PRESENTATION
With this program, we are trying to simulate Nicolas Brunnel's model of "the dynamics of sparsely connected excitatory and inhibitory integrate-and-fire neurons". First we simulated the interaction between only two neurons. Then we moved forward to the simulation of a network of 12 500 neurons. The neurons are connected to one another and thus their behaviour has an inpact on the rest of the network.

III- HOW TO RUN THE PROGRAM ON YOUR COMPUTER


 A) TWO NEURONS :
      Here we will see how to simulate two neurons interacting. Neuron 1 will receive an input current chosen by the user while
      neuron 2 will receive no input current, but only the stimulation of neuron 1 when it spikes. You should also be aware that
      neuron 2 will receive the input from neuron 1 with a delay set at 1.5ms.
      
      How to proceed :
      In your terminal, go where you uploaded the files "neuron.hpp, neuron.cpp, main_two_neurons.cpp, CmakeLists.txt".
      
      Write (press enter between each command) :
      cd build
      cmake ..
      make
      ./main_two_neurons
      
      Here you will be asked to enter :
      - the external current, enter a value of 1.01.
      - the start time (ms), enter a value of 0.
      - the end time (ms), enter a value of 100 for example.
      
      Now you can go in the file build.
      A MembranePotential.txt is created. You can open it and see that we have a spike of neuron 1 at 92.4ms, then neuron 2
      receives an input of value 0.1 at time 93.9, which is 1.5ms after the spike of neuron 1.
      Note that you can set the end time at 400. You will see spikes of neuron 1 at times 92.4ms, 186.8ms, 281.2ms and 375.6ms
      
      --> We have a good connection between two neurons. Now we can simulate many neurons to get closer to a brain-like
      simulation.
     
     
 B) A NETWORK OF NEURONS :
      Here we will see how to simulate 12 500 NEURONS interacting.
      Now the neurons have no input current (even if the user can still set one). But they are subject to a "background noise"
      which randomly sends them an input. This input is the same value as if they received a spike from an other neuron.
      You should also know that the network will be made of 10 000 excitatory neurons and 2 500 inhibitory neurons. Each neuron
      willreceive 1 000 excitatory connexions and 250 inhibitory connexions.
      Be aware that we still have a delay when neurons send signals to eachother.
      Also, here we will create the figure C of the Brunnel's simulation because in this program, g=5 and Vext/Vthr=2.
      If you want to see the figure A, B and D, you just have to run the following python code on Jupyter with spikesA.gdf,
      spikesB.gdf, spikesD.gdf instead of spikes.gdf.
      
      How to proceed :
      In your terminal, go where you uploaded the files "neuron.hpp, neuron.cpp, CMakeLists.txt, network.hpp, network.cpp,
      main_network.cpp".
      
      Write (press enter between each command) :
      cd build
      cmake ..
      make
      ./main_network
      
      Here you will be asked to enter :
      - the external current, enter a value of 0.
      - the start time (ms), enter a value of 0.
      - the end time (ms), enter a value of 100 for example .
      
      The running will take 4 minutes.
      Note that if you set a larger end time, the simulation will take longer, and your spikes.gdp will be heavier.
      After that the message "End of simulation" will appear on your terminal.
      Now you can go in the file build.
      A spikes.gdf is created. You can open it and see in the first column the times when the neurons spiked, and in the second
      column,the ID of the corresponding neuron.
      
      Now you want to have a representation of the spikes of your neurons. So we will make a plot by doing the following :
      Go on internet.
      Go on the welcome page of Jupyter.
      Click on "Try it in your browser".
      Upload the file : spikes.gdf
      Click on new > Python 3
      Copy paste the following code : 
      
         import numpy as np
         import matplotlib.pyplot as pl

         data = np.genfromtxt('spikes.gdf')

         select= np.array([d for d in data if d[1] < 80])
         data1= select.transpose()
         pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
         pl.show();

         n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
         pl.show();
         
      Click on Run.
      You will see a rasta plot and a histogram appear.
      On the X axis is the time in ms. On the Y axis is the ID of the neuron which spiked at that time.
      On the histogram, you can observe that it forms peaks. This is explained by the fact that when the number of
      spiking neuron is lowering, the ihibition is strong, it wins over the excitation of the neurons. Right after, the
      excitations wins over the inhibition, thus the number of spiking neurons increase.
      
      
 C) GOOLE TESTS :
      Here we will see how to run the google tests.
      
      How to proceed :
      In your terminal, go where you uploaded the files "neuron.hpp, neuron.cpp, CMakeLists.txt, network.hpp, network.cpp,
      main_network.cpp, NeuronProject_unittest.cpp".
      
      Write (press enter between each command) :
      cd build
      cmake ..
      make
      ./NeuronProject_unittest
      
      Now you should see that all the tests passed.
      If you want to have further information about what the google tests do, you can open the NeuronProject_unittest.cpp. A
      description of the role of each of them is included.
      
 D) DOXYGEN :
      Here we will see how to generate a Doxygen document.
      
      How to proceed :
      In your terminal, go where you uploaded the files "neuron.hpp, neuron.cpp, main_two_neurons.cpp, CmakeLists.txt".
      
      Write (press enter between each command) :
      doxygen Doxyfile.in
      cd build
      make
      make doc

      Now you can go in the file html that was just created.
      Click on the annoted.html document. It will open a web page on which you can find our two classes (neuron and network). If
      you click on the network or neuron class, you will have furhter information on how it was implemented.
