# Rendering

Transforms raycasting data into a textured 3D perspective view.

## Files

### render_3d.c
- **`render_3d()`** — iterates over all `WIDTH` rays. For each ray, computes the perpendicular distance (to fix fisheye), calculates wall height, draws ceiling pixels, a textured wall column, and floor pixels.
- Uses the perpendicular distance formula: `distance × cos(ray_angle - player_angle)` to correct the fisheye distortion that occurs with raw Euclidean distances.
- Wall height is inversely proportional to distance: closer walls appear taller.

### textures.c
- **`load_textures()`** — loads the 4 wall textures (NO, EA, SO, WE) from XPM files using `mlx_xpm_file_to_image()`. Stores pixel data addresses for fast access.
- **`get_texture_color()`** — reads a pixel color from a texture image at (x, y) coordinates, handling the bits-per-pixel and line length calculations.

### texture_utils.c
- **`get_tex_x()`** — computes the X coordinate within the texture based on where the ray hit the wall. Uses `fmod()` of the hit position against the tile size to get the fractional position within the tile.
- **`clamp_tex_y()`** — clamps the texture Y coordinate to valid bounds to prevent out-of-range reads.
- **`get_start_y()` / `get_end_y()`** — clamp wall top/bottom to screen bounds (0 to HEIGHT).

## How It Works

For each vertical screen column (one per ray):

```
     ceiling_color (from y=0 to wall_top)
     ┌─────────────┐
     │   texture    │  (from wall_top to wall_bottom)
     │   column     │  texture X from hit position
     │              │  texture Y interpolated along wall height
     └─────────────┘
     floor_color (from wall_bottom to HEIGHT)
```

The texture selection depends on which wall face was hit:
- Horizontal hit + ray going up → **North** texture
- Horizontal hit + ray going down → **South** texture
- Vertical hit + ray going left → **West** texture
- Vertical hit + ray going right → **East** texture
