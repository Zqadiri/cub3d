# cub3d
 This project is inspired by the world-famous eponymous 90’s game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

# SOme raycasting ressources:

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

https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/


https://stackoverflow.com/questions/62393477/what-is-the-math-behind-billboard-sprite-drawing-inverse-matrix


## The basic idea of raycasting  (lodev.org)

### The 2D calculations: 

 
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
	m->data.delta_dist_x = sqrt(1 + (m->data.ray_dir_y * m->data.ray_dir_y) / (m->data.ray_dir_x * m->data.ray_dir_x));
	m->data.delta_dist_y = sqrt(1 + (m->data.ray_dir_x * m->data.ray_dir_x) / (m->data.ray_dir_y * m->data.ray_dir_y));
}

```
* mapX and mapY represent the current square of the map the ray is in. The ray position itself is a floating point number and contains both info about in which square of the map we are, and where in that square we are, but mapX and mapY are only the coordinates of that square.

* sideDistX and sideDistY are initially the distance the ray has to travel from its start position to the first x-side and the first y-side. Later in the code their meaning will slightly change.

* deltaDistX and deltaDistY are the distance the ray has to travel to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side. The following image shows the initial sideDistX, sideDistY and deltaDistX and deltaDistY: 


![image 2](https://lodev.org/cgtutor/images/raycastdelta.gif)

Assuming the unit length of each grid distance is 1.

You start with your normalized vector that represents your ray it has an x component and a y component. First we want to see how long it is when it travels one unit in the x direction. We want to scale the entire vector so that the x component equals 1. To figure out what to scale it by, we do the following:

For the x component :

#####	      scale_Factor = 1/rayDirX;

in math it's just :

#####         scaled_X = rayDirX * (1/rayDirX) = 1

them for the y component :

#####         scaled_Y = rayDirY * (1/rayDirX) = rayDirY/rayDirX

So now we have our scaled components as (1, rayDirY/rayDirX)
Now, we want to know the length. Now Pythagorean comes into play. Which is :

#####         length = sqrt((x * x) + (y * y))

So plugging in our scaled components we get:

#####         length = sqrt((1 * 1 ) + (rayDirY / rayDirX) * (rayDirY / rayDirX))

Apply some algebra and simplify and we get:

#####         length = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))

Same goes for the length when the y component travels one unit, except we'll have (rayDirX/rayDirY, 1) which results in :

#####         length = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
 
There we have your two equations. The variable perpWallDist will be used later to calculate the length of the ray.
 

NOTE: If rayDirX or rayDirY are 0, then division through 0 occurs above, making the value of deltaDistX or deltaDistY infinity. That is fine if your system uses the IEEE 754 floating point standard and doesn't throw exceptions for this (e.g. if you use C++, Java or JS it works correctly, but Python does not allow it): The infinity will be used correctly in the comparison in the DDA steps below. If, however, you use a programming language that doesn't allow this, you can set the finite one to 0  which will make the DDA loop also work correctly.

Now, before the actual DDA can start, first stepX, stepY, and the initial sideDistX and sideDistY still have to be calculated.

If the ray direction has a negative x-component, stepX is -1, if the ray direciton has a positive x-component it's +1. If the x-component is 0, it doesn't matter what value stepX has since it'll then be unused.
The same goes for the y-component.

If the ray direction has a negative x-component, sideDistX is the distance from the ray starting position to the first side to the left, if the ray direciton has a positive x-component the first side to the right is used instead.
The same goes for the y-component, but now with the first side above or below the position.
For these values, the integer value mapX is used and the real position subtracted from it, and 1.0 is added in some of the cases depending if the side to the left or right, of the top or the bottom is used. Then you get the perpendicular distance to this side, so multiply it with deltaDistX or deltaDistY to get the real Euclidean distance.

```c
void	calculate_step_sidedist(t_index *m)
{
	//calculate step and initial sideDist
	if (m->data.ray_dir_x < 0)
	{
		m->data.step_x = -1;
		m->data.side_dist_x = (m->data.pos_x - m->data.map_x) * m->data.delta_dist_x;
	}
	else
	{
		m->data.step_x = 1;
		m->data.side_dist_x = (m->data.map_x + 1.0 - m->data.pos_x) * m->data.delta_dist_x;
	}
	if (m->data.ray_dir_y < 0)
	{
		m->data.step_y = -1;
		m->data.side_dist_y = (m->data.pos_y - m->data.map_y) * m->data.delta_dist_y;
	}
	else 
	{
		m->data.step_y = 1;
		m->data.side_dist_y = (m->data.map_y + 1.0 - m->data.pos_y) * m->data.delta_dist_y;
	}
}

