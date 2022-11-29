#ifndef __CELL_H__
#define __CELL_H__
#include "TowerDefence.h"
namespace TowerDefence{
	enum CellType {
		PALACE,
		TOWER,
		LAIR,
		ROAD,
		NONE,
		TOWER_PLACE,
		TRAP
	};
	class Cell {
	private:
		Point topLeft;
		CellType type = CellType::NONE;
		std::shared_ptr<Building> objectPtr = nullptr;
		float height;
		float width;
	public:
		Cell(const Point& topLeft,CellType type, Building* objectPtr, float height, float length);
		/**
		@return Building type
		*/
		CellType getType() const;
		/**
		Set building type
		\param type - building type
		\param objectPtr - building pointer
		*/
		void setType(CellType type, std::shared_ptr<Building> objectPtr);
		/**
		\return Building pointer
		*/
		Building* getObject();
		/**
		\return Cell height
		*/
		size_t getHeight()const;
		/**
		\return Cell width
		*/
		size_t getWidth()const;
		/**
		\return Top level point of cell
		*/
		Point getTopLeft()const;
	};
}
#endif
