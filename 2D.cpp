#include <windows.h>
#include <stdlib.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <math.h>
#include "stb_image.h"
#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#define PI 3.141592653
#define SCREEN_WIDTH	1920
#define SCREEN_HEIGHT	1080
#define FPS	60

//colors
#define clear glColor4ub(255, 255, 255, 255);
#define white glColor3ub(255, 255, 255);
#define black glColor3ub(0, 0, 0);
#define red_strip glColor3ub(188, 1, 3);
#define yellow_strip glColor3ub(204, 179, 10);
#define beta_dark glColor3ub(79, 79, 81);
#define beta_darker glColor3ub(63, 62, 67);
#define beta_cyan glColor3ub(15, 105, 123);
#define hq_yellow glColor3ub(209, 173, 86);
#define hq_red glColor3ub(201, 78, 64);
#define hq_white glColor3ub(212, 213, 203);
#define hq_beard glColor3ub(165, 180, 175);
#define hq_uniform glColor3ub(160, 130, 105);
#define hq_skin glColor3ub(226, 185, 140);
#define hq_black glColor3ub(37, 39, 40);
#define hq_shoes glColor3ub(116, 84, 72);
#define hq_table_brown glColor3ub(86, 61, 49);
#define hq_table_black glColor3ub(47, 42, 39);
#define hq_chair_mesh glColor3ub(63, 63, 63);
#define hq_chair_black glColor3ub(41, 41, 41);
#define hq_chair_silver glColor3ub(118, 118, 118);
#define hq_monitor_black glColor3ub(62, 62, 62);
#define hq_monitor_blue glColor3ub(0, 120, 215);
#define hq_printer_black glColor3ub(36, 36, 36);
#define hq_printer_black2 glColor3ub(29, 29, 29);
#define hq_printer_black3 glColor3ub(5, 5, 5);
#define hq_building_wall glColor3ub(215, 218, 255);
#define hq_building_floor glColor3ub(92, 92, 92);
#define dr_blue glColor3ub(97, 186, 246);
#define dr_brown glColor3ub(71, 50, 0);
#define dr_hair glColor3ub(71, 71, 71);
#define midnight glClearColor(0.18, 0.18, 0.35, 0.0);
#define navyblue glColor3ub(0, 0, 128);

bool crash, dream;
int scene, sceneA = 0, sceneA2_time = 0, sceneA4_time = 0, sceneDKP_time = 0, current_subtitle, eye_alpha = 0, dkp_alpha = 255, alarm_alpha = 0, visor_alpha = 255, chalk_alpha = 0, chalk_border = 0;
float subtitle_offsetY = .04;
float bouncing_ballX, bouncing_ballY, bouncing_ballDX = 4, bouncing_ballDY = 4;
float sceneA_alphaX, sceneA_alphaY, sceneA_alphaR, sceneA_alphaSX = 1, sceneA_alphaSY = 1;
float sceneA_clockX, sceneA_clockY, sceneA_clockSX = 1, sceneA_clockSY = 1, sceneA_clockMins = 0, sceneA_clockHrs = 30;
float sceneA2_hqX, sceneA2_hqY, sceneA2_hqR, sceneA2_hqSX = 1, sceneA2_hqSY = 1;
float sceneA4_hqY, sceneA4_alphaX, sceneA4_alpha_upperarmL, sceneA4_alpha_lowerarmL;
float sceneDKP_drX, sceneDKP_drY, sceneDKP_drR, sceneDKP_drUpperarmL, sceneDKP_drLowerarmL;
float sceneDKP_studentX, sceneDKP_studentY, sceneDKP_studentR, sceneDKP_studentUpperarmR, sceneDKP_studentLowerarmR;
float sceneDKP_chalkX, sceneDKP_chalkY, sceneDKP_chalkR;
float sceneCloseUp_deadX, sceneCloseUp_deadY, sceneCloseUp_deadR, sceneCloseUp_betaR;
float elapsed_time = 0, sceneDKP_timer, sceneCloseUp_timer, sceneCD8_timer, sceneHQ_timer;
float dreamScale;

float X, Y = 0;
float Y_after = 0;
float r_angle = 0;

float scene1X, scene1Y, scene1R, scene1SX = 1, scene1SY = 1;
float scene2X, scene2Y, scene2R, scene2SX = 1, scene2SY = 1;

int CD8_alpha = 0;
float sceneCD2_alphaX, sceneCD2_alphaY, sceneCD2_alphaR, sceneCD2_alphaSX = 1, sceneCD2_alphaSY = 1;
float sceneCD2_betaX, sceneCD2_betaY, sceneCD2_betaR, sceneCD2_betaSX = 1, sceneCD2_betaSY = 1;
float sceneCD3_alphaX, sceneCD3_alphaY, sceneCD3_alphaR, sceneCD3_alphaSX = 1, sceneCD3_alphaSY = 1;
float sceneCD3_betaX, sceneCD3_betaY, sceneCD3_betaR, sceneCD3_betaSX = 1, sceneCD3_betaSY = 1;
float sceneCD4_alphaX, sceneCD4_alphaY, sceneCD4_alphaR, sceneCD4_alphaSX = 1, sceneCD4_alphaSY = 1;
float sceneCD5_alphaX, sceneCD5_alphaY, sceneCD5_alphaR, sceneCD5_alphaSX = 1, sceneCD5_alphaSY = 1;
float sceneCD6_alphaX, sceneCD6_alphaY, sceneCD6_alphaR, sceneCD6_alphaSX = 1, sceneCD6_alphaSY = 1;
float sceneCD7_alphaX, sceneCD7_alphaY, sceneCD7_alphaR, sceneCD7_alphaSX = 1, sceneCD7_alphaSY = 1;
float sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, sceneCD_deadSX = 1, sceneCD_deadSY = 1;

float kubidspike = 0;
float sceneKubid20X, sceneKubid20Y, sceneKubid20SX = 1, sceneKubid20R, sceneKubid20SY = 1;
float sceneKubid20X1, sceneKubid20Y1, sceneKubid20SX1 = 1, sceneKubid20R1, sceneKubid20SY1 = 1;
float sceneKubid20X2, sceneKubid20Y2, sceneKubid20SX2 = 1, sceneKubid20R2, sceneKubid20SY2 = 1;
float sceneKubid20X3, sceneKubid20Y3, sceneKubid20SX3 = 1, sceneKubid20R3, sceneKubid20SY3 = 1;
float sceneKubid20X4, sceneKubid20Y4, sceneKubid20SX4 = 1, sceneKubid20R4, sceneKubid20SY4 = 1;
float sceneKubid20X5, sceneKubid20Y5, sceneKubid20SX5 = 1, sceneKubid20R5, sceneKubid20SY5 = 1;
float sceneKubid20X6, sceneKubid20Y6, sceneKubid20SX6 = 1, sceneKubid20R6, sceneKubid20SY6 = 1;

//TEXTURES FOR SCENE CD1======================================================================================================================================================================================
unsigned char* tex_windows, * tex_floor, * tex_ceiling;
int tex_windowsX, tex_windowsY, tex_floorX, tex_floorY, tex_ceilingX, tex_ceilingY;

//END OF SCENE CD1============================================================================================================================================================================================

//test var
float sceneB_alphaX, sceneB_alphaY, sceneB_alphaR, sceneB_alphaSX = 1, sceneB_alphaSY = 1;
float sceneC_hqX, sceneC_hqY, sceneC_hqR, sceneC_hqSX = 1, sceneC_hqSY = 1;
float sceneCD_alphaX, sceneCD_alphaY, sceneCD_alphaR, sceneCD_alphaSX = 1, sceneCD_alphaSY = 1;
float sceneCD_betaX, sceneCD_betaY, sceneCD_betaR, sceneCD_betaSX = 1, sceneCD_betaSY = 1;

//textures
unsigned char* tex_nasa, * tex_nasa_old, * tex_ribbon, * tex_space, * tex_clock, * tex_monitor_rear, * tex_monitor_main, * tex_skull, * tex_game, * tex_bsod, * tex_word;
int tex_nasaX, tex_nasaY, tex_nasa_oldX, tex_nasa_oldY, tex_ribbonX, tex_ribbonY, tex_spaceX, tex_spaceY, tex_clockX, tex_clockY, tex_monitor_rearX, tex_monitor_rearY, tex_monitor_mainX, tex_monitor_mainY, tex_bsodX, tex_bsodY, tex_skullX, tex_skullY, tex_gameX, tex_gameY, tex_wordX, tex_wordY;
int tex_X, tex_Y;

unsigned char* tex_loader(string file)
{
	int numColCh;
	unsigned char* bytes = stbi_load(file.c_str(), &tex_X, &tex_Y, &numColCh, 0);

	return bytes;
	stbi_image_free(bytes);
}

void rectangle_texture(int x, int y, int w, int h, unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(x, y);
	glTexCoord2i(1, 0); glVertex2i(x + w, y);
	glTexCoord2i(1, 1); glVertex2i(x + w, y + h);
	glTexCoord2i(0, 1); glVertex2i(x, y + h);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void rectangle(int x, int y, int w, int h, bool border) {
	if (border == 1)
	{
		black;
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
	}
	else
		glBegin(GL_POLYGON);

	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

void rectangle_gradient(int x, int y, int w, int h, bool border, int r1, int g1, int b1, int r2, int g2, int b2) {
	if (border == 1)
	{
		black;
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
	}
	else
		glBegin(GL_POLYGON);

	glColor3ub(r1, g1, b1);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glColor3ub(r2, g2, b2);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

void triangle(int x, int y, int w, int h, bool border) {
	if (border == 1)
	{
		black;
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
	}
	else
		glBegin(GL_POLYGON);

	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + (w / 2.0), y - h);
	glEnd();
}

void triangle_upcenter(int x, int y, int w, int h, bool border) {
	if (border == 1)
	{
		black;
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
	}
	else
		glBegin(GL_POLYGON);

	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w / 2, h);
	glEnd();
}

void righttriangle(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);

	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x, y + h);
	glEnd();
}

void nGon(int n, int x, int y, int r, bool border) {
	double inc = 2 * PI / (double)n;

	if (border == 1)
	{
		black;
		glBegin(GL_LINE_LOOP);
	}
	else
		glBegin(GL_POLYGON);

	for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
		glVertex2i(r * cos(theta) + x, r * sin(theta) + y);
	}
	glEnd();
}

void lines(int x1, int y1, int x2, int y2, int width) {
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

void house(int x, int y, int w) {
	int h = 0.75 * w;
	// draw body
	glColor3ub(0, 150, 250);
	rectangle(x, y, w, h, 0);
	// draw door
	glColor3ub(200, 250, 0);
	rectangle(x + w / 2 - w / 10, y, w / 5, h / 2, 0);
	// draw left window
	glColor3ub(200, 250, 200);
	rectangle(x + w / 8, y + h / 2, w / 5, w / 5, 0);
	// draw right window
	glColor3ub(200, 250, 200);
	rectangle(x + w - (w / 8 + w / 5), y + h / 2, w / 5, w / 5, 0);
	glColor3ub(0, 0, 0);
	// draw roof
	glColor3ub(200, 25, 20);
	glBegin(GL_POLYGON);
	//glBegin(GL_LINE_LOOP);
	glVertex2i(x - w / 8, y + h);
	glVertex2i(x + w + w / 8, y + h);
	glVertex2i(x + w, y + h + h / 2);
	glVertex2i(x, y + h + h / 2);
	glEnd();
}

void subtitle(const char* string, int y)
{
	size_t len;
	int i, w;
	len = (size_t)strlen(string);
	w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)string);

	black;
	rectangle((SCREEN_WIDTH / 2 - w / 2) - w * .05, y * .7, w + w * 0.1, y * 1, 0);

	white;
	glRasterPos2f(SCREEN_WIDTH / 2 - w / 2, y);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//stack order: top = back
void chara_alpha(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   HEAD     */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.3), w * .75, w * .85, 0);
	//visor
	glColor3ub(149, 61, 61);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.3), w * .75, w * .85, 1);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 1);
	//forehead
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.8), w * .82, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .17), y + (w * 1.735), w * .38, w * .33, 0);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .31), y + (w * 2), w * .05, w * .145, 0);
	rectangle(x + (w / 2.0) + (w * .29), y + (w * 2), w * .05, w * .145, 0);

	/****************/
	/*	   BODY     */
	/****************/
	white;
	rectangle(x, y, w, w * 1.15, 0);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .49), y + (w * .18), w * 0.99, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .49), y + (w * .55), w * 0.23, w * .23, 0);
	rectangle(x + (w / 2.0) + (w * .24), y + (w * .55), w * 0.26, w * .23, 0);
	rectangle(x + (w / 2.0) - (w * .30), y + (w * .18), w * 0.05, w * .6, 0);
	rectangle(x + (w / 2.0) + (w * .24), y + (w * .18), w * 0.05, w * .6, 0);
	//body mid
	white;
	rectangle(x + (w / 2.0) - (w * .12), y, w * .25, w * 1.15, 0);
	rectangle(x + (w / 2.0) - (w * .07), y + (w * .05), w * .155, w * 1.02, 0);
	//chest
	black;
	rectangle(x + (w / 2.0) - (w * .49), y + (w * .6), w * 0.2, w * .13, 0);
	rectangle(x + (w / 2.0) + (w * .29), y + (w * .6), w * 0.21, w * .13, 0);
	rectangle(x, y, w, w * 1.15, 1);
	rectangle(x + (w / 2.0) - (w * .12), y, w * .25, w * 1.13, 1);
	rectangle(x + (w / 2.0) - (w * .07), y + (w * .05), w * .155, w * 1.02, 1);
	//shoulder
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) - (w * .53), y + (w * 1.02), w * 0.31, w * .17, 0);
	rectangle(x + (w / 2.0) + (w * .23), y + (w * 1.02), w * 0.31, w * .17, 0);
	rectangle(x + (w / 2.0) - (w * .53), y + (w * 1.02), w * 0.31, w * .17, 1);
	rectangle(x + (w / 2.0) + (w * .23), y + (w * 1.02), w * 0.31, w * .17, 1);
	white;
	rectangle(x + (w / 2.0) - (w * .42), y + (w * 1.02), w * 0.12, w * .19, 0);
	rectangle(x + (w / 2.0) + (w * .31), y + (w * 1.02), w * 0.12, w * .19, 0);
	rectangle(x + (w / 2.0) - (w * .42), y + (w * 1.02), w * 0.12, w * .19, 1);
	rectangle(x + (w / 2.0) + (w * .31), y + (w * 1.02), w * 0.12, w * .19, 1);
	//circle
	//12
	//34
	glColor3ub(116, 116, 106);
	nGon(64, x + (w / 2.0) - (w * .36), y + (w * .98), w * .08, 0);
	nGon(64, x + (w / 2.0) + (w * .37), y + (w * .98), w * .08, 0);
	nGon(64, x + (w / 2.0) - (w * .27), y + (w * .21), w * .08, 0);
	nGon(64, x + (w / 2.0) + (w * .27), y + (w * .21), w * .08, 0);

	//circle border
	nGon(64, x + (w / 2.0) - (w * .36), y + (w * .98), w * .08, 1);
	nGon(64, x + (w / 2.0) - (w * .36), y + (w * .98), w * .045, 1);

	nGon(64, x + (w / 2.0) + (w * .37), y + (w * .98), w * .08, 1);
	nGon(64, x + (w / 2.0) + (w * .37), y + (w * .98), w * .045, 1);

	nGon(64, x + (w / 2.0) - (w * .27), y + (w * .21), w * .08, 1);
	nGon(64, x + (w / 2.0) - (w * .27), y + (w * .21), w * .045, 1);

	nGon(64, x + (w / 2.0) + (w * .27), y + (w * .21), w * .08, 1);
	nGon(64, x + (w / 2.0) + (w * .27), y + (w * .21), w * .045, 1);

	/****************/
	/*	   HIP      */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .86), w * 0.9, w * .86, 0);
	black;
	rectangle(x + (w / 2.0) - (w * .06), y - (w * .86), w * .13, w * .86, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .3), w * .18, w * .3, 0);
	rectangle(x + (w / 2.0) + (w * .28), y - (w * .3), w * .18, w * .3, 0);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .30), y - (w * .855), w * 0.05, w * .86, 0);
	rectangle(x + (w / 2.0) + (w * .24), y - (w * .855), w * 0.05, w * .86, 0);
	//belt
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .86), w * 0.9, w * .86, 1);
	white;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * .35), w * .28, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .19), y - (w * .35), w * .3, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * .35), w * .28, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .19), y - (w * .35), w * .3, w * .16, 1);

	/****************/
	/*	   NECK     */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.13), w * .45, w * .12, 0);
	black;
	rectangle(x + (w / 2.0) - (w * .06), y + (w * 1.13), w * .13, w * .12, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.13), w * .45, w * .12, 1);

	/****************/
	/*	UPPERARM_L  */
	/****************/
	glPushMatrix();

	glTranslatef(x - (w * .2), y + (w * .95), 0);
	glRotatef(rotate_shoulderL, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .95)), 0);

	white;
	rectangle(x - (w * .32), y + (w * .27), w * 0.265, w * .85, 0);
	red_strip;
	rectangle(x - (w * .315), y + (w * .275), w * 0.255, w * .05, 0);
	black;
	rectangle(x - (w * .2), y + (w * .69), w * 0.14, w * .43, 0);
	rectangle(x - (w * .32), y + (w * .27), w * 0.265, w * .85, 1);

	/****************/
	/*	LOWERARM_L  */
	/****************/
	glTranslatef(x - (w * .2), y + (w * .18), 0);
	glRotatef(rotate_elbowL, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .18)), 0);

	white;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 0);
	black;
	rectangle(x - (w * .3), y + (w * .10), w * 0.225, w * .17, 0);
	//strips
	glColor3ub(188, 188, 203);
	rectangle(x - (w * .315), y - (w * .55), w * 0.255, w * .05, 0);
	red_strip;
	rectangle(x - (w * .315), y + (w * .04), w * 0.255, w * .05, 0);
	//hand
	glColor3ub(151, 153, 136);
	rectangle(x - (w * .26), y - (w * .86), w * 0.2, w * .24, 0);
	rectangle(x - (w * .26), y - (w * .86), w * 0.2, w * .24, 1);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 1);

	glPopMatrix();

	/****************/
	/*	UPPERARM_R  */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w * 1.18), y + (w * .95), 0);
	glRotatef(rotate_shoulderR, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .95)), 0);

	white;
	rectangle(x + (w * 1.06), y + (w * .27), w * 0.265, w * .85, 0);
	red_strip;
	rectangle(x + (w * 1.065), y + (w * .275), w * 0.255, w * .05, 0);
	black;
	rectangle(x + (w * 1.06), y + (w * .69), w * 0.14, w * .43, 0);
	rectangle(x + (w * 1.06), y + (w * .27), w * 0.265, w * .85, 1);

	/****************/
	/*	LOWERARM_R  */
	/****************/
	glTranslatef(x + (w * 1.18), y + (w * .18), 0);
	glRotatef(rotate_elbowR, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .18)), 0);

	white;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 0);
	black;
	rectangle(x + (w * 1.08), y + (w * .10), w * 0.225, w * .17, 0);
	//strips
	glColor3ub(188, 188, 203);
	rectangle(x + (w * 1.065), y - (w * .55), w * 0.255, w * .05, 0);
	red_strip;
	rectangle(x + (w * 1.065), y + (w * .04), w * 0.255, w * .05, 0);
	//hand
	glColor3ub(151, 153, 136);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.2, w * .24, 0);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.2, w * .24, 1);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 1);

	glPopMatrix();

	/****************/
	/*	  THIGH_L   */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * .9), 0);
	glRotatef(rotate_hipL, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * .9)), 0);

	white;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 1.75), w * 0.35, w * .83, 0);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .30), y - (w * 1.74), w * 0.05, w * .82, 0);
	//strap
	white;
	rectangle(x + (w / 2.0) - (w * .35), y - (w * 1.67), w * 0.15, w * .06, 0);
	rectangle(x + (w / 2.0) - (w * .35), y - (w * 1.67), w * 0.15, w * .06, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 1.75), w * 0.35, w * .83, 1);

	/****************/
	/*	  CALF_L    */
	/****************/
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * 1.75), 0);
	glRotatef(rotate_kneeL, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * 1.75)), 0);

	white;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.54), w * 0.35, w * .47, 0);
	//knee
	glColor3ub(233, 230, 226);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * .33, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * .33, 1);
	rectangle(x + (w / 2.0) - (w * .4), y - (w * 2.075), w * 0.245, w * .33, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.54), w * 0.35, w * .47, 1);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .30), y - (w * 2.535), w * 0.05, w * .46, 0);
	//boot
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .86, 0);
	glColor3ub(116, 116, 106);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .86, 1);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.17), w * 0.42, w * .5, 1);
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 3.17), w * 0.1, w * .63, 0);
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 3.17), w * 0.1, w * .63, 1);

	glPopMatrix();

	/****************/
	/*	  THIGH_R   */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * .9), 0);
	glRotatef(rotate_hipR, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * .9)), 0);

	white;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.75), w * 0.35, w * .83, 0);
	red_strip;
	rectangle(x + (w / 2.0) + (w * .24), y - (w * 1.74), w * 0.05, w * .82, 0);
	//strap
	white;
	rectangle(x + (w / 2.0) + (w * .19), y - (w * 1.67), w * 0.15, w * .06, 0);
	rectangle(x + (w / 2.0) + (w * .19), y - (w * 1.67), w * 0.15, w * .06, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.75), w * 0.35, w * .83, 1);

	/****************/
	/*	  CALF_R    */
	/****************/
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * 1.75), 0);
	glRotatef(rotate_kneeR, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * 1.75)), 0);

	white;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.54), w * 0.35, w * .47, 0);
	//knee
	glColor3ub(233, 230, 226);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * .33, 0);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * .33, 1);
	rectangle(x + (w / 2.0) + (w * .15), y - (w * 2.075), w * 0.245, w * .33, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.54), w * 0.35, w * .47, 1);
	red_strip;
	rectangle(x + (w / 2.0) + (w * .24), y - (w * 2.535), w * 0.05, w * .46, 0);
	//boot
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .86, 0);
	glColor3ub(116, 116, 106);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .86, 1);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.17), w * 0.42, w * .5, 1);
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) + (w * .215), y - (w * 3.17), w * 0.1, w * .63, 0);
	rectangle(x + (w / 2.0) + (w * .215), y - (w * 3.17), w * 0.1, w * .63, 1);

	glPopMatrix();
	glPopMatrix();
}

