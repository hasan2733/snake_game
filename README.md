# Snake Game

A small Windows console game written in C. Move the player around the board
and reach the randomly placed target. Every move leaves a trail, giving the
game a simple snake-like appearance.

> This is a beginner-friendly console game rather than a full arcade-style
> Snake clone: the player does not grow, and there is no automatic movement.

## Gameplay

The board uses these symbols:

```text
#  Wall
*  Player
$  Target
.  Movement trail
```

Use the movement keys:

| Key | Direction |
| --- | --- |
| `W` | Up |
| `A` | Left |
| `S` | Down |
| `D` | Right |

Reach `$` to complete the current level. After each level, choose whether to
continue or exit.

## Example Board

```text
#######################
#                     #
#        . .          #
#          *     $    #
#                     #
#######################
```

The target position is randomized at the start of every level.

## Build and Run

The game uses the Windows-specific `<conio.h>` and `<windows.h>` headers, so
compile it on Windows with MinGW-w64 or another C compiler that provides
these headers.

### MinGW-w64

From the repository root:

```bash
gcc -std=c11 -Wall -Wextra src/snake_game.c -o snake_game.exe
./snake_game.exe
```

If running from PowerShell, use:

```powershell
gcc -std=c11 -Wall -Wextra src/snake_game.c -o snake_game.exe
.\snake_game.exe
```

## Project Layout

```text
snake_game/
├── README.md
└── src/
    └── snake_game.c
```

The project intentionally keeps one canonical source file. Earlier duplicate
versions were removed so future fixes only need to be made in one place.

## Implementation Notes

- The board is a 23 × 23 character square.
- The player starts at coordinate `(0, 0)`.
- A target is generated inside the border at a random coordinate.
- The last 100 player positions are retained as a trail.
- `clock()` measures the total CPU time spent playing completed levels.

## Limitations

- Movement is controlled manually rather than continuously.
- The player can move into the border; collision detection is not implemented.
- The game currently targets Windows because of its console input and cursor
  APIs.
