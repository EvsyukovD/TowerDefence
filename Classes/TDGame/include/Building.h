#ifndef __BUILDING_H__
#define __BUILDING_H__
#include "TDObject.h"
namespace TowerDefence {
    class Building : public TDObject {
    protected:
        //Название строения
        std::string name;
    public:
        Building(const std::string& name, const std::string& filename);
        std::string getName() const;
        void setName(const std::string&);
        virtual ~Building() {
        
        }
    };
    
}
#endif // !__BUILDING_H__
