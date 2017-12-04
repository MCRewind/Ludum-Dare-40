#version 330 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform float distance;

void main()
{
	outColor = texture(tex, Texcoord);
		if (outColor.a == 0)
			discard;
		if (outColor.r > 1)
			outColor.r = 1;
}
