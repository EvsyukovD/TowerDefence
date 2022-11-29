#ifndef __BUILDING_H__
#define __BUILDING_H__
#include "TDObject.h"
namespace TowerDefence {
    class Building : public TDObject {
    protected:
        //Building name
        std::string name;
    public:
        Building();
        Building(const std::string& name, const std::string& filename);
        std::string getName() const;
        void setName(const std::string&);
        virtual ~Building() {
        
        }
    };
    
}
#endif // !__BUILDING_H__
