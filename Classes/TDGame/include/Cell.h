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
		CellType type = CellType::NONE;
		std::shared_ptr<Building> objectPtr = nullptr;
		float height;
		float length;
	public:
		Cell(CellType type, Building* objectPtr, float height, float length);
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
	
	};
}
#endif
