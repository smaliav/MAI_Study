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
	TBinTree binTree;
	int size;
	int menuOpt = 4;
	int menuFigure;
	std::shared_ptr<Figure> figure;

	while (menuOpt != 0) {
		if (menuOpt >= 0 && menuOpt <= 4) {
			switch (menuOpt) {
			case 0:
				break;
			case 1:
				std::cout << "Enter your Figure(1 - Pentagon, 2 - Hexagon, 3 - Octagon): ";
				std::cin >> menuFigure;
				if (menuFigure == 1) {
					figure = std::make_shared<Pentagon>(std::cin);
					binTree.Insert(figure);
					std::cout << "Pentagon Added" << std::endl;
				}
				else if (menuFigure == 2) {
					figure = std::make_shared<Hexagon>(std::cin);
					binTree.Insert(figure);
					std::cout << "Hexagon Added" << std::endl;
				}
				else if (menuFigure == 3) {
					figure = std::make_shared<Octagon>(std::cin);
					binTree.Insert(figure);
					std::cout << "Octagon Added" << std::endl;
				}
				else {
					std::cout << "Input ERROR" << std::endl;
				}
				break;
			case 2:
				std::cout << "Enter Figure to delete: ";
				std::cin >> size;
				binTree.DeleteItem(size);
				break;
			case 3:
				binTree.Print();
				break;
			case 4:
				std::cout << "****************MENU****************" << std::endl;
				std::cout << "1. Add a new Figure to the BinTree" << std::endl;
				std::cout << "2. Delete a Figure from the BinTree" << std::endl;
				std::cout << "3. Print the BinTree" << std::endl;
				std::cout << "4. Print the MENU" << std::endl;
				std::cout << "0. Exit the Program" << std::endl;
				std::cout << "************************************" << std::endl;
				break;
			}
		}
		else {
			std::cout << "Input ERROR" << std::endl;
		}
		std::cout << "Enter the Number of an Action: ";
		std::cin >> menuOpt;
	}

	system("pause");
	return 0;
}