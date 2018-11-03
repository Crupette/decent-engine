#ifndef SCREEN_H
#define SCREEN_H

namespace DecentEngine {

class Screen {
public:
	Screen() {}
	virtual ~Screen() {}

	virtual void init() = 0;
	virtual void destroy() = 0;

	virtual void update() = 0;
	virtual void render() = 0;
};

}

#endif
