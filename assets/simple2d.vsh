
uniform vec2 Pos;
uniform vec2 Scale;
uniform vec2 Angle;		// *convert to x:sin(theta) and y:cos(theta)
uniform float Width;
uniform float Height;
uniform float Scrollx;
uniform float Scrolly;
	
attribute vec3 aPosition;
attribute vec2 aTextureCoord;
    
varying vec2 vTextureCoord;
void main() {
	gl_Position = vec4(aPosition, 1.0);
    
    
    // Scaling
	gl_Position.x *= Scale.x;
	gl_Position.y *= Scale.y;
    
    // Rotate
	float _x, _y;
	_x = gl_Position.x;
	_y = gl_Position.y;
	gl_Position.x = _x * Angle.y - _y * Angle.x;
	gl_Position.y = _x * Angle.x + _y * Angle.y;

    // Aspect
	gl_Position.x /= Width;
	gl_Position.y /= Height;
    
    // Position
	gl_Position.x += (Pos.x-Scrollx)/Width;
	gl_Position.y += (Pos.y-Scrolly)/Height;
 
    // ViewPort
	gl_Position.x = 2.0*(gl_Position.x-0.5);
	gl_Position.y = -2.0*(gl_Position.y-0.5);
 
 	
	vTextureCoord = aTextureCoord;
}
