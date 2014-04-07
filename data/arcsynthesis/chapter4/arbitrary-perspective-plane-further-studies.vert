#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform vec2 offset;
uniform vec4 eye;
uniform float zNear;
uniform float zFar;
uniform float frustumScale;


void main()
{
	vec4 cameraPos = position + vec4(offset.x, offset.y, 0.0, 0.0);
	vec4 clipPos;
	
	clipPos.xy = cameraPos.xy * frustumScale;
    
//    clipPos.xy = clipPos.xy + eye.xy;
    
	
	clipPos.z = cameraPos.z * (zFar + zNear) / (zNear - zFar);
	clipPos.z += 2 * zNear * zFar / (zNear - zFar);
	
    clipPos.xy += eye.xy;
	clipPos.w = cameraPos.z/eye.z;
	
//	gl_Position = cameraPos;
    
	gl_Position = clipPos;
	theColor = color;
}