void chara_beta(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   HEAD     */
	/****************/
	beta_dark;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.3), w * .75, w * .85, 0);
	//visor
	glColor3ub(135, 135, 135);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.3), w * .75, w * .85, 1);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 1);
	//forehead
	beta_darker;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.8), w * .82, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.8), w * .82, w * .2, 1);
	yellow_strip;
	rectangle(x + (w / 2.0) - (w * .08), y + (w * 2.05), w * .2, w * .095, 0);
	beta_darker;
	rectangle(x + (w / 2.0) - (w * .17), y + (w * 1.735), w * .38, w * .33, 0);
	yellow_strip;
	rectangle(x + (w / 2.0) - (w * .04), y + (w * 1.89), w * .13, w * .165, 0);
	rectangle(x + (w / 2.0) - (w * .17), y + (w * 1.735), w * .38, w * .33, 1);

	/****************/
	/*	   BODY     */
	/****************/
	beta_dark;
	rectangle(x, y - (w * .7), w, w * 1.4, 0);
	rectangle(x, y - (w * .7), w, w * 1.4, 1);
	rectangle(x, y - (w * .7), w, w * .18, 1);
	rectangle(x, y - (w * .52), w * .18, w, 1);
	rectangle(x + (w / 2.0) + (w * .325), y - (w * .52), w * .18, w, 1);
	//chest
	beta_darker;
	rectangle(x - (w * .02), y + (w * .695), w * 1.045, w * .48, 0);
	yellow_strip;
	rectangle(x - (w * .02), y + (w * 1.12), w * 1.045, w * .05, 0);
	rectangle(x - (w * .02), y + (w * .695), w * 1.045, w * .48, 1);
	beta_cyan;
	rectangle(x + (w / 2.0) - (w * .08), y + (w * .61), w * .17, w * .17, 0);
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .7), w * .1, w * 1.31, 0);
	rectangle(x + (w / 2.0) - (w * .08), y + (w * .61), w * .17, w * .17, 1);
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .7), w * .1, w * 1.31, 1);
	//shoulder
	beta_darker;
	rectangle(x + (w / 2.0) - (w * .45), y + (w * .66), w * 0.17, w * .55, 0);
	yellow_strip;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * .66), w * 0.05, w * .15, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * .85), w * 0.05, w * .36, 0);
	rectangle(x + (w / 2.0) - (w * .45), y + (w * .66), w * 0.17, w * .55, 1);
	beta_darker;
	rectangle(x + (w / 2.0) + (w * .29), y + (w * .66), w * 0.17, w * .55, 0);
	yellow_strip;
	rectangle(x + (w / 2.0) + (w * .35), y + (w * .66), w * 0.05, w * .15, 0);
	rectangle(x + (w / 2.0) + (w * .35), y + (w * .85), w * 0.05, w * .36, 0);
	rectangle(x + (w / 2.0) + (w * .29), y + (w * .66), w * 0.17, w * .55, 1);

	/****************/
	/*	   HIP      */
	/****************/
	beta_darker;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .86), w * 0.9, w * .165, 0);
	beta_dark;
	rectangle(x + (w / 2.0) - (w * .32), y - (w * .86), w * .64, w * .165, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .86), w * 0.9, w * .165, 1);
	beta_dark;
	rectangle(x + (w / 2.0) - (w * .32), y - (w * .86), w * .64, w * .165, 1);

	/****************/
	/*	   NECK     */
	/****************/
	beta_darker;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 0);
	yellow_strip;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.12), w * .05, w * .13, 0);
	rectangle(x + (w / 2.0) + (w * .18), y + (w * 1.12), w * .05, w * .13, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 1);

	/****************/
	/*	UPPERARM_L  */
	/****************/
	glPushMatrix();

	glTranslatef(x - (w * .2), y + (w * .95), 0);
	glRotatef(rotate_shoulderL, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .95)), 0);

	beta_darker;
	rectangle(x - (w * .4), y + (w * .39), w * 0.34, w * .71, 0);
	yellow_strip;
	rectangle(x - (w * .4), y + (w * .8), w * 0.05, w * .3, 0);
	rectangle(x - (w * .4), y + (w * 1.04), w * 0.34, w * .05, 0);
	rectangle(x - (w * .4), y + (w * .39), w * 0.34, w * .71, 1);
	beta_dark;
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w * .61, 0);
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w * .61, 1);
	beta_cyan;
	rectangle(x - (w * .32), y + (w * .42), w * 0.265, w * .1, 0);
	rectangle(x - (w * .32), y + (w * .42), w * 0.265, w * .1, 1);

	/****************/
	/*	LOWERARM_L  */
	/****************/
	glTranslatef(x - (w * .2), y + (w * .09), 0);
	glRotatef(rotate_elbowL, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .09)), 0);

	beta_darker;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 0);
	yellow_strip;
	rectangle(x - (w * .32), y - (w * .8), w * 0.05, w * .9, 0);
	//hand
	beta_dark;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 1);

	glPopMatrix();

	/****************/
	/*	UPPERARM_R  */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w * 1.18), y + (w * .95), 0);
	glRotatef(rotate_shoulderR, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .95)), 0);

	beta_darker;
	rectangle(x + (w * 1.06), y + (w * .39), w * 0.34, w * .71, 0);
	yellow_strip;
	rectangle(x + (w * 1.34), y + (w * .8), w * 0.05, w * .3, 0);
	rectangle(x + (w * 1.06), y + (w * 1.04), w * 0.34, w * .05, 0);
	rectangle(x + (w * 1.06), y + (w * .39), w * 0.34, w * .71, 1);
	beta_dark;
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w * .61, 0);
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w * .61, 1);
	beta_cyan;
	rectangle(x + (w * 1.06), y + (w * .42), w * 0.265, w * .1, 0);
	rectangle(x + (w * 1.06), y + (w * .42), w * 0.265, w * .1, 1);

	/****************/
	/*	LOWERARM_R  */
	/****************/
	glTranslatef(x + (w * 1.18), y + (w * .09), 0);
	glRotatef(rotate_elbowR, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .09)), 0);

	beta_darker;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 0);
	yellow_strip;
	rectangle(x + (w * 1.265), y - (w * .8), w * 0.05, w * .9, 0);
	//hand
	beta_dark;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 1);

	glPopMatrix();

	/****************/
	/*	  THIGH_L   */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * .9), 0);
	glRotatef(rotate_hipL, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * .9)), 0);

	beta_darker;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	beta_dark;
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 1.42), w * 0.22, w * .5, 0);
	//strap
	beta_cyan;
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 1.08), w * 0.22, w * .08, 0);
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 1.08), w * 0.22, w * .08, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 1);
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 1.42), w * 0.22, w * .5, 1);

	/****************/
	/*	  CALF_L    */
	/****************/
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * 2.075), 0);
	glRotatef(rotate_kneeL, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * 2.075)), 0);

	beta_darker;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.95), w * 0.35, w * .875, 0);
	//boot
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .45, 0);
	yellow_strip;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3), w * 0.1, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .17), y - (w * 3), w * 0.1, w * .05, 0);
	beta_dark;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .45, 1);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.33), w * 0.42, w * .15, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.95), w * 0.35, w * .875, 1);

	glPopMatrix();

	/****************/
	/*	  THIGH_R   */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * .9), 0);
	glRotatef(rotate_hipR, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * .9)), 0);

	beta_darker;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	beta_dark;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.42), w * 0.22, w * .5, 0);
	//strap
	beta_cyan;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.08), w * 0.22, w * .08, 0);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.08), w * 0.22, w * .08, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.42), w * 0.22, w * .5, 1);

	/****************/
	/*	  CALF_R    */
	/****************/
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * 2.075), 0);
	glRotatef(rotate_kneeR, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * 2.075)), 0);

	beta_darker;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.95), w * 0.35, w * .875, 0);
	//boot
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .45, 0);
	yellow_strip;
	rectangle(x + (w / 2.0) + (w * .38), y - (w * 3), w * 0.1, w * .05, 0);
	rectangle(x + (w / 2.0) + (w * .07), y - (w * 3), w * 0.1, w * .05, 0);
	beta_dark;
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .45, 1);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.33), w * 0.42, w * .15, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.95), w * 0.35, w * .875, 1);

	glPopMatrix();
	glPopMatrix();
}

void chara_hq_lowerarmL(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x - (w * .2), y + (w * .09), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .09)), 0);

	/****************/
	/*	LOWERARM_L  */
	/****************/
	hq_uniform;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 0);
	//hand
	hq_white;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 1);
	hq_red;
	rectangle(x - (w * .36), y - (w * .62), w * 0.34, w * .23, 0);
	rectangle(x - (w * .36), y - (w * .62), w * 0.34, w * .23, 1);

	glPopMatrix();
}

void chara_hq_lowerarmR(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w * 1.18), y + (w * .09), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .09)), 0);

	/****************/
	/*	LOWERARM_R  */
	/****************/
	hq_uniform;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 0);
	//hand
	hq_white;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 1);
	hq_red;
	rectangle(x + (w * 1.02), y - (w * .62), w * 0.34, w * .23, 0);
	rectangle(x + (w * 1.02), y - (w * .62), w * 0.34, w * .23, 1);

	glPopMatrix();
}

void chara_hq_upperarmL(int x, int y, int w, int tx, int ty, float rotate, float rotate_elbowL, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x - (w * .2), y + (w * .95), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .95)), 0);

	/****************/
	/*	UPPERARM_L  */
	/****************/
	hq_uniform;
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w, 0);
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w, 1);

	chara_hq_lowerarmL(x, y, w, tx, ty, rotate_elbowL, sx, sy);
	glPopMatrix();
}

void chara_hq_upperarmR(int x, int y, int w, int tx, int ty, float rotate, float rotate_elbowR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w * 1.18), y + (w * .95), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .95)), 0);

	/****************/
	/*	UPPERARM_R  */
	/****************/
	hq_uniform;
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w, 0);
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w, 1);

	chara_hq_lowerarmR(x, y, w, tx, ty, rotate_elbowR, sx, sy);
	glPopMatrix();
}

void chara_hq_calfL(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * 2.075), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * 2.075)), 0);

	/****************/
	/*	  CALF_L    */
	/****************/
	hq_shoes;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .23, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 0);
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 3.17), w * 0.35, w * 1.095, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .23, 1);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 3.17), w * 0.35, w * 1.095, 1);

	glPopMatrix();
}

void chara_hq_calfR(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * 2.075), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * 2.075)), 0);

	/****************/
	/*	  CALF_R    */
	/****************/
	hq_shoes;
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .23, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 0);
	hq_uniform;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 3.17), w * 0.35, w * 1.095, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .23, 1);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 3.17), w * 0.35, w * 1.095, 1);

	glPopMatrix();
}

void chara_hq_thighL(int x, int y, int w, int tx, int ty, float rotate, float rotate_kneeL, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * .9), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * .9)), 0);

	/****************/
	/*	  THIGH_L   */
	/****************/
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 1);

	chara_hq_calfL(x, y, w, tx, ty, rotate_kneeL, sx, sy);
	glPopMatrix();
}

void chara_hq_thighR(int x, int y, int w, int tx, int ty, float rotate, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * .9), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * .9)), 0);

	/****************/
	/*	  THIGH_R   */
	/****************/
	hq_uniform;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 1);

	chara_hq_calfR(x, y, w, tx, ty, rotate_kneeR, sx, sy);
	glPopMatrix();
}

