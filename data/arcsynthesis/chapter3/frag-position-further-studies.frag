#version 330

uniform int height;

out vec4 outputColor;

void main()
{
    // use the height uniform to compute lerpValue for mix-function.
	float lerpValue = gl_FragCoord.y / height;
    
	outputColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
}
