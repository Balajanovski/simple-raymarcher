# simple-raymarcher
![Screenshot of default raymarcher output](https://raw.githubusercontent.com/Balajanovski/simple-raymarcher/master/screenshot.png)

## About
The simple raymarcher is a project I've created as a "reference" for the SDF raymarching rendering technique which can be used and understood by beginners to CGI. Unfortunately there are not many projects on github written in C++ (all calculated on the CPU) for raymarching. The technique is mostly implemented on ShaderToy in GLSL, and when I was learning about this rendering technique, I had noticed a distinct abscence of information on the topic. This is why I've created this repository.<br> 
## Structure
The program is written entirely in C++.<br>
The shaders are only to put pixels to the screen. The values of the pixels are calculated on the CPU in `Raymarcher.cpp`.<br>
All of the raymarching code is in the `Raymarcher.cpp` file.<br>
You can change the scene via the file `Config/config.yaml`<br>
## Raymarching information
Raymarching is the alternative technique to Raytracing. Both of these techniques are part of the ray rendering family.<br>
Instead of casting out a ray and attempting to intersect a line with an object, raymarching, as it's name suggests, marches along a ray based on the scene's signed distance function until the distance output from the signed distance function is < 0.<br>
Due to the versatility of signed distance functions (SDFs), complex scenes can be rendered easily like fractals.<br><br>

### Constructive Solid Geometry
The scene's SDF is made up of the scene's object's SDFs unioned together through constructive solid geometry.<br>
https://en.wikipedia.org/wiki/Constructive_solid_geometry <br>
Practical code for constructive solid geometry can be found via the link below in the "distance operations" section. <br>
http://iquilezles.org/www/articles/distfunctions/distfunctions.htm <br><br>

### Blinn-Phong lighting
The lighting model used is the Blinn-Phong lighting model, which is an extension of the Phong lighting model.<br>
Information about the Blinn-Phong lighting model can be found below:<br>
https://glium.github.io/glium/book/tuto-13-phong.html <br>
While information on the Phong lighting model can be found below: <br>
https://blogs.igalia.com/itoral/2017/07/06/working_lights_shadows_parti_phong_reflection_model/ <br>
Although the article on Phong lighting is not on Blinn-Phong, I strongly suggest you read it because of the detail it goes into lighting in general.<br><br>

### Articles on Raymarching
Here is a list of resources on raymarching:<br>
* Jamie Wong's article (Raymarching in general): http://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/
* Raymarching vs. Sphere tracing: https://computergraphics.stackexchange.com/questions/161/what-is-ray-marching-is-sphere-tracing-the-same-thing
* Inigo Quilez's articles: 
  - Signed distance functions: http://iquilezles.org/www/articles/distfunctions/distfunctions.htm
  - Iterative shapes (Prelude to fractals): http://iquilezles.org/www/articles/menger/menger.htm
  - Mandelbulb fractal: http://iquilezles.org/www/articles/mandelbulb/mandelbulb.htm


## Screenshots
![Screenshot of default raymarcher output](https://raw.githubusercontent.com/Balajanovski/simple-raymarcher/master/screenshot.png)
![Screenshot of rendered menger sponge](https://raw.githubusercontent.com/Balajanovski/simple-raymarcher/master/screenshot2.png)
