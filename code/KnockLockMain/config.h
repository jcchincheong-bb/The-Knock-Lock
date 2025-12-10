#ifndef CONFIG_H
#define CONFIG_H

// --- Hardware Pins (Already in hardware.h, but listing here for completeness) ---
// Note: Pins are defined in hardware.cpp, but constants are config settings.

// --- Knock Detection Configuration ---
// The acceleration magnitude (in 'g') above 1.0g that counts as a knock.
constexpr float KNOCK_THRESHOLD = 0.15;

// The maximum number of knocks the system will record.
constexpr int MAX_KNOCKS = 30;

// The minimum number of knocks required to successfully save a pattern.
constexpr int MIN_KNOCKS = 5;

// The minimum time (ms) between two valid knocks (debouncing).
constexpr int DEBOUNCE_TIME = 120;

// The time (ms) the system waits after the last knock before it checks the pattern.
constexpr int PATTERN_TIMEOUT = 1000; // 1 second (used in KnockLockMain.ino)

// The time (ms) the recorder waits for the next knock before ending the recording.
constexpr int IDLE_RESET_TIME = 5000; // 5 seconds (used in knockRecorder.cpp)

// --- Pattern Matching Configuration ---
// The maximum allowed difference (ms) between a recorded interval and the target interval.
constexpr int KNOCK_TOL = 150;

// The number of "junk" knocks allowed *before* the pattern starts.
constexpr int EXTRA_BEFORE = 3;

// The number of "junk" knocks allowed *after* the pattern ends.
constexpr int EXTRA_AFTER  = 3;


// --- Servo Configuration ---
// The angle for the locked position (usually 0 or 180)
constexpr int SERVO_LOCKED_ANGLE = 0;
// The angle for the unlocked position (e.g., 90 degrees)
constexpr int SERVO_UNLOCKED_ANGLE = 90;

#endif