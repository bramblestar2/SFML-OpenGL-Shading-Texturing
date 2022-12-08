uniform sampler2D texture;


void main()
{
    vec2 textureCoordinates = gl_TexCoord[0].xy;
    vec4 something = vec4(0.5);
    something += texture2D(texture, textureCoordinates);
    gl_FragColor = something;
}

//#version 330 core
//out vec4 FragColor;
//  
//uniform vec4 ourColor;
//
//void main()
//{
//    FragColor = ourColor;
//} 