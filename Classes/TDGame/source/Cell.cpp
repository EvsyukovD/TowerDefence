#include "../include/Cell.h"
namespace TowerDefence {
	Cell::Cell(const Point& topLeft,CellType type, Building* objectPtr, float height, float width):
		topLeft(topLeft),
		type(type),
		objectPtr(objectPtr), 
		height(height), 
		width(width) {}
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
	size_t Cell::getHeight()const { 
		return height; 
	}
	size_t Cell::getWidth()const { 
		return width; 
	}
	Point Cell::getTopLeft()const { 
		return topLeft; 
	}
}