#include "../include/TDObject.h"
namespace TowerDefence {
	TDObject::TDObject(const std::string& filename) {
		object = Sprite::create(filename);
	}
	Sprite* TDObject::getSprite() {
		return object;
	}
	void TDObject::setSprite(Sprite* o) {
		object->cleanup();
		delete object;
		object = o;
	}
	TDObject::TDObject(const TDObject& o) {
		object = Sprite::create();
		object->initWithTexture(o.object->getTexture());
	}
	TDObject::TDObject(TDObject&& o): object(o.object) {
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