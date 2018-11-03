#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

namespace DecentEngine {

class FileManager {
public:
	/**
	 * @brief Reads the file contents of specified file and dumps the contents into a vector of unsigned chars
	 *
	 * @param filePath path to file
	 * @param contents vector to write to
	 */
	static void dumpFile(const std::string& filePath, std::vector<unsigned char>& contents);
};

}
#endif