void chara_hq(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   BODY     */
	/****************/
	hq_uniform;
	rectangle(x, y - (w * .86), w, w * 1.96, 0);
	rectangle(x, y - (w * .86), w, w * 1.96, 1);
	//shoulder
	hq_white;
	rectangle(x + (w / 2.0) - (w * .48), y + (w * 1.03), w * 0.13, w * .1, 0);
	rectangle(x + (w / 2.0) + (w * .35), y + (w * 1.03), w * 0.13, w * .1, 0);
	rectangle(x + (w / 2.0) - (w * .48), y + (w * 1.03), w * 0.13, w * .1, 1);
	rectangle(x + (w / 2.0) + (w * .35), y + (w * 1.03), w * 0.13, w * .1, 1);
	//pocket
	hq_yellow;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * .55), w * .25, w * .05, 0);
	rectangle(x + (w / 2.0) + (w * .17), y + (w * .55), w * .25, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * .55), w * .25, w * .05, 1);
	rectangle(x + (w / 2.0) + (w * .17), y + (w * .55), w * .25, w * .05, 1);
	//ribbon
	clear;
	rectangle_texture(x + (w / 2.0) + (w * .12), y + (w * .65), w * .36, w * .3, tex_ribbon, tex_ribbonX, tex_ribbonY);
	//rectangle_texture(x + (w / 2.0) - (w * .37), y - (w * .5), w * .35, w * .3, tex_space, tex_spaceX, tex_spaceY);
	//rectangle_texture(x + (w / 2.0) - (w * .37), y + (w * .65), w * .35, w * .3, tex_space, tex_spaceX, tex_spaceY);
	//rectangle_texture(x + (w / 2.0) - (w * .37), y - (w * .8), w * .35, w * .3, tex_space, tex_spaceX, tex_spaceY);

	/****************/
	/*	   NECK     */
	/****************/
	hq_black;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 1);
	hq_red;
	rectangle(x + (w / 2.0) - (w * .24), y + (w * 1.03), w * .1, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.03), w * .1, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .24), y + (w * 1.03), w * .1, w * .2, 1);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.03), w * .1, w * .2, 1);
	//chest
	hq_yellow;
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .86), w * .1, w * 2.115, 0);
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .86), w * .1, w * 2.115, 1);
	rectangle(x + (w / 2.0), y - (w * .86), 0, w * 2.115, 1);

	/****************/
	/*	   HEAD     */
	/****************/
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 1);
	hq_beard;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 0);
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.48), w * .63, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 1);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.48), w * .63, w * .5, 1);
	black;
	rectangle(x + (w / 2.0) - (w * .15), y + (w * 1.35), w * .31, w * .04, 0);
	//eye
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.65), w * .07, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .19), y + (w * 1.65), w * .07, w * .07, 0);
	hq_beard;
	rectangle(x + (w / 2.0) + (w * .1), y + (w * 1.72), w * .18, w * .04, 0);
	rectangle(x + (w / 2.0) - (w * .25), y + (w * 1.72), w * .18, w * .04, 0);
	rectangle(x + (w / 2.0) + (w * .1), y + (w * 1.72), w * .18, w * .04, 1);
	rectangle(x + (w / 2.0) - (w * .25), y + (w * 1.72), w * .18, w * .04, 1);
	//hat
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .35, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .35, 1);
	hq_black;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .14, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .14, 1);
	hq_yellow;
	triangle(x + (w / 2.0) - (w * .11), y + (w * 2.15), w * .24, w * .23, 0);
	triangle(x + (w / 2.0) - (w * .11), y + (w * 2.15), w * .24, w * .23, 1);

	chara_hq_thighL(x, y, w, 0, 0, rotate_hipL, rotate_kneeL, sx, sy);
	chara_hq_thighR(x, y, w, 0, 0, rotate_hipR, rotate_kneeR, sx, sy);
	chara_hq_upperarmL(x, y, w, 0, 0, rotate_shoulderL, rotate_elbowL, sx, sy);
	chara_hq_upperarmR(x, y, w, 0, 0, rotate_shoulderR, rotate_elbowR, sx, sy);

	glPopMatrix();
	////origin thigh
	//rectangle(x + (w / 2.0) - (w * .3), y - (w * .9), w * 0.1, w * .1, 1);
	//rectangle(x + (w / 2.0) + (w * .25), y - (w * .9), w * 0.1, w * .1, 1);
	////calf
	//rectangle(x + (w / 2.0) - (w * .3), y - (w * 2.075), w * 0.1, w * .1, 1);
	//rectangle(x + (w / 2.0) + (w * .25), y - (w * 2.075), w * 0.1, w * .1, 1);
	////upperarm
	//rectangle(x - (w * .2), y + (w * .95), w * 0.1, w * 0.1, 1);
	//rectangle(x + (w * 1.18), y + (w * .95), w * 0.1, w * 0.1, 1);
	////forearml
	//rectangle(x - (w * .2), y + (w * .09), w * 0.1, w * 0.1, 1);
	//rectangle(x + (w * 1.18), y + (w * .09), w * 0.1, w * 0.1, 1);
}

void chara_hq_back(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   BODY     */
	/****************/
	hq_uniform;
	rectangle(x, y - (w * .86), w, w * 1.96, 0);
	rectangle(x, y - (w * .86), w, w * 1.96, 1);

	/****************/
	/*	   NECK     */
	/****************/
	hq_black;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 1);
	hq_red;
	rectangle(x + (w / 2.0) - (w * .24), y + (w * 1.03), w * .1, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.03), w * .1, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .24), y + (w * 1.03), w * .1, w * .2, 1);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.03), w * .1, w * .2, 1);

	/****************/
	/*	   HEAD     */
	/****************/
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 1);
	black;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 1);
	black;
	rectangle(x + (w / 2.0) - (w * .15), y + (w * 1.35), w * .31, w * .04, 0);
	//hat
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .35, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .35, 1);
	hq_black;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .14, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .14, 1);

	chara_hq_calfL(x, y * 1.4, w, 0, 0, rotate_kneeL, sx, sy);
	chara_hq_calfR(x, y * 1.4, w, 0, 0, rotate_kneeR, sx, sy);
	chara_hq_upperarmL(x, y, w, 0, 0, rotate_shoulderL, 90, sx, sy);
	chara_hq_upperarmR(x, y, w, 0, 0, rotate_shoulderR, -90, sx, sy);

	glPopMatrix();
}

void chara_hq_back2(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   BODY     */
	/****************/
	hq_uniform;
	rectangle(x, y - (w * .86), w, w * 1.96, 0);
	rectangle(x, y - (w * .86), w, w * 1.96, 1);

	/****************/
	/*	   NECK     */
	/****************/
	hq_black;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 1);
	hq_red;
	rectangle(x + (w / 2.0) - (w * .24), y + (w * 1.03), w * .1, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.03), w * .1, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .24), y + (w * 1.03), w * .1, w * .2, 1);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.03), w * .1, w * .2, 1);

	/****************/
	/*	   HEAD     */
	/****************/
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 1);
	hq_beard;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 1);
	//hat
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .35, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .35, 1);
	hq_black;
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .14, 0);
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.85), w * .82, w * .14, 1);

	chara_hq_calfL(x, y * 1.4, w, 0, 0, rotate_kneeL, sx, sy);
	chara_hq_calfR(x, y * 1.4, w, 0, 0, rotate_kneeR, sx, sy);
	chara_hq_upperarmL(x, y, w, 0, 0, rotate_shoulderL, 90, sx, sy);
	chara_hq_upperarmR(x, y, w, 0, 0, rotate_shoulderR, -90, sx, sy);

	glPopMatrix();
}

void chara_dr_lowerarmL(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x - (w * .2), y + (w * .09), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .09)), 0);

	/****************/
	/*	LOWERARM_L  */
	/****************/
	dr_blue;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 0);
	//hand
	hq_skin;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 1);
	dr_blue;
	rectangle(x - (w * .36), y - (w * .62), w * 0.34, w * .23, 0);
	rectangle(x - (w * .36), y - (w * .62), w * 0.34, w * .23, 1);

	glPopMatrix();
}

void chara_dr_lowerarmR(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w * 1.18), y + (w * .09), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .09)), 0);

	/****************/
	/*	LOWERARM_R  */
	/****************/
	dr_blue;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 0);
	//hand
	hq_skin;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 1);
	dr_blue;
	rectangle(x + (w * 1.02), y - (w * .62), w * 0.34, w * .23, 0);
	rectangle(x + (w * 1.02), y - (w * .62), w * 0.34, w * .23, 1);

	glPopMatrix();
}

void chara_dr_upperarmL(int x, int y, int w, int tx, int ty, float rotate, float rotate_elbowL, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x - (w * .2), y + (w * .95), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .95)), 0);

	/****************/
	/*	UPPERARM_L  */
	/****************/
	dr_blue;
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w, 0);
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w, 1);

	chara_dr_lowerarmL(x, y, w, tx, ty, rotate_elbowL, sx, sy);
	glPopMatrix();
}

void chara_dr_upperarmR(int x, int y, int w, int tx, int ty, float rotate, float rotate_elbowR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w * 1.18), y + (w * .95), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .95)), 0);

	/****************/
	/*	UPPERARM_R  */
	/****************/
	dr_blue;
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w, 0);
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w, 1);

	chara_dr_lowerarmR(x, y, w, tx, ty, rotate_elbowR, sx, sy);
	glPopMatrix();
}

void chara_dr_calfL(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * 2.075), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * 2.075)), 0);

	/****************/
	/*	  CALF_L    */
	/****************/
	hq_shoes;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .23, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 0);
	dr_brown;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 3.17), w * 0.35, w * 1.095, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .23, 1);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 3.17), w * 0.35, w * 1.095, 1);

	glPopMatrix();
}

void chara_dr_calfR(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * 2.075), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * 2.075)), 0);

	/****************/
	/*	  CALF_R    */
	/****************/
	hq_shoes;
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .23, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 0);
	dr_brown;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 3.17), w * 0.35, w * 1.095, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .23, 1);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 3.17), w * 0.35, w * 1.095, 1);

	glPopMatrix();
}

void chara_dr_thighL(int x, int y, int w, int tx, int ty, float rotate, float rotate_kneeL, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * .9), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * .9)), 0);

	/****************/
	/*	  THIGH_L   */
	/****************/
	dr_brown;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 1);

	chara_dr_calfL(x, y, w, tx, ty, rotate_kneeL, sx, sy);
	glPopMatrix();
}

void chara_dr_thighR(int x, int y, int w, int tx, int ty, float rotate, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * .9), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * .9)), 0);

	/****************/
	/*	  THIGH_R   */
	/****************/
	dr_brown;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 1);

	chara_dr_calfR(x, y, w, tx, ty, rotate_kneeR, sx, sy);
	glPopMatrix();
}

void chara_dr(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   BODY     */
	/****************/
	dr_blue;
	rectangle(x, y - (w * .86), w, w * 1.96, 0);
	rectangle(x, y - (w * .86), w, w * 1.96, 1);
	//pocket
	dr_blue;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * .55), w * .25, w * .05, 0);
	rectangle(x + (w / 2.0) + (w * .17), y + (w * .55), w * .25, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * .55), w * .25, w * .05, 1);
	rectangle(x + (w / 2.0) + (w * .17), y + (w * .55), w * .25, w * .05, 1);

	/****************/
	/*	   NECK     */
	/****************/
	dr_blue;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 1);
	//chest
	black;
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .86), w * .1, w * 2.115, 0);
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .86), w * .1, w * 2.115, 1);
	rectangle(x + (w / 2.0), y - (w * .86), 0, w * 2.115, 1);

	/****************/
	/*	   HEAD     */
	/****************/
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 1);
	dr_hair;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 0);
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.2), w * .63, w * .8, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .35, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 1);
	//rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.2), w * .63, w * .8, 1);
	black;
	rectangle(x + (w / 2.0) - (w * .15), y + (w * 1.35), w * .31, w * .04, 0);
	//eye
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.65), w * .07, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .19), y + (w * 1.65), w * .07, w * .07, 0);
	dr_hair;
	rectangle(x + (w / 2.0) + (w * .1), y + (w * 1.72), w * .18, w * .04, 0);
	rectangle(x + (w / 2.0) - (w * .25), y + (w * 1.72), w * .18, w * .04, 0);
	rectangle(x + (w / 2.0) + (w * .1), y + (w * 1.72), w * .18, w * .04, 1);
	rectangle(x + (w / 2.0) - (w * .25), y + (w * 1.72), w * .18, w * .04, 1);

	chara_dr_thighL(x, y, w, 0, 0, rotate_hipL, rotate_kneeL, sx, sy);
	chara_dr_thighR(x, y, w, 0, 0, rotate_hipR, rotate_kneeR, sx, sy);
	chara_dr_upperarmL(x, y, w, 0, 0, rotate_shoulderL, rotate_elbowL, sx, sy);
	chara_dr_upperarmR(x, y, w, 0, 0, rotate_shoulderR, rotate_elbowR, sx, sy);

	glPopMatrix();
}

void chara_student_lowerarmL(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x - (w * .2), y + (w * .09), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .09)), 0);

	/****************/
	/*	LOWERARM_L  */
	/****************/
	white;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 0);
	//hand
	hq_skin;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 1);
	white;
	rectangle(x - (w * .36), y - (w * .62), w * 0.34, w * .23, 0);
	rectangle(x - (w * .36), y - (w * .62), w * 0.34, w * .23, 1);

	glPopMatrix();
}

void chara_student_lowerarmR(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w * 1.18), y + (w * .09), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .09)), 0);

	/****************/
	/*	LOWERARM_R  */
	/****************/
	white;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 0);
	//hand
	hq_skin;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 0);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .24, 1);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 1);
	white;
	rectangle(x + (w * 1.02), y - (w * .62), w * 0.34, w * .23, 0);
	rectangle(x + (w * 1.02), y - (w * .62), w * 0.34, w * .23, 1);

	glPopMatrix();
}

void chara_student_upperarmL(int x, int y, int w, int tx, int ty, float rotate, float rotate_elbowL, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x - (w * .2), y + (w * .95), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .95)), 0);

	/****************/
	/*	UPPERARM_L  */
	/****************/
	white;
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w, 0);
	rectangle(x - (w * .32), y + (w * .09), w * 0.265, w, 1);

	chara_student_lowerarmL(x, y, w, tx, ty, rotate_elbowL, sx, sy);
	glPopMatrix();
}

void chara_student_upperarmR(int x, int y, int w, int tx, int ty, float rotate, float rotate_elbowR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w * 1.18), y + (w * .95), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .95)), 0);

	/****************/
	/*	UPPERARM_R  */
	/****************/
	white;
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w, 0);
	rectangle(x + (w * 1.06), y + (w * .09), w * 0.265, w, 1);

	chara_student_lowerarmR(x, y, w, tx, ty, rotate_elbowR, sx, sy);
	glPopMatrix();
}

void chara_student_calfL(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * 2.075), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * 2.075)), 0);

	/****************/
	/*	  CALF_L    */
	/****************/
	black;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .23, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 0);
	black;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 3.17), w * 0.35, w * 1.095, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .23, 1);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 3.17), w * 0.35, w * 1.095, 1);

	glPopMatrix();
}

void chara_student_calfR(int x, int y, int w, int tx, int ty, float rotate, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * 2.075), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * 2.075)), 0);

	/****************/
	/*	  CALF_R    */
	/****************/
	black;
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .23, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 0);
	black;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 3.17), w * 0.35, w * 1.095, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .23, 1);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 3.17), w * 0.35, w * 1.095, 1);

	glPopMatrix();
}

void chara_student_thighL(int x, int y, int w, int tx, int ty, float rotate, float rotate_kneeL, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * .9), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * .9)), 0);

	/****************/
	/*	  THIGH_L   */
	/****************/
	black;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * 1.16, 1);

	chara_student_calfL(x, y, w, tx, ty, rotate_kneeL, sx, sy);
	glPopMatrix();
}

void chara_student_thighR(int x, int y, int w, int tx, int ty, float rotate, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * .9), 0);
	glRotatef(rotate, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * .9)), 0);

	/****************/
	/*	  THIGH_R   */
	/****************/
	black;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 0);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * 1.16, 1);

	chara_student_calfR(x, y, w, tx, ty, rotate_kneeR, sx, sy);
	glPopMatrix();
}

void chara_student(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   BODY     */
	/****************/
	white;
	rectangle(x, y - (w * .86), w, w * 1.96, 0);
	rectangle(x, y - (w * .86), w, w * 1.96, 1);
	//pocket
	white;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * .55), w * .25, w * .05, 0);
	rectangle(x + (w / 2.0) + (w * .17), y + (w * .55), w * .25, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * .55), w * .25, w * .05, 1);
	rectangle(x + (w / 2.0) + (w * .17), y + (w * .55), w * .25, w * .05, 1);

	/****************/
	/*	   NECK     */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.05), w * .45, w * .2, 1);
	//chest
	black;
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .86), w * .1, w * 2.115, 0);
	rectangle(x + (w / 2.0) - (w * .05), y - (w * .86), w * .1, w * 2.115, 1);
	rectangle(x + (w / 2.0), y - (w * .86), 0, w * 2.115, 1);

	/****************/
	/*	   HEAD     */
	/****************/
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .41), y + (w * 1.53), w * .07, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .38), y + (w * 1.53), w * .07, w * .16, 1);
	dr_hair;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 0);
	hq_skin;
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.2), w * .63, w * .65, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .35, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.2), w * .75, w * .85, 1);
	//rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.2), w * .63, w * .8, 1);
	black;
	rectangle(x + (w / 2.0) - (w * .15), y + (w * 1.35), w * .31, w * .04, 0);
	rectangle(x + (w / 2.0) + (w * .1), y + (w * 1.65), w * .18, w * .04, 0);
	rectangle(x + (w / 2.0) - (w * .25), y + (w * 1.65), w * .18, w * .04, 0);
	//eye
	glColor4ub(0, 0, 0, eye_alpha);
	rectangle(x + (w / 2.0) + (w * .15), y + (w * 1.6), w * .07, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .19), y + (w * 1.6), w * .07, w * .07, 0);

	chara_student_thighL(x, y, w, 0, 0, rotate_hipL, rotate_kneeL, sx, sy);
	chara_student_thighR(x, y, w, 0, 0, rotate_hipR, rotate_kneeR, sx, sy);
	chara_student_upperarmL(x, y, w, 0, 0, rotate_shoulderL, rotate_elbowL, sx, sy);
	chara_student_upperarmR(x, y, w, 0, 0, rotate_shoulderR, rotate_elbowR, sx, sy);

	glPopMatrix();
}

void chara_dead(int x, int y, int w, int tx, int ty, float rotate_all, float rotate_shoulderL, float rotate_elbowL, float rotate_shoulderR, float rotate_elbowR, float rotate_hipL, float rotate_kneeL, float rotate_hipR, float rotate_kneeR, float sx, float sy, int a)
{
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2.0)), -y, 0);

	/****************/
	/*	   HEAD     */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.3), w * .75, w * .85, 0);
	//visor
	black;
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 0);
	clear;
	rectangle_texture(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, tex_skull, tex_skullX, tex_skullY);
	glColor4ub(5, 5, 5, a);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w * 1.3), w * .75, w * .85, 1);
	rectangle(x + (w / 2.0) - (w * .3), y + (w * 1.4), w * .63, w * .5, 1);
	//forehead
	rectangle(x + (w / 2.0) - (w * .39), y + (w * 1.8), w * .82, w * .2, 0);
	//rectangle(x + (w / 2.0) - (w * .17), y + (w * 1.735), w * .38, w * .33, 0);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .31), y + (w * 2), w * .05, w * .145, 0);
	rectangle(x + (w / 2.0) + (w * .29), y + (w * 2), w * .05, w * .145, 0);

	/****************/
	/*	   BODY     */
	/****************/
	glColor3ub(125, 125, 125);
	rectangle(x, y, w, w * 1.15, 0);
	red_strip;
	rectangle(x + (w / 2.0) - (w * .49), y + (w * .18), w * 0.99, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .49), y + (w * .55), w * 0.23, w * .23, 0);
	rectangle(x + (w / 2.0) + (w * .24), y + (w * .55), w * 0.26, w * .23, 0);
	rectangle(x + (w / 2.0) - (w * .30), y + (w * .18), w * 0.05, w * .6, 0);
	rectangle(x + (w / 2.0) + (w * .24), y + (w * .18), w * 0.05, w * .6, 0);
	//body mid
	white;
	rectangle(x + (w / 2.0) - (w * .12), y, w * .25, w * 1.15, 0);
	rectangle(x + (w / 2.0) - (w * .07), y + (w * .05), w * .155, w * 1.02, 0);
	//chest
	black;
	rectangle(x + (w / 2.0) - (w * .49), y + (w * .6), w * 0.2, w * .13, 0);
	rectangle(x + (w / 2.0) + (w * .29), y + (w * .6), w * 0.21, w * .13, 0);
	rectangle(x, y, w, w * 1.15, 1);
	rectangle(x + (w / 2.0) - (w * .12), y, w * .25, w * 1.13, 1);
	rectangle(x + (w / 2.0) - (w * .07), y + (w * .05), w * .155, w * 1.02, 1);
	//shoulder
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) - (w * .53), y + (w * 1.02), w * 0.31, w * .17, 0);
	rectangle(x + (w / 2.0) + (w * .23), y + (w * 1.02), w * 0.31, w * .17, 0);
	rectangle(x + (w / 2.0) - (w * .53), y + (w * 1.02), w * 0.31, w * .17, 1);
	rectangle(x + (w / 2.0) + (w * .23), y + (w * 1.02), w * 0.31, w * .17, 1);
	white;
	rectangle(x + (w / 2.0) - (w * .42), y + (w * 1.02), w * 0.12, w * .19, 0);
	rectangle(x + (w / 2.0) + (w * .31), y + (w * 1.02), w * 0.12, w * .19, 0);
	rectangle(x + (w / 2.0) - (w * .42), y + (w * 1.02), w * 0.12, w * .19, 1);
	rectangle(x + (w / 2.0) + (w * .31), y + (w * 1.02), w * 0.12, w * .19, 1);
	//circle
	//12
	//34
	glColor3ub(116, 116, 106);
	nGon(64, x + (w / 2.0) - (w * .36), y + (w * .98), w * .08, 0);
	nGon(64, x + (w / 2.0) + (w * .37), y + (w * .98), w * .08, 0);
	nGon(64, x + (w / 2.0) - (w * .27), y + (w * .21), w * .08, 0);
	nGon(64, x + (w / 2.0) + (w * .27), y + (w * .21), w * .08, 0);

	//circle border
	nGon(64, x + (w / 2.0) - (w * .36), y + (w * .98), w * .08, 1);
	nGon(64, x + (w / 2.0) - (w * .36), y + (w * .98), w * .045, 1);

	nGon(64, x + (w / 2.0) + (w * .37), y + (w * .98), w * .08, 1);
	nGon(64, x + (w / 2.0) + (w * .37), y + (w * .98), w * .045, 1);

	nGon(64, x + (w / 2.0) - (w * .27), y + (w * .21), w * .08, 1);
	nGon(64, x + (w / 2.0) - (w * .27), y + (w * .21), w * .045, 1);

	nGon(64, x + (w / 2.0) + (w * .27), y + (w * .21), w * .08, 1);
	nGon(64, x + (w / 2.0) + (w * .27), y + (w * .21), w * .045, 1);

	/****************/
	/*	   HIP      */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .86), w * 0.9, w * .86, 0);
	black;
	rectangle(x + (w / 2.0) - (w * .06), y - (w * .86), w * .13, w * .86, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .3), w * .18, w * .3, 0);
	rectangle(x + (w / 2.0) + (w * .28), y - (w * .3), w * .18, w * .3, 0);
	glColor3ub(125, 125, 125);
	rectangle(x + (w / 2.0) - (w * .30), y - (w * .855), w * 0.05, w * .86, 0);
	rectangle(x + (w / 2.0) + (w * .24), y - (w * .855), w * 0.05, w * .86, 0);
	//belt
	rectangle(x + (w / 2.0) - (w * .445), y - (w * .86), w * 0.9, w * .86, 1);
	white;
	rectangle(x + (w / 2.0) - (w * .48), y - (w * .35), w * .28, w * .16, 0);
	rectangle(x + (w / 2.0) + (w * .19), y - (w * .35), w * .3, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * .35), w * .28, w * .16, 1);
	rectangle(x + (w / 2.0) + (w * .19), y - (w * .35), w * .3, w * .16, 1);

	/****************/
	/*	   NECK     */
	/****************/
	white;
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.13), w * .45, w * .12, 0);
	black;
	rectangle(x + (w / 2.0) - (w * .06), y + (w * 1.13), w * .13, w * .12, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w * 1.13), w * .45, w * .12, 1);

	/****************/
	/*	UPPERARM_L  */
	/****************/
	glPushMatrix();

	glTranslatef(x - (w * .2), y + (w * .95), 0);
	glRotatef(rotate_shoulderL, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .95)), 0);

	white;
	rectangle(x - (w * .32), y + (w * .27), w * 0.265, w * .85, 0);
	glColor3ub(125, 125, 125);
	rectangle(x - (w * .315), y + (w * .275), w * 0.255, w * .05, 0);
	black;
	rectangle(x - (w * .2), y + (w * .69), w * 0.14, w * .43, 0);
	rectangle(x - (w * .32), y + (w * .27), w * 0.265, w * .85, 1);

	/****************/
	/*	LOWERARM_L  */
	/****************/
	glTranslatef(x - (w * .2), y + (w * .18), 0);
	glRotatef(rotate_elbowL, 0, 0, 1);
	glTranslatef(-(x - (w * .2)), -(y + (w * .18)), 0);

	white;
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 0);
	black;
	rectangle(x - (w * .3), y + (w * .10), w * 0.225, w * .17, 0);
	//strips
	glColor3ub(188, 188, 203);
	rectangle(x - (w * .315), y - (w * .55), w * 0.255, w * .05, 0);
	glColor3ub(125, 125, 125);
	rectangle(x - (w * .315), y + (w * .04), w * 0.255, w * .05, 0);
	//hand
	glColor3ub(151, 153, 136);
	rectangle(x - (w * .26), y - (w * .86), w * 0.2, w * .24, 0);
	rectangle(x - (w * .26), y - (w * .86), w * 0.2, w * .24, 1);
	rectangle(x - (w * .32), y - (w * .86), w * 0.265, w * .96, 1);

	glPopMatrix();

	/****************/
	/*	UPPERARM_R  */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w * 1.18), y + (w * .95), 0);
	glRotatef(rotate_shoulderR, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .95)), 0);

	white;
	rectangle(x + (w * 1.06), y + (w * .27), w * 0.265, w * .85, 0);
	glColor3ub(125, 125, 125);
	rectangle(x + (w * 1.065), y + (w * .275), w * 0.255, w * .05, 0);
	black;
	rectangle(x + (w * 1.06), y + (w * .69), w * 0.14, w * .43, 0);
	rectangle(x + (w * 1.06), y + (w * .27), w * 0.265, w * .85, 1);

	/****************/
	/*	LOWERARM_R  */
	/****************/
	glTranslatef(x + (w * 1.18), y + (w * .18), 0);
	glRotatef(rotate_elbowR, 0, 0, 1);
	glTranslatef(-(x + (w * 1.18)), -(y + (w * .18)), 0);

	white;
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 0);
	black;
	rectangle(x + (w * 1.08), y + (w * .10), w * 0.225, w * .17, 0);
	//strips
	glColor3ub(188, 188, 203);
	rectangle(x + (w * 1.065), y - (w * .55), w * 0.255, w * .05, 0);
	glColor3ub(125, 125, 125);
	rectangle(x + (w * 1.065), y + (w * .04), w * 0.255, w * .05, 0);
	//hand
	glColor3ub(151, 153, 136);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.2, w * .24, 0);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.2, w * .24, 1);
	rectangle(x + (w * 1.06), y - (w * .86), w * 0.265, w * .96, 1);

	glPopMatrix();

	/****************/
	/*	  THIGH_L   */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * .9), 0);
	glRotatef(rotate_hipL, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * .9)), 0);

	white;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 1.75), w * 0.35, w * .83, 0);
	glColor3ub(125, 125, 125);
	rectangle(x + (w / 2.0) - (w * .30), y - (w * 1.74), w * 0.05, w * .82, 0);
	//strap
	white;
	rectangle(x + (w / 2.0) - (w * .35), y - (w * 1.67), w * 0.15, w * .06, 0);
	rectangle(x + (w / 2.0) - (w * .35), y - (w * 1.67), w * 0.15, w * .06, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 1.75), w * 0.35, w * .83, 1);

	/****************/
	/*	  CALF_L    */
	/****************/
	glTranslatef(x + (w / 2.0) - (w * .3), y - (w * 1.75), 0);
	glRotatef(rotate_kneeL, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .3)), -(y - (w * 1.75)), 0);

	white;
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.54), w * 0.35, w * .47, 0);
	//knee
	glColor3ub(233, 230, 226);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * .33, 0);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.075), w * 0.35, w * .33, 1);
	rectangle(x + (w / 2.0) - (w * .4), y - (w * 2.075), w * 0.245, w * .33, 1);
	rectangle(x + (w / 2.0) - (w * .445), y - (w * 2.54), w * 0.35, w * .47, 1);
	glColor3ub(125, 125, 125);
	rectangle(x + (w / 2.0) - (w * .30), y - (w * 2.535), w * 0.05, w * .46, 0);
	//boot
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .86, 0);
	glColor3ub(116, 116, 106);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.4), w * 0.42, w * .86, 1);
	rectangle(x + (w / 2.0) - (w * .48), y - (w * 3.17), w * 0.42, w * .5, 1);
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 3.17), w * 0.1, w * .63, 0);
	rectangle(x + (w / 2.0) - (w * .32), y - (w * 3.17), w * 0.1, w * .63, 1);

	glPopMatrix();

	/****************/
	/*	  THIGH_R   */
	/****************/
	glPushMatrix();

	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * .9), 0);
	glRotatef(rotate_hipR, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * .9)), 0);

	white;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.75), w * 0.35, w * .83, 0);
	glColor3ub(125, 125, 125);
	rectangle(x + (w / 2.0) + (w * .24), y - (w * 1.74), w * 0.05, w * .82, 0);
	//strap
	white;
	rectangle(x + (w / 2.0) + (w * .19), y - (w * 1.67), w * 0.15, w * .06, 0);
	rectangle(x + (w / 2.0) + (w * .19), y - (w * 1.67), w * 0.15, w * .06, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 1.75), w * 0.35, w * .83, 1);

	/****************/
	/*	  CALF_R    */
	/****************/
	glTranslatef(x + (w / 2.0) + (w * .25), y - (w * 1.75), 0);
	glRotatef(rotate_kneeR, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .25)), -(y - (w * 1.75)), 0);

	white;
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.54), w * 0.35, w * .47, 0);
	//knee
	glColor3ub(233, 230, 226);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * .33, 0);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.075), w * 0.35, w * .33, 1);
	rectangle(x + (w / 2.0) + (w * .15), y - (w * 2.075), w * 0.245, w * .33, 1);
	rectangle(x + (w / 2.0) + (w * .1), y - (w * 2.54), w * 0.35, w * .47, 1);
	glColor3ub(125, 125, 125);
	rectangle(x + (w / 2.0) + (w * .24), y - (w * 2.535), w * 0.05, w * .46, 0);
	//boot
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .86, 0);
	glColor3ub(116, 116, 106);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .07, 0);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.4), w * 0.42, w * .86, 1);
	rectangle(x + (w / 2.0) + (w * .065), y - (w * 3.17), w * 0.42, w * .5, 1);
	glColor3ub(151, 153, 136);
	rectangle(x + (w / 2.0) + (w * .215), y - (w * 3.17), w * 0.1, w * .63, 0);
	rectangle(x + (w / 2.0) + (w * .215), y - (w * 3.17), w * 0.1, w * .63, 1);

	glPopMatrix();
	glPopMatrix();
}

void rocket() {

	glPushMatrix();
	glTranslatef(X, Y, 0.0);
	glRotatef(r_angle, X, Y, 0);

	glColor3ub(255, 127, 0);
	rectangle(420, 80, 100, 530, 0);
	rectangle(420, 80, 100, 530, 1);
	glColor3ub(255, 127, 0);
	triangle_upcenter(420, 610, 100, 690, 0);
	triangle_upcenter(420, 610, 100, 690, 1);

	glColor3ub(179, 179, 179);
	rectangle(385, 80, 30, 440, 0);
	rectangle(385, 80, 30, 440, 1);
	glColor3ub(179, 179, 179);
	triangle_upcenter(385, 520, 30, 560, 0);
	triangle_upcenter(385, 520, 30, 560, 1);

	glColor3ub(179, 179, 179);
	rectangle(525, 80, 30, 440, 0);
	rectangle(525, 80, 30, 440, 1);
	glColor3ub(179, 179, 179);
	triangle_upcenter(525, 520, 30, 560, 0);
	triangle_upcenter(525, 520, 30, 560, 1);

	glColor3ub(255, 255, 255);
	rectangle(430, 95, 80, 350, 0);
	rectangle(430, 95, 80, 350, 1);
	glColor3ub(255, 255, 255);
	triangle_upcenter(430, 445, 80, 500, 0);
	triangle_upcenter(430, 445, 80, 500, 1);
	glColor3ub(179, 179, 179);
	triangle_upcenter(450, 100, 40, 250, 0);
	triangle_upcenter(450, 100, 40, 250, 1);
	if (Y > 100) {
		glColor3ub(200, 0, 0);
		triangle(420, 80, 100, 160, 0);
		glColor3ub(200, 0, 0);
		triangle(385, 80, 30, 100, 0);
		glColor3ub(200, 0, 0);
		triangle(525, 80, 30, 100, 0);
	}
	glPopMatrix();
}

void rocket_after() {

	glPushMatrix();
	glTranslatef(0, Y_after, 0.0);
	glRotatef(r_angle, X, Y, 0);

	glColor3ub(255, 127, 0);
	rectangle(420, 80, 100, 530, 0);
	rectangle(420, 80, 100, 530, 1);
	glColor3ub(255, 127, 0);
	triangle_upcenter(420, 610, 100, 690, 0);
	triangle_upcenter(420, 610, 100, 690, 1);
	glColor3ub(255, 255, 255);
	rectangle(430, 95, 80, 350, 0);
	rectangle(430, 95, 80, 350, 1);
	glColor3ub(255, 255, 255);
	triangle_upcenter(430, 445, 80, 500, 0);
	triangle_upcenter(430, 445, 80, 500, 1);
	glColor3ub(179, 179, 179);
	triangle_upcenter(450, 100, 40, 250, 0);
	triangle_upcenter(450, 100, 40, 250, 1);
	glColor3ub(200, 0, 0);
	triangle(420, 80, 100, 160, 0);

	if (Y_after > 290) {
		glColor3ub(0, 0, 13);
		triangle(420, 80, 100, 160, 0);

		chara_alpha(1600, 200, 50, sceneB_alphaX, sceneB_alphaY, sceneB_alphaR, 0, 0, 0, 0, 0, 0, 0, 0, sceneB_alphaSX, sceneB_alphaSY);
		chara_beta(1700, 200, 50, sceneB_alphaX, sceneB_alphaY, sceneB_alphaR, 0, 0, 0, 0, 0, 0, 0, 0, sceneB_alphaSX, sceneB_alphaSY);
	}

	glPopMatrix();
}

