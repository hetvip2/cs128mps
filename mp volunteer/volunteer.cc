#include "volunteer.hpp"

#include <string>
Volunteer ::Volunteer(const std::string& name,
                      int building_experience,
                      int physical_stamina,
                      bool returning):
    name_(name),
    buildingexp_(building_experience),
    phystamina_(physical_stamina),
    returning_(returning) {
  if (building_experience < kMinBuildingExp) {
    buildingexp_ = kMinBuildingExp;
  }
  if (physical_stamina < kMinStamina) {
    phystamina_ = kMinStamina;
  }
  if (building_experience > kMaxBuildingExp) {
    buildingexp_ = kMaxBuildingExp;
  }
  if (physical_stamina > kMaxStamina) {
    phystamina_ = kMaxStamina;
  }
}

std::string Volunteer ::GetName() const { return name_; }

int Volunteer ::GetBuildingExperience() const { return buildingexp_; }

int Volunteer ::GetPhysicalStamina() const { return phystamina_; }

bool Volunteer ::IsReturning() const { return returning_; }