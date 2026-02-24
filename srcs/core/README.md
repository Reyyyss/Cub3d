# Core

Program entry point, MLX graphics setup, and event handling.

## Files

### main.c
- **`main()`** — validates argument count, calls the parser, initializes MLX, renders the first frame, and starts the event loop.
- **`re_render()`** — clears the image buffer, then calls ray casting, 3D rendering, minimap drawing, and the instructions overlay. Called every frame.

### mlx_init.c
- **`my_mlx_pixel_put()`** — writes a single pixel to the image buffer at (x, y) with a given color. Used everywhere for drawing.
- **`init_connection()`** — establishes a connection with the X server via `mlx_init()`.
- **`init_window()`** — creates the game window with WIDTH × HEIGHT dimensions.
- **`init_image()`** — allocates an off-screen image buffer for double-buffered rendering.
- **`init_mlx()`** — orchestrates all initialization: connection, window, image, player, rays, textures, events, and sets default visibility flags.

### mlx_hooks.c
- **`init_events()`** — registers keyboard and window-close event hooks with MLX.
- **`key_press()`** — dispatches key events: WASD for movement, arrows for rotation, ESC to quit, M to toggle minimap, I to toggle instructions.
- **`close_handler()`** — frees all allocated resources (rays, player, textures, parsing data, MLX objects) and exits cleanly.
- **`free_parsing_data()`** — frees texture paths and the map grid. Also called from `main()` on parse failure to prevent leaks.

## Flow

```
main() → parse_cub_file() → init_mlx() → re_render() → mlx_loop()
                                              ↓
                                    key_press() ← event loop
                                         ↓
                                    re_render() (redraw)
```
