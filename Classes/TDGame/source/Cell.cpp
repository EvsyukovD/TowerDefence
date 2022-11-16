#include "../include/Cell.h"
namespace TowerDefence {
	Cell::Cell(CellType type, Building* objectPtr, float height, float length):
		type(type),
		objectPtr(objectPtr), 
		height(height), 
		length(length) {}
	Building* Cell::getObject() {
		return objectPtr.get();
	}
	CellType Cell::getType() const {
		return type;
	}
	void Cell::setType(CellType type, std::shared_ptr<Building> objectPtr) {
		this->type = type;
		this->objectPtr = objectPtr;
	}
}