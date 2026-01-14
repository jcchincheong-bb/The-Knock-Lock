#ifndef CONFIG_H
#define CONFIG_H

// -------------------------------------------------------------
// KNOCK DETECTION SETTINGS
// -------------------------------------------------------------
constexpr int KNOCK_THRESHOLD     = 150;      // In raw ADXL values
constexpr int MAX_KNOCKS          = 30;       // Max length of pattern possible
constexpr int MIN_KNOCKS          = 5;        // Min length of pattern possible
constexpr int KNOCKS_TO_LOCK      = 2;        // Knocks to do in unlocked state to lock the box back
constexpr int KNOCK_TOL           = 150;      // How many milliseconds close to target pattern for correct recognition (Higher makes it easier to repeat knock but also less safe)
constexpr int DEBOUNCE_TIME       = 150;      // Minimum duration before next knock is detected
constexpr int PATTERN_TIMEOUT     = 2000;     // Max duration between two knocks
//constexpr int IDLE_RESET_TIME     = 5000;     // Max duration before going back to start of pattern recognition
constexpr int SLEEP_TIMEOUT       = 60000;    // 1 Minute

constexpr int ALLOWED_MISTAKES = 1;           // How many accidental knocks before or after can be tolerated

// -------------------------------------------------------------
// ADXL345 SETTINGS
// -------------------------------------------------------------
constexpr int SENSITIVITY         = 2;    // Sensitivity can be: +-2g, +-4g, +-8g, +-16g
constexpr int TAP_THRESHOLD       = 40;   // This is now g, it is 0-255 (62.5mg per increment)
constexpr int TAP_DURATION        = 20;   // In ms
constexpr int DOUBLE_TAP_LATENCY  = 80;   // In ms
constexpr int DOUBLE_TAP_WINDOW   = 200;  // In ms
constexpr int ADXL_EN_X           = 1;  // Turn individual sensing off (0) or on (1)
constexpr int ADXL_EN_Y           = 1;  // Turn individual sensing off (0) or on (1)
constexpr int ADXL_EN_Z           = 1;  // Turn individual sensing off (0) or on (1)

// -------------------------------------------------------------
// BATTERY SETTINGS
// -------------------------------------------------------------
constexpr float VOLTAGE_MULTIPLIER   = 2.47;  // To get correct voltage, may need to alter depending on resistors if changed
constexpr float LOW_BAT_THRESHOLD_V  = 4.6;   // 30% of 4xAA - low battery alert to starts below this voltage
constexpr unsigned long BAT_CHECK_INTERVAL = 900000; // in ms, interval to check battery (Set to 15 minutes by default)
constexpr int FLASHING_TIME = 60; // in seconds, to change how frequently the system wakes up to indicate low battery with Red LED

// -------------------------------------------------------------
// DEBUG SETTINGS
// -------------------------------------------------------------
constexpr int DEBUG_MODE = 0; // Make 1 to allow pattern setting in locked state or unlocked state
constexpr int SERIAL_MONITOR_EN   = 1;  // Turn Serial Monitor on with 1 and off with 0
// To enter manual override
constexpr int OVERRIDE_CLICK_COUNT = 4;     // Total clicks needed
constexpr int CLICK_GAP_TIMEOUT    = 500;   // Max time (ms) between clicks
#endif