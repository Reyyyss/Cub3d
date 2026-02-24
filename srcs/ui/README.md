# UI

In-game user interface overlays.

## Files

### game_instructions.c
- **`draw_instructions()`** — entry point. When instructions are visible, draws a full overlay with a semi-transparent black background and control descriptions. When hidden, draws a small hint bar at the top.
- Draws a black rectangle on the image buffer for the background, then uses `mlx_string_put()` to render white text on top of the window.

## How It Works

Toggled with the **I** key. Two states:

### Hidden (default)
A small dark bar at the top of the screen shows:
```
Press [I] for controls
```

### Visible
A centered overlay listing all controls:

```
┌─────────────────────┐
│     CONTROLS         │
│                      │
│  W/A/S/D - Move      │
│  ←/→ - Rotate        │
│  M - Toggle minimap  │
│  I - Toggle controls │
│  ESC - Quit          │
└─────────────────────┘
```

The background is drawn directly on the image buffer (pixel by pixel), while the text is rendered via MLX's built-in string drawing on the window surface. This means the background appears behind the text without needing transparency support.
