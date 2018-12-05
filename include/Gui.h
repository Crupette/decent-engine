/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-4
 *	Compiler:		gcc --std=c++17
 * */

#ifndef GUI_H
#define GUI_H

namespace DecentEngine {

class Gui {
public:
	enum class Type { CONST, NOINTERRUPT, INTERRUPT };

	Gui(Type type) : type(type) {}
	virtual ~Gui() {}

	virtual void update() = 0;
	virtual void render() = 0;

	Type type;
};

}

#endif
