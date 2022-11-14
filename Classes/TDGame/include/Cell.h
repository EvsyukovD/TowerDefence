#ifndef __CELL_H__
#define __CELL_H__
#include "TowerDefence.h"
namespace TowerDefence{
	class Cell {
	public:
		enum CellType {
			PALACE,
			TOWER,
			LAIR,
			ROAD,
			NONE,
			TOWER_PLACE,
			TRAP
		};
	private:
		CellType type = CellType::NONE;
		Building* objectPtr = nullptr;
		float height;
		float length;
	public:
		Cell(CellType type, Building* objectPtr, float height, float length);
		/*
		@return ��� ��������
		**/
		CellType getType() const;
		/*
		���������� ��� ��������
		**/
		void setType(CellType, Building*);
		/*
		@return ��������� �� �������� 
		**/
		Building* getObject();
	
	};
}
#endif