# `./src/tap_dances`

This directory wrangles individual tap dances into logical groups based on their semantic meanings, with each group split into a C header/source file pair.

## `NOTE:`

There’s inevitably some boilerplate from repeating the tap-dance pattern across many actions. A little [C macro](https://en.wikipedia.org/wiki/C_preprocessor) trickery in the shared [`tap_dance_actions.h`](./tap_dance_actions.h) header helps keep that repetition under control.
