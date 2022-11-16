#ifndef __TDOBJECT_H__
#define __TDOBJECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	/*
	Базовый класс для всех объектов на карте TowerDefence,\n
	включая карту уровня
	**/
	class TDObject {
	private:
		static int count;
		int id = 0;
	protected:
		std::shared_ptr<Sprite> object;
		/*
		Функция, уничтожающая текстуру
		**/
		virtual void kill();
	public:
		/*
		@returns ID объекта
		**/
		int getObjectID()const;
		/*
		Создание экзнмпляра класса TDObject на основе\n
		файла с текстурой
		@param filename - файл с текстурой
		**/
		TDObject(const std::string& filename);
		TDObject(const TDObject&);
		TDObject(TDObject&&);
		/**
		Получить спрайт
		@returns Указатель на Sprite
		*/
		std::shared_ptr<Sprite> getSprite();
		/**
		Установить спрайт
		@param Указатель на Sprite
		*/
		void setSprite(std::shared_ptr<Sprite>);
		/*
		Копирующее присваивание
		**/
		TDObject& operator =(const TDObject&);
		/*
		Перемещающее присваивание 
		**/
		TDObject& operator =(TDObject&&);
		virtual ~TDObject();
	};
};
#endif // !__TDOBJECT_H__