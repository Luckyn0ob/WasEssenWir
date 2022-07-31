#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <fstream>
#include <ios>
#include <chrono>
#include <filesystem>

void menu();
std::vector<std::string> recipe;


void loadData() 
{
	std::fstream readDataToVector("C:/Users/XxAnu/OneDrive/Desktop/save.txt", std::ios::in);
	std::string copyData;
	while (std::getline(readDataToVector, copyData)) {
		if (copyData.size() > 0) 
		{
			recipe.push_back(copyData);
		}
	}

}


void deleteRecipe() 
{
	int inputDelete = 0;
	std::string copyData;
	system("CLS");
	
	for (int i = 0; i <= recipe.size() - 1; i++) 
	{
	 std::cout << i << ". " << recipe[i] << std::endl;
	}
	std::cout << "\n Welches Gericht moechten Sie loeschen ? :";
	
	std::cin >> inputDelete;
	if (inputDelete > recipe.size() - 1) 
	{
		std::cout << "Error, Eingabe war so hoch" << std::endl;
	}
	else if (inputDelete < 0) 
	{
		std::cout << "Error, Eingabe war zu niedrig" << std::endl;
	}
	else if (inputDelete >=  0 && inputDelete <= recipe.size() - 1) 
	{
		recipe.erase(recipe.begin()+inputDelete);
		std::remove("C:/Users/XxAnu/OneDrive/Desktop/save.txt");
		std::fstream saveInput("C:/Users/XxAnu/OneDrive/Desktop/save.txt", std::ios::in | std::ios::out | std::ios::app);
		for (int i = 0; i <= recipe.size() - 1; i++) 
		{
			saveInput << recipe[i] << std::endl;
		}
				
	}

	menu();
}


void addRecipe() 
{
	bool menueLoop = true;

	while (menueLoop == true) 
	{
		std::string inputRecipe;
		std::cout << "Bitte geben Sie hier ein Rezept ein: ";
		std::getline(std::cin, inputRecipe);
		if (inputRecipe == "") 
		{
			std::cout << "Error, Eingabe war leer." << std::endl;
		}
		else 
		{
			recipe.push_back(inputRecipe);
			std::fstream saveInput("C:/Users/XxAnu/OneDrive/Desktop/save.txt", std::ios::in | std::ios::out | std::ios::app);
			saveInput << inputRecipe << std::endl;
		}
	}
}


void randomRecipe() 
{

	if (recipe.empty()) 
	{
		system("CLS");
		std::cout << "FEHLER !!! : Bitte tragen Sie erst ein Rezept\n" << std::endl;
		menu();
	}

	else 
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed);
		std::uniform_int_distribution<> distr(0, recipe.size() - 1);
		
		for (int i = 1; i <= 5; i++) 
		{
			std::cout << i << ". " << recipe[distr(generator)] << std::endl;
		}
		std::cout << std::endl;
		
		menu();

	}
	
}


void menu() 
{
	std::string input;
	bool menueLoop = true;

	std::cout << "Willkommen im Zufallsgenerator fuer das Mittagessen: \n" << std::endl;
	std::cout << "1. Zufälliges Essen generiern" << std::endl;
	std::cout << "2. Essen hinzufügen" << std::endl;
	std::cout << "3. Essen löschen" << std::endl;
	std::cout << "4. Exit\n" << std::endl;

	while (menueLoop == true) 
	{
		std::cout << "Input: ";

		std::getline(std::cin, input);
		std::cout << std::endl;

		if (input == "1") 
		{
			randomRecipe();
			menueLoop = false;
		}

		else if (input == "2") 
		{
			addRecipe();
			menueLoop = false;
		}

		else if (input == "3") 
		{
			deleteRecipe();
			menueLoop = false;
		}

		else if (input == "4") 
		{
			std::cout << "Vielen Dank und noch einen schoenen Abend." << std::endl;
			menueLoop = false;
		}

		else 
		{
			std::cout << "FEHLER !!!! : Falsche Eingabe.\n" << std::endl;
		}

	}

}


int main() {
	loadData();
	menu();

	return 0;
}