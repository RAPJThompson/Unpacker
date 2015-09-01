// Unpacker.cpp : Defines the entry point for the console application.
//


#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <iostream>

using std::cout;
#define GetCurrentDir _getcwd

using namespace std;
using namespace boost::filesystem;

char currentPath[FILENAME_MAX];

int moveUp(boost::filesystem::path topDir, boost::filesystem::path currentDir) {
	if (is_regular_file(currentDir))
		if (topDir.string().compare(currentDir.string()) == 0) {
			//if it is a file and it is in the top folder, then we don't need to do anything with it
		}
		else {
			std::string new_fileDest = topDir.string() + "/" + currentDir.filename().string();
			boost::filesystem::path destDirPath = boost::filesystem::path(new_fileDest);
			boost::filesystem::rename(currentDir, destDirPath); //rename(old, new)
			cout << currentDir << " moved to " << topDir.string() << ".\n";
			//is a file, and not in the top folder, move it up (reduction step)
		}
	else if (is_directory(currentDir))
	{
		cout << currentDir << " is a directory containing:\n";
		//is a folder, iterate through it and recurse on everything
		for (directory_entry& x : directory_iterator(currentDir)) {
			moveUp(topDir, x.path());
			//recurse
		}

		if (topDir.string().compare(currentDir.string()) != 0) {
			boost::filesystem::remove(currentDir);
			cout << currentDir << " deleted.\n";
		}
	}
	else
		cout << currentDir << " exists, but is not a regular file or directory\n";
	return 0;
}

int main(int argc, char* argv[])
{

	boost::filesystem::path currentBoostPath;
	
	if (argc < 2)
	{
		//This assumes that the program is to unpack all in the current dir
		currentBoostPath = boost::filesystem::current_path();
	}
	else {
		currentBoostPath = boost::filesystem::path(argv[1]);
		//currentBoostPath = "unknown";B
	}
	cout << "Active Directory is " << currentBoostPath << '\n';

	moveUp(currentBoostPath, currentBoostPath);
	
	cout << "Press Enter to exit." << '\n';
	string ctemp;
	ctemp = cin.get();
	return 0;
}
