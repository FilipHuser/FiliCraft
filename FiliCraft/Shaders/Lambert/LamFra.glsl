#version 330

out vec4 frag_colour;

in vec3 ex_normal;
in vec3 ex_objColor;

void main() {
    
    //Ambient
    float ra = 0.5;
    vec3 ambient = ex_objColor * ra * 0.5;
    
    //Diffuse
    vec3 lightDir = normalize(vec3(5.0, 5.0, -5.0)); // Example light direction
    float diffuseIntensity = max(dot(normalize(-ex_normal), lightDir), 0.0);
    vec3 diffuse = ex_objColor * diffuseIntensity * 0.5;
    
    frag_colour = vec4(ambient + diffuse, 1.0);
}
