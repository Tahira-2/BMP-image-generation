# BMP Circle Generator

A C++ program that generates a BMP image file from scratch — no external libraries required. It manually constructs BMP file headers and pixel data to render a red circle on a white background.

## How It Works

The program builds a valid 24-bit BMP file by:

1. **Constructing BMP headers** — Writes the 14-byte file header and 40-byte info header using packed structs to ensure correct binary layout.
2. **Generating pixel data** — Iterates over a 100×100 pixel grid, using the circle equation `(x - cx)² + (y - cy)² ≤ r²` to determine whether each pixel falls inside the circle (red) or outside (white).
3. **Handling row padding** — Each row is padded to a 4-byte boundary, as required by the BMP specification.
4. **Writing to file** — Outputs the raw binary data to `circle.bmp`.

## Output

A 100×100 pixel BMP image with a red circle (radius 30) centered at (50, 50) on a white background.

## Build & Run

```bash
g++ -o circle "circlcle bmp.cpp"
./circle
```

This creates `circle.bmp` in the current directory.

## Concepts Demonstrated

- Low-level binary file I/O in C++
- BMP file format specification (headers, pixel layout, row padding)
- Memory layout control with `#pragma pack`
- Pointer arithmetic and `reinterpret_cast`