void bouncing_ball(int x, int y, int tx, int ty)
{
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	red_strip;
	nGon(16, x, y, 5, 0);
	glPopMatrix();
}

void hq_printer(int x, int y, int w)
{
	hq_printer_black2;
	rectangle(x + (w / 2.0) - (w * .36), y + (w / 2.0) - (w * .2), w * .86, w * .22, 0);
	rectangle(x + (w / 2.0) - (w * .36), y + (w / 2.0) - (w * .2), w * .86, w * .22, 1);
	white;
	rectangle(x + (w / 2.0) - (w * .27), y + (w / 2.0) - (w * .2), w * .69, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .27), y + (w / 2.0) - (w * .2), w * .69, w * .5, 1);
	hq_printer_black;
	rectangle(x, y, w * 1.11, w * .41, 0);
	rectangle(x, y, w * 1.11, w * .41, 1);
	hq_printer_black2;
	rectangle(x + (w / 2.0) - (w * .36), y, w * .86, w * .31, 0);
	rectangle(x + (w / 2.0) - (w * .36), y, w * .86, w * .31, 1);
	hq_printer_black3;
	rectangle(x + (w / 2.0) - (w * .3), y, w * .74, w * .15, 0);
	rectangle(x + (w / 2.0) - (w * .3), y, w * .74, w * .15, 1);
	white;
	rectangle(x + (w / 2.0) - (w * .27), y, w * .69, w * .05, 0);
	//rectangle(x + (w / 2.0) - (w * .27), y, w * .69, w * .05, 1);
}

void hq_monitor(int x, int y, int w)
{
	black;
	rectangle(x, y, w * 2.83, w * .87, 0);
	rectangle(x, y, w * 2.83, w * .87, 1);
	hq_monitor_blue;
	rectangle(x + (w / 2.0) - (w * .48), y + (w / 2.0) - (w * .46), w * 2.79, w * .81, 0);
	clear;
	if (crash)
		rectangle_texture(x + (w / 2.0) - (w * .48), y + (w / 2.0) - (w * .46), w * 2.79, w * .81, tex_bsod, tex_bsodX, tex_bsodY);
	else
		rectangle_texture(x + (w / 2.0) - (w * .48), y + (w / 2.0) - (w * .46), w * 2.79, w * .81, tex_game, tex_gameX, tex_gameY);
	hq_monitor_black;
	rectangle(x + (w / 2.0) + (w * .79), y + (w / 2.0) - (w * .69), w * .25, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .79), y + (w / 2.0) - (w * .69), w * .25, w * .2, 1);
	hq_monitor_black;
	rectangle(x, y, w * 2.83, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .02), y + (w / 2.0) - (w * .71), w * 1.87, w * .04, 0);
	rectangle(x, y, w * 2.83, w * .05, 1);
	rectangle(x + (w / 2.0) - (w * .02), y + (w / 2.0) - (w * .71), w * 1.87, w * .04, 1);
}

void hq_monitor_left(int x, int y, int w)
{
	black;
	rectangle(x, y, w * 2.83, w * .87, 0);
	rectangle(x, y, w * 2.83, w * .87, 1);
	hq_monitor_blue;
	rectangle(x + (w / 2.0) - (w * .48), y + (w / 2.0) - (w * .46), w * 2.79, w * .81, 0);
	clear;
	rectangle_texture(x + (w / 2.0) - (w * .48), y + (w / 2.0) - (w * .46), w * 2.79, w * .81, tex_word, tex_wordX, tex_wordY);
	hq_monitor_black;
	rectangle(x + (w / 2.0) + (w * .79), y + (w / 2.0) - (w * .69), w * .25, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .79), y + (w / 2.0) - (w * .69), w * .25, w * .2, 1);
	hq_monitor_black;
	rectangle(x, y, w * 2.83, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .02), y + (w / 2.0) - (w * .71), w * 1.87, w * .04, 0);
	rectangle(x, y, w * 2.83, w * .05, 1);
	rectangle(x + (w / 2.0) - (w * .02), y + (w / 2.0) - (w * .71), w * 1.87, w * .04, 1);
}

void hq_monitor_right(int x, int y, int w)
{
	black;
	rectangle(x, y, w * 2.83, w * .87, 0);
	rectangle(x, y, w * 2.83, w * .87, 1);
	hq_monitor_black;
	rectangle(x + (w / 2.0) + (w * .79), y + (w / 2.0) - (w * .69), w * .25, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .79), y + (w / 2.0) - (w * .69), w * .25, w * .2, 1);
	hq_monitor_black;
	rectangle(x, y, w * 2.83, w * .05, 0);
	rectangle(x + (w / 2.0) - (w * .02), y + (w / 2.0) - (w * .71), w * 1.87, w * .04, 0);
	rectangle(x, y, w * 2.83, w * .05, 1);
	rectangle(x + (w / 2.0) - (w * .02), y + (w / 2.0) - (w * .71), w * 1.87, w * .04, 1);
}

void hq_monitor_rear(int x, int y, int w, int tx, int ty)
{
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clear;
	rectangle_texture(x + (w / 2.0) - (w * .7), y + (w / 2.0) - (w * 1.55), w * 4.2, w * 2.2, tex_monitor_rear, tex_monitor_rearX, tex_monitor_rearY);
	glPopMatrix();
}

void hq_table(int x, int y, int w)
{
	hq_table_black;
	rectangle_gradient(x, y + (w / 2.0) - (w * .12), w * 2.3, w * .8, 0, 47, 42, 39, 0, 0, 0);
	rectangle(x, y + (w / 2.0) - (w * .12), w * 2.3, w * .8, 1);
	hq_table_black;
	rectangle(x, y + (w / 2.0) + (w * .6), w * 2.3, w * .15, 0);
	rectangle(x, y + (w / 2.0) + (w * .6), w * 2.3, w * .15, 1);
	hq_table_black;
	rectangle(x, y, w * .14, w * 1.25, 0);
	rectangle(x + (w / 2.0) + (w * 1.66), y, w * .73, w * 1.25, 0);
	rectangle(x, y, w * .14, w * 1.25, 1);
	rectangle(x + (w / 2.0) + (w * 1.66), y, w * .73, w * 1.25, 1);
	hq_table_brown;
	rectangle(x + (w / 2.0) - (w * .55), y + (w / 2.0) + (w * .71), w * 3, w * .1, 0);
	rectangle(x + (w / 2.0) + (w * 1.7), y + (w / 2.0) + (w * .33), w * .65, w * .34, 0);
	rectangle(x + (w / 2.0) + (w * 1.7), y + (w / 2.0) - (w * .06), w * .65, w * .34, 0);
	rectangle(x + (w / 2.0) + (w * 1.7), y + (w / 2.0) - (w * .45), w * .65, w * .34, 0);
	rectangle(x + (w / 2.0) - (w * .55), y + (w / 2.0) + (w * .71), w * 3, w * .1, 1);
	rectangle(x + (w / 2.0) + (w * 1.7), y + (w / 2.0) + (w * .33), w * .65, w * .34, 1);
	rectangle(x + (w / 2.0) + (w * 1.7), y + (w / 2.0) - (w * .06), w * .65, w * .34, 1);
	rectangle(x + (w / 2.0) + (w * 1.7), y + (w / 2.0) - (w * .45), w * .65, w * .34, 1);
	hq_table_black;
	rectangle(x + (w / 2.0) + (w * 1.92), y + (w / 2.0) + (w * .57), w * .23, w * .04, 0);
	rectangle(x + (w / 2.0) + (w * 1.92), y + (w / 2.0) + (w * .19), w * .23, w * .04, 0);
	rectangle(x + (w / 2.0) + (w * 1.92), y + (w / 2.0) - (w * .21), w * .23, w * .04, 0);
	rectangle(x + (w / 2.0) + (w * 1.92), y + (w / 2.0) + (w * .57), w * .23, w * .04, 1);
	rectangle(x + (w / 2.0) + (w * 1.92), y + (w / 2.0) + (w * .19), w * .23, w * .04, 1);
	rectangle(x + (w / 2.0) + (w * 1.92), y + (w / 2.0) - (w * .21), w * .23, w * .04, 1);
}

void hq_chair(int x, int y, int w)
{
	hq_chair_silver;
	rectangle(x + (w / 2.0) - (w * .01), y + (w / 2.0) - (w * 1.1), w * .115, w * .75, 0);
	rectangle(x + (w / 2.0) - (w * .01), y + (w / 2.0) - (w * 1.1), w * .115, w * .75, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .56), y + (w / 2.0) - (w * .49), w * 1.2, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .09), y + (w / 2.0) - (w * .57), w * .28, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .56), y + (w / 2.0) - (w * .49), w * 1.2, w * .16, 1);
	rectangle(x + (w / 2.0) - (w * .09), y + (w / 2.0) - (w * .57), w * .28, w * .16, 1);

	//back
	hq_chair_black;
	rectangle(x, y, w * 1.08, w * 1.77, 0);
	rectangle(x, y, w * 1.08, w * 1.77, 1);
	hq_chair_mesh;
	rectangle(x + (w / 2.0) - (w * .375), y + (w / 2.0) - (w * .35), w * .84, w * 1.48, 0);
	rectangle(x + (w / 2.0) - (w * .375), y + (w / 2.0) - (w * .35), w * .84, w * 1.48, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .22), y + (w / 2.0) - (w * .12), w * .515, w * .34, 0);
	rectangle(x + (w / 2.0) - (w * .22), y + (w / 2.0) - (w * .12), w * .515, w * .34, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .44), y + (w / 2.0) + (w * .07), w * .96, w * .12, 0);
	rectangle(x + (w / 2.0) - (w * .44), y + (w / 2.0) - (w * .09), w * .96, w * .12, 0);
	rectangle(x + (w / 2.0) - (w * .44), y + (w / 2.0) + (w * .07), w * .96, w * .12, 1);
	rectangle(x + (w / 2.0) - (w * .44), y + (w / 2.0) - (w * .09), w * .96, w * .12, 1);

	//left armrest
	hq_chair_silver;
	rectangle(x + (w / 2.0) - (w * .6), y + (w / 2.0) - (w * .45), w * .04, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .6), y + (w / 2.0) - (w * .45), w * .04, w * .5, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .63), y + (w / 2.0) - (w * .15), w * .1, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .63), y + (w / 2.0) - (w * .15), w * .1, w * .5, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .79), y + (w / 2.0) + (w * .33), w * .26, w * .07, 0);
	rectangle(x + (w / 2.0) - (w * .79), y + (w / 2.0) + (w * .33), w * .26, w * .07, 1);

	//right armrest
	hq_chair_silver;
	rectangle(x + (w / 2.0) + (w * .64), y + (w / 2.0) - (w * .45), w * .04, w * .5, 0);
	rectangle(x + (w / 2.0) + (w * .64), y + (w / 2.0) - (w * .45), w * .04, w * .5, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) + (w * .61), y + (w / 2.0) - (w * .15), w * .1, w * .5, 0);
	rectangle(x + (w / 2.0) + (w * .61), y + (w / 2.0) - (w * .15), w * .1, w * .5, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) + (w * .61), y + (w / 2.0) + (w * .33), w * .26, w * .07, 0);
	rectangle(x + (w / 2.0) + (w * .61), y + (w / 2.0) + (w * .33), w * .26, w * .07, 1);

	//wheels
	glPushMatrix();
	glTranslatef(x + (w / 2.0) - (w * .5), y + (w / 2.0) - (w * 1.36), 0);
	glRotatef(10, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .5)), -(y + (w / 2.0) - (w * 1.36)), 0);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .5), y + (w / 2.0) - (w * 1.36), w * .54, w * .12, 0);
	rectangle(x + (w / 2.0) - (w * .5), y + (w / 2.0) - (w * 1.36), w * .54, w * .12, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x + (w / 2.0) + (w * .63), y + (w / 2.0) - (w * 1.25), 0);
	glRotatef(170, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) + (w * .63)), -(y + (w / 2.0) - (w * 1.25)), 0);
	hq_chair_black;
	rectangle(x + (w / 2.0) + (w * .63), y + (w / 2.0) - (w * 1.25), w * .54, w * .12, 0);
	rectangle(x + (w / 2.0) + (w * .63), y + (w / 2.0) - (w * 1.25), w * .54, w * .12, 1);
	glPopMatrix();

	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .03), y + (w / 2.0) - (w * 1.3), w * .155, w * .35, 0);
	rectangle(x + (w / 2.0) - (w * .03), y + (w / 2.0) - (w * 1.3), w * .155, w * .35, 1);
	hq_chair_black;
	rectangle(x + (w / 2.0) - (w * .01), y + (w / 2.0) - (w * 1.36), w * .115, w * .2, 0);
	rectangle(x + (w / 2.0) + (w * .01), y + (w / 2.0) - (w * 1.53), w * .075, w * .16, 0);
	rectangle(x + (w / 2.0) - (w * .01), y + (w / 2.0) - (w * 1.36), w * .115, w * .2, 1);
	rectangle(x + (w / 2.0) - (w * .01), y + (w / 2.0) - (w * 1.36), w * .115, w * .1, 1);
	rectangle(x + (w / 2.0) + (w * .01), y + (w / 2.0) - (w * 1.53), w * .075, w * .16, 1);

	//wheels left
	hq_chair_black;
	nGon(16, x + (w / 2.0) - (w * .49), y + (w / 2.0) - (w * 1.44), w * .08, 0);
	nGon(16, x + (w / 2.0) - (w * .49), y + (w / 2.0) - (w * 1.44), w * .08, 1);

	//wheels right
	hq_chair_black;
	nGon(16, x + (w / 2.0) + (w * .6), y + (w / 2.0) - (w * 1.44), w * .08, 0);
	nGon(16, x + (w / 2.0) + (w * .6), y + (w / 2.0) - (w * 1.44), w * .08, 1);
}

void hq(int x, int y, int w)
{
	//building
	hq_building_wall;
	rectangle(x, y, w, w, 0);
	hq_building_floor;
	rectangle(x, y, w, w * .07, 0);
	rectangle(x, y, w, w * .07, 1);

	//nasa logo
	clear;
	rectangle_texture(x + (w / 2.0) - (w * .045), y + (w / 2.0) + (w * .02), w * .1, w * .03, tex_nasa_old, tex_nasa_oldX, tex_nasa_oldY);

	//monitor
	hq_chair_black;
	rectangle(x, y + (w / 2.0) - (w * .17), w, w * .18, 0);
	rectangle(x, y + (w / 2.0) - (w * .17), w, w * .18, 1);
	hq_monitor_blue;
	rectangle(x + w * .018, y + (w / 2.0) - (w * .15), w * .965, w * .14, 0);
	clear;
	rectangle_texture(x + w * .018, y + (w / 2.0) - (w * .15), w * .965, w * .14, tex_monitor_main, tex_monitor_mainX, tex_monitor_mainY);
	rectangle(x + w * .018, y + (w / 2.0) - (w * .15), w * .965, w * .14, 1);

	//center
	hq_table(x + (w / 2.0) - (w * .12), y + (w / 2.0) - (w * .435), w * .102);
	hq_printer(x + (w / 2.0) + (w * .117), y + (w / 2.0) - (w * .305), w * .05);
	hq_monitor(x + (w / 2.0) - (w * .098), y + (w / 2.0) - (w * .29), w * .07);
	chara_hq_back2(x + (w / 2.0) - (w * 0.027), 340, w * .0521, 0, sceneA4_hqY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
	hq_chair(x + (w / 2.0) - (w * .034), y + (w / 2.0) - (w * .371), w * .063);

	//left
	hq_table(x + (w / 2.0) - (w * .57), y + (w / 2.0) - (w * .435), w * .102);
	hq_printer(x + (w / 2.0) - (w * 0.332), y + (w / 2.0) - (w * .305), w * .05);
	hq_monitor_left(x + (w / 2.0) - (w * 0.548), y + (w / 2.0) - (w * .29), w * .07);
	chara_hq_back(x + (w / 2.0) - (w * 0.477), 340, w * .0521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
	hq_chair(x + (w / 2.0) - (w * 0.484), y + (w / 2.0) - (w * .371), w * .063);

	//right
	hq_table(x + (w / 2.0) + (w * .33), y + (w / 2.0) - (w * .435), w * .102);
	hq_monitor_right(x + (w / 2.0) + (w * 0.35), y + (w / 2.0) - (w * .29), w * .07);
	bouncing_ball(1643, 420, bouncing_ballX, bouncing_ballY);
	hq_chair(x + (w / 2.0) + (w * .42), y + (w / 2.0) - (w * .371), w * .063);
}

void clock(int x, int y, int w, int tx, int ty, float sx, float sy)
{
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);
	glTranslatef(-x, -y, 0);

	white;
	nGon(64, x, y, w * .95, 0);
	clear;
	rectangle_texture(x + (w / 2.0) - (w * 1.5), y + (w / 2.0) - (w * 1.5), w * 2, w * 2, tex_clock, tex_clockX, tex_clockY);

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(sceneA_clockMins -= .1, 0, 0, 1);
	glTranslatef(-x, -y, 0);
	white;
	rectangle(x + (w / 2.0) - (w * .52), y, w * .04, w * .85, 0);
	rectangle(x + (w / 2.0) - (w * .52), y, w * .04, w * .85, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(sceneA_clockHrs -= 0.00833333333, 0, 0, 1);
	glTranslatef(-x, -y, 0);
	white;
	rectangle(x + (w / 2.0) - (w * .52), y, w * .04, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .52), y, w * .04, w * .5, 1);
	glPopMatrix();
	black;
	nGon(24, x, y, w * .05, 0);
	nGon(24, x, y, w * .05, 1);
	glPopMatrix();
}

void class_table(int x, int y, int w)
{
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .52), y, w * .15, w * 1.2, 0);
	rectangle(x + (w / 2.0) + (w * .52), y, w * .15, w * 1.2, 0);
	rectangle(x + (w / 2.0) - (w * .52), y, w * .15, w * 1.2, 1);
	rectangle(x + (w / 2.0) + (w * .52), y, w * .15, w * 1.2, 1);
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .55), y + (w / 2.0) + (w * .6), w * 1.25, w * .13, 0);
	rectangle(x + (w / 2.0) - (w * .55), y + (w / 2.0) + (w * .6), w * 1.25, w * .13, 1);
}

