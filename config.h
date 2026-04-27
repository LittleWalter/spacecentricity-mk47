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
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN          // rainbow that cycles vertically
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN           // Matrix‑style falling green code
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON // chevron‑shaped rainbow motion
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP         // lights based on how often you type
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL          // branching pixel fractal animation
#define ENABLE_RGB_MATRIX_STARLIGHT              // random twinkling star pulses
#define ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH       // smoother, softer starlight effect
#define ENABLE_RGB_MATRIX_RIVERFLOW              // flowing horizontal water‑like motion
#define ENABLE_RGB_MATRIX_SPLASH                 // ripple effect radiating from keypresses
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS    // colorful falling droplets across the board

// Crowd‑Pleaser Animations
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE      // wide reactive ripple on keypress
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS     // center‑out reactive pulse (fan favorite)
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE // multi‑key wide ripples for fast typing
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEEL         // spinning rainbow pinwheel
#define ENABLE_RGB_MATRIX_RAINBOW_SPIRAL           // smooth spiraling rainbow motion
#define ENABLE_RGB_MATRIX_BREATHING                // gentle breathing brightness cycle
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL             // continuous rainbow spiral sweep
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL           // continuous rainbow pinwheel sweep

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON
