// Interloper.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ----------------------------------------------------------------
// It is intended to be a tool that allows for manual packet analysis and processing of packets
// The tool is called Interloper but it basically taps the loopback or selected interface and will run in the background providing data
// for the user to perform other actions.
// ----------------------------------------------------------------



#include <iostream>
#include "InterfaceSelector.h"



int main()
{

    bool exit = true;
    std::string selectedInterface = "None"; //default setting is none. 
    std::cout << "Hello World!\n";
	

    while (exit == true) {

        std::cout << "Selected Interface: " << selectedInterface << "\n";


        std::cout << "What would you like to do?\n";
        std::cout << "1: Packet Capture\n";
        std::cout << "2: Select Interface\n";
        std::cout << "3: Exit\n";

        int input;
        std::cin >> input;


        switch (input) {
        case 1:
            std::cout << "Packet Capture Selected\n";
            break;
        case 2:
			selectedInterface = InterfaceSelector::chooseInterface();
            break;
        case 3:
            std::cout << "Exiting Program\n";
            return 0;
        default:
            std::cout << "Invalid Input\n";
            break;
        }
    }
}
