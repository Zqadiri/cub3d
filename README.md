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

https://github.com/vinibiavatti1/RayCastingTutorial/wiki/RayCasting


# The basic idea of raycasting  (lodev.org)

## The 2D calculations: 

 
The basic idea of raycasting is as follows: the map is a 2D square grid, and each square can either be 0 (= no wall), or a positive value (= a wall with a certain color or texture). 

 
For every vertical stripe of the screen send out a ray that starts at the player position And with a direction that depends on both the player's looking direction and the x-coordinate of th screen . Let the ray move forward on 2d map until it hits a wall (reprsented by a map square) , when it hits the wall calculate the distance of this hit point to the player . We will use this distance to calculate the height of the wall :  the further away the wall, the smaller it's on screen, and the closer, the higher it appears to be .  

 

To find the first wall that a single ray meets on its way, you have to start from the player's positions and check whether or not the ray is inside a wall . When the ray hits a wall , the loop can stop so we can calculate the distance and draw the wall with the correct height . If the ray position is not in a wall, you have to trace it further: add a certain value to its position, in the direction of the direction of this ray, and for this new position, again check if it's inside a wall or not. Keep doing this until finally a wall is hit.


![image 1](https://lodev.org/cgtutor/images/raycastingcamera.gif)


The image above represents such a 2D camera :

* The green spot is the position [vector "pos"].
* The black line, ending in the black spot, represents the direction vector [vector "dir"].
* The position of the black dot is pos+dir .
* The blue line represents the full camera plane .
* The vector from the black dot to the right blue dot represents the vector "plane" .
* The position of the right blue point is pos+dir+plane .
* The posistion of the left blue dot is pos+dir-plane .
(Addition of vectors)

![Addiction of vectors](https://www.mathsisfun.com/algebra/images/vector-add.svg)

FOR EXAMPLE : The red lines in the image are a few rays. The direction of these rays is easily calculated out of the camera: it's the sum of the direction vector of the camear, and a part of the plane vector of the camera: for example the third red ray on the image, goes through the right part of the camera plane at the point about 1/3th of its length. So the direction of this ray is dir + plane * 1/3.
This ray direction is the vector rayDir, and the X and Y component of this vector are then used by the DDA algorithm.


## UNTextured raycaster :

A first few variables are declared: posX and posY represent the position vector of the player, dirX and dirY represent the direction of the player, and planeX and planeY the camera plane of the player. Make sure the camera plane is perpendicular to the direction, but you can change the length of it.

* The ratio between the length of the direction and the camera plane determinates the FOV, here the direction vector is a bit longer than the camera plane, so the FOV will be smaller than 90° . MORE the FOV is 2 * atan(0.66/1.0)=66°, which is perfect for a first person shooter game). Later on when rotating around with the input keys, the values of dir and plane will be changed, but they'll always remain perpendicular and keep the same length (θ = tan-1 ( y / x ) define the angle in the Euclidean plane, given in radians, between the positive x axis and the ray to the point (x, y) ).

![Cartesian Coordinates to Polar Coordinates](https://www.google.com/imgres?imgurl=https%3A%2F%2Fmdn.mozillademos.org%2Ffiles%2F11557%2Fatan2.png&imgrefurl=https%3A%2F%2Fdeveloper.mozilla.org%2Fen-US%2Fdocs%2FWeb%2FJavaScript%2FReference%2FGlobal_Objects%2FMath%2Fatan2&tbnid=v1h7m3R7TSD8mM&vet=10CAMQxiAoAGoXChMI2Pj48pOP7QIVAAAAAB0AAAAAEAc..i&docid=3vrNlndlNn1TdM&w=300&h=300&itg=1&q=%CE%B8%20%3D%20tan-1%20(%20y%20%2F%20x%20)&ved=0CAMQxiAoAGoXChMI2Pj48pOP7QIVAAAAAB0AAAAAEAc)

 Later on when rotating around with the input keys, the values of dir and plane will be changed, but they'll always remain perpendicular and keep the same length.

# C Example

```c
    if (m->parse.dir == 'E')
	{
		m->data.plane_x = 0.0;
		m->data.plane_y = 0.66;
		m->data.dir_x = 1;
		m->data.dir_y = 0;
	}
	if (m->parse.dir == 'W')
	{
		m->data.plane_x = 0;
		m->data.plane_y = -0.66;
		m->data.dir_x = -1;
		m->data.dir_y = 0;
	}
	if (m->parse.dir == 'S')
	{
		m->data.plane_x = -0.66;
		m->data.plane_y = 0;
		m->data.dir_x = 0;
		m->data.dir_y = 1;
	}
	if (m->parse.dir == 'N')
	{
		m->data.plane_x = 0.66;
		m->data.plane_y = 0;
		m->data.dir_x = 0;
		m->data.dir_y = -1;
	}
```






 

 

 