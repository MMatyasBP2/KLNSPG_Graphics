# Computer graphics semester task specification

In the game, the player must find a futuristic Porsche among a few house objects. The player can navigate through the track in first-person view, and upon finding the car, they can "exit the game" by pressing the ESC key.
Camera control is done with the mouse, while movement is controlled using the W, A, S, D key combinations.
Pressing the 1 and 2 keys allows the player to move one house up and down. The player needs to discover the purpose of this action. Only in this one house can we look inside, as we collide with the other houses if we try to enter. Additionally, there is collision on every edge of the track, preventing us from walking into "off-limits areas."
The + and - keys can increase the brightness of the track. Along the edges of the track, we can observe the movement of water based on sinusoidal waves. The game also features a Hard Mode for the more adventurous, where fog covers the entire track. Hard Mode can be toggled on/off using the 3 key.
The player can request further assistance by pressing the F1 key.


# Application of Geometric Modeling

While the structure and models of the game remained consistent, significant changes were made to the design and movement of the water. The objective was to simulate natural water waves and enhance the realism of the environment.

## 1. **Water Surface Modeling**

The water was modeled using a 45x45 grid, where each point on the grid represents a three-dimensional space (x, y, z). The z-coordinate represents the height of the water at each point. The water's surface was animated using mathematical functions that simulate wave behavior. The key idea was to create a smooth, flowing surface that responds to sinusoidal waves and vortex effects.

## 2. **Wave Animation and Mathematical Formulas**

To simulate realistic wave motion, sinusoidal functions were employed. These functions allow the water surface to move in an undulating manner, resembling natural water waves. The core of the wave animation was based on the following concepts:

- **Wave Phase Calculation**: The wave's phase was calculated using the formula:
  
  \[
  \text{wave\_phase} = \frac{y}{45} \times 2\pi
  \]

  where \( y \) represents the y-coordinate of the grid, and \( 2\pi \) ensures the full oscillation of the wave over one cycle.

- **De Casteljau Algorithm for Wave Interpolation**: To create smooth, curved waveforms, I used the De Casteljau algorithm, which is typically applied to Bézier curves. This algorithm allows for the interpolation of the wave height based on control points. The wave height at each grid point is given by:

  \[
  \text{wave\_height} = \text{de\_casteljau}(t, p_0, p_1, p_2, p_3)
  \]

  where \( t \) is a time-dependent variable, and \( p_0, p_1, p_2, p_3 \) are control points that define the wave's shape.

## 3. **Vortex Effect Simulation**

To further enhance the realism, I added a vortex effect to the water surface, which simulates the influence of swirling currents on the water. This effect was implemented using polar coordinates to calculate the radius and angle of each point relative to the center of the vortex. The following calculations were used:

- **Vortex Radius and Angle**:
  
  \[
  \text{radius} = \sqrt{(x - x_{\text{vortex}})^2 + (y - y_{\text{vortex}})^2}
  \]

  where \( (x_{\text{vortex}}, y_{\text{vortex}}) \) is the position of the vortex, and \( (x, y) \) are the coordinates of a point on the water grid.

- **Swirl and Falloff Effects**: The vortex generates a swirl that affects the wave height based on the distance from the vortex center. The effect is strongest near the vortex and decays with distance. The calculation for the swirl was:

  \[
  \text{swirl} = \sin(water\_delta \times 1.5 + \text{angle} \times 4 + \text{radius} \times 0.5)
  \]

  and the falloff effect was calculated as:

  \[
  \text{falloff} = \frac{1}{1 + \text{radius} \times 0.3}
  \]

## 4. **Water Surface Rendering**

The water was rendered using OpenGL, where each point on the grid was represented as a vertex in the 3D space. To improve performance and smooth the rendering, I used indexed triangles (quads) to represent the water surface. The water texture was applied to the surface, and the normal vectors were calculated for each vertex to simulate lighting effects, giving the water a more realistic appearance.

- **Lighting and Materials**: The material properties of the water surface were set using OpenGL material functions. These properties define the ambient, diffuse, and specular lighting characteristics of the water surface, which were adjusted to make the water reflect light in a natural way.

  \[
  \text{water\_mat\_ambient} = \{0.2, 0.2, 0.2, 1.0\}
  \]
  
  \[
  \text{water\_mat\_diffuse} = \{0.8, 0.8, 0.8, 1.0\}
  \]

  \[
  \text{water\_mat\_specular} = \{0.5, 0.5, 0.5, 1.0\}
  \]
