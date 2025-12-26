#ifndef CONFIG_H
#define CONFIG_H

// -------------------------------------------------------------
// KNOCK DETECTION SETTINGS
// -------------------------------------------------------------
constexpr float KNOCK_THRESHOLD   = 0.25; 
constexpr int MAX_KNOCKS          = 30;
constexpr int MIN_KNOCKS          = 5;
constexpr int KNOCK_TOL           = 200;
constexpr int DEBOUNCE_TIME       = 200;      
constexpr int PATTERN_TIMEOUT     = 2000;   
constexpr int IDLE_RESET_TIME     = 5000;   
constexpr int SLEEP_TIMEOUT       = 60000;    // 1 Minute

constexpr int EXTRA_BEFORE        = 3;
constexpr int EXTRA_AFTER         = 3;

// -------------------------------------------------------------
// ADXL345 SETTINGS
// -------------------------------------------------------------
constexpr int SENSITIVITY         = 2;
constexpr int TAP_THRESHOLD       = 40;
constexpr int TAP_DURATION        = 20;
constexpr int DOUBLE_TAP_LATENCY  = 80;
constexpr int DOUBLE_TAP_WINDOW   = 200;
constexpr int ADXL_EN_X           = 1;
constexpr int ADXL_EN_Y           = 1;
constexpr int ADXL_EN_Z           = 1;

// -------------------------------------------------------------
// SYSTEM & BATTERY SETTINGS
// -------------------------------------------------------------
constexpr int SERIAL_MONITOR_EN   = 1;
constexpr float VOLTAGE_MULTIPLIER   = 2.47; 
constexpr float LOW_BAT_THRESHOLD_V  = 4.6;   // 30% of 4xAA
constexpr unsigned long BAT_CHECK_INTERVAL = 5000; 

#endif