precision mediump float;
varying vec2 vTextureCoord;
uniform sampler2D sTexture;
uniform vec4 Color;
	
void main() {
	gl_FragColor = texture2D(sTexture, vTextureCoord);
	//gl_FragColor.rgb /= gl_FragColor.a;
	gl_FragColor.rgba *= Color.rgba;
	
	//gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    
}