
/**
* AUTOGENERATED BY convert.py
* DO NOT EDIT THIS FILE!
*
* IF MODIFICATIONS NEED TO BE MADE, MODIFY can_data.txt!
*
* CAN Defintiion for ECU 'EWM'
*/

#ifdef EGS52_MODE

#ifndef __ECU_EWM_H_
#define __ECU_EWM_H_

#include <stdint.h>
    
#define EWM_230_CAN_ID 0x0230

/** gear selector lever position (NAG only) */
enum class EWM_230h_WHC {
	D = 5, // selector lever in position "D"
	N = 6, // selector lever in position "N"
	R = 7, // selector lever in position "R"
	P = 8, // selector lever in position "P"
	PLUS = 9, // selector lever in position "+"
	MINUS = 10, // selector lever in position "-"
	N_ZW_D = 11, // selector lever in intermediate position "N-D"
	R_ZW_N = 12, // selector lever in intermediate position "R-N"
	P_ZW_R = 13, // selector lever in intermediate position "P-R"
	SNV = 15, // selector lever position unplausible
};



typedef union {
	uint64_t raw;
	uint8_t bytes[8];

	/** Gets CAN ID of EWM_230 */
	uint32_t get_canid(){ return EWM_230_CAN_ID; }
    /** Sets Driving program */
    void set_W_S(bool value){ raw = (raw & 0x7fffffffffffffff) | ((uint64_t)value & 0x1) << 63; }

    /** Gets Driving program */
    bool get_W_S() const { return (bool)(raw >> 63 & 0x1); }
        
    /** Sets Driving program button actuated */
    void set_FPT(bool value){ raw = (raw & 0xbfffffffffffffff) | ((uint64_t)value & 0x1) << 62; }

    /** Gets Driving program button actuated */
    bool get_FPT() const { return (bool)(raw >> 62 & 0x1); }
        
    /** Sets Kickdown */
    void set_KD(bool value){ raw = (raw & 0xdfffffffffffffff) | ((uint64_t)value & 0x1) << 61; }

    /** Gets Kickdown */
    bool get_KD() const { return (bool)(raw >> 61 & 0x1); }
        
    /** Sets barrier magnet energized */
    void set_SPERR(bool value){ raw = (raw & 0xefffffffffffffff) | ((uint64_t)value & 0x1) << 60; }

    /** Gets barrier magnet energized */
    bool get_SPERR() const { return (bool)(raw >> 60 & 0x1); }
        
    /** Sets gear selector lever position (NAG only) */
    void set_WHC(EWM_230h_WHC value){ raw = (raw & 0xf0ffffffffffffff) | ((uint64_t)value & 0xf) << 56; }

    /** Gets gear selector lever position (NAG only) */
    EWM_230h_WHC get_WHC() const { return (EWM_230h_WHC)(raw >> 56 & 0xf); }
        
} EWM_230;



class ECU_EWM {
	public:
        /**
         * @brief Imports the CAN frame given the CAN ID, CAN Contents, and current timestamp
         *
         * Returns true if the frame was imported successfully, and false if import failed (Due to non-matching CAN ID).
         *
         * NOTE: The endianness of the value cannot be guaranteed. It is up to the caller to correct the byte order!
         */
        bool import_frames(uint64_t value, uint32_t can_id, uint64_t timestamp_now) {
            switch(can_id) {
                case EWM_230_CAN_ID:
                    LAST_FRAME_TIMES[0] = timestamp_now;
                    FRAME_DATA[0] = value;
                    return true;
                default:
                    return false;
            }
        }
        
        /** Sets data in pointer to EWM_230
          * 
          * If this function returns false, then the CAN Frame is invalid or has not been seen
          * on the CANBUS network yet. Meaning it's data cannot be used.
          *
          * If the function returns true, then the pointer to 'dest' has been updated with the new CAN data
          */
        bool get_EWM_230(uint64_t now, uint64_t max_expire_time, EWM_230* dest) const {
            if (LAST_FRAME_TIMES[0] == 0 || dest == nullptr) { // CAN Frame has not been seen on bus yet / NULL pointer
                //ESP_LOG_LEVEL(ESP_LOG_INFO, "EWM", "NP");
                return false;
            } else if (now > LAST_FRAME_TIMES[0] && now - LAST_FRAME_TIMES[0] > max_expire_time) { // CAN Frame has not refreshed in valid interval
                //ESP_LOG_LEVEL(ESP_LOG_INFO, "EWM", "EX %d %d %d", (int)now, (int)LAST_FRAME_TIMES[0], (int)max_expire_time);
                return false;
            } else { // CAN Frame is valid! return it
                //ESP_LOG_LEVEL(ESP_LOG_INFO, "EWM", "OK");
                dest->raw = FRAME_DATA[0];
                return true;
            }
        }
            
	private:
		uint64_t FRAME_DATA[1];
		uint64_t LAST_FRAME_TIMES[1];
};
#endif // __ECU_EWM_H_

#endif // EGS52_MODE