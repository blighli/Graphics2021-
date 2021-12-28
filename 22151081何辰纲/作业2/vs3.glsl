#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 color_light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vec3 ourColor = aColor;
	vec2 TexCoord = vec2(aTexCoord.x, aTexCoord.y);

	mat4 mv=view*model;
	mat3 n_mv=mat3(vec3(mv[0]),vec3(mv[1]),vec3(mv[2]));
	vec3 n=normalize(n_mv*aPos);
	vec3 v_pos=vec3(mv*vec4(aPos,1.0));
	vec3 v_light=vec3(view*vec4(lightPos,1.0));

    //ambient
    float amb=0.1;
    vec3 a_out=vec3(amb,amb,amb);

    //diffuse
    vec3 s =normalize(vec3(v_light-v_pos));
    float diff=max(dot(s,n),0.0);
    vec3 d_out=diff*vec3(1.0,1.0,1.0);
    
    //specular
    vec3 v=normalize(-v_pos);
    vec3 r=reflect(s,n);
    float specular=max(dot(r,v),0.0);
    vec3 s_out= pow(specular, 128)*vec3(1.0,1.0,1.0);

    vec3 color_out=a_out+d_out+s_out;
    vec3 result = texture(texture1, TexCoord).xyz;
    result=color_out*result;
    color_light=vec4(result,1.0);
}