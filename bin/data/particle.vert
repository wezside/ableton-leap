// vertex shader
 
#version 150
 
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;

uniform float u_size;
uniform int u_screen_x;
uniform int u_screen_y;
 
void main()
{
	// Calculate particle size based on distance to camera
	float size = u_size;
	vec4 vertex = vec4(position.xyz, 1.0);
	vec4 eyePos = modelViewMatrix * vertex;
	vec4 projVoxel = vec4(20.0, 20.0, eyePos.z, eyePos.w) * modelViewProjectionMatrix;
	vec2 projSize = vec2(u_screen_x, u_screen_y) * projVoxel.xy / projVoxel.w;
	gl_PointSize = (projSize.x + projSize.y) * size;

	gl_Position = modelViewProjectionMatrix * eyePos;
}