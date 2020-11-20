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

![Cartesian Coordinates to Polar Coordinates](https://www.mathsisfun.com/images/coordinates-triangle.gif)

Later on when rotating around with the input keys, the values of dir and plane will be changed, but they'll always remain perpendicular and keep the same length.

### set data basing on the player’s start position and spawning orientation.
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
Here starts the actual raycasting. The raycasting loop is a for loop that goes through every x, so there isn't a calculation for every pixel of the screen, but only for every vertical stripe, which isn't much at all! To begin the raycasting loop, some variables are delcared and calculated:

```c  
void	calculate_ray_pos_dir(int i, t_index *m)
{
	//calculate ray position and direction
	m->data.camera_x = 2 * i / (float)m->el.res_x - 1;//find the x-coordinate in camera space
	m->data.ray_dir_x = m->data.dir_x + m->data.plane_x * m->data.camera_x;
	m->data.ray_dir_y = m->data.dir_y + m->data.plane_y * m->data.camera_x;

```
* CameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1. 

* rayDirY and rayDirX are the direction of a ray that has been cast.

*  Out of this, the direction of the ray can be calculated as was explained earlier: as the sum of the direction vector, and a part of the plane vector. This has to be done both for the x and y coordinate of the vector (since adding two vectors is adding their x-coordinates, and adding their y-coordinates).

In the next code piece, more variables are declared and calculated:

```c
	//which box of the map we're in
	m->data.map_x = (int)m->data.pos_x;
	m->data.map_y = (int)m->data.pos_y;
    
	//length of ray from one x or y-side to next x or y-side
	m->data.delta_dist_x = fabs(1 / m->data.ray_dir_x);
	m->data.delta_dist_y = fabs(1 / m->data.ray_dir_y);
}

```

* mapX and mapY represent the current square of the map the ray is in. The ray position itself is a floating point number and contains both info about in which square of the map we are, and where in that square we are, but mapX and mapY are only the coordinates of that square.

* sideDistX and sideDistY are initially the distance the ray has to travel from its start position to the first x-side and the first y-side. Later in the code their meaning will slightly change.

* deltaDistX and deltaDistY are the distance the ray has to travel to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side. The following image shows the initial sideDistX, sideDistY and deltaDistX and deltaDistY: 


![image 2](https://lodev.org/cgtutor/images/raycastdelta.gif)

You start with your normalized vector that represents your ray 







 

 

 