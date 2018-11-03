#include "FileManager.h"

#include <fstream>

namespace DecentEngine {

void FileManager::dumpFile(const std::string& filePath, std::vector<unsigned char>& contents){
	std::ifstream file(filePath, std::ios::binary);

	if(file.fail()){
		//TODO: Add logger message with [WARN] tag
	printf("Failed to dump file contents into vector.\nError is as follows:\n404 FILE NOT FOUND");
	return;
	}

	file.seekg(0, std::ios::end);
	size_t len = file.tellg();
	file.seekg(0, std::ios::beg);

	contents.resize(len);
	file.read((char*)(&contents[0]), len);

	file.close();
}

}
