#include "../include/TDObject.h"
namespace TowerDefence {
	long TDObject::count = 0;
	TDObject::TDObject(const std::string& filename) {
		count++;
		id = count;
		object = Sprite::create(filename);
	}
	Sprite* TDObject::getSprite() {
		return object;
	}
	long TDObject::getObjectID()const {
		return id;
	}
	void TDObject::setSprite(Sprite* o) {
		object->cleanup();
		delete object;
		object = o;
	}
	TDObject::TDObject(const TDObject& o) {
		count++;
		id = count;
		object = Sprite::create();
		object->initWithTexture(o.object->getTexture());
	}
	TDObject::TDObject(TDObject&& o): object(o.object) {
		count++;
		id = count;
		o.object = nullptr;
	}
	TDObject& TDObject::operator=(const TDObject& o) {
		if (this == &o) {
			return *this;
		}
		object->cleanup();
		delete object;
		object = Sprite::create();
		object->initWithTexture(o.object->getTexture());
		return *this;
	}
	TDObject& TDObject::operator=(TDObject&& o) {
		object = o.object;
		o.object = nullptr;
		return *this;
	}
	void TDObject::kill() {
		if (object) {
			object->cleanup();
			object = nullptr;
		}
	}
	TDObject::~TDObject() {
		kill();
	}
}