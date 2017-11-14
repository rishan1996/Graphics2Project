#shader vertex
#version 330

//Input data from the vbo
in vec2 vertexPosition;
in vec4 vertexColour;
in vec2 vertexUV;

out vec4 fragmentColour;
out vec2 fragmentPosition;
out vec2 fragmentUV;

//Represents the orthographic projection matrix
uniform mat4 projMatrix;

void main(){
	//Set the x, y position on the screen
	gl_Position.xy = (projMatrix * vec4(vertexPosition, 0.0, 1.0)).xy;
	
	//Set z to 0 since 2D
	gl_Position.z = 0.0;
	
	//Indicate that the coordinates are normalized
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;

	fragmentColour = vertexColour;

	//Flip the Y to make the image appear normal
	fragmentUV = vec2(vertexUV.x, 1 - vertexUV.y);
}

#shader fragment
#version 330 
//Fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

//This is a float vector that gets outputted to the 
//screen for each pixel
out vec4 colour;

//A variable to hold the texture
uniform sampler2D myTexture;

void main(){

	vec4 textureColour = texture(myTexture, fragmentUV);

	colour = textureColour * fragmentColour;
	
}