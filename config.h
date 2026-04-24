// Enable 32-layer support
#define LAYER_STATE_32BIT

// Enabled for tap dance functionality
#define TAPPING_TERM 150       // ms
#define TAPPING_TERM_PER_KEY   // allow specific time for specific keys

#define ONESHOT_TAP_TOGGLE 2   // double‑tap to lock
#define ONESHOT_TIMEOUT 500    // ms before it cancels if unused

#define LEADER_KEY_STRICT_KEY_PROCESSING
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 750 // ms

// RGB LED settings for Planck layout
#define RGB_MATRIX_LED_COUNT 47
#define RGB_DI_PIN D3

// Enable Per-Key RGB
#define RGB_MATRIX_LAYER_INDICATORS

// Animation settings
#define RGB_MATRIX_KEYPRESSES  // allow ripple, heatmap, spectrum wave, etc.
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // allow more complex animations

// Animations Enabled
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT       // rainbow that cycles horizontally
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN          // rainbow that cylces vertically
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN           // Matrix-style falling green code
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON // chevron-shaped rainbow
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP         // lights based on how often you type
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_STARLIGHT
#define ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
#define ENABLE_RGB_MATRIX_RIVERFLOW
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