void class_chair(int x, int y, int w)
{
	hq_uniform;
	rectangle(x + (w / 2.0) + (w * .2), y, w * .08, w * .8, 0);
	rectangle(x + (w / 2.0) + (w * .2), y, w * .08, w * .8, 1);
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .32), y + (w / 2.0) + (w * .22), w * .6, w * .08, 0);
	rectangle(x + (w / 2.0) - (w * .32), y + (w / 2.0) + (w * .22), w * .6, w * .08, 1);
	hq_uniform;
	rectangle(x + (w / 2.0) - (w * .32), y, w * .08, w * 2, 0);
	rectangle(x + (w / 2.0) - (w * .32), y, w * .08, w * 2, 1);
}

void class_chalk(int x, int y, int w, int tx, int ty, int r, int a, int b)
{
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2.0) - (w * .52), y + (w / 2.0) - w * .25, 0);
	glRotatef(r, 0, 0, 1);
	glTranslatef(-(x + (w / 2.0) - (w * .52)), -(y + (w / 2.0) - w * .25), 0);

	glColor4ub(255, 255, 255, a);
	rectangle(x + (w / 2.0) - (w * .52), y, w * .1, w * .5, 0);
	rectangle(x + (w / 2.0) - (w * .52), y, w * .1, w * .5, b);
	glPopMatrix();
}

