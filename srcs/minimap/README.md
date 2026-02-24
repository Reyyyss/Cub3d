# Minimap

A 2D overhead minimap overlay drawn in the bottom-left corner of the screen. Toggled with the **M** key.

## Files

### mini_map.c
- **`draw_2dmap()`** — the main entry point. Checks if the minimap is visible, initializes scaling, then draws tiles, rays, and the player dot in order.
- Manages `t_minimap` which holds position, size, tile dimensions, and world-to-minimap scale factors.

### mini_map_rays.c
- **`draw_minimap_rays()`** — draws the center ray on the minimap to show the player's look direction. Converts the ray's world-space endpoint to minimap coordinates and draws a cyan line.
- Uses `calculate_steps()` to interpolate pixels along the ray line, clipping to minimap bounds.

### mini_map_utils.c
- **`draw_minimap_player()`** — draws a small colored square at the player's minimap position.
- **`is_wall()`** — collision detection function used by player movement. Checks a square area (defined by `COLLISION_RADIUS`) around a pixel position against the map grid. Returns 1 if any checked point hits a non-walkable tile.

## How It Works

The minimap takes 1/4 of the screen (WIDTH/4 × HEIGHT/4) and maps the entire game world into that space:

```
┌────────────────────────────────┐
│                          3D    │
│                          view  │
│                                │
│ ┌──────────┐                   │
│ │ minimap  │                   │
│ │ ■ player │                   │
│ │ ─ ray    │                   │
│ └──────────┘                   │
└────────────────────────────────┘
```

- **Pink tiles** = walls (`1`)
- **Orange tiles** = walkable floor (`0`)
- **Black tiles** = empty space (` `)
- **Red borders** = grid lines between tiles
- **Cyan line** = center ray (look direction)
- **Player dot** = colored square at player position

Scale factors `sx`/`sy` convert world coordinates (64px tiles) to minimap pixel coordinates.
