uniform sampler2D al_tex;
uniform float tint_intensity;
uniform vec3 tint;
varying vec4 varying_color;
varying vec2 varying_texcoord;

uniform bool swapping_colors;
uniform vec4 swap_color_0;
uniform vec4 swap_color_1;
uniform vec4 swap_color_2;
uniform vec4 swap_color_3;

uniform vec4 source_color_1;
//0.408, 0.443, 0.376



//const uvec3 gl_WorkGroupSize

bool near(vec4 colorA, vec4 colorB)
{
  if (abs(colorA.a - colorB.a) > 0.001) return false;
  if (abs(colorA.r - colorB.r) > 0.001) return false;
  if (abs(colorA.g - colorB.g) > 0.001) return false;
  if (abs(colorA.b - colorB.b) > 0.001) return false;
  return true;
}



vec4 swap_color(vec4 color)
{
  const vec4 source_color_0 = vec4(0.098, 0.22, 0.188, 1.0); // dark green
  const vec4 source_color_1 = vec4(0.408, 0.443, 0.376, 1.0); // medium green
  const vec4 source_color_2 = vec4(0.671, 0.647, 0.506, 1.0); // light green
  const vec4 source_color_3 = vec4(0.957, 0.875, 0.667, 1.0); // ultralight tan

  if (near(color, source_color_0)) color = swap_color_0;
  if (near(color, source_color_1)) color = swap_color_1;
  if (near(color, source_color_2)) color = swap_color_2;
  if (near(color, source_color_3)) color = swap_color_3;

  return color;
}



void main()
{
   vec4 tmp = texture2D(al_tex, varying_texcoord);

   if (swapping_colors) tmp = swap_color(tmp);
   gl_FragColor = tmp;
   return;

   float inverse_tint_intensity = 1.0 - tint_intensity;
   tmp.r = (tmp.r * inverse_tint_intensity + tint.r * tint_intensity) * tmp.a;
   tmp.g = (tmp.g * inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
   tmp.b = (tmp.b * inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
   tmp.a = tmp.a;
   gl_FragColor = tmp;
}
