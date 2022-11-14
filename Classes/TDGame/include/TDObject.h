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
		static long count;
		long id = 0;
	protected:
		Sprite* object = nullptr;
		/*
		�������, ������������ ��������
		**/
		virtual void kill();
	public:
		/*
		@returns ID �������
		**/
		long getObjectID()const;
		/*
		�������� ���������� ������ TDObject �� ������\n
		����� � ���������
		@param filename - ���� � ���������
		**/
		TDObject(const std::string& filename);
		TDObject(const TDObject&);
		TDObject(TDObject&&);
		/**
		�������� ������
		@returns ��������� �� Sprite
		*/
		Sprite* getSprite();
		/**
		���������� ������
		@param ��������� �� Sprite
		*/
		void setSprite(Sprite*);
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