//==============================================================================================THIS IS FOR SCENE CD======================================================================================
void windowLeft_texture(int x, int y, int w, int h, unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex2i(x, y);
	glTexCoord2i(1, 0); glVertex2i(x + w, y);
	glTexCoord2i(0, 1); glVertex2i(x + (w / 400), y - h);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void windowRight_texture(int x, int y, int w, int h, unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glBegin(GL_POLYGON);
	glTexCoord2i(0, 0); glVertex2i(x, y);
	glTexCoord2i(1, 0); glVertex2i(x + w, y);
	glTexCoord2i(1, 1); glVertex2i(x + (w / 1), y - h);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void floor_texture(int x, int y, int w, int h, unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(x, y);
	glTexCoord2i(1, 0); glVertex2i(x + w, y);
	glTexCoord2i(1, 1); glVertex2i(x + w, y + h);
	glTexCoord2i(0, 1); glVertex2i(x, y + h);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void forMess(int x, int y, int w, int h, bool border) {
	if (border == 1)
	{
		black;
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
	}
	else
		glBegin(GL_POLYGON);

	glBegin(GL_POLYGON);
	glVertex2i(x - -0.41 * w, y + h);
	glVertex2i(x + 1.5 * w, y + h);
	glVertex2i(x + w, y + h + h / 2);
	glVertex2i(x, y + h + h / 2);
	glEnd();
}

void backgroundScene20(int x, int y, int w) {
	int h = 0.75 * w;

	clear;
	rectangle_texture(x, y, w, h, tex_space, tex_spaceX, tex_spaceY);
}

void backgroundScene20Up(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(58, 91, 181);
	rectangle(x, y, w, h, 0);
}

void backgroundScene20Down(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(58, 91, 181);
	rectangle(x, y, w, h, 0);
}

void backgroundScene20Left(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(58, 91, 181);
	glBegin(GL_POLYGON);
	glVertex2i(x - 0.1 * w, y + h);
	glVertex2i(x + 0.61 * w, y + h);
	glVertex2i(x + w, y + h + h / 2);
	glVertex2i(x, y + h + h / 2);
	glEnd();
}

void backgroundScene20Right(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(58, 91, 181);
	glBegin(GL_POLYGON);
	glVertex2i(x - -0.41 * w, y + h);
	glVertex2i(x + 1.1 * w, y + h);
	glVertex2i(x + w, y + h + h / 2);
	glVertex2i(x, y + h + h / 2);
	glEnd();
}

void windowLeft(int x, int y, int w) {

	int h = 0.75 * w;
	clear;
	windowLeft_texture(x, y, w, h, tex_windows, tex_windowsX, tex_windowsY);
}

void windowRight(int x, int y, int w) {

	int h = 0.75 * w;
	clear;
	windowRight_texture(x, y, w, h, tex_windows, tex_windowsX, tex_windowsY);
}

void floor(int x, int y, int w) {
	int h = 0.75 * w;

	floor_texture(x, y, w, h, tex_floor, tex_floorX, tex_floorY);
}

void ceiling(int x, int y, int w) {
	int h = 0.75 * w;
	floor_texture(x, y, w, h, tex_ceiling, tex_ceilingX, tex_ceilingY);
}

void backgroundMess(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(0, 0, 20);
	rectangle(x, y, w, h, 0);

}

void backgroundMess2(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(58, 91, 181);
	glBegin(GL_POLYGON);
	glVertex2i(x - -0.41 * w, y + h);
	glVertex2i(x + 1.5 * w, y + h);
	glVertex2i(x + w, y + h + h / 2);
	glVertex2i(x, y + h + h / 2);
	glEnd();
	forMess(x, y, w, h, 1);

}

void bg_floor2(int x, int y, int w)
{
	int h = 0.75 * w;

	clear;
	rectangle_texture(x, y, w, h, tex_space, tex_spaceX, tex_spaceY);

}

void holeToLevelBelowbg(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(58, 91, 181);
	glBegin(GL_POLYGON);
	glVertex2i(x - 1 * w, y + h);
	glVertex2i(x + 0 * w, y + h);
	glVertex2i(x + w, y + h + h / 0.37);
	glVertex2i(x, y + h + h / 0.37);
	glEnd();

}

void holeToLevelBelow(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(0, 0, 81);
	glBegin(GL_POLYGON);
	glVertex2i(x - 1 * w, y + h);
	glVertex2i(x + 0 * w, y + h);
	glVertex2i(x + w, y + h + h / 0.37);
	glVertex2i(x, y + h + h / 0.37);
	glEnd();

}

void holeToLevelBelow1(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(0, 0, 61);
	glBegin(GL_POLYGON);
	glVertex2i(x - 1 * w, y + h);
	glVertex2i(x + 0 * w, y + h);
	glVertex2i(x + w, y + h + h / 0.37);
	glVertex2i(x, y + h + h / 0.37);
	glEnd();

}

void holeToLevelBelow2(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(0, 0, 41);
	glBegin(GL_POLYGON);
	glVertex2i(x - 1 * w, y + h);
	glVertex2i(x + 0 * w, y + h);
	glVertex2i(x + w, y + h + h / 0.37);
	glVertex2i(x, y + h + h / 0.37);
	glEnd();

}

void holeToLevelBelow3(int x, int y, int w) {
	int h = 0.75 * w;

	glColor3ub(0, 0, 21);
	glBegin(GL_POLYGON);
	glVertex2i(x - 1 * w, y + h);
	glVertex2i(x + 0 * w, y + h);
	glVertex2i(x + w, y + h + h / 0.37);
	glVertex2i(x, y + h + h / 0.37);
	glEnd();

}

void kubid20(int x, int y, int tx, int ty, float rotate_all, float sx, float sy)
{
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glColor3ub(255, 51, 51);
	nGon(128, x, y, 10, 0);
	nGon(128, x, y, 10, 1);
	glPopMatrix();
}

void kubid21(int x, int y, int w, int tx, int ty, float rotate_all, float sx, float sy, int spike)
{
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glColor3ub(255, 51, 51);
	triangle(x + (w / 2) - (w), y, w, spike, 0);
	triangle(x + (w / 2) - (w), y, w, spike, 1);

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(-(x), -y, 0);
	glColor3ub(255, 51, 51);
	triangle(x + (w / 2) - (w), y, w, spike, 0);
	triangle(x + (w / 2) - (w), y, w, spike, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-(x), -y, 0);
	glColor3ub(255, 51, 51);
	triangle(x + (w / 2) - (w), y, w, spike, 0);
	triangle(x + (w / 2) - (w), y, w, spike, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-(x), -y, 0);
	glColor3ub(255, 51, 51);
	triangle(x + (w / 2) - (w), y, w, spike, 0);
	triangle(x + (w / 2) - (w), y, w, spike, 1);
	glPopMatrix();

	glColor3ub(255, 51, 51);
	nGon(128, x, y, w, 0);
	nGon(128, x, y, w, 1);
	glPopMatrix();
}
//=======================================================================================THIS IS THE END OF SCENE CD======================================================================================

void SceneA1()
{
	hq_building_wall;
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	clock(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 500, sceneA_clockX, sceneA_clockY, sceneA_clockSX, sceneA_clockSY);
}

void SceneA2()
{
	hq_building_wall;
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	chara_hq(760, -1000, 400, sceneA2_hqX, sceneA2_hqY, sceneA2_hqR, 0, 0, 0, 0, 0, 0, 0, 0, sceneA2_hqSX, sceneA2_hqSY);
	hq_monitor_rear(0, -1080, 500, 0, sceneA2_hqY);

	glColor4ub(255, 0, 0, alarm_alpha);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	string subtitles[2] =
	{
		"",
		"HQ: Hmm. What should I eat for lunch today?",
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void SceneA3()
{
	hq(0, 0, 1920);
	glColor4ub(255, 0, 0, alarm_alpha);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void SceneA4()
{
	hq(0, 0, 1920);
	chara_hq(1100, 450, 100, sceneA_alphaX, sceneA_alphaY, sceneA_alphaR, 0, 0, 0, 0, 0, 0, 0, 0, sceneA_alphaSX, sceneA_alphaSY);
	chara_alpha(2000, 450, 100, sceneA4_alphaX, 0, 0, sceneA4_alpha_upperarmL, sceneA4_alpha_lowerarmL, 0, 0, 0, 0, 0, 0, 1, 1);
	chara_beta(2250, 450, 100, sceneA4_alphaX, 0, 0, sceneA4_alpha_upperarmL, sceneA4_alpha_lowerarmL, 0, 0, 0, 0, 0, 0, 1, 1);//135 110 salute, follow alpha pos

	string subtitles[5] =
	{
		"",
		"HQ: Bring me the rescue team now!",
		"A & B: We're here, sir!",
		"HQ: I need you guys to investigate the ISS & find any survivors.",
		"A & B: Roger!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void SceneB()
{
	clear;
	if (Y < 1150)
	{
		rectangle_texture(0, 0, 1920, 1080, tex_space, tex_spaceX, tex_spaceY);

		glColor3ub(0, 255, 0);
		rectangle(0, 0, SCREEN_WIDTH, 110, 0);
		rectangle(0, 0, SCREEN_WIDTH, 110, 1);
		glColor3ub(173, 200, 250);
		rectangle(0, 50, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		rectangle(0, 50, SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		glColor3ub(40, 40, 40);
		rectangle(530, 50, 30, 20, 0);
		rectangle(530, 50, 30, 20, 1);
		glColor3ub(40, 40, 40);
		rectangle(380, 50, 30, 20, 0);
		rectangle(380, 50, 30, 20, 1);

		glColor3ub(40, 40, 40);
		rectangle(300, 50, 55, 500, 0);
		rectangle(300, 50, 55, 500, 1);

		glColor3ub(40, 40, 40);
		rectangle(355, 70, 230, 10, 0);
		rectangle(355, 70, 230, 10, 1);

		rocket();
		chara_alpha(1600, 200, 50, sceneB_alphaX, sceneB_alphaY, 35, -60, -30, 90, -80, -70, 75, -10, 100, sceneB_alphaSX, sceneB_alphaSY);
		chara_beta(1900, 200, 50, sceneB_alphaX, sceneB_alphaY, 35, -60, -30, 90, -80, -70, 75, -10, 100, sceneB_alphaSX, sceneB_alphaSY);
	}
	else if (Y > 1130)
	{
		clear;
		rectangle_texture(0, 0, 1920, 1080, tex_space, tex_spaceX, tex_spaceY);
		glColor3ub(0, 0, 13);
		rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		rocket_after();
		glColor3ub(255, 255, 255);
		rectangle(0, 400, 370, 60, 0);
		glColor3ub(255, 255, 255);
		rectangle(0, 1000, 600, 60, 0);
	}

	string subtitles[4] =
	{
		"",
		"Alpha: Alpha & Beta. Preparing for take off.",
		"HQ: 3..2..1..Launch confirmed!",
		"Beta: We're approaching the ISS."
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

//=============================================================MY SCENE =====================================================================================================================================
void testSceneCD1()
{

	backgroundScene20(152, -200, 1640);
	backgroundScene20Up(-500, 800, 5000);
	backgroundScene20Down(-50, -1100, 2000);
	backgroundScene20Left(-500, -402, 1070);
	backgroundScene20Right(1350, -402, 1070);
	windowLeft(-50, 800, 530);
	windowRight(1450, 800, 530);
	floor(-5, -1200, 1950);
	ceiling(-5, 859, 1950);
	backgroundMess(300, 290, 120); backgroundMess2(300, 155, 120);
	backgroundMess(1850, 290, 120); backgroundMess2(1650, 105, 120);
	backgroundMess(1050, 290, 50); backgroundMess2(1050, 236, 50);
	backgroundMess(-40, 810, 50); backgroundMess2(-40, 756, 50);
	backgroundMess(800, 810, 50); backgroundMess2(800, 156, 50);
	chara_alpha(0, 600, 100, sceneCD_alphaX, sceneCD_alphaY, sceneCD_alphaR, 10, 10, 10, 10, -20, -20, -10, -10, sceneCD_alphaSX, sceneCD_alphaSY);
	chara_beta(300, 600, 100, sceneCD_betaX, sceneCD_betaY, sceneCD_betaR, 10, 10, 10, 10, -20, -20, -10, -10, sceneCD_betaSX, sceneCD_betaSY);

	string subtitles[3] =
	{
		"",
		"Alpha: This place is a mess.",
		"Beta: What the hell happened here?"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void testSceneCD2()
{
	bg_floor2(0, -200, 1940);
	backgroundScene20Up(-500, 800, 5000);
	ceiling(-5, 859, 1950);
	backgroundScene20Down(-50, -1100, 2000);
	floor(-5, -1200, 1950);
	holeToLevelBelowbg(635, 465, 530);
	holeToLevelBelow(615, 495, 490);
	holeToLevelBelow1(645, 555, 490);
	holeToLevelBelow2(675, 615, 490);
	holeToLevelBelow3(705, 675, 490);
	backgroundMess(1000, 290, 120); backgroundMess2(1000, 155, 120);
	backgroundMess(-70, 290, 120); backgroundMess2(-70, 105, 120);
	backgroundMess(460, 810, 50); backgroundMess2(460, 156, 50);
	backgroundMess(1500, 810, 50); backgroundMess2(1500, 756, 50);
	backgroundMess(1750, 265, 50); backgroundMess2(1750, 211, 50);
	chara_alpha(350, 1080, 100, sceneCD2_alphaX, sceneCD2_alphaY, sceneCD2_alphaR, -20, -20, 20, 20, -45, 45, 45, -45, sceneCD2_alphaSX, sceneCD2_alphaSY);
	chara_beta(380, 1080, 100, sceneCD2_betaX, sceneCD2_betaY, sceneCD2_betaR, -20, -20, 20, 20, -45, 45, 45, -45, sceneCD2_betaSX, sceneCD2_betaSY);
	chara_dead(1612, 310, 80, sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, 0, 0, 10, 25, -120, 100, 120, -100, sceneCD_deadSX, sceneCD_deadSY, 255);

	string subtitles[2] =
	{
		"",
		"Alpha: HQ, we found someone!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void testSceneCD3()
{
	bg_floor2(0, -200, 1940);
	backgroundScene20Up(-500, 800, 5000);
	ceiling(-5, 859, 1950);
	backgroundScene20Down(-50, -1100, 2000);
	floor(-5, -1200, 1950);
	holeToLevelBelowbg(635, 465, 530);
	holeToLevelBelow(615, 495, 490);
	holeToLevelBelow1(645, 555, 490);
	holeToLevelBelow2(675, 615, 490);
	holeToLevelBelow3(705, 675, 490);
	backgroundMess(1000, 290, 120); backgroundMess2(1000, 155, 120);
	backgroundMess(-70, 290, 120); backgroundMess2(-70, 105, 120);
	backgroundMess(460, 810, 50); backgroundMess2(460, 156, 50);
	backgroundMess(1500, 810, 50); backgroundMess2(1500, 756, 50);
	backgroundMess(1750, 265, 50); backgroundMess2(1750, 211, 50);
	chara_alpha(218, 420, 100, sceneCD3_alphaX, sceneCD3_alphaY, sceneCD3_alphaR, 10, 10, 10, 10, -20, -20, -10, -10, sceneCD3_alphaSX, sceneCD3_alphaSY);
	chara_beta(512, 420, 100, sceneCD3_betaX, sceneCD3_betaY, sceneCD3_betaR, 10, 10, 10, 10, -20, -20, -10, -10, sceneCD3_betaSX, sceneCD3_betaSY);
	chara_dead(1612, 310, 80, sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, 0, 0, 10, 25, -120, 100, 120, -100, sceneCD_deadSX, sceneCD_deadSY, 255);

	string subtitles[2] =
	{
		"",
		"HQ: Proceed with caution."
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void testSceneCD4()
{
	bg_floor2(0, -200, 1940);
	backgroundScene20Up(-500, 800, 5000);
	ceiling(-5, 859, 1950);
	backgroundScene20Down(-50, -1100, 2000);
	floor(-5, -1200, 1950);
	holeToLevelBelowbg(635, 465, 530);
	holeToLevelBelow(615, 495, 490);
	holeToLevelBelow1(645, 555, 490);
	holeToLevelBelow2(675, 615, 490);
	holeToLevelBelow3(705, 675, 490);
	backgroundMess(1000, 290, 120); backgroundMess2(1000, 155, 120);
	backgroundMess(-70, 290, 120); backgroundMess2(-70, 105, 120);
	backgroundMess(460, 810, 50); backgroundMess2(460, 156, 50);
	backgroundMess(1500, 810, 50); backgroundMess2(1500, 756, 50);
	backgroundMess(1750, 265, 50); backgroundMess2(1750, 211, 50);
	chara_alpha(218, 420, 100, sceneCD3_alphaX, sceneCD3_alphaY, 0, 0, 0, 0, 0, 0, 0, 0, 0, sceneCD3_alphaSX, sceneCD3_alphaSY);
	chara_beta(512, 380, 100, sceneCD3_betaX, sceneCD3_betaY, 0, -10, 0, 40, 50, -20, -60, 100, -100, sceneCD3_betaSX, sceneCD3_betaSY);
	kubid21(1650, 450, 10, sceneKubid20X, sceneKubid20Y, sceneKubid20R, sceneKubid20SX, sceneKubid20SY, kubidspike);
	kubid20(1650, 450, sceneKubid20X1, sceneKubid20Y1, sceneKubid20R1, sceneKubid20SX1, sceneKubid20SY1);
	kubid20(1650, 450, sceneKubid20X2, sceneKubid20Y2, sceneKubid20R2, sceneKubid20SX2, sceneKubid20SY2);
	chara_dead(1612, 310, 80, sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, 0, 0, 10, 25, -120, 100, 120, -100, sceneCD_deadSX, sceneCD_deadSY, 255);

	string subtitles[2] =
	{
		"",
		"Alpha: WATCH OUT!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void testSceneCD5()
{
	bg_floor2(0, -200, 1940);
	backgroundScene20Up(-500, 800, 5000);
	ceiling(-5, 859, 1950);
	backgroundScene20Down(-50, -1100, 2000);
	floor(-5, -1200, 1950);
	holeToLevelBelowbg(635, 465, 530);
	holeToLevelBelow(615, 495, 490);
	holeToLevelBelow1(645, 555, 490);
	holeToLevelBelow2(675, 615, 490);
	holeToLevelBelow3(705, 675, 490);
	backgroundMess(1000, 290, 120); backgroundMess2(1000, 155, 120);
	backgroundMess(-70, 290, 120); backgroundMess2(-70, 105, 120);
	backgroundMess(460, 810, 50); backgroundMess2(460, 156, 50);
	backgroundMess(1500, 810, 50); backgroundMess2(1500, 756, 50);
	backgroundMess(1750, 265, 50); backgroundMess2(1750, 211, 50);
	chara_alpha(558, 420, 100, sceneCD5_alphaX, sceneCD5_alphaY, 0, -80, -50, -100, -60, 20, 20, 40, 50, sceneCD5_alphaSX, sceneCD5_alphaSY);
	chara_beta(312, 180, 100, sceneCD3_betaX, sceneCD3_betaY, 90, -10, 0, 10, 20, -20, -60, 50, -90, sceneCD3_betaSX, sceneCD3_betaSY);

	kubid21(1650, 450, 10, sceneKubid20X, sceneKubid20Y, sceneKubid20R, sceneKubid20SX, sceneKubid20SY, kubidspike);
	kubid20(1650, 450, sceneKubid20X1, sceneKubid20Y1, sceneKubid20R1, sceneKubid20SX1, sceneKubid20SY1);
	kubid20(1650, 450, sceneKubid20X2, sceneKubid20Y2, sceneKubid20R2, sceneKubid20SX2, sceneKubid20SY2);
	chara_dead(1612, 310, 80, sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, 0, 0, 10, 25, -120, 100, 120, -100, sceneCD_deadSX, sceneCD_deadSY, 255);

	string subtitles[2] =
	{
		"",
		"Alpha: BETA!! NOOOO!!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void testSceneCD6()
{
	bg_floor2(0, -200, 1940);
	backgroundScene20Up(-500, 800, 5000);
	ceiling(-5, 859, 1950);
	backgroundScene20Down(-50, -1100, 2000);
	floor(-5, -1200, 1950);
	holeToLevelBelowbg(635, 465, 530);
	holeToLevelBelow(615, 495, 490);
	holeToLevelBelow1(645, 555, 490);
	holeToLevelBelow2(675, 615, 490);
	holeToLevelBelow3(705, 675, 490);
	backgroundMess(1000, 290, 120); backgroundMess2(1000, 155, 120);
	backgroundMess(-70, 290, 120); backgroundMess2(-70, 105, 120);
	backgroundMess(460, 810, 50); backgroundMess2(460, 156, 50);
	backgroundMess(1500, 810, 50); backgroundMess2(1500, 756, 50);
	backgroundMess(1750, 265, 50); backgroundMess2(1750, 211, 50);
	chara_alpha(558, 350, 100, sceneCD5_alphaX, sceneCD5_alphaY, 0, 0, -50, 0, 50, -100, 90, 100, -90, sceneCD5_alphaSX, sceneCD5_alphaSY);
	chara_beta(312, 180, 100, sceneCD3_betaX, sceneCD3_betaY, 90, -10, 0, 10, 20, -20, -60, 50, -90, sceneCD3_betaSX, sceneCD3_betaSY);

	kubid21(1650, 450, 10, sceneKubid20X, sceneKubid20Y, sceneKubid20R, sceneKubid20SX, sceneKubid20SY, kubidspike);
	kubid20(1650, 450, sceneKubid20X1, sceneKubid20Y1, sceneKubid20R1, sceneKubid20SX1, sceneKubid20SY1);
	kubid20(1650, 450, sceneKubid20X2, sceneKubid20Y2, sceneKubid20R2, sceneKubid20SX2, sceneKubid20SY2);
	chara_dead(1612, 310, 80, sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, 0, 0, 10, 25, -120, 100, 120, -100, sceneCD_deadSX, sceneCD_deadSY, 255);
}

void testSceneCD7()
{
	bg_floor2(0, -200, 1940);
	backgroundScene20Up(-500, 800, 5000);
	ceiling(-5, 859, 1950);
	backgroundScene20Down(-50, -1100, 2000);
	floor(-5, -1200, 1950);
	holeToLevelBelowbg(635, 465, 530);
	holeToLevelBelow(615, 495, 490);
	holeToLevelBelow1(645, 555, 490);
	holeToLevelBelow2(675, 615, 490);
	holeToLevelBelow3(705, 675, 490);
	backgroundMess(1000, 290, 120); backgroundMess2(1000, 155, 120);
	backgroundMess(-70, 290, 120); backgroundMess2(-70, 105, 120);
	backgroundMess(460, 810, 50); backgroundMess2(460, 156, 50);
	backgroundMess(1500, 810, 50); backgroundMess2(1500, 756, 50);
	backgroundMess(1750, 265, 50); backgroundMess2(1750, 211, 50);
	chara_alpha(300, 550, 100, sceneCD6_alphaX, sceneCD6_alphaY, 0, -180, 0, 180, 0, 0, 0, 0, 0, sceneCD6_alphaSX, sceneCD6_alphaSY);
	chara_beta(312, 180, 100, sceneCD3_betaX, sceneCD3_betaY, 90, -10, 0, 10, 20, -20, -60, 50, -90, sceneCD3_betaSX, sceneCD3_betaSY);

	kubid21(1650, 450, 10, sceneKubid20X, sceneKubid20Y, sceneKubid20R, sceneKubid20SX, sceneKubid20SY, kubidspike);
	kubid20(1650, 450, sceneKubid20X1, sceneKubid20Y1, sceneKubid20R1, sceneKubid20SX1, sceneKubid20SY1);
	kubid20(1650, 450, sceneKubid20X2, sceneKubid20Y2, sceneKubid20R2, sceneKubid20SX2, sceneKubid20SY2);
	kubid20(1650, 450, sceneKubid20X6, sceneKubid20Y6, sceneKubid20R6, sceneKubid20SX6, sceneKubid20SY6);
	chara_dead(1612, 310, 80, sceneCD_deadX, sceneCD_deadY, sceneCD_deadR, 0, 0, 10, 25, -120, 100, 120, -100, sceneCD_deadSX, sceneCD_deadSY, 255);

	string subtitles[2] =
	{
		"",
		"Alpha: HQ! Beta has been killed. I repeat. Beta has been killed!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void testSceneCD8()
{
	backgroundScene20(152, -200, 1640);
	backgroundScene20Up(-500, 800, 5000);
	backgroundScene20Down(-50, -1100, 2000);
	backgroundScene20Left(-500, -402, 1070);
	backgroundScene20Right(1350, -402, 1070);
	windowLeft(-50, 800, 530);
	windowRight(1450, 800, 530);
	floor(-5, -1200, 1950);
	ceiling(-5, 859, 1950);
	backgroundMess(300, 290, 120); backgroundMess2(300, 155, 120);
	backgroundMess(1850, 290, 120); backgroundMess2(1650, 105, 120);
	backgroundMess(1050, 290, 50); backgroundMess2(1050, 236, 50);
	backgroundMess(-40, 810, 50); backgroundMess2(-40, 756, 50);
	backgroundMess(800, 810, 50); backgroundMess2(800, 156, 50);
	kubid20(3700, 1000, sceneKubid20X3, sceneKubid20Y3, sceneKubid20R3, sceneKubid20SX3, sceneKubid20SY3);
	kubid20(3200, 900, sceneKubid20X5, sceneKubid20Y5, sceneKubid20R5, sceneKubid20SX5, sceneKubid20SY5);
	kubid20(3500, 800, sceneKubid20X3, sceneKubid20Y3, sceneKubid20R3, sceneKubid20SX3, sceneKubid20SY3);
	kubid20(3000, 700, sceneKubid20X4, sceneKubid20Y4, sceneKubid20R4, sceneKubid20SX4, sceneKubid20SY4);
	kubid20(3600, 600, sceneKubid20X3, sceneKubid20Y3, sceneKubid20R3, sceneKubid20SX3, sceneKubid20SY3);
	kubid20(2730, 500, sceneKubid20X3, sceneKubid20Y3, sceneKubid20R3, sceneKubid20SX3, sceneKubid20SY3);
	kubid20(2600, 400, sceneKubid20X5, sceneKubid20Y5, sceneKubid20R5, sceneKubid20SX5, sceneKubid20SY5);
	kubid20(2500, 300, sceneKubid20X4, sceneKubid20Y4, sceneKubid20R4, sceneKubid20SX4, sceneKubid20SY4);
	kubid20(2800, 200, sceneKubid20X3, sceneKubid20Y3, sceneKubid20R3, sceneKubid20SX3, sceneKubid20SY3);
	kubid20(2100, 100, sceneKubid20X4, sceneKubid20Y4, sceneKubid20R4, sceneKubid20SX4, sceneKubid20SY4);
	kubid20(3650, 0, sceneKubid20X4, sceneKubid20Y4, sceneKubid20R4, sceneKubid20SX4, sceneKubid20SY4);
	chara_alpha(1800, 440, 100, sceneCD7_alphaX, sceneCD7_alphaY, sceneCD7_alphaR, -80, -50, -100, -60, 20, 20, 40, 50, sceneCD7_alphaSX, sceneCD7_alphaSY);

	glColor4ub(0, 0, 0, CD8_alpha);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	string subtitles[5] =
	{
		"",
		"HQ: Get to the shuttle now!",
		"Alpha: Huh? The door's jammed.",
		"Alpha: Oh god.",
		"HQ: Alpha? Are you there? Answer me!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}
//==========================================================================================================================================================================================================

void SceneCloseUp()
{
	glColor3ub(58, 91, 181);
	rectangle(0, 0, SCREEN_WIDTH, 394, 0);
	glColor3ub(25, 39, 80);
	rectangle(0, 394, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	chara_dead(650, -310, 600, sceneCloseUp_deadX, sceneCloseUp_deadY, sceneCloseUp_deadR, 0, 0, 10, 25, -120, 100, 120, -100, 1, 1, visor_alpha);
	chara_beta(750, -1010, 600, 0, 0, 90, 0, 0, 90, sceneCloseUp_betaR, 0, 0, 0, 0, 1, 1);

	string subtitles[5] =
	{
		"",
		"Beta: Hey! We received your distress signal.",
		"Beta: Tell us what's going on here.",
		"Beta: Hello? Are you with us?",
		"Beta: What the f#@$!"
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void SceneDKP()
{
	glColor3ub(240, 233, 195);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	class_table(700, 0, 300);
	class_chair(300, 0, 300);
	chara_dr(2080, 470, 140, sceneDKP_drX, sceneDKP_drY, sceneDKP_drR, sceneDKP_drUpperarmL, sceneDKP_drLowerarmL, 0, 0, 0, 0, 0, 0, sceneA_alphaSX, sceneA_alphaSY);
	chara_student(400, 380, 120, sceneDKP_studentX, sceneDKP_studentY, sceneDKP_studentR, 0, 90, sceneDKP_studentUpperarmR, sceneDKP_studentLowerarmR, 90, -90, 90, -90, sceneA_alphaSX, sceneA_alphaSY);
	class_chalk(1333, 593, 100, sceneDKP_chalkX, sceneDKP_chalkY, sceneDKP_chalkR, chalk_alpha, chalk_border);

	glColor4ub(0, 0, 0, dkp_alpha);
	rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (dream)
	{
		white;
		nGon(16, 629, 711, 30, 0);
		nGon(16, 554, 662, 20, 0);
		rectangle(296, 764, 400, 200, 0);
		nGon(16, 629, 711, 30, 1);
		nGon(16, 554, 662, 20, 1);
		rectangle(296, 764, 400, 200, 1);
		black;
		glPushMatrix();
		glTranslatef(493, 860, 0);
		glScalef(dreamScale, dreamScale, 0);
		glTranslatef(-493, -860, 0);
		rectangle(330, 786, 335, 155, 0);
		glPopMatrix();
	}

	string subtitles[5] =
	{
		"",
		"Edward: Zzzz...Zzzz",
		"Edward: Heh...Ez",
		"Dr. James: DON'T SLEEP DURING MY LECTURE!",
		"Edward: Sorry, sir."
	};
	subtitle(subtitles[current_subtitle].c_str(), SCREEN_HEIGHT * subtitle_offsetY);
}

void rocketA(int x, int y, int w, int h, int tx, int ty, float rotate_all, float sx, float sy)
{

	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glTranslatef(x + (w / 2), y, 0);
	glRotatef(rotate_all, 0, 0, 1);
	glScalef(sx, sy, 0);
	glTranslatef(-(x + (w / 2)), -y, 0);

	//rocket body
	glColor3ub(211, 211, 211);
	rectangle(x, y, w, h * 0.66, 0);
	//rocket head
	red_strip;
	righttriangle(x, y + h * 0.66, w, h * 0.33);
	//rockettail
	righttriangle(x + w, y, w * 0.66, h * 0.25);

	black;
	rectangle(x + w * 0.2, y - 40, 40, 40, 0);
	rectangle(x + w * 0.6, y - 40, 40, 40, 0);
}

void earth(int n, int x, int y, int r)
{
	nGon(n, x, y, r, 0);
}

void scene1()
{
	glClearColor(0, 0, 50, 0);
	/*red_strip;
	righttriangle(1220, 830, 250, 200);
	glColor3ub(211,211,211);
	red_strip;
	righttriangle(1470, 150, 200, 150);
	white;
	rectangle(1260, 110, 40, 40);
	rectangle(1380, 110, 40, 40);*/
	white;
	rectangle(1480, 650, 200, 50, 0);
	rectangle(1680, 620, 250, 100, 0);
	rocketA(1220, 200, 250, 850, scene1X, scene1Y, scene1R, scene1SX, scene1SY);
}

void scene2()
{
	glPushMatrix();
	//glTranslatef(tx, ty, 0);
	glScalef(.5, .5, 0);
	//glTranslatef(tx, ty, 0);
	glClearColor(0, 0, 50, 0);
	white;
	earth(100, -10, -500, 1000);
	rocketA(1220, 200, 250, 850, scene2X, scene2Y, scene2R, scene2SX, scene2SY);
	glPopMatrix();
}

//animate things here
void animator(int)
{
	switch (scene)
	{
	case 0:
		break;
	case 1:
		switch (sceneA)
		{
		case 0:
			if (sceneA_clockMins <= -10)
			{
				if (sceneA_clockSX >= .6)
				{
					sceneA_clockSX -= .005;
					sceneA_clockSY -= .005;
				}
				else
				{
					sceneA = 1;
				}
			}
			break;
		case 1:
			if (sceneA_clockY < 1100)
			{
				sceneA_clockY += 10;
			}
			else
			{
				sceneA = 2;
			}
			break;
		default:
			break;
		}
		break;
	case 2:
		if (sceneA2_hqY < 1050)
		{
			sceneA2_hqY += 10;
		}
		else
		{
			if (sceneA2_time < 400)
			{
				current_subtitle = 1;
			}
			else
			{
				current_subtitle = 0;
				sceneA = 3;
			}

			if (alarm_alpha <= 100 && sceneA == 3)
			{
				alarm_alpha += 5;
			}
			else
			{
				alarm_alpha = 0;
			}
		}
		break;
	case 3:
		sceneA4_hqY = 0;
		bouncing_ballX += bouncing_ballDX;
		bouncing_ballY += bouncing_ballDY;

		if (bouncing_ballX < 0 || bouncing_ballX > 300)
		{
			bouncing_ballDX *= -1;
		}

		if (bouncing_ballY < 0 || bouncing_ballY > 82)
		{
			bouncing_ballDY *= -1;
		}

		if (alarm_alpha <= 100 && sceneA == 3)
		{
			alarm_alpha += 5;
		}
		else
		{
			alarm_alpha = 0;
		}
		break;
	case 4:
		if (elapsed_time >= 5000)
		{
			crash = TRUE;
		}
		else if (elapsed_time < 5000)
		{
			crash = FALSE;
		}

		sceneA4_hqY = -1000;
		bouncing_ballX += bouncing_ballDX;
		bouncing_ballY += bouncing_ballDY;

		if (bouncing_ballX < 0 || bouncing_ballX > 300)
		{
			bouncing_ballDX *= -1;
		}

		if (bouncing_ballY < 0 || bouncing_ballY > 82)
		{
			bouncing_ballDY *= -1;
		}

		if (sceneA4_alphaX >= -550 && sceneA4_time <= 229)
		{
			sceneA4_alphaX -= 5;
		}

		if (sceneA4_alphaX >= -250)
		{
			current_subtitle = 1;
		}
		else if (sceneA4_alphaX >= -554 && sceneA4_alphaX < -250)
		{
			current_subtitle = 2;
		}

		if (sceneA4_time >= 233 && sceneA4_time < 341)
		{
			current_subtitle = 3;
		}

		if (sceneA4_time >= 341 && sceneA4_time <= 380)
		{
			current_subtitle = 4;

			if (sceneA4_alpha_upperarmL > -120)
			{
				sceneA4_alpha_upperarmL -= 15;
				sceneA4_alpha_lowerarmL -= 15;
			}
		}
		else if (sceneA4_time >= 380 && sceneA4_time <= 400)
		{
			if (sceneA4_alpha_upperarmL < 0)
			{
				sceneA4_alpha_upperarmL += 15;
				sceneA4_alpha_lowerarmL += 15;
			}
		}
		else if (sceneA4_time > 400)
		{
			current_subtitle = 0;
			sceneA4_alphaX += 5;
		}
		break;
	case 5:
		if (sceneB_alphaX > -1000)
		{
			//2 orang masuk
			current_subtitle = 1;
			sceneB_alphaX -= 12;
		}
		else if (sceneB_alphaX < 1 && Y < 150)
		{
			//Roket gerak atas
			Y = Y + 2;
			sceneB_alphaY = -800;
			current_subtitle = 2;
		}
		else if (Y > 130 && Y < 1200)
		{
			Y = Y + 10;
			current_subtitle = 2;
		}

		if (Y_after < 300 && Y > 1150)
		{
			Y_after = Y_after + 5;
			current_subtitle = 3;
		}
		else if (Y_after == 290)
		{
			Y = 0;
			Y = Y - 3;
		}
		break;
	case 6:
		if (sceneCD_alphaX != 835 && sceneCD_alphaY != 655)
		{
			sceneCD_alphaX += 10;
			sceneCD_alphaR = -15;
		}

		if (sceneCD_betaX != 835 && sceneCD_betaY != 655)
		{
			sceneCD_betaX += 10;
			sceneCD_betaR = -15;
		}

		if (sceneCD_alphaX <= 800)
		{
			current_subtitle = 1;
		}
		else
		{
			current_subtitle = 2;
		}
		break;
	case 7:
		current_subtitle = 1;

		if (sceneCD2_alphaY >= -655)
		{
			sceneCD2_alphaY -= 10;
			sceneCD2_alphaX += -2;
		}

		if (sceneCD2_betaY >= -655)
		{
			sceneCD2_betaY -= 10;
			sceneCD2_betaX += 2;
		}
		break;
	case 8:
		if (sceneCD3_alphaX >= -655 && sceneCD3_alphaX <= 500)
		{
			current_subtitle = 1;
			sceneCD3_alphaX += 5;
			sceneCD3_alphaR = -15;
		}

		if (sceneCD3_betaX >= -655 && sceneCD3_betaX <= 800)
		{
			sceneCD3_betaX += 10;
			sceneCD3_betaR = -15;
		}
		break;
	case 9:
		if (elapsed_time < 2000)
		{
			sceneCloseUp_betaR = -20;
			current_subtitle = 1;
			visor_alpha = 255;
		}

		if (elapsed_time > 2000 && elapsed_time <= 3000 && sceneCloseUp_deadR >= -10)
		{
			sceneCloseUp_deadR -= 1;
			sceneCloseUp_betaR -= 1;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4500 && sceneCloseUp_deadR <= 10)
		{
			sceneCloseUp_deadR += 2;
			sceneCloseUp_betaR += 2;
			current_subtitle = 2;
		}
		else if (elapsed_time > 4500 && elapsed_time <= 6000 && sceneCloseUp_deadR >= -10)
		{
			sceneCloseUp_deadR -= 2;
			sceneCloseUp_betaR -= 2;
		}
		else if (elapsed_time > 6000 && elapsed_time <= 7000 && sceneCloseUp_deadR <= 0)
		{
			current_subtitle = 3;
			sceneCloseUp_deadR += 1;

			if (sceneCloseUp_deadR >= 0)
			{
				sceneCloseUp_deadR = 0;
			}
			if (sceneCloseUp_betaR <= -20)
			{
				sceneCloseUp_betaR += 1;
			}
		}
		else if (elapsed_time > 8000)
		{
			visor_alpha = 0;
			current_subtitle = 4;
		}
		break;
	case 10:
		current_subtitle = 1;

		if (sceneKubid20X >= -255)
		{
			sceneKubid20X -= 5;

			if (sceneKubid20X <= -240 && kubidspike <= 200)
			{
				kubidspike += 50;
			}
		}

		if (sceneKubid20X1 >= -655 && sceneKubid20Y1 <= 300)
		{
			sceneKubid20X1 -= 10;
			sceneKubid20Y1 += 5;
		}

		if (sceneKubid20X2 >= -655 && sceneKubid20Y2 <= 300)
		{
			sceneKubid20X2 -= 5;
			sceneKubid20Y2 += 5;
		}
		break;
	case 11:
		current_subtitle = 1;

		if (sceneCD5_alphaX >= -255)
		{
			sceneCD5_alphaX -= 8;
		}

		if (kubidspike > 0)
		{
			kubidspike -= 50;
		}
		break;
	case 12:
		break;
	case 13:
		current_subtitle = 1;

		if (sceneCD6_alphaY >= -255)
		{
			sceneCD6_alphaY += 8;
		}

		if (sceneKubid20X6 >= -2055)
		{
			sceneKubid20X6 -= 10;
			sceneKubid20Y6 += 5;
		}
		break;

	case 14:
		if (sceneCD7_alphaX != 835 && sceneCD7_alphaY != 655)
		{
			sceneCD7_alphaX += -15;
			sceneCD7_alphaR = 40;

			if (sceneCD7_alphaX <= -1600)
			{
				sceneCD7_alphaR = 0;
			}
		}

		if (sceneKubid20X3 != 835 && sceneKubid20Y3 != 655)
		{
			sceneKubid20X3 += -8;
		}

		if (sceneKubid20X4 != 835 && sceneKubid20Y4 != 655)
		{
			sceneKubid20X4 += -10;
			sceneKubid20Y4 += 5;
		}

		if (sceneKubid20X5 != 835 && sceneKubid20Y5 != 655)
		{
			sceneKubid20X5 += -10;
			sceneKubid20Y5 += -2;
		}

		if (elapsed_time < 1800)
		{
			current_subtitle = 1;
		}
		else if (elapsed_time >= 3400 && elapsed_time <= 6000)
		{
			current_subtitle = 2;
		}
		else if (elapsed_time > 6000 && elapsed_time <= 8000)
		{
			current_subtitle = 3;
		}
		else if (elapsed_time > 8000)
		{
			current_subtitle = 4;
		}

		if (elapsed_time >= 3400)
		{
			sceneCD7_alphaX = -1600;
		}

		if (elapsed_time <= 7000)
		{
			CD8_alpha = 0;
		}
		else
		{
			CD8_alpha = 255;
		}
		break;
	case 15:
		if (elapsed_time < 2000)
		{
			dreamScale = 13;
		}

		else if (elapsed_time >= 2000 && elapsed_time <= 4000 && dreamScale > 1)
		{
			dkp_alpha = 0;
			dreamScale -= .4;

			if (dreamScale < 1)
			{
				dreamScale = 1;
			}
		}

		if (sceneDKP_chalkX > -660)
		{
			sceneDKP_studentLowerarmR = 90;
			current_subtitle = 1;
		}
		else if (sceneDKP_chalkX == -660)
		{
			sceneDKP_studentUpperarmR = 90;
			sceneDKP_studentLowerarmR = 120;
			chalk_alpha = 0;
			chalk_border = 0;
		}

		if (elapsed_time >= 8840 && elapsed_time < 9012)
		{
			current_subtitle = 2;
		}

		if (sceneDKP_drX >= -500)
		{
			sceneDKP_drX -= 10;
		}

		if (elapsed_time >= 4275 && elapsed_time < 4510)
		{
			if (sceneDKP_drUpperarmL >= -50)
			{
				sceneDKP_drUpperarmL -= 10;
			}

			sceneDKP_drLowerarmL -= 10;
		}
		else if (elapsed_time >= 4510 && elapsed_time <= 5871)
		{
			chalk_alpha = 255;
			chalk_border = 1;
			sceneDKP_chalkY += 10;

			if (sceneDKP_chalkY >= 10)
			{
				sceneDKP_chalkR += 20;
			}
		}
		else if (elapsed_time > 5871 && sceneDKP_chalkY >= 0)
		{
			sceneDKP_chalkY -= 10;

			if (sceneDKP_chalkY >= 10)
			{
				sceneDKP_chalkR += 20;
			}

			if (sceneDKP_chalkY == 0)
			{
				chalk_alpha = 0;
				chalk_border = 0;
			}
		}
		else if (elapsed_time >= 7211 && elapsed_time < 7923)
		{
			if (sceneDKP_drUpperarmL <= 60)
			{
				sceneDKP_drUpperarmL += 10;
				sceneDKP_drLowerarmL += 10;
			}
		}
		else if (elapsed_time >= 7923 && elapsed_time < 8092)
		{
			sceneDKP_drUpperarmL = -88;
			sceneDKP_drLowerarmL = 0;
			sceneDKP_chalkR = -88;
			chalk_alpha = 255;
			chalk_border = 1;
		}
		else if (elapsed_time >= 8092 && elapsed_time <= 11215)
		{
			sceneDKP_chalkX -= 30;
			sceneDKP_chalkY -= .45;

			if (elapsed_time >= 9049 && sceneDKP_drUpperarmL < 0)
			{
				sceneDKP_drUpperarmL += 10;

				if (sceneDKP_drUpperarmL >= 0)
				{
					sceneDKP_drUpperarmL = 0;
					current_subtitle = 3;
				}

				sceneDKP_studentUpperarmR -= 10;

				if (sceneDKP_studentLowerarmR > 90)
				{
					sceneDKP_studentLowerarmR -= 10;
				}
			}
		}
		else if (elapsed_time > 11215)
		{
			current_subtitle = 4;
		}

		if (elapsed_time >= 8700)
		{
			eye_alpha = 255;
			dream = FALSE;
		}
		else
		{
			eye_alpha = 0;
			dream = TRUE;
		}
	default:
		break;
	}
	glutTimerFunc(30, animator, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	switch (scene)
	{
	case 0:
		break;
	case 1:
		SceneA1();
		break;
	case 2:
		sceneA2_time++;
		SceneA2();
		break;
	case 3:
		SceneA3();
		break;
	case 4:
		elapsed_time -= sceneHQ_timer;
		sceneA4_time++;
		SceneA4();
		break;
	case 5:
		SceneB();
		break;
	case 6:
		testSceneCD1();
		break;
	case 7:
		testSceneCD2();
		break;
	case 8:
		testSceneCD3();
		break;
	case 9:
		elapsed_time -= sceneCloseUp_timer;
		SceneCloseUp();
		break;
	case 10:
		testSceneCD4();
		break;
	case 11:
		testSceneCD5();
		break;
	case 12:
		testSceneCD6();
		break;
	case 13:
		testSceneCD7();
		break;
	case 14:
		elapsed_time -= sceneCD8_timer;
		testSceneCD8();
		break;
	case 15:
		elapsed_time -= sceneDKP_timer;
		SceneDKP();
	default:
		break;
	}
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

void keyboard_input(int key, int x, int y)
{
	current_subtitle = 0;

	switch (key)
	{
	case GLUT_KEY_RIGHT:
		scene++;
		break;
	case GLUT_KEY_LEFT:
		scene--;
		break;
	default:
		break;
	}

	switch (scene)
	{
	case 4:
		sceneHQ_timer = glutGet(GLUT_ELAPSED_TIME);
		break;
	case 9:
		sceneCloseUp_timer = glutGet(GLUT_ELAPSED_TIME);
		break;
	case 14:
		sceneCD8_timer = glutGet(GLUT_ELAPSED_TIME);
		break;
	case 15:
		sceneDKP_timer = glutGet(GLUT_ELAPSED_TIME);
		break;
	default:
		break;
	}
}

void initGL()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_LINE_SMOOTH);
}

//use png only
void textures()
{
	tex_nasa = tex_loader("../nasa_circle.png");
	tex_nasaX = tex_X;
	tex_nasaY = tex_Y;

	tex_ribbon = tex_loader("../ribbon.png");
	tex_ribbonX = tex_X;
	tex_ribbonY = tex_Y;

	tex_nasa_old = tex_loader("../nasa_old.png");
	tex_nasa_oldX = tex_X;
	tex_nasa_oldY = tex_Y;

	tex_clock = tex_loader("../clock.png");
	tex_clockX = tex_X;
	tex_clockY = tex_Y;

	tex_monitor_rear = tex_loader("../monitor_rear.png");
	tex_monitor_rearX = tex_X;
	tex_monitor_rearY = tex_Y;

	tex_monitor_main = tex_loader("../main_screen.png");
	tex_monitor_mainX = tex_X;
	tex_monitor_mainY = tex_Y;

	tex_skull = tex_loader("../skull.png");
	tex_skullX = tex_X;
	tex_skullY = tex_Y;

	tex_space = tex_loader("../space.png");
	tex_spaceX = tex_X;
	tex_spaceY = tex_Y;
	tex_ceiling = tex_loader("../ceiling.png");
	tex_ceilingX = tex_X;
	tex_ceilingY = tex_Y;

	tex_floor = tex_loader("../floor.png");
	tex_floorX = tex_X;
	tex_floorY = tex_Y;

	tex_windows = tex_loader("../windows.png");
	tex_windowsX = tex_X;
	tex_windowsY = tex_Y;

	tex_bsod = tex_loader("../bsod.png");
	tex_bsodX = tex_X;
	tex_bsodY = tex_Y;

	tex_game = tex_loader("../game.png");
	tex_gameX = tex_X;
	tex_gameY = tex_Y;

	tex_word = tex_loader("../word.png");
	tex_wordX = tex_X;
	tex_wordY = tex_Y;
}

int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Another Variant");
	glutDisplayFunc(display);
	glutTimerFunc(30, animator, 0);
	glutSpecialFunc(keyboard_input);
	initGL();
	textures();

	//maximize window
	HWND win_handle = FindWindow(0, L"Another Variant");
	ShowWindowAsync(win_handle, SW_SHOWMAXIMIZED);

	glutMainLoop();
}