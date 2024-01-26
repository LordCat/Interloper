#include <iostream>
#include "InterfaceSelector.h"
#include "capturePackets.h"

int main()
{
    bool exit = true;
    std::string selectedInterface = "None"; // Default setting is none.
    std::cout << "Hello World!\n";

    while (exit) {

        std::cout << "Selected Interface: " << selectedInterface << "\n";

        std::cout << "What would you like to do?\n";
        std::cout << "1: Packet Capture\n";
        std::cout << "2: Select Interface\n";
        std::cout << "3: Exit\n";

        int input;
        std::cin >> input;

        switch (input) {
        case 1:
        {
            std::cout << "Packet Capture Selected\n";

            // Create an instance of capturePacket with the selectedInterface
            capturePacket packetCapture(selectedInterface);

            std::cout << "Instants started with " << selectedInterface << std::endl;

            // Start the packet capture coroutine
            auto captureCoroutine = packetCapture.startCapture();

            std::cout << "Packet capture started with " << selectedInterface << std::endl;
            break;
        }
        
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

    return 0;
}
