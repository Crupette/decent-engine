#include "DecentEngine.h"

namespace DecentEngine {

    Logger baseLogger("DecentEngine");

    void engine_init() {
		baseLogger.log(Logger::Type::INFO, "Using decent-engine version", VERSION);
	}

}
