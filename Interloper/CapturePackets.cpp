#include "CapturePackets.h"
#include <iostream>
#include <pcap.h>
#include <Windows.h>

capturePacket::capturePacket(const std::string& sInterface) : selectedInterface(sInterface) {}

capturePacket::CaptureCoroutine capturePacket::startCapture() {
    co_return;
}

// Actual function for capturing packets
void capturePacket::startCaptureAsync(std::coroutine_handle<> coroutine) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcapHandle;

    // Open the network interface for capturing
    pcapHandle = pcap_open_live(selectedInterface.c_str(), BUFSIZ, 1, 1000, errbuf);

    if (pcapHandle == nullptr) {
        std::cerr << "Error Opening Interface: " << errbuf << std::endl;
        coroutine.destroy(); // Destroy the coroutine on error
        return;
    }

    std::cout << "Packet Capture started on interface: " << selectedInterface << std::endl;

    // Option for capture rate
    std::cout << "Choose capture rate:\n";
    std::cout << "1: 1 packet/sec\n";
    std::cout << "2: 3 packet/sec\n";
    std::cout << "3: 5 packet/sec\n";

    char choice;
    std::cin >> choice;

    int packetRate;
    switch (choice) {
    case '1':
        packetRate = 1;
        break;
    case '2':
        packetRate = 3;
        break;
    case '3':
        packetRate = 5;
        break;
    default:
        std::cerr << "Invalid choice. Exiting. \n";
        pcap_close(pcapHandle);
        coroutine.destroy();
        return;
    }

    // Capture loop
    while (true) {
        struct pcap_pkthdr header;
        const u_char* packet;

        // Capture packet
        packet = pcap_next(pcapHandle, &header);

        if (packet != nullptr) {
            // Output packet information
            std::cout << "Packet captured on " << selectedInterface << ".\n Time: " << header.ts.tv_sec << "." << header.ts.tv_usec << "\n Length: " << header.len << std::endl;

            // Sleep for the specified capture wait
            Sleep(1000 / packetRate);
        }

        // Check 'S' press to stop capture
        if (std::cin.peek() == 'S' || std::cin.peek() == 's') {
            std::cout << "Stopping capture... \n";
            break;
        }
    }

    // Close the capture handle
    pcap_close(pcapHandle);

    std::cout << "Capture stopped. Returning to the main menu. \n";

    coroutine.destroy();
}
