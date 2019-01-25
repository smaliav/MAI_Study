#include "stdafx.h"
#include <cstdlib>
#include "Pentagon.h"
#include "Hexagon.h"
#include "Octagon.h"
#include "TBinTree.h"
#include "TBinTreeItem.h"
#include <string>

int main(int argc, char** argv)
{
	std::string option;
	bool correctInput = false;
	Figure *ptr = NULL;
	TBinTree binTree; //GLOBAL BINTREE

	while (true)
	{
		while (!correctInput)
		{
			std::cout << "Choose Figure(Pentagon/Hexagon/Octagon or Exit): ";
			std::cin >> option;
			
			if (option == "Pentagon") {
				std::string addAnother;
				do {
					Pentagon pentagon(std::cin);
					binTree.Insert(pentagon);

					std::cout << "Add another Pentagon?('Yes' for Adding): ";
					std::cin >> addAnother;
				} while (addAnother == "Yes");
				binTree.Print();

				size_t sizeOfDeletingPentagon;
				do {
					std::cout << "Enter the Side of Deleting Pentagon(Enter 0 to Exit): ";
					std::cin >> sizeOfDeletingPentagon;
					if (sizeOfDeletingPentagon == 0) {
						break;
					}
					binTree.DeleteItem(sizeOfDeletingPentagon);
					binTree.Print();
				} while (!binTree.Empty());
				correctInput = true;
			}
			else if (option == "Hexagon") {
				ptr = new Hexagon(std::cin);
				correctInput = true;
			}
			else if (option == "Octagon") {
				ptr = new Octagon(std::cin);
				correctInput = true;
			}
			else if (option == "Exit") {
				return 0;
			}
			else {
				std::cout << "\n***INPUT ERROR***\n" << std::endl;
			}
		}

		if (ptr != NULL) {
			std::cout << "\n" << option << " Info: " << std::endl;
			ptr->Print();
			std::cout << "Square = " << ptr->Square() << "\n" << std::endl;
		}

		delete ptr;
		ptr = NULL;
		correctInput = false;
	}

	return 0;
}