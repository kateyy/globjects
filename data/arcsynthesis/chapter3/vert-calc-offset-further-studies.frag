#version 330

out vec4 outputColor;

void main()
{
	outputColor = mix(
                      vec4(1.0f, 1.0f, 1.0f, 1.0f),
                      vec4(0.9f, 0.6f, 0.0f, 1.0f),
                      0.5
                      );
}