```

Now the actual DDA starts. It's a loop that increments the ray with 1 square every time, until a wall is hit. Each time, either it jumps a square in the x-direction (with stepX) or a square in the y-direction (with stepY), it always jumps 1 square at once. If the ray's direction would be the x-direction, the loop will only have to jump a square in the x-direction everytime, because the ray will never change its y-direction. If the ray is a bit sloped to the y-direction, then every so many jumps in the x-direction, the ray will have to jump one square in the y-direction. If the ray is exactly the y-direction, it never has to jump in the x-direction, etc..


So sideDistX and sideDistY get incremented with deltaDistX with every jump in their direction, and mapX and mapY get incremented with stepX and stepY respectively.

```c
void	perform_dda(t_index *m, int  hit)
{
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (m->data.side_dist_x < m->data.side_dist_y)
		{
			m->data.side_dist_x += m->data.delta_dist_x;
			m->data.map_x += m->data.step_x;
			m->data.side = 0;
		}
		else
		{
			m->data.side_dist_y += m->data.delta_dist_y;
			m->data.map_y += m->data.step_y;
			m->data.side = 1;
		}
		//Check if ray has hit a wall
		if (m->parse.map[m->data.map_y][m->data.map_x] == '1')
			hit = 1;
	}
}
```
After the DDA is done, we have to calculate the distance of the ray to the wall, so that we can calculate how high the wall has to be drawn after this.

We don't use the Euclidean distance to the point representing player, but instead the distance to the camera plane (or, the distance of the point projected on the camera direction to the player), to avoid the fisheye effect. The fisheye effect is an effect you see if you use the real distance, where all the walls become rounded, and can make you sick if you rotate.

The following image shows why we take distance to camera plane instead of player. With P the player, and the black line the camera plane: To the left of the player, a few red rays are shown from hitpoints on the wall to the player, representing Euclidean distance. On the right side of the player, a few green rays are shown going from hitpoints on the wall directly to the camera plane instead of to the player. So the lengths of those green lines are examples of the perpendicular distance we'll use instead of direct Euclidean distance.

In the image, the player is looking directly at the wall, and in that case you would expect the wall's bottom and top to form a perfectly horizontal line on the screen. However, the red rays all have a different lenght, so would compute different wall heights for different vertical stripes, hence the rounded effect.
The green rays on the right all have the same length, so will give the correct result. The same still apllies for when the player rotates (then the camera plane is no longer horizontal and the green lines will have different lengths, but still with a constant change between each) and the walls become diagonal but straight lines on the screen. This explanation is somewhat handwavy but gives the idea.

![image 2](https://lodev.org/cgtutor/images/raycastdist.png)

Note that this part of the code isn't "fisheye correction", such a correction isn't needed for the way of raycasting used here, the fisheye effect is simply avoided by the way the distance is calculated here. It's even easier to calculate this perpendicular distance than the real distance, we don't even need to know the exact location where the wall was hit.

In the code below, (1-stepX)/2 is 1 if stepX = -1 and 0 if stepX is +1, this is needed because we need to add 1 to the length when rayDirX < 0, this is for the same reason why 1.0 was added to the initial value of sideDistX in one case but not in the other.

The distance is then calculated as follows: if an x-side is hit, mapX-posX+(1-stepX)/2) is the number of squares the ray has crossed in X direction (this is not necessarily a whole number).

If the ray is perpendicular to the X side, this is the correct value already, but because the direction of the ray is different most of the times, its real perpendicular distance will be larger, so we divide it through the X coordinate of the rayDir vector.

The computation is similar in case an y-side is hit. The calculated distance is never negative, since mapX-posX will be negative only if rayDirX is negative, and we divide these two through each other.

```c
void	calculate_dist(t_index *m)
{
	// Calculate distance projected on camera direction 
	// (Euclidean distance will give fisheye effect!)
	if (m->data.side == 0)
		m->data.perp_wall_dist = (m->data.map_x - m->data.pos_x +
		(1 - m->data.step_x) / 2) / m->data.ray_dir_x;
	else
		m->data.perp_wall_dist = (m->data.map_y - m->data.pos_y +
		(1 - m->data.step_y) / 2) / m->data.ray_dir_y;
}

