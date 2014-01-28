#version 330

smooth in vec4 theColor;

out vec4 outputColor;

void main()
{
    // Dividing by a constant value is always a bad idea, however,
    // to comply to the original tutorial the division is retained.
    //
    // IMPORTANT: For those retina-display/high-resolution display
    // users out there that will run this example, the result will
    // differ from a normal display! Try using the constant value
    // 1000.0f insead ;).
	float lerpValue = gl_FragCoord.y / 500.0f; // use for normal displays
//  	float lerpValue = gl_FragCoord.y / 1000.0f; // use for high-resolution / retina displays
    
	outputColor = mix(theColor, vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
}
