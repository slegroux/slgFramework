#ifndef __SLGPHYSICS_H__
#define __SLGPHYSICS_H__

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "slgGraphics.h"

class slgMover{
public:
	slgMover();
	slgMover(int width,int height);
	~slgMover();
public:
	void applyForce();
	void checkEdges(int width, int height);
	void checkTop(int width, int height);
	void bounce(int width, int height);
	void update(glm::vec2 g_mouse);
	void draw();
	void applyForce(glm::vec2 force);
	void printState();
	void increaseAcceleration();
	void decreaseAcceleration();
	void resetAcceleration();
private:
	glm::vec2 _location, _velocity, _acceleration;
	glm::vec4 _color;
	float _size;
	float _mass;

};

/*class Spring{
public:
private:
	glm::vec2 anchor;
};*/

#endif