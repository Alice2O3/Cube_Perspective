# Cube_Perspective

<div align=center>
    <img src="img/Krenz_Cushart_Avatar.jpeg" width = "400" height = "400">
</div>

A computer graphic demo for learning perspective, vanishing points of boxes at different angle.

**Image Source:** Avatar of [https://www.artstation.com/krenz](https://www.artstation.com/krenz) (Support him is possible!)

<div align=center>
    <img src="img/boxes.png" width = "1600" height = "1600">
</div>

## Usage

This project runs on Windows (x64) and is build with C++ using OpenGL library. You can just download the release or manually build it.

## Build

This project is build with Visual Studio 2019 (or newer).

You can build it as follows:

1. Fetch the project

```bash
git clone https://github.com/Alice2O3/Cube_Perspective.git
```

2. Open the project with Visual Studio 2019.
3. In build settings, select option `Release` and `x64`.
4. The build `.exe` is in `run` directory, which already contains `.dll` files of OpenGL library like `freeglut.dll`, `glew32.dll` and `glut32.dll`.

## Keyboard Control

### Moving

- `W / S`: Move the camera forward/backward
- `A / D`: Move the camera left/right
- `E / Q`: Move the camera up/down

### Changing View

- `I / K`: Rotate the view up/down
- `J / L`: Rotate the view left/right
- `U / O`: Rotate the canva counterclockwise/clockwise

### Rotating the Cube

- `Up / Down`: Rotate the cube along x-axis counterclockwise/clockwise, equivalent to looking from down/up
- `Left / Right`: Rotate the cube along y-axis
- `, / .`: Rotate the cube along y0-axis counterclockwise/clockwise (rotated y-axis), equivalent to rotating the cube on the ground left/right

### Reset

- `R`: Reset the player and view to default
- `/`: Reset the cube to default angle

### Changing Moving/Rotating Speed

- `[ / ]`: Decelerate/Accelerate moving speed
- `- / =`: Decelerate/Accelerate rotating speed of view
- `; / '`: Decelerate/Accelerate rotating speed of cube

### Changing Rotating Mode

- `1`: Change Rotating Mode to Euler Rotation
- `2`: Change Rotating Mode to Free Rotation

## HUD/Gizmo

The HUD will show the angle of the cube and camera, and the width/height of the window by pixel.

The Gizmo will show the vanishing points of each side of the cube. Scaling the width of the window will not affect the relative position of the vanishing points, but scaling the height of the window can.