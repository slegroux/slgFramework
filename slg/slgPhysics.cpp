#include "slgPhysics.h"
#include "slgMath.h"

slgMover::slgMover(){
	_location = glm::vec2(0,0);
	_velocity = glm::vec2(0,0);
	_acceleration = glm::vec2(0,0);
	_color = glm::vec4(1,1,1,1);
	_mass = 1.0;
}

slgMover::slgMover(int width, int height){
	_location = glm::vec2(200,200);//glm::vec2(Random(0,width),Random(0,height));
	_velocity = glm::vec2(0,0);//glm::vec2(Random(-1.0,1.0),Random(-1.0,1.0));
	//don't forget the f at the end of the float
	_acceleration = glm::vec2(0,0);//0.0001f*glm::vec2(Random(-0.01,0.01),Random(-0.01,0.01));
	//_acceleration = 0.01f*_acceleration;
	_color = glm::vec4(Random(0,1.0),Random(0,1.0),Random(0,1.0),Random(0.0,1));
	_size = Random(0,50);
	_mass = _size;
	//std::cout<<glm::to_string(_color)<<std::endl;
}

slgMover::~slgMover(){

}

void slgMover::checkEdges(int width, int height){
	if (_location.x>width){
		_location.x=0;
		//std::cout<<"x>width"<<std::endl;
	}
	else if (_location.x<0){
		_location.x = width;
	}

	if (_location.y>height){
		_location.y=0;
	}
	else if (_location.y<0){
		_location.y=height;
	}
}

void slgMover::bounce(int width, int height){
	if ((_location.x>width)||(_location.x<0)){
		_velocity.x = -_velocity.x;
	}

	if ((_location.y>height)||(_location.y<0)){
		_velocity.y = -_velocity.y;
	}
}

void slgMover::checkTop(int width, int height){
	if(_location.y>height-20){
		_location.y = height-20;
	}
}

void slgMover::applyForce(){

}

void slgMover::increaseAcceleration(){
	/*_acceleration.x += Random(-0.01,0.01);
	_acceleration.y += Random(-0.01,0.01);*/
}

void slgMover::resetAcceleration(){
	_acceleration = glm::vec2(0.0);
}

void slgMover::decreaseAcceleration(){
	/*_acceleration.x -= Random(-0.01,0.01);
	_acceleration.y -= Random(-0.01,0.01);*/
}

void slgMover::applyForce(glm::vec2 force){
	force = force/_mass;
	_acceleration += force;
}

void slgMover::update(glm::vec2 g_mouse){
	// Random accelaration at each update
	/*_acceleration.x = Random(-0.1,0.1);
	_acceleration.y = Random(-0.1,0.1);*/

	// acceleration proportional to the distance from mouse
	/*glm::vec2 direction = g_mouse - _location;
	direction = glm::normalize(direction);
	//std::cout<<"Normalized direction: "<<glm::to_string(direction)<<std::endl;
	_acceleration = 0.1f*direction;*/

	_velocity += _acceleration;
	_velocity.x = Clamp(_velocity.x,-10,10);
	_velocity.y = Clamp(_velocity.y,-10,10);
	_location += _velocity;
	// reinitialize acceleration as setup by external forces
	_acceleration = glm::vec2(0.0f);
}

void slgMover::draw(){
	glColor4f(_color.x,_color.y,_color.z,_color.w);
	Circle(_location.x,_location.y,_size);
}

void slgMover::printState(){
	std::cout<<"Location: "<<glm::to_string(_location)<<std::endl;
	std::cout<<"Velocity: "<<glm::to_string(_velocity)<<std::endl;
	std::cout<<"Acceleration: "<<glm::to_string(_acceleration)<<std::endl;
}