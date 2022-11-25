#include "../include/TDObject.h"
namespace TowerDefence {
	int TDObject::count = 0;
	TDObject::TDObject(const std::string& filename):object(Sprite::create(filename)) {
		count++;
		id = count;
	}
	TDObject::TDObject():object(Sprite::create()) {
		
	}
	std::shared_ptr<Sprite> TDObject::getSprite() {
		return object;
	}
	int TDObject::getObjectID()const {
		return id;
	}
	void TDObject::setSprite(std::shared_ptr<Sprite> o) {
		object->cleanup();
		object = o;
	}
	TDObject::TDObject(const TDObject& o) {
		count++;
		id = count;
		object = std::shared_ptr<Sprite>(Sprite::create());
		object->initWithTexture(o.object->getTexture());
	}
	TDObject::TDObject(TDObject&& o): object(o.object.get())  {
		count++;
		id = count;
		o.object = nullptr;
	}
	TDObject& TDObject::operator=(const TDObject& o) {
		if (this == &o) {
			return *this;
		}
		object->cleanup();
		object = std::shared_ptr<Sprite>(Sprite::create());
		object->initWithTexture(o.object->getTexture());
		return *this;
	}
	TDObject& TDObject::operator=(TDObject&& o) {
		object = o.object;
		o.object = nullptr;
		return *this;
	}
	void TDObject::kill() {
		if (object.get()) {
			object->cleanup();
			object = nullptr;
		}
	}
	TDObject::~TDObject() {
		kill();
	}
}