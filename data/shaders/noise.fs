#version 410 core                                                 

uniform sampler2D texture_background; //this is the texture
uniform sampler2D texture_foreground; //this is the texture

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

uniform int texture_blend;

uniform sampler2D colorMap;
uniform sampler2D noiseMap;

in vec2 texCoord;

void main(void)                                                   
{
    vec2 noiseVec;
    
    noiseVec = normalize(texture(noiseMap,texCoord));
    
    noiseVec = (noiseVec * 2.0 - 1) * .035;
    
    gl_FragColor = texture(colorMap, texCoord + noiseVec);
}