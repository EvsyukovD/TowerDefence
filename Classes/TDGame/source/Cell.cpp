#include "../include/Cell.h"
namespace TowerDefence {
	Cell::Cell(const Point& topLeft,CellType type, Building* objectPtr, float height, float width):
		topLeft(topLeft),
		type(type),
		objectPtr(objectPtr), 
		height(height), 
		width(width) {}
	Building* Cell::getObject() {
		return objectPtr;
	}
	CellType Cell::getType() const {
		return type;
	}
	void Cell::setType(CellType type, Building* objectPtr) {
		this->type = type;
		this->objectPtr = objectPtr;
	}
	float Cell::getHeight()const { 
		return height; 
	}
	float Cell::getWidth()const { 
		return width; 
	}
	Point Cell::getTopLeft()const { 
		return topLeft; 
	}
}