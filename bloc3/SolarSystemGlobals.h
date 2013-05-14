#ifndef SOLAR_SYSTEM_GLOBALS_H 

const GLfloat PI                    = 3.1415926535;
const GLfloat TO_RADIANS            = PI/180.0;

// Window Position/Resizing Constants
const GLint INIT_WINDOW_POSITION[2] = { 150, 150 };
const GLfloat ASPECT_RATIO          = 1.5;

// Viewer Positioning Constants
const GLfloat MAXIMUM_VIEWER_DISTANCE   = 20;
const GLfloat MINIMUM_VIEWER_DISTANCE   = 2;
const GLfloat INITIAL_VIEWER_DISTANCE   = 10;
const GLfloat VIEWER_DISTANCE_INCREMENT = 0.1;
const GLfloat INITIAL_VIEWER_AZIMUTH    = 0.0;
const GLfloat INITIAL_VIEWER_ZENITH     = PI / 2.0;
const GLfloat VIEWER_ANGLE_INCREMENT    = PI / 60.0;
const GLfloat LOOK_AT_POSITION[]        = { 0.0, 0.0, 0.0 };

/* PLANETS CONSTANTS */
// Earth and Moon Constants
const GLfloat MOON_RADIUS        = 0.04;
const GLfloat MOON_ORBIT_RADIUS  = 0.50;
const GLfloat LUNAR_CYCLE        = 30.0;
const GLfloat EARTH_RADIUS       = 0.18;
const GLfloat EARTH_ROTATION     = 1.00;
const GLfloat EARTH_ORBIT_RADIUS = 3.0;
const GLfloat EARTH_ORBIT_DUR    = 365;
const GLfloat EARTH_INCLINATION  = 7;

// Sun Constants
const GLfloat SUN_RADIUS = 1.0;

// Mercury Constants
const GLfloat MERCURY_RADIUS       = 0.1;
const GLfloat MERCURY_ORBIT_RADIUS = 1.5;
const GLfloat MERCURY_ORBIT_DUR    = 88;
const GLfloat MERCURY_ROTATION_DUR = 59;
const GLfloat MERCURY_INCLINATION  = 7;

// Venus Constants
const GLfloat VENUS_RADIUS       = 0.18;
const GLfloat VENUS_ORBIT_RADIUS = 2.0;
const GLfloat VENUS_ORBIT_DUR    = 225;
const GLfloat VENUS_ROTATION_DUR = -243;
const GLfloat VENUS_INCLINATION  = 3; 

#define SOLAR_SYSTEM_H
#endif