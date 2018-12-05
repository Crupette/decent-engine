#include "DecentEngine.h"
#include "TextureCache.h"

#include <string>

namespace DecentEngine {

Logger baseLogger("DecentEngine");

void engine_init() {
	baseLogger.log(Logger::Type::INFO, "Using decent-engine version", VERSION);
}

void engine_postgl_init(){
	std::basic_string<unsigned char> blank = {0xFF, 0xFF, 0xFF, 0xFF};
	TextureCache::loadTextureFromData(blank, "blank");
	baseLogger.log(Logger::Type::INFO, "Loaded blank texture as", "'blank'");
}

}
