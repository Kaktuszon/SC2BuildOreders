#include <iostream>
#include <string>
#include <Windows.h>
#include <filesystem>
#include <fstream>

void readDirectory();
void runBuildOrder(std::string s);

int main(int argc, char *argv[]) {
	std::string buildorder;

	readDirectory();
	std::cout << "Select build order: ";
	std::cin >> buildorder;

	buildorder = "buildorders/" + buildorder;

	system("cls");
	runBuildOrder(buildorder);

	return 0;
}

//Read all buildorders in the directory
void readDirectory() {
	std::string path = "buildorders/";
	for(const auto &entry : std::filesystem::directory_iterator(path)) {
		std::cout << entry.path().filename() << std::endl;
	}
	std::cout << std::endl;
}

//This is such a fulhack because I am tired, sorry not tired me!
void runBuildOrder(std::string s) {
	std::ifstream file;
	std::string line;
	file.open(s);

	std::vector<std::string> build;

	//Read rows from file and place in array
	if(file.is_open()) {
		while(std::getline(file, line)) {
			build.push_back(line);
		}
	} else {
		std::cout << "Could not open file." << std::endl;
	}

	int i = 1; //Keep track of line
	std::cout << build.at(0) << std::endl; //Print first line
	while(true) {
		if(GetAsyncKeyState(VK_PAUSE)) { //Print new line after pause button is pressed
			std::cout << build.at(i) << std::endl;
			i = i + 1;
			Sleep(200);
		}

		if(i >= build.size()) {
			break;
		}
	}

	file.close();
}