```
Now that we have the calculated distance (perpWallDist), we can calculate the height of the line that has to be drawn on screen: this is the inverse of perpWallDist, and then multiplied by h, the height in pixels of the screen, to bring it to pixel coordinates. You can of course also multiply it with another value, for example 2*h, if you want to walls to be higher or lower. The value of h will make the walls look like cubes with equal height, width and depth, while large values will create higher boxes (depending on your monitor).

Then out of this lineHeight (which is thus the height of the vertical line that should be drawn), the start and end position of where we should really draw are calculated. The center of the wall should be at the center of the screen, and if these points lie outside the screen, they're capped to 0 or h-1.


```c
void	calculate_wall_height(t_index *m)
{
	//Calculate height of line to draw on screen
	m->data.wall_height = m->el.res_y;
	m->data.line_height = (int)(m->data.wall_height / m->data.perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	m->data.draw_start = -m->data.line_height / 2 + m->el.res_y / 2;
	if (m->data.draw_start < 0)
		m->data.draw_start = 0;
	m->data.draw_end = m->data.line_height / 2 + m->el.res_y / 2;
	if (m->data.draw_end >= m->el.res_y)
		m->data.draw_end = m->el.res_y - 1;
}
```
## Screenshot :

### Some ressources :

https://docs.fileformat.com/image/bmp/

http://www.fastgraph.com/help/bmp_header_format.html

https://stackoverflow.com/questions/50090500/create-simple-bitmap-in-c-without-external-libraries

https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393

https://4nsi.com/faq/how-do-i-calculate-the-file-size-for-a-digital-image

### What is a BMP file ?

BMP is an image file format that contains bitmap graphics data . A bitmap (or raster graphic) is a digital image composed of a matrix of dots. When viewed at 100%, each dot corresponds to an individual pixel on a display. In a standard bitmap image, each dot can be assigned a different color. Together, these dots can be used to represent any type of rectangular picture.

### BMP File Format Specifications :

A BMP file format contains different sections that contain information about metadata, color pallet, and actual pixel data.

![BMP Specifications](https://miro.medium.com/max/1400/1*2ohsW8Chn2QsTcSyVcTZcw.png)

## Sprites :

The technique used to draw the sprites is totally different from the raycasting technique. We have to do the projection only in 2D, and some extra techniques to combine it with the actual raycasting . Here we use 2D pictures always facing to you to represent sprites (so they're easy to draw and require a single picture), but that become smaller if they're further away.

Drawing the sprites is done after the walls are already drawn. Here are the steps used to draw the sprites:

*  While raycasting the walls, store the perpendicular distance of each vertical stripe in a 1D Buffer .

*  Calculate the distance of each sprite to the  and  Use this distance to sort the sprites, from furthest away to closest to the camera .

```c

void		order(t_index *m)
{
	int i;

	i = -1;
	while (++i < m->spr.numsprites)
	{
		m->s_xy[i].dist = ((m->data.pos_x - m->s_xy[i].x) *
				(m->data.pos_x - m->s_xy[i].x) + (m->data.pos_y -
					m->s_xy[i].y) * (m->data.pos_y - m->s_xy[i].y));
	}
}

void		sort_sprites(t_index *m)
{
	int		i;
	int		j;
	double	tmp;

	order(m);
	i = -1;
	while (++i < m->spr.numsprites)
	{
		j = -1;
		while (++j < m->spr.numsprites - 1)
		{
			if (m->s_xy[j].dist < m->s_xy[j + 1].dist)
			{
				tmp = m->s_xy[j].dist;
				m->s_xy[j].dist = m->s_xy[j + 1].dist;
				m->s_xy[j + 1].dist = tmp;
				tmp = m->s_xy[j].x;
				m->s_xy[j].x = m->s_xy[j + 1].x;
				m->s_xy[j + 1].x = tmp;
				tmp = m->s_xy[j].y;
				m->s_xy[j].y = m->s_xy[j + 1].y;
				m->s_xy[j + 1].y = tmp;
			}
		}
	}
}

```

*  Project the sprite on the camera plane (in 2D): subtract the player position from the sprite position, then multiply the result with the inverse of the 2x2 camera matrix .

![matrix inverse](https://i.pinimg.com/originals/c0/ad/cd/c0adcd88a08b12b2861f9b44712d67ef.gif)

```c
void         update(t_index *m, int i)
{
    //translate sprite position to relative to camera
    m->spr.spr_x = m->s_xy[i].x - m->data.pos_x;
	m->spr.spr_y = m->s_xy[i].y - m->data.pos_y;
    //transform sprite with the inverse camera matrix
    // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    // [ planeY   dirY ]                                          [ -planeY  planeX ]
    
    //required for correct matrix multiplication                                          [ -planeY  planeX ]
    m->spr.invdet = 1.0 / (m->data.plane_x * m->data.dir_y -
			m->data.dir_x * m->data.plane_y);
	m->spr.transform_x = m->spr.invdet * (m->data.dir_y * m->spr.spr_x -
			m->data.dir_x * m->spr.spr_y);
	m->spr.transform_y = m->spr.invdet * (-m->data.plane_y * m->spr.spr_x +
			m->data.plane_x * m->spr.spr_y);
	m->spr.spr_screen_x = (int)((m->el.res_x / 2) *
			(1 + m->spr.transform_x / m->spr.transform_y));
}

```

*  Calculate the size of the sprite on the screen (both in x and y direction) by using the perpendicular distance.

```c

void        calculate_start_end(t_index *m)
{
    //calculate height of the sprite on screen
    //using "transformY" instead of the real distance prevents fisheye
    m->spr.spr_height = abs((int)(m->el.res_y / m->spr.transform_y));
    //calculate lowest and highest pixel to fill in current stripe
    m->spr.draw_start_y = -m->spr.spr_height / 2 + m->el.res_y / 2;
    if (m->spr.draw_start_y < 0)
        m->spr.draw_start_y = 0;
    m->spr.draw_end_y = m->spr.spr_height / 2 + m->el.res_y / 2;
    if (m->spr.draw_end_y >= m->el.res_y)
        m->spr.draw_end_y = m->el.res_y;
    //calculate width of the sprite
    m->spr.spr_width = abs((int)(m->el.res_y / m->spr.transform_y));
    m->spr.draw_start_x = -m->spr.spr_width / 2 + m->spr.spr_screen_x;
    if (m->spr.draw_start_x < 0)
        m->spr.draw_start_x = 0;
    m->spr.draw_end_x = m->spr.spr_width / 2 + m->spr.spr_screen_x;
    if (m->spr.draw_end_x >= m->el.res_y)
        m->spr.draw_end_x = m->el.res_x;  
}  
  
```
*  Draw the sprites vertical stripe by vertical stripe, don't draw the vertical stripe if the distance is further away than the 1D ZBuffer of the walls of the current stripe .

```c
void		sprite_raycasting(t_index *m)
{
	int	i;

	sort_sprites(m);
	i = -1;
	while (++i < m->spr.numsprites)
	{
		update(m, i);
		calculate_start_end(m);
		m->spr.stripe = m->spr.draw_start_x;
		while (m->spr.stripe < m->spr.draw_end_x)
		{
			m->spr.tex_x = (int)(256 * (m->spr.stripe -
						(-m->spr.spr_width / 2 + m->spr.spr_screen_x)) *
						64 / m->spr.spr_width) / 256;
			if (m->spr.transform_y > 0 && m->spr.stripe >= 0
					&& m->spr.stripe < m->el.res_x
					&& m->spr.transform_y < m->spr.spr_buffer[m->spr.stripe]
					&& m->spr.tex_x < 64)
			{
				draw_sprite(m);
			}
			m->spr.stripe++;
		}
	}
}
```
* Draw the vertical stripe pixel by pixel, make sure there's an invisible color or all sprites would be rectangles .

```c
void        draw_sprite(t_index *m)
{
    int y;
    int d;

    d = 0;
    y = m->spr.draw_start_y;
    while (y < m->spr.draw_end_y)
    {
        //256 and 128 factors to avoid floats
        d = (y) * 256 - m->el.res_y *
             128 + m->spr.spr_height * 128;
        m->spr.tex_y = ((d * 64) / m->spr.spr_height) / 256;
        //get current color from the texture
        if ((m->spr.color[64 * m->spr.tex_y + m->spr.tex_x] & 0x00FFFFFF) != 0)
            m->img.addr[y * m->el.res_x + m->spr.stripe] =
				m->spr.color[64 * m->spr.tex_y + m->spr.tex_x];
        y++;
    }
}
```





