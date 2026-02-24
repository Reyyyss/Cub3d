# Parsing

Reads and validates `.cub` map files, extracting textures, colors, and the map grid.

## Files

### parse_main.c
- **`init_parsing_data()`** — zeroes out all parsing-related fields in `t_game` (map, texture paths, colors, player start) before parsing begins.
- **`parse_cub_file()`** — the main parsing orchestrator. Validates the filename (`.cub` extension), opens the file, parses the header (textures + colors), counts map dimensions, loads the map grid, and validates it.

### parse_colors.c
- **`parse_color_line()`** — parses a floor (`F`) or ceiling (`C`) line, splitting by space to get the RGB string (e.g., `"F 220,100,0"`).
- Internally splits the RGB string by commas, validates each component is a number in range [0, 255], and packs it into a single int: `(R << 16) | (G << 8) | B`.

### parse_header.c
- **`parse_header()`** — reads lines from the file until all 6 header elements are found (4 textures + 2 colors). Skips empty lines. Reports errors for invalid or incomplete headers.
- Dispatches texture lines (`NO`, `SO`, `WE`, `EA`) and color lines (`F`, `C`) to their respective parsers.
- Validates texture files exist by attempting to `open()` them.

### checking_map.c
- **`validate_map()`** — walks every cell in the map grid. Checks that:
  - Walkable tiles (`0`) and player spawns (`NSEW`) are fully enclosed by walls (not adjacent to spaces or map edges).
  - Only valid characters exist (`0`, `1`, `N`, `S`, `E`, `W`, space).
  - Exactly one player start position exists.
- Converts the player start tile to `0` after recording the spawn position and direction.

### map_loading.c
- **`count_map_dimensions()`** — first pass: reads remaining lines after the header to count rows and find the widest column.
- **`load_map()`** — second pass: reopens the file, skips the header, allocates the 2D char grid, and fills each row. Short rows are padded with spaces to match the widest column.

### parsing_utils.c
- **`parsing_error()`** — prints a colored error message with usage instructions and lists available maps from the `maps/` directory.
- **`free_str_arr()`** — frees a NULL-terminated array of strings.
- **`ft_strtrim_nl()`** — strips trailing newline from a string in-place.
- **`pad_line()`** — creates a new string padded with spaces to a target width.

## .cub File Format

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 0,150,255

        1111111111111111
        1000000000110001
1111111100000100000000011111
1000000000001000011100001
100000000000001000000010001
11000010110100010110000001
100000000110100010010111101
111111111011010001011101111
              1000000001
       11111111111111111
```

- **Header**: 6 elements (4 textures + 2 colors), any order, empty lines allowed between them.
- **Map**: must come after the header, enclosed by walls (`1`), with exactly one player spawn (`N`/`S`/`E`/`W`).
