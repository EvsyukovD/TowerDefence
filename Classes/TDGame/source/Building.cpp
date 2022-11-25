#include "../include/Building.h"
namespace TowerDefence {
	Building::Building(const std::string& name, const std::string& filename): TDObject(filename) {
		this->name = name;
	}
	Building::Building(){}
	std::string Building::getName() const {
		return name;
	}
	void Building::setName(const std::string& name) {
		this->name = name;
	}
}