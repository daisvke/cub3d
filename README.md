# cub3D

## Description
This project is about creating a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective, using the Ray-Casting principles.

## Commands
* Run<br />
```
make
./cub3D [map]       ex: ./cub3D maps/ok_test_map_labyrinth.cub
```

* QWERTY<br />
Up = W<br />
Down = S<br />
Left = A<br />
Right = D<br />

* AZERTY<br />
Up = Z<br />
Down = S<br />
Left = Q<br />
Right = D<br />

* Quit = ESC

## Map
* The program takes as a first argument a map description file with the .cub extension.
* The map can be composed of only 7 possible characters:<br />
0 for an empty space<br />
1 for a wall<br />
X for the map exit<br />
N, S, W, or E for the player’s starting position and gaze direction

This is a simple valid map:
```
1111111111111
1001000000001
1000011111001
100011E000001
1111111111111
```

* The map must be closed/surrounded by walls.

## Screenshots
<p align="center">
  <img src="/screenshots/labyrinth.png" width="80%" />
</p>
