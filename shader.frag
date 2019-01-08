#version 420

layout(origin_upper_left) in vec4 gl_FragCoord;

layout(binding = 0) uniform usamplerBuffer pixels;
uniform uint scaleX;
uniform uint scaleY;
uniform uint width;

out vec4 colour;

void main() {
    uvec4 pixel = texelFetch(pixels, int(gl_FragCoord.x / scaleX + gl_FragCoord.y / scaleY * width));
    colour.r = ((pixel.r >> 16) & 0xFF) * 0.00390625;
    colour.g = ((pixel.r >> 8) & 0xFF) * 0.00390625;
    colour.b = (pixel.r & 0xFF) * 0.00390625;
}