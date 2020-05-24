#pragma once
#include <iostream>
#include "listStreams.h"
#include "clearScreen.h"

void choice(const int &c, ListStreams &list) {
    clearScreen();

    switch (c) {
	case 0:
	{
	    if (list.isEmpty())
		std::cout << "List is empty\n";
	    else {
		ListStreams::Iterator it = list.getHead()->getNextBySurname();
		std::cout << "List sorted by surname\n";
		while (it->getNextBySurname()) {
		    std::cout << it->getSurname() << " ";
		    std::cout << it->getNumber() << "\n";
		    it = it->getNextBySurname();
		}
		std::cout << "\n\n";

		it = list.getHead()->getNextByNumber();
		std::cout << "List sorted by number\n";
		while (it->getNextByNumber()) {
		    std::cout << it->getNumber() << " ";
		    std::cout << it->getSurname() << "\n";
		    it = it->getNextByNumber();
		}
		std::cout << "\n\n";
	    }
	    break;
	}

	case 1:
	{
	    string name;
	    unsigned int number;
	    std::cout << "Enter surname and number: ";
	    std::cin >> name;
	    std::cin >> number;
	    list.push(name, number);
	    std::cout << "Node pushed\n";
	    break;
	}

	case 2:
	{
	    unsigned int number;
	    std::cout << "Enter number: ";
	    std::cin >> number;

	    short int result = list.pop(number);
	    switch (result) {
		case -1:
		    std::cout << "List is empty\n";
		    break;

		case 1:
		    std::cout << "Node not found\n";
		    break;

		default:
		    std::cout << "Node popped\n";
		    break;
	    }
	    break;
	}

	case 3:
	{
	    string name;
	    std::cout << "Enter surname: ";
	    std::cin >> name;

	    short int result = list.pop(name);
	    switch (result) {
		case -1:
		    std::cout << "List is empty\n";
		    break;

		case 1:
		    std::cout << "Node not found\n";
		    break;

		default:
		    std::cout << "Node popped\n";
		    break;
	    }
	    break;
	}

	case 4:
	{
	    string name;
	    std::cout << "Enter surname: ";
	    std::cin >> name;
	    unsigned int result = list.getNumber(name);
	    switch (result) {
		case UINT32_MAX - 1:
		    std::cout << "List is empty\n";
		    break;

		case UINT32_MAX:
		    std::cout << "Node not found\n";
		    break;

		default:
		    std::cout << name << "'s number is " << result << std::endl;
		    break;
	    }
	    break;
	}

	case 5:
	{
	    unsigned int number;
	    std::cout << "Enter number: ";
	    std::cin >> number;
	    string result = list.getSurname(number);
	    if (result == "*empty*")
		std::cout << "List is empty\n";
	    else if (result == "not found")
		std::cout << "Node not found\n";
	    else
		std::cout << "The owner of number " << number << " is " << result << std::endl;
	    break;
	}

	case 6:
	{
	    list.clear();
	    std::cout << "List cleared\n";
	    break;
	}

	case 7:
	{
	    if (list.isEmpty())
		std::cout << "List is empty\n";
	    else
		std::cout << "List is not empty\n";
	    break;
	}
    }
}

void menu(ListStreams &list) {
    short int c;
    while (true) {
	std::cout << "Options:\n\n";
	std::cout << "0. Print list\n";
	std::cout << "1. Push node\n";
	std::cout << "2. Find and pop node by number\n";
	std::cout << "3. Find and pop node by surname (first occurrence)\n";
	std::cout << "4. Find number by surname\n";
	std::cout << "5. Find surname by number\n";
	std::cout << "6. Clear list\n";
	std::cout << "7. Check if empty\n";

	std::cin >> c;

	choice(c, list);
    }
}
