// Profile code

#ifndef __PROFILES_H_
#define __PROFILES_H_

#include "canbus/can_hal.h"
#include "common_structs.h"

#define MAX_PROFILES 4

/**
 * A profile is designed to read the current conditions of the gearbox and request the gearbox to do something
 */
class AbstractProfile {
public:
    virtual GearboxProfile get_profile() const;
    virtual GearboxDisplayGear get_display_gear(GearboxGear target, GearboxGear actual);
    virtual bool should_upshift(GearboxGear current_gear, SensorData* sensors);
    virtual bool should_downshift(GearboxGear current_gear, SensorData* sensors);
    virtual ShiftCharacteristics get_shift_characteristics(ProfileGearChange requested, SensorData* sensors);
    virtual GearboxGear get_start_gear() const {
        return GearboxGear::First;
    }
    void increment_subprofile() {
        profile_id += 1;
        if (profile_id >= MAX_PROFILES) {
            profile_id = 0;
        }
    }
protected:
    uint8_t profile_id = 0;
};

class AgilityProfile : public AbstractProfile {
public:
    GearboxProfile get_profile() const override { return GearboxProfile::Agility; }
    GearboxDisplayGear get_display_gear(GearboxGear target, GearboxGear actual) override;
    bool should_upshift(GearboxGear current_gear, SensorData* sensors) override;
    bool should_downshift(GearboxGear current_gear, SensorData* sensors) override;
    ShiftCharacteristics get_shift_characteristics(ProfileGearChange requested, SensorData* sensors) override;
};

class ComfortProfile : public AbstractProfile {
public:
    GearboxProfile get_profile() const override { return GearboxProfile::Comfort; }
    GearboxDisplayGear get_display_gear(GearboxGear target, GearboxGear actual) override;
    bool should_upshift(GearboxGear current_gear, SensorData* sensors) override;
    bool should_downshift(GearboxGear current_gear, SensorData* sensors) override;
    ShiftCharacteristics get_shift_characteristics(ProfileGearChange requested, SensorData* sensors) override;
    GearboxGear get_start_gear() const override {
        return GearboxGear::Second;
    }
};

class WinterProfile : public AbstractProfile {
public:
    GearboxProfile get_profile() const override { return GearboxProfile::Winter; }
    GearboxDisplayGear get_display_gear(GearboxGear target, GearboxGear actual) override;
    bool should_upshift(GearboxGear current_gear, SensorData* sensors) override;
    bool should_downshift(GearboxGear current_gear, SensorData* sensors) override;
    ShiftCharacteristics get_shift_characteristics(ProfileGearChange requested, SensorData* sensors) override;
    GearboxGear get_start_gear() const override {
        return GearboxGear::Second;
    }
};

class StandardProfile : public AbstractProfile {
public:
    GearboxProfile get_profile() const override { return GearboxProfile::Standard; }
    GearboxDisplayGear get_display_gear(GearboxGear target, GearboxGear actual) override;
    bool should_upshift(GearboxGear current_gear, SensorData* sensors) override;
    bool should_downshift(GearboxGear current_gear, SensorData* sensors) override;
    void on_upshift_complete(ShiftResponse response, uint8_t from_gear, SensorData* sensors);
    ShiftCharacteristics get_shift_characteristics(ProfileGearChange requested, SensorData* sensors) override;
};

class ManualProfile : public AbstractProfile {
public:
    GearboxProfile get_profile() const override { return GearboxProfile::Manual; }
    GearboxDisplayGear get_display_gear(GearboxGear target, GearboxGear actual) override;
    bool should_upshift(GearboxGear current_gear, SensorData* sensors) override;
    bool should_downshift(GearboxGear current_gear, SensorData* sensors) override;
    ShiftCharacteristics get_shift_characteristics(ProfileGearChange requested, SensorData* sensors) override;
};

extern AgilityProfile* agility;
extern ComfortProfile* comfort;
extern WinterProfile* winter;
extern ManualProfile* manual;
extern StandardProfile* standard;

#endif