#ifndef __TDOBJECT_H__
#define __TDOBJECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	/*
	������� ����� ��� ���� �������� �� ����� TowerDefence,\n
	������� ����� ������
	**/
	class TDObject {
	private:
		static int count;
		int id = 0;
	protected:
		std::shared_ptr<Sprite> object;
		/*
		�������, ������������ ��������
		**/
		virtual void kill();
	public:
		/*
		@returns ID �������
		**/
		int getObjectID()const;
		/*
		�������� ���������� ������ TDObject �� ������\n
		����� � ���������
		@param filename - ���� � ���������
		**/
		TDObject();
		TDObject(const std::string& filename);
		TDObject(const TDObject&);
		TDObject(TDObject&&);
		/**
		�������� ������
		@returns ��������� �� Sprite
		*/
		std::shared_ptr<Sprite> getSprite();
		/**
		���������� ������
		@param ��������� �� Sprite
		*/
		void setSprite(std::shared_ptr<Sprite>);
		/*
		���������� ������������
		**/
		TDObject& operator =(const TDObject&);
		/*
		������������ ������������ 
		**/
		TDObject& operator =(TDObject&&);
		virtual ~TDObject();
	};
};
#endif // !__TDOBJECT_H__