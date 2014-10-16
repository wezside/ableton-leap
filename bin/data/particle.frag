// fragment shader
 
#version 150
 
uniform int u_screen_x;
uniform int u_screen_y;

out vec4 color;
 
void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.
 
    float r = gl_FragCoord.x / u_screen_x;
    float g = gl_FragCoord.y / u_screen_y;
    float b = 1.0;
    float a = 0.4;
    
    color = vec4(r, g, b, a);
}