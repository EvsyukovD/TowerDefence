#include "../include/Cell.h"
namespace TowerDefence {
	Cell::Cell(Cell::CellType type, Building* objectPtr, float height, float length):
		type(type),
		objectPtr(objectPtr), 
		height(height), 
		length(length) {}
	Building* Cell::getObject() {
		return objectPtr;
	}
	Cell::CellType Cell::getType() const {
		return type;
	}
	void Cell::setType(Cell::CellType type, Building* objectPtr) {
		this->type = type;
		this->objectPtr = objectPtr;
	}
}