#include "../include/TowerDefence.h"
namespace TowerDefence {
     template<class Base,class T>
     bool instanceof(T* ptr) {
         return dynamic_cast<Base*>(ptr) != nullptr;
     }
}