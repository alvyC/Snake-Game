There are many variants of Snake, so to avoid confusion we'll explicitly spell out the rules of the game we're implementing:

- The snake moves by extending its head in the direction it's moving and pulling its tail in one space.
- The snake wins if it eats twenty pieces of food.
- The snake loses if it crashes into itself or into a wall.
- If the snake eats a piece of food, its length grows by one and a new piece of food is randomly
placed.
- There is only one level, the starting level.

We'll use the following characters to encode game information:

- A space character (' ') represents an empty tile.
- A pound sign ('#') represents a wall.
- A dollar sign ('$') represents food.
- An asterisk ('*') represents a tile occupied by a snake.