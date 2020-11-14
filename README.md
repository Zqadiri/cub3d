# cub3d
 This project is inspired by the world-famous eponymous 90’s game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

# SOme ressources:

https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
https://courses.pikuma.com/courses/raycasting
https://harm-smits.github.io/42docs/projects/cub3d.html
https://harm-smits.github.io/42docs/libs/minilibx.html
https://lodev.org/cgtutor/raycasting.html
https://lodev.org/cgtutor/raycasting2.html
https://qst0.github.io/ft_libgfx/man_mlx.html
https://github.com/keuhdall/images_example
https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/

# The basic idea of raycasting  

# The 2D calculations: 

 
The basic idea of raycasting is as follows: the map is a 2D square grid, and each square can either be 0 (= no wall), or a positive value (= a wall with a certain color or texture). 

 
For every vertical stripe of the screen send out a ray that starts at the player position And with a direction that depends on both the player's looking direction and the x-coordinate of th screen . Let the ray move forward on 2d map until it hits a wall (reprsented by a map square) , when it hits the wall calculate the distance of this hit point to the player . We will use this distance to calculate the height of the wall :  the further away the wall, the smaller it's on screen, and the closer, the higher it appears to be .  

 

To find the first wall that a single ray meets on its way, you have to start from the player's positions and check whether or not the ray is inside a wall . When the ray hits a wall , the loop can stop so we can calculate the distance and draw the wall with the correct height . 

 

 

 