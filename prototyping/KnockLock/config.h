#ifndef CONFIG_H
#define CONFIG_H

// -------------------------------------------------------------
// KNOCK DETECTION SETTINGS
// -------------------------------------------------------------
constexpr float KNOCK_THRESHOLD   = 0.25; 
constexpr int MAX_KNOCKS          = 30;       // Max length of pattern possible
constexpr int MIN_KNOCKS          = 5;        // Min length of pattern possible
constexpr int KNOCK_TOL           = 200;      // How many milliseconds close to target pattern for correct recognition (Higher makes it easier to repeat knock but also less safe)
constexpr int DEBOUNCE_TIME       = 200;      // Minimum duration before next knock is detected
constexpr int PATTERN_TIMEOUT     = 2000;     // Max duration between two knocks
constexpr int IDLE_RESET_TIME     = 5000;     // Maax duration before going back to start of pattern recognition
constexpr int SLEEP_TIMEOUT       = 60000;    // 1 Minute

constexpr int ALLOWED_MISTAKES    // Change how many incorrect knocks after can be tolerated before or after correct knock

// -------------------------------------------------------------
// ADXL345 SETTINGS
// -------------------------------------------------------------
constexpr int SENSITIVITY         = 2;    // Sensitivity can be: +-2g, +-4g, +-8g, +-16g
constexpr int TAP_THRESHOLD       = 40;   
constexpr int TAP_DURATION        = 20;   // In ms
constexpr int DOUBLE_TAP_LATENCY  = 80;   // In ms
constexpr int DOUBLE_TAP_WINDOW   = 200;  // In ms
constexpr int ADXL_EN_X           = 1;  // Turn individual sensing off or on
constexpr int ADXL_EN_Y           = 1;  // Turn individual sensing off or on
constexpr int ADXL_EN_Z           = 1;  // Turn individual sensing off or on

// -------------------------------------------------------------
// BATTERY SETTINGS
// -------------------------------------------------------------
constexpr float VOLTAGE_MULTIPLIER   = 2.47;  // To get correct voltage, may need to alter depending on resistors if changed
constexpr float LOW_BAT_THRESHOLD_V  = 4.6;   // 30% of 4xAA - low battery alert to starts below this voltage
constexpr unsigned long BAT_CHECK_INTERVAL = 900000; // in ms, interval to check battery (Set to 15 minutes by default)

// -------------------------------------------------------------
// DEBUG SETTINGS
// -------------------------------------------------------------
constexpr int DEBUG_MODE = 0; // Make 0 to allow pattern setting even in locked state, 1 for only in unlocked state
constexpr int SERIAL_MONITOR_EN   = 1;  // Turn Serial Monitor on with 1 and off with 0
#endif