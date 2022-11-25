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
		@return ��� ��������
		**/
		CellType getType() const;
		/*
		���������� ��� ��������
		**/
		void setType(CellType, std::shared_ptr<Building>);
		/*
		@return ��������� �� �������� 
		**/
		Building* getObject();
		/*
		@return ������ ������
		**/
		size_t getHeight()const;
		/*
		@return ������ ������
		**/
		size_t getWidth()const;
		/*
		@return ������� ����� ���� ������
		**/
		Point getTopLeft()const;
	};
}
#endif
