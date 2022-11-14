#ifndef __PALACE_H__
#define __PALACE_H__
#include "Building.h"
namespace TowerDefence {
	class Palace : public Building {
	private:
		unsigned int gold;
		const unsigned int MAX_STRENGTH;
		unsigned int currentStrength;
	public:
		Palace();
		Palace(const std::string& name, const std::string& filename,unsigned int gold, unsigned int maxStrength);
		/*
		@return ������� ���������� ������
		**/
		unsigned int getGold()const;

		/*
		���� ����� ������
		@param g - ���������� �������� ������
		**/
		void addGold(unsigned int g);
		/*
		������� � ����� ������ ���������� ������
		@param ����� ���������� ������
		@throws std::invalid_argument - ���� � ����� �� ������� ������
		**/
		void takeGold(unsigned int);
		/*
		@return ������� ��������� �����
		**/
		unsigned int getStrength() const;
		/*
		������� ���� �����
		@param d - �������� �����
		**/
		void getDamage(unsigned int d);
		/*
		@return ���� ��������� �� �����
		**/
		bool isDestroyed() const;
	};
}
#endif // !__PALACE_H__

