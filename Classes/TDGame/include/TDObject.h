#ifndef __TDOBJECT_H__
#define __TDOBJECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	
	class TDObject {
	private:
		static int count;
		int id = 0;
	protected:
		Sprite* object;
		/**
		 * \brief Remove object from scenery graph
		 */
		virtual void kill();
	public:
		/**
		 * \return object's id
		 */
		int getObjectID()const;
		TDObject();
		/**  
		\brief create object with texture file
		\param filename - file with texture
		*/
		TDObject(const std::string& filename);
		TDObject(const TDObject&);
		TDObject(TDObject&&);
		/**
		\returns Sprite's pointer
		*/
		Sprite* getSprite();
		/**
		\brief Set sprite
		\param  Sprite's ptr
		*/
		void setSprite(Sprite*);
		TDObject& operator =(const TDObject&);
		TDObject& operator =(TDObject&&);
		virtual ~TDObject();
	};
};
#endif // !__TDOBJECT_H__