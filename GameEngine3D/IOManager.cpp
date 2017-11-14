#include "IOManager.h"

#include <fstream>

namespace GameEngine3D {

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		//Read file in binary
		std::ifstream file(filePath, std::ios::binary);

		//Error checking on file
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//Seek to the end of the file
		file.seekg(0, std::ios::end);

		//Get the file size
		int fileSize = (int)file.tellg();

		//Seek back to the begining
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes
		fileSize -= (int)file.tellg();

		//Resize buffer
		buffer.resize(fileSize);

		//Read in the file to the buffer
		file.read((char*)&(buffer[0]), fileSize);

		//Close the file
		file.close();

		return true;
	}

}