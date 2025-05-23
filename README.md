# Raytracer Compilation and Usage Guide

## Prerequisites

- C++ compiler with C++11 support (g++ recommended)
- Make utility
- An OFF (Object File Format) 3D model file for rendering

## Compilation

### Using Make (Recommended)

```bash
make
```

This will compile the program using the predefined Makefile settings:
- Compiler: g++
- Standard: C++11
- Flags: `-Wall` (all warnings) and `-I..` (include parent directory)
- Output: `raytracer` executable

### Manual Compilation

If you prefer to compile manually without make:

```bash
g++ -std=c++11 -Wall -I.. main.cpp -o raytracer
```

## Running the Program

The raytracer requires an OFF file as a command line argument:

```bash
./raytracer path/to/your/model.off
```

### Example Usage

```bash
./raytracer models/teapot.off
```

## Output

- The program will generate an image file called `image.ppm` in the current directory
- The rendered scene includes:
  - A ground sphere (acts as the floor)
  - Your 3D model loaded from the OFF file
- Image specifications:
  - Aspect ratio: 16:9
  - Width: 400 pixels
  - Format: PPM (Portable Pixmap)

## Viewing the Result

To view the generated PPM image, you can:
- Use image viewers that support PPM format
- Convert to other formats using tools like ImageMagick:
  ```bash
  convert image.ppm image.png
  ```

## Error Handling

The program will display error messages if:
- No OFF file path is provided as an argument
- The output file cannot be created
- Issues occur during rendering

## Cleaning Up

To remove the compiled executable:

```bash
make clean
```

## Required Files

Make sure these header files are present in your project directory:
- `vec3.h`
- `ray.h` 
- `color.h`
- `hittable.h`
- `hittable_list.h`
- `interval.h`
- `camera.h`
- `sphere.h`
- `triangle.h`
- `mesh.h`
- `rtweekend.h`
- `../OFFReader.h` (in parent directory)
