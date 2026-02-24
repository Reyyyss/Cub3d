# Player

Player initialization, rendering, movement, and rotation.

## Files

### player.c
- **`init_player()`** — allocates the player struct, sets the starting position from parsed map data (centered in the tile), calculates the initial direction vector from the spawn orientation (N/S/E/W), and sets default size/color.
- **`draw_player()`** — draws the player as a small square on the 2D view (used during development/debugging).

### player_movement.c
- **`player_movement()`** — computes the new position based on WASD input, then applies it with wall-sliding collision detection via `is_wall()`. If the full move is blocked, it tries each axis independently to allow sliding along walls.
- **`player_direction()`** — rotates the player's view angle by ±0.05 radians on LEFT/RIGHT arrow keys and recalculates the direction vector using cos/sin.

## How It Works

The player exists in world space where each map tile is 64×64 pixels (`MAP_S_W` × `MAP_S_H`). Movement is along the direction vector (`p_dir`), which is 5 units long. Strafing (A/D) uses a perpendicular vector derived from rotating the direction by 90°.

Collision is checked with a `COLLISION_RADIUS` of 20 pixels around the player to prevent clipping through walls. The wall-slide mechanic tries X-only and Y-only movement when diagonal movement is blocked, giving smooth movement along walls.
