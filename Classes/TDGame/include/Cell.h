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
		size_t height;
		size_t width;
	public:
		Cell(const Point& topLeft,CellType type, Building* objectPtr, size_t height, size_t length);
		/*
		@return тип строения
		**/
		CellType getType() const;
		/*
		Установить тип строения
		**/
		void setType(CellType, std::shared_ptr<Building>);
		/*
		@return указатель на строение 
		**/
		Building* getObject();
		/*
		@return Высота клетки
		**/
		size_t getHeight()const;
		/*
		@return Ширина клетки
		**/
		size_t getWidth()const;
		/*
		@return Верхний левый угол клетки
		**/
		Point getTopLeft()const;
	};
}
#endif
