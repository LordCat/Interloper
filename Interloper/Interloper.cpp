// Interloper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Test for commit to git hub 2
#include <iostream>

int main()
{

    bool exit = true;
    std::cout << "Hello World!\n";


    std::cout << "What would you like to do?\n"; 
    std::cout << "1: Packet Capture\n";
    std::cout << "2: Exit\n";

    while (exit == true) {

        int input;
        std::cin >> input;


        switch (input) {
        case 1:
            std::cout << "Packet Capture Selected\n";
            break;
        case 2:
		    std::cout << "Exiting Program\n";
            return 0;
        default:
            std::cout << "Invalid Input\n";
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
