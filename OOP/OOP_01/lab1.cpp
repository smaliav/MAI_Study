#include "stdafx.h"
#include <cstdlib>
#include "Pentagon.h"
#include "Hexagon.h"
#include "Octagon.h"
#include <string>

int main(int argc, char** argv)
{
	std::string option;
	bool flag = false;
	Figure *ptr = NULL;

	while (true)
	{
		while (!flag)
		{
			std::cout << "Choose Figure(Pentagon/Hexagon/Octagon or Exit): ";
			std::cin >> option;

			if (option == "Pentagon")
			{
				std::cout << "Enter side: ";
				ptr = new Pentagon(std::cin);
				std::cout << "\nPentagon created\n" << std::endl;
				flag = true;
			}
			else if (option == "Hexagon")
			{
				std::cout << "Enter side: ";
				ptr = new Hexagon(std::cin);
				std::cout << "\nHexagon created\n" << std::endl;
				flag = true;
			}
			else if (option == "Octagon")
			{
				std::cout << "Enter side: ";
				ptr = new Octagon(std::cin);
				std::cout << "\nOctagon created\n" << std::endl;
				flag = true;
			}
			else if (option == "Exit")
			{
				return 0;
			}
			else
			{
				std::cout << "ERROR" << std::endl;
			}
		}
		ptr->Print();
		std::cout << "Square = " << ptr->Square() << std::endl;

		std::cout << "\n";
		delete ptr;
		std::cout << "\n";

		flag = false;
	}

	return 0;
}