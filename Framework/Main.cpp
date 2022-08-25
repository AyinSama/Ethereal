// 主函数仅用于测试
#include "Pch.h"
#include "EventManager.hpp"

class MotionEvent : public Event<MotionEvent> {
public:
	MotionEvent(float motionX, float motionY) : motionX(motionX), motionY(motionY) {}
	float getMotionX() const { return this->motionX; }
	float getMotionY() const { return this->motionY; }
private:
	float motionX;
	float motionY;
};

void handleMotionFunc1(const MotionEvent& event) {
	std::cout << "Handler 1" << std::endl;
	std::cout << "MotionX: " << event.getMotionX() << std::endl;
	std::cout << "MotionY: " << event.getMotionY() << std::endl;
}

class MotionEventHandler {
public:
	MotionEventHandler() {
		BindClassHandler(MotionEvent, this, MotionEventHandler::onMotion);
	}

	void onMotion(const MotionEvent& event) {
		std::cout << "on motion func." << std::endl;
	}
};

int main() {
	
	EventManager& emgr = Singleton<EventManager>().getInstance();
	BindHandler(MotionEvent, handleMotionFunc1)

	MotionEventHandler meh;

	MotionEvent me{ 10.125f, 10.456f };
	emgr.call<MotionEvent>(me);

	return 0;
}
