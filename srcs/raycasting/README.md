# Raycasting

The core raycasting engine — casts rays from the player into the map grid to find wall intersections.

## Files

### rays.c
- **`cast_rays()`** — the main loop that casts `WIDTH` rays across the player's field of view. For each ray, it calculates the angle, finds the nearest horizontal and vertical wall intersections, picks the closest one, and draws the ray line on the 2D view.

### rays_init.c
- **`init_rays()`** — allocates all `WIDTH` ray structs and their sub-points (origin, endpoint, offset, increment). Sets the initial grid offset to `MAP_S_W` × `MAP_S_H` (64×64).

### rays_utils.c
- **`step_ray()`** — advances a ray by one grid step along its offset vector, incrementing the depth-of-field counter.
- **`calculate_ray_angle()`** — computes the angle for ray `r` by distributing `FOV` (60°) evenly across `WIDTH` rays, centered on the player's viewing angle. Normalizes the result to [0, 2π].

### rays_collision.c
- **`check_horizontal_line()`** — casts a ray against horizontal grid lines (rows). Snaps to the nearest horizontal boundary, then steps in `MAP_S_H` increments until it hits a wall or exceeds depth of field.
- **`check_vertical_line()`** — same logic but against vertical grid lines (columns), stepping in `MAP_S_W` increments.

### lines.c
- **`draw_line()`** — draws a ray line from origin to endpoint using incremental stepping (Bresenham-style). Used for the 2D debug view.

### math.c
- **`deg_to_rad()`** — converts degrees to radians.
- **`calculate_steps()`** — returns the number of pixel steps needed to draw a line from dx/dy deltas (the larger of |dx| and |dy|).
- **`distance()`** — Euclidean distance between two points.

## How It Works

The raycaster uses a **DDA (Digital Differential Analyzer)** algorithm on a uniform grid. For each ray:

1. Calculate the ray angle from the FOV spread
2. Find the first horizontal grid intersection, then step row by row
3. Find the first vertical grid intersection, then step column by column
4. Compare distances — the shorter one is the wall hit point
5. Store the hit point, distance, and which side was hit (used for texturing)

The `hit_vertical` flag tells the renderer whether a north/south or east/west texture should be used, and whether the wall was approached from the horizontal or vertical direction.
