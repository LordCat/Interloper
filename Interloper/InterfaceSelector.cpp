#include "InterfaceSelector.h"
#include <pcap/pcap.h>
#include <iostream>
#include <vector>
#include <limits>

std::string InterfaceSelector::chooseInterface() {
    pcap_if_t* alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    std::vector<std::string> availableInterfaces;

    // Retrieve the list of available network interfaces
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << std::endl;
        return "";
    }

    // Store the interface names in a vector
    for (pcap_if_t* dev = alldevs; dev != NULL; dev = dev->next) {
        availableInterfaces.push_back(dev->name);
    }

    // Free the device list
    pcap_freealldevs(alldevs);

    // Display interface options
    if (availableInterfaces.empty()) {
        std::cerr << "No network interfaces found." << std::endl;
        return "";
    }

    std::cout << "Available interfaces:\n";
    for (size_t i = 0; i < availableInterfaces.size(); ++i) {
        std::cout << i + 1 << ": " << availableInterfaces[i] << std::endl;
    }

    // Prompt the user to choose an interface
    int selectedInterfaceIndex;
    std::cout << "Enter the interface number to capture (0 to cancel): ";
    std::cin >> selectedInterfaceIndex;

    // Validate the selected index
    if (selectedInterfaceIndex == 0) {
        std::cout << "Interface selection canceled." << std::endl;
        return "";
    }

    if (selectedInterfaceIndex < 1 || static_cast<size_t>(selectedInterfaceIndex) > availableInterfaces.size()) {
        std::cerr << "Invalid interface number" << std::endl;
        return "";
    }

    // Return the selected interface
    return availableInterfaces[selectedInterfaceIndex];
}
