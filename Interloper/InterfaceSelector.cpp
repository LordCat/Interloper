#include "InterfaceSelector.h"

#include <pcap/pcap.h>
#include <iostream>
#include <vector>

std::string InterfaceSelector::chooseInterface() {

	pcap_if_t* alldevs;
	char errbuf[PCAP_ERRBUF_SIZE];
	std::vector<std::string> availableInterface;

	//retrive the list of available network interfaces

	if (pcap_findalldevs(&alldevs, errbuf) == -1) {
		std::cerr << "Error finding devices: " << errbuf << std::endl;
		return "";
	}

	//store the interface names in a vector
	for (pcap_if_t* dev = alldevs; dev != NULL; dev = dev->next) {
		availableInterface.push_back(dev->name);
	}

	//Free the device list
	pcap_freealldevs(alldevs);

	//display interface options
	int index = 0;
	std::cout << "Available interfaces:\n";
	for (std::vector<std::string>::iterator it = availableInterface.begin(); it != availableInterface.end(); ++it) {
		
		std::cout << index++ << ": " << *it << std::endl;
	}

	//promtp the user to choose an interface
	int selectedInterfaceIndex;
	std::cout << "Enter the interface number to capture: ";
	std::cin >> selectedInterfaceIndex;

	//validate the selected index
	if (selectedInterfaceIndex < 0 || selectedInterfaceIndex > static_cast<int>(availableInterface.size())) {
		std::cerr << "Invalid interface number" << std::endl; 
		return "";
	}
	//return the selected interface
	return availableInterface[selectedInterfaceIndex];


}