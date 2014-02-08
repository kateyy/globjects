#version 330

out vec4 outputColor;

uniform float fragLoopDuration;
uniform float time;

const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = mix(firstColor, vec4(0.9f, 0.6f, 0.0f, 1.0f), 0.5);//vec4(0.0f, 1.0f, 0.0f, 1.0f);

void main()
{

    /*
     * Compute continuous lerp value using the cos() function.
     */
    float cosLerp = 1-(cos(time)+1)*0.5f;
	outputColor = mix(firstColor, secondColor, cosLerp);
    

    /*
     * Alternative solutions using if-else clause or ?-operator to compute continuous
     * lerp value.
     *
     
	float currTime = mod(time, fragLoopDuration);
	float currLerp = (currTime / fragLoopDuration);

    
    // compute continuous lerp value using if-else clause.
    if ((currLerp * 2) > 1) {
        currLerp = (1 - currLerp)*2;
    }
    
    // compute continuous lerp value using "?-operator".
    //currLerp = (currLerp * 2 > 1) ? (1-currLerp)*2 : currLerp;
    
	outputColor = mix(firstColor, secondColor, currLerp);
     
    */
    
}
