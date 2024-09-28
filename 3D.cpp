#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <array>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "glm/glm.hpp" // https://github.com/g-truc/glm
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "stb_image.h" // https://github.com/nothings/stb
#include "tiny_obj_loader.h" // https://github.com/tinyobjloader/tinyobjloader

using namespace std;
using namespace tinyobj;
using namespace glm;

#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define SCREEN_WIDTH	1920
#define SCREEN_HEIGHT	1080

//-------------------------------------------------------------- define colors
#define clear glColor4ub(255, 255, 255, 255);
#define white glColor3ub(255, 255, 255);

struct Triangle
{
	//normals, uv map, vertex colors, vertex
	array<int, 3> nor; array<int, 3> uv; array<int, 3> vc; array<int, 3> vt;
	Triangle(array<int, 3> n, array<int, 3> u, array<int, 3> c, array<int, 3> v) : nor(n), uv(u), vc(c), vt(v) {};
};

//-------------------------------------------------------------- model variable
vector<Triangle>	tri_zucc_descend, tri_zucc_stand, tri_laser, tri_baseStand, tri_baseHover;
vector<vec3>		nor_zucc_descend, nor_zucc_stand, nor_laser, nor_baseStand, nor_baseHover;
vector<vec2>		uvm_zucc_descend, uvm_zucc_stand, uvm_laser, uvm_baseStand, uvm_baseHover;
vector<vec3>		vtx_zucc_descend, vtx_zucc_stand, vtx_laser, vtx_baseStand, vtx_baseHover;
vector<vec3>		vcl_zucc_descend, vcl_zucc_stand, vcl_laser, vcl_baseStand, vcl_baseHover;

vector<Triangle>	tri_baseAtt1, tri_baseAtt2, tri_baseAtt3, tri_slash;
vector<vec3>		nor_baseAtt1, nor_baseAtt2, nor_baseAtt3, nor_slash;
vector<vec2>		uvm_baseAtt1, uvm_baseAtt2, uvm_baseAtt3, uvm_slash;
vector<vec3>		vtx_baseAtt1, vtx_baseAtt2, vtx_baseAtt3, vtx_slash;
vector<vec3>		vcl_baseAtt1, vcl_baseAtt2, vcl_baseAtt3, vcl_slash;

vector<Triangle>	tri_zucc_stands3, tri_base_behind, tri_sao, tri_zucc_stands3_head;
vector<vec3>		nor_zucc_stands3, nor_base_behind, nor_sao, nor_zucc_stands3_head;
vector<vec2>		uvm_zucc_stands3, uvm_base_behind, uvm_sao, uvm_zucc_stands3_head;
vector<vec3>		vtx_zucc_stands3, vtx_base_behind, vtx_sao, vtx_zucc_stands3_head;
vector<vec3>		vcl_zucc_stands3, vcl_base_behind, vcl_sao, vcl_zucc_stands3_head;

vector<Triangle>	tri_shield, tri_base_throw, tri_elucidator, tri_repulsor, tri_shieldL, tri_shieldR, tri_base_charge;
vector<vec3>		nor_shield, nor_base_throw, nor_elucidator, nor_repulsor, nor_shieldL, nor_shieldR, nor_base_charge;
vector<vec2>		uvm_shield, uvm_base_throw, uvm_elucidator, uvm_repulsor, uvm_shieldL, uvm_shieldR, uvm_base_charge;
vector<vec3>		vtx_shield, vtx_base_throw, vtx_elucidator, vtx_repulsor, vtx_shieldL, vtx_shieldR, vtx_base_charge;
vector<vec3>		vcl_shield, vcl_base_throw, vcl_elucidator, vcl_repulsor, vcl_shieldL, vcl_shieldR, vcl_base_charge;

vector<Triangle>	tri_beam, tri_beamin, tri_beam_core, tri_beam_ring, tri_base_charge2, tri_base_charge2_arm;
vector<vec3>		nor_beam, nor_beamin, nor_beam_core, nor_beam_ring, nor_base_charge2, nor_base_charge2_arm;
vector<vec2>		uvm_beam, uvm_beamin, uvm_beam_core, uvm_beam_ring, uvm_base_charge2, uvm_base_charge2_arm;
vector<vec3>		vtx_beam, vtx_beamin, vtx_beam_core, vtx_beam_ring, vtx_base_charge2, vtx_base_charge2_arm;
vector<vec3>		vcl_beam, vcl_beamin, vcl_beam_core, vcl_beam_ring, vcl_base_charge2, vcl_base_charge2_arm;

vector<Triangle>	tri_base_stab, tri_sword_stab, tri_sword_decap, tri_zucc_descendh, tri_zucc_standh, tri_zucc_finalh;
vector<vec3>		nor_base_stab, nor_sword_stab, nor_sword_decap, nor_zucc_descendh, nor_zucc_standh, nor_zucc_finalh;
vector<vec2>		uvm_base_stab, uvm_sword_stab, uvm_sword_decap, uvm_zucc_descendh, uvm_zucc_standh, uvm_zucc_finalh;
vector<vec3>		vtx_base_stab, vtx_sword_stab, vtx_sword_decap, vtx_zucc_descendh, vtx_zucc_standh, vtx_zucc_finalh;
vector<vec3>		vcl_base_stab, vcl_sword_stab, vcl_sword_decap, vcl_zucc_descendh, vcl_zucc_standh, vcl_zucc_finalh;

vector<Triangle>	tri_zucc_final, tri_base_final, tri_base_final_leg, tri_final_stage, tri_explosion;
vector<vec3>		nor_zucc_final, nor_base_final, nor_base_final_leg, nor_final_stage, nor_explosion;
vector<vec2>		uvm_zucc_final, uvm_base_final, uvm_base_final_leg, uvm_final_stage, uvm_explosion;
vector<vec3>		vtx_zucc_final, vtx_base_final, vtx_base_final_leg, vtx_final_stage, vtx_explosion;
vector<vec3>		vcl_zucc_final, vcl_base_final, vcl_base_final_leg, vcl_final_stage, vcl_explosion;

vector<Triangle>	tri_stage_dkp, tri_truck, tri_dom, tri_bruh, tri_bruh_ring, tri_bruh_ring2, tri_item_sword, tri_item_cc;
vector<vec3>		nor_stage_dkp, nor_truck, nor_dom, nor_bruh, nor_bruh_ring, nor_bruh_ring2, nor_item_sword, nor_item_cc;
vector<vec2>		uvm_stage_dkp, uvm_truck, uvm_dom, uvm_bruh, uvm_bruh_ring, uvm_bruh_ring2, uvm_item_sword, uvm_item_cc;
vector<vec3>		vtx_stage_dkp, vtx_truck, vtx_dom, vtx_bruh, vtx_bruh_ring, vtx_bruh_ring2, vtx_item_sword, vtx_item_cc;
vector<vec3>		vcl_stage_dkp, vcl_truck, vcl_dom, vcl_bruh, vcl_bruh_ring, vcl_bruh_ring2, vcl_item_sword, vcl_item_cc;

//-------------------------------------------------------------- THIS IS ALL MODEL VARIABLES THAT I USE, ALREADY DELETED THAT ISNT USED --------------------------------------------------------------------------
vector<Triangle>tri_weapon2Re, tri_weapon2, tri_weapon3, tri_expeloson, tri_Charselection2, tri_blackScreen, tri_blackScreenText, tri_p2wcharBody, tri_p2wcharHead, tri_p2wcharLeftArm, tri_p2wcharLeftCalf, tri_p2wcharLeftForearm, tri_p2wcharLeftThigh, tri_p2wcharRightArm, tri_p2wcharRightCalf, tri_p2wcharRightForearm, tri_p2wcharRightThigh, tri_Charselection, tri_map, tri_selectLefthand, tri_selectRighthand, tri_p2wcharStatic, tri_1, tri_1Re, tri_4Re, tri_4, tri_p2wcharStaticv2, tri_skyGlobe, tri_p2wcharStaticv3, tri_weapon3Re;
vector<vec3>nor_weapon2Re, nor_weapon2, nor_weapon3, nor_expeloson, nor_Charselection2, nor_blackScreen, nor_blackScreenText, nor_p2wcharBody, nor_p2wcharHead, nor_p2wcharLeftArm, nor_p2wcharLeftCalf, nor_p2wcharLeftForearm, nor_p2wcharLeftThigh, nor_p2wcharRightArm, nor_p2wcharRightCalf, nor_p2wcharRightForearm, nor_p2wcharRightThigh, nor_Charselection, nor_map, nor_selectLefthand, nor_selectRighthand, nor_p2wcharStatic, nor_1, nor_1Re, nor_4Re, nor_4, nor_p2wcharStaticv2, nor_skyGlobe, nor_p2wcharStaticv3, nor_weapon3Re;
vector<vec2>uv_weapon2Re, uv_weapon2, uv_weapon3, uv_expeloson, uv_Charselection2, uv_blackScreen, uv_blackScreenText, uv_p2wcharBody, uv_p2wcharHead, uv_p2wcharLeftArm, uv_p2wcharLeftCalf, uv_p2wcharLeftForearm, uv_p2wcharLeftThigh, uv_p2wcharRightArm, uv_p2wcharRightCalf, uv_p2wcharRightForearm, uv_p2wcharRightThigh, uv_Charselection, uv_map, uv_selectLefthand, uv_selectRighthand, uv_p2wcharStatic, uv_1, uv_1Re, uv_4Re, uv_4, uv_p2wcharStaticv2, uv_skyGlobe, uv_p2wcharStaticv3, uv_weapon3Re;
vector<vec3>vt_weapon2Re, vt_weapon2, vt_weapon3, vt_expeloson, vt_Charselection2, vt_blackScreen, vt_blackScreenText, vt_p2wcharBody, vt_p2wcharHead, vt_p2wcharLeftArm, vt_p2wcharLeftCalf, vt_p2wcharLeftForearm, vt_p2wcharLeftThigh, vt_p2wcharRightArm, vt_p2wcharRightCalf, vt_p2wcharRightForearm, vt_p2wcharRightThigh, vt_Charselection, vt_map, vt_selectLefthand, vt_selectRighthand, vt_p2wcharStatic, vt_1, vt_1Re, vt_4Re, vt_4, vt_p2wcharStaticv2, vt_skyGlobe, vt_p2wcharStaticv3, vt_weapon3Re;
vector<vec3>vc_weapon2Re, vc_weapon2, vc_weapon3, vc_expeloson, vc_Charselection2, vc_blackScreen, vc_blackScreenText, vc_p2wcharBody, vc_p2wcharHead, vc_p2wcharLeftArm, vc_p2wcharLeftCalf, vc_p2wcharLeftForearm, vc_p2wcharLeftThigh, vc_p2wcharRightArm, vc_p2wcharRightCalf, vc_p2wcharRightForearm, vc_p2wcharRightThigh, vc_Charselection, vc_map, vc_selectLefthand, vc_selectRighthand, vc_p2wcharStatic, vc_1, vc_1Re, vc_4Re, vc_4, vc_p2wcharStaticv2, vc_skyGlobe, vc_p2wcharStaticv3, vc_weapon3Re;

//-------------------------------------------------------------- texture variables
unsigned char* tex_shield, * tex_final_stage, * tex_dkp, * tex_dom, * tex_void, * tex_bruh, * tex_cc,*tex_zucc,*tex_zucch;
int tex_X, tex_shieldX, tex_final_stageX, tex_dkpX, tex_domX, tex_voidX, tex_bruhX, tex_ccX, tex_zuccX, tex_zucchX;
int tex_Y, tex_shieldY, tex_final_stageY, tex_dkpY, tex_domY, tex_voidY, tex_bruhY, tex_ccY, tex_zuccY, tex_zucchY;

//--------------------------------------------------------------ALL texture variables HERE ARE USED--------------------------------------------------------------------------------------------------------------
unsigned char* tex_map, * tex_map2, * tex_sky;
int tex_mapX, tex_mapY, tex_map2X, tex_map2Y, tex_skyX, tex_skyY;

//-------------------------------------------------------------- camera variables
float eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0, eyeXcase2;

//-------------------------------------------------------------- timer variables
float elapsed_time = 0, sceneZaku_timer, sceneBase_timer;
float sceneC1_timer, sceneC2_timer, sceneC3_timer, sceneC4_timer, sceneC5_timer, sceneC6_timer, sceneC7_timer, sceneC8_timer, sceneC9_timer, scene10_timer;
float sceneA1_timer, sceneA2_timer;

//-------------------------------------------------------------- other variables
int scene = 0;
float zucc_descendY, laserrot, laserY, zuccrotY, baseHoverY, baseStandY, baseAtt1Y, baseAtt2Y, baseAtt3Y, slashRot, slashZ, slashY;
float base_behindY, saoY, saoZ, saoY2, saoRot, saoRot2, zucc_stands3_headRot, explosionS, explosionY;
float base_throwZ, shieldZ, shieldLX, shieldRX, char7Z, base_charge2_armRot, stabRot, decapRot;
float base_finalY, base_finalZ, base_finalKneeRot, base_finalRot, beam_coreRot, stage_dkpRot, truckX, truckZ;
float bruh_ringH, bruh_ringV, bruh_stageRot, bruh_stageRot2, bruh_stageRotX, bruh_stageRotY, item_swordRot, item_ccRot, item_swordY, item_Rot;
int shootWeapon1, shootWeapon2, shootWeapon3, shootWeapon4, shootWeapon5, explosionM, screenCleared, charFlyUp, textGup;
int hand_rotationL, hand_rotationR, selectchar;

//-------------------------------------------------------------- texture loader
unsigned char* tex_loader(string file)
{
	int numColCh;
	unsigned char* bytes = stbi_load(file.c_str(), &tex_X, &tex_Y, &numColCh, 0);
	return bytes;
	stbi_image_free(bytes);
}

//-------------------------------------------------------------- model loader
void load_triangles(const shape_t& shape, vector<Triangle>& faces)
{
	const vector<index_t>& index = shape.mesh.indices;
	const vector<int>& mat_id = shape.mesh.material_ids;

	for (size_t face_ind = 0; face_ind < mat_id.size(); face_ind++)
	{
		faces.push_back(Triangle(
			{ index[3 * face_ind].normal_index, index[3 * face_ind + 1].normal_index, index[3 * face_ind + 2].normal_index },
			{ index[3 * face_ind].texcoord_index, index[3 * face_ind + 1].texcoord_index, index[3 * face_ind + 2].texcoord_index },
			{ index[3 * face_ind].vertex_index, index[3 * face_ind + 1].vertex_index, index[3 * face_ind + 2].vertex_index },
			{ index[3 * face_ind].vertex_index, index[3 * face_ind + 1].vertex_index, index[3 * face_ind + 2].vertex_index }
		));
	}
}

void obj_loader(string file, vector<Triangle>& tri, vector<vec3>& nor, vector<vec2>& uv, vector<vec3>& vc, vector<vec3>& vt)
{
	string inputfile = file;
	ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "./"; // Path to material files

	ObjReader reader;

	if (!reader.ParseFromFile(inputfile, reader_config)) {
		if (!reader.Error().empty()) {
			cerr << "TinyObjReader: " << reader.Error();
		}
		exit(1);
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();

	for (size_t vec = 0; vec < attrib.normals.size(); vec += 3)
	{
		nor.push_back(vec3(
			attrib.normals[vec],
			attrib.normals[vec + 1],
			attrib.normals[vec + 2]
		));
	}

	for (size_t vec = 0; vec < attrib.texcoords.size(); vec += 2)
	{
		uv.push_back(vec2(
			attrib.texcoords[vec],
			attrib.texcoords[vec + 1]
		));
	}

	for (size_t vec = 0; vec < attrib.colors.size(); vec += 3)
	{
		vc.push_back(vec3(
			attrib.colors[vec],
			attrib.colors[vec + 1],
			attrib.colors[vec + 2]
		));
	}

	for (size_t vec = 0; vec < attrib.vertices.size(); vec += 3)
	{
		vt.push_back(vec3(
			attrib.vertices[vec],
			attrib.vertices[vec + 1],
			attrib.vertices[vec + 2]
		));
	}

	for (auto shape = shapes.begin(); shape < shapes.end(); ++shape)
	{
		load_triangles(*shape, tri);
	}
}

void draw(vector<Triangle>& tri, vector<vec3>& nor, vector<vec2>& uv, vector<vec3>& vc, vector<vec3>& vt)
{
	glBegin(GL_TRIANGLES);
	for (auto faces = tri.begin(); faces != tri.end(); ++faces)
	{
		glNormal3f(nor[faces->nor[0]].x, nor[faces->nor[0]].y, nor[faces->nor[0]].z);
		glTexCoord2f(uv[faces->uv[0]].x, uv[faces->uv[0]].y);
		glColor3f(vc[faces->vc[0]].x, vc[faces->vc[0]].y, vc[faces->vc[0]].z);
		glVertex3f(vt[faces->vt[0]].x, vt[faces->vt[0]].y, vt[faces->vt[0]].z);

		glNormal3f(nor[faces->nor[1]].x, nor[faces->nor[1]].y, nor[faces->nor[1]].z);
		glTexCoord2f(uv[faces->uv[1]].x, uv[faces->uv[1]].y);
		glColor3f(vc[faces->vc[1]].x, vc[faces->vc[1]].y, vc[faces->vc[1]].z);
		glVertex3f(vt[faces->vt[1]].x, vt[faces->vt[1]].y, vt[faces->vt[1]].z);

		glNormal3f(nor[faces->nor[2]].x, nor[faces->nor[2]].y, nor[faces->nor[2]].z);
		glTexCoord2f(uv[faces->uv[2]].x, uv[faces->uv[2]].y);
		glColor3f(vc[faces->vc[2]].x, vc[faces->vc[2]].y, vc[faces->vc[2]].z);
		glVertex3f(vt[faces->vt[2]].x, vt[faces->vt[2]].y, vt[faces->vt[2]].z);
	}
	glEnd();
}

void draw(vector<Triangle>& tri, vector<vec3>& nor, vector<vec2>& uv, vector<vec3>& vt)
{
	glBegin(GL_TRIANGLES);
	for (auto faces = tri.begin(); faces != tri.end(); ++faces)
	{
		glNormal3f(nor[faces->nor[0]].x, nor[faces->nor[0]].y, nor[faces->nor[0]].z);
		glTexCoord2f(uv[faces->uv[0]].x, uv[faces->uv[0]].y);
		glVertex3f(vt[faces->vt[0]].x, vt[faces->vt[0]].y, vt[faces->vt[0]].z);

		glNormal3f(nor[faces->nor[1]].x, nor[faces->nor[1]].y, nor[faces->nor[1]].z);
		glTexCoord2f(uv[faces->uv[1]].x, uv[faces->uv[1]].y);
		glVertex3f(vt[faces->vt[1]].x, vt[faces->vt[1]].y, vt[faces->vt[1]].z);

		glNormal3f(nor[faces->nor[2]].x, nor[faces->nor[2]].y, nor[faces->nor[2]].z);
		glTexCoord2f(uv[faces->uv[2]].x, uv[faces->uv[2]].y);
		glVertex3f(vt[faces->vt[2]].x, vt[faces->vt[2]].y, vt[faces->vt[2]].z);
	}
	glEnd();
}

//-------------------------------------------------------------- models
void XYZaxis()
{
	//X
	glColor3f(255, 0, 0);
	glBegin(GL_LINE_LOOP);
	glNormal3f(1, 1, 1);
	glVertex3f(999.0, 0.0, 0);
	glVertex3f(-999.0, 0.0, 0);
	glEnd();

	//Y
	glColor3f(0, 255, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 999.0, 0.0);
	glVertex3f(0, -999.0, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glutSolidSphere(0.05, 64, 64);
	glPopMatrix();

	//Z
	glColor3f(0, 0, 255);
	glNormal3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0.0, -999.0);
	glVertex3f(0, 0.0, 999.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0, 0, 1);
	glutSolidSphere(0.05, 64, 64);
	glPopMatrix();
}

void square_texture(unsigned char* bytes, int imgX, int imgY, int x, int z)
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
	glNormal3f(1, 1, 1);
	glTexCoord2i(1, 1); glVertex3f(x, 0.0, -z);
	glTexCoord2i(0, 1); glVertex3f(-x, 0.0, -z);
	glTexCoord2i(0, 0); glVertex3f(-x, 0.0, z);
	glTexCoord2i(1, 0); glVertex3f(x, 0.0, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void zucc_descend()
{
	draw(tri_zucc_descend, nor_zucc_descend, uvm_zucc_descend, vcl_zucc_descend, vtx_zucc_descend);
}

void zucc_descendh(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_zucc_descendh, nor_zucc_descendh, uvm_zucc_descendh, vtx_zucc_descendh);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void zucc_standh(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_zucc_standh, nor_zucc_standh, uvm_zucc_standh, vtx_zucc_standh);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void zucc_stand()
{
	draw(tri_zucc_stand, nor_zucc_stand, uvm_zucc_stand, vcl_zucc_stand, vtx_zucc_stand);
	clear;
	zucc_standh(tex_zucch, tex_zucchX, tex_zucchY);
}

void zucc_stands3()
{
	draw(tri_zucc_stands3, nor_zucc_stands3, uvm_zucc_stands3, vcl_zucc_stands3, vtx_zucc_stands3);
}

void zucc_stands3_head(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_zucc_stands3_head, nor_zucc_stands3_head, uvm_zucc_stands3_head, vcl_zucc_stands3_head, vtx_zucc_stands3_head);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void zucc_finalh(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_zucc_finalh, nor_zucc_finalh, uvm_zucc_finalh, vcl_zucc_finalh, vtx_zucc_finalh);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void shield(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_shield, nor_shield, uvm_shield, vtx_shield);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void shieldL(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_shieldL, nor_shieldL, uvm_shieldL, vtx_shieldL);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void shieldR(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_shieldR, nor_shieldR, uvm_shieldR, vtx_shieldR);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void stage_final(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_final_stage, nor_final_stage, uvm_final_stage, vtx_final_stage);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void stage_dkp(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_stage_dkp, nor_stage_dkp, uvm_stage_dkp, vtx_stage_dkp);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void dom(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_dom, nor_dom, uvm_dom, vtx_dom);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void bruh(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_bruh, nor_bruh, uvm_bruh, vtx_bruh);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

void cc(unsigned char* bytes, int imgX, int imgY)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	draw(tri_item_cc, nor_item_cc, uvm_item_cc, vtx_item_cc);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

//------------------------------------------------------------------------------------ALL MODELS HERE ARE USED---------------------------------------------------------------------------------------------------
void p2wcharStatic() {
	glBegin(GL_TRIANGLES);
	draw(tri_p2wcharStatic, nor_p2wcharStatic, uv_p2wcharStatic, vc_p2wcharStatic, vt_p2wcharStatic);
	glEnd();
}

void p2wcharStaticv2() {

	glBegin(GL_TRIANGLES);
	draw(tri_p2wcharStaticv2, nor_p2wcharStaticv2, uv_p2wcharStaticv2, vc_p2wcharStaticv2, vt_p2wcharStaticv2);
	glEnd();

}

void p2wcharStaticv3() {

	glBegin(GL_TRIANGLES);
	draw(tri_p2wcharStaticv3, nor_p2wcharStaticv3, uv_p2wcharStaticv3, vc_p2wcharStaticv3, vt_p2wcharStaticv3);
	glEnd();

}

void Charselection() {
	glBegin(GL_TRIANGLES);
	draw(tri_Charselection, nor_Charselection, uv_Charselection, vc_Charselection, vt_Charselection);
	glEnd();
}

void Charselection2() {
	glBegin(GL_TRIANGLES);
	draw(tri_Charselection2, nor_Charselection2, uv_Charselection2, vc_Charselection2, vt_Charselection2);
	glEnd();
}

void selectLefthand() {
	glBegin(GL_TRIANGLES);
	draw(tri_selectLefthand, nor_selectLefthand, uv_selectLefthand, vc_selectLefthand, vt_selectLefthand);
	glEnd();
}

void selectRighthand() {
	glBegin(GL_TRIANGLES);
	draw(tri_selectRighthand, nor_selectRighthand, uv_selectRighthand, vc_selectRighthand, vt_selectRighthand);
	glEnd();


}

void weapon2() {
	glBegin(GL_TRIANGLES);
	draw(tri_weapon2, nor_weapon2, uv_weapon2, vc_weapon2, vt_weapon2);
	glEnd();
}

void weapon3() {
	glBegin(GL_TRIANGLES);
	draw(tri_weapon3, nor_weapon3, uv_weapon3, vc_weapon3, vt_weapon3);
	glEnd();
}

void w1() {
	glBegin(GL_TRIANGLES);
	draw(tri_1, nor_1, uv_1, vc_1, vt_1);
	glEnd();
}

void w4() {
	glBegin(GL_TRIANGLES);
	draw(tri_4, nor_4, uv_4, vc_4, vt_4);
	glEnd();
}

void w1Re() {
	glBegin(GL_TRIANGLES);
	draw(tri_1Re, nor_1Re, uv_1Re, vc_1Re, vt_1Re);
	glEnd();
}

void weapon3Re() {
	glBegin(GL_TRIANGLES);
	draw(tri_weapon3Re, nor_weapon3Re, uv_weapon3Re, vc_weapon3Re, vt_weapon3Re);
	glEnd();
}

void w4Re() {
	glBegin(GL_TRIANGLES);
	draw(tri_4Re, nor_4Re, uv_4Re, vc_4Re, vt_4Re);
	glEnd();
}

void weapon2Re() {
	glBegin(GL_TRIANGLES);
	draw(tri_weapon2Re, nor_weapon2Re, uv_weapon2Re, vc_weapon2Re, vt_weapon2Re);
	glEnd();
}

void expeloson() {
	glBegin(GL_TRIANGLES);
	draw(tri_expeloson, nor_expeloson, uv_expeloson, vc_expeloson, vt_expeloson);
	glEnd();
}

void blackScreen() {
	glBegin(GL_TRIANGLES);
	draw(tri_blackScreen, nor_blackScreen, uv_blackScreen, vc_blackScreen, vt_blackScreen);
	glEnd();
}

void blackScreenText() {
	glBegin(GL_TRIANGLES);
	draw(tri_blackScreenText, nor_blackScreenText, uv_blackScreenText, vc_blackScreenText, vt_blackScreenText);
	glEnd();
}

void skyGlobe(unsigned char* bytes, int imgX, int imgY, int x, int z) {
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgX, imgY, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glBegin(GL_TRIANGLES);
	draw(tri_skyGlobe, nor_skyGlobe, uv_skyGlobe, vc_skyGlobe, vt_skyGlobe);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex);
}

//-------------------------------------------------------------- scene builder
void sceneA1()
{
	clear;
	glPushMatrix();
	glRotatef(stage_dkpRot, 0, 1, 0);
	stage_dkp(tex_dkp, tex_dkpX, tex_dkpY);

	glPushMatrix();
	glTranslatef(truckX, 0, truckZ);
	dom(tex_dom, tex_domX, tex_domY);
	draw(tri_truck, nor_truck, uvm_truck, vcl_truck, vtx_truck);
	glPopMatrix();
	glPopMatrix();
}

void sceneA2()
{
	clear;
	glPushMatrix();
	glRotatef(bruh_stageRot, 0, 1, 0);
	stage_dkp(tex_void, tex_voidX, tex_voidY);

	glPushMatrix();
	glTranslatef(0, 0, 10);
	glRotatef(180, 0, 1, 0);
	bruh(tex_bruh, tex_bruhX, tex_bruhY);

	glPushMatrix();
	glRotatef(bruh_ringH, 1, 1, 1);
	draw(tri_bruh_ring, nor_bruh_ring, uvm_bruh_ring, vcl_bruh_ring, vtx_bruh_ring);
	glPopMatrix();

	glPushMatrix();
	glRotatef(bruh_ringV, 1, 1, 1);
	draw(tri_bruh_ring2, nor_bruh_ring2, uvm_bruh_ring2, vcl_bruh_ring2, vtx_bruh_ring2);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, item_swordY, 5);
	glRotatef(item_Rot, 0, 1, 0);
	draw(tri_item_sword, nor_item_sword, uvm_item_sword, vcl_item_sword, vtx_item_sword);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, item_swordY, 5);
	glRotatef(item_Rot, 0, 1, 0);
	cc(tex_cc, tex_ccX, tex_ccY);
	glPopMatrix();
	glPopMatrix();


}



void sceneB1()
{
	clear;
	glPushMatrix();
	glTranslatef(0.0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map, tex_mapX, tex_mapY, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	Charselection();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 40);
	glRotatef(hand_rotationL, 0, 1, 0);
	glTranslatef(15, 0, -40);
	selectLefthand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 13);
	glPushMatrix();
	glTranslatef(30, 0, 40);
	glRotatef(hand_rotationR, 0, 1, 0);
	glTranslatef(-30, 0, -40);
	selectRighthand();
	glPopMatrix();
	glPopMatrix();

}

void sceneB2()
{
	clear;
	glPushMatrix();
	glTranslatef(0.0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map, tex_mapX, tex_mapY, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	Charselection();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 13);
	glPushMatrix();
	glTranslatef(-15, 0, 40);
	glRotatef(hand_rotationL, 0, 1, 0);
	glTranslatef(15, 0, -40);
	selectLefthand();
	glPopMatrix();
	glPopMatrix();


}

void sceneB3()
{
	clear;
	glPushMatrix();
	glTranslatef(0.0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map, tex_mapX, tex_mapY, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	Charselection2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 13);
	glPushMatrix();
	glTranslatef(-15, 0, 40);
	glRotatef(hand_rotationL, 0, 1, 0);
	glTranslatef(15, 0, -40);
	selectLefthand();
	glPopMatrix();
	glPopMatrix();


}

void sceneB4()
{
	clear;
	skyGlobe(tex_sky, tex_skyX, tex_skyY, 10, 10);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 50.0);

	p2wcharStatic();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.0);
	weapon2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.0);
	weapon3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 30, 0.0);
	w1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 30, 20.0);
	w4();
	glPopMatrix();


}

void sceneB5()
{
	clear;

	skyGlobe(tex_sky, tex_skyX, tex_skyY, 10, 10);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	p2wcharStaticv2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -60);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon2);
	weapon2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -60);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon3);
	weapon3();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 30, -60);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon4);
	w1();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 30, -60);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon5);
	w4();
	glPopMatrix();
	glPopMatrix();

}

void sceneB6()
{
	clear;
	glPushMatrix();
	glTranslatef(0.0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map, tex_mapX, tex_mapY, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 36.0);
	glRotatef(-40, 20, 0, 0);
	p2wcharStaticv3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -60);
	glRotatef(-40, 20, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon2);
	weapon2Re();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -60);
	glRotatef(-40, 20, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon3);
	weapon3Re();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 30, -60);
	glRotatef(-40, 20, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon4);
	w1Re();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -30, -60);
	glRotatef(-40, 20, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, shootWeapon5);
	w4Re();
	glPopMatrix();
	glPopMatrix();


}

void sceneB7()
{
	clear;
	glPushMatrix();
	glTranslatef(0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map, tex_mapX, tex_mapY, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -105, -147);
	glScalef(80, -105, 15);
	glPushMatrix();
	glTranslatef(0, 0, explosionM);
	expeloson();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 36.0);
	glRotatef(-40, 20, 0, 0);
	p2wcharStaticv3();
	glPopMatrix();

}

void sceneB8()
{
	clear;
	glPushMatrix();
	glTranslatef(0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map2, tex_map2X, tex_map2Y, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -105, -147);
	glScalef(80, -105, 15);
	glPushMatrix();
	glTranslatef(0, 0, explosionM);
	expeloson();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 36.0);
	glRotatef(-40, 20, 0, 0);
	p2wcharStaticv3();
	glPopMatrix();

}

void sceneB9()
{
	clear;
	glPushMatrix();
	glTranslatef(0, -72, -137.0);
	glScalef(24, 15.5, 10);
	glRotatef(40, 20, 0, 0);
	square_texture(tex_map2, tex_map2X, tex_map2Y, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -105, -147);
	glScalef(80, -105, 15);
	glPushMatrix();
	glTranslatef(0, 0, screenCleared);
	blackScreen();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 36.0);
	glRotatef(-40, 20, 0, 0);
	glPushMatrix();
	glTranslatef(0, charFlyUp, 0);
	p2wcharStaticv3();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -100, 0);
	glPushMatrix();
	glTranslatef(0, textGup, 0);
	blackScreenText();
	glPopMatrix();
	glPopMatrix();


}




void sceneC1()
{
	clear;
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);

	glPushMatrix();
	glTranslatef(0, zucc_descendY, 0);
	zucc_descend();
	clear;
	zucc_descendh(tex_zucch, tex_zucchX, tex_zucchY);
	glPopMatrix();
}

void sceneC2()
{
	clear;
	glPushMatrix();
	glRotatef(zuccrotY, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(zuccrotY, 0, 1, 0);
	zucc_stand();
	glPushMatrix();
	glTranslatef(0, laserY, 0);
	glTranslatef(0, 19.9487, 0.902889);
	glRotatef(laserrot, 1, 0, 0);
	glTranslatef(0, -19.9487, -0.902889);
	glColor3f(255, 0, 0);
	draw(tri_laser, nor_laser, uvm_laser, vtx_laser);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, baseStandY, 0);
	draw(tri_baseStand, nor_baseStand, uvm_baseStand, vcl_baseStand, vtx_baseStand);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, baseHoverY, 0);
	draw(tri_baseHover, nor_baseHover, uvm_baseHover, vcl_baseHover, vtx_baseHover);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, baseAtt1Y, 0);
	draw(tri_baseAtt1, nor_baseAtt1, uvm_baseAtt1, vcl_baseAtt1, vtx_baseAtt1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, baseAtt2Y, 0);
	draw(tri_baseAtt2, nor_baseAtt2, uvm_baseAtt2, vcl_baseAtt2, vtx_baseAtt2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, baseAtt3Y, 0);
	draw(tri_baseAtt3, nor_baseAtt3, uvm_baseAtt3, vcl_baseAtt3, vtx_baseAtt3);
	glPopMatrix();

	glColor3f(0, 153, 255);
	glPushMatrix();
	glTranslatef(0, slashY, slashZ);
	glTranslatef(0.08719, 14.8896, 69.51);
	glRotatef(slashRot, 0, 0, 1);
	glTranslatef(-0.08719, -14.8896, -69.51);
	draw(tri_slash, nor_slash, uvm_slash, vtx_slash);
	glPopMatrix();
}

void sceneC3()
{
	clear;
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);

	glPushMatrix();
	glRotatef(zuccrotY, 0, 1, 0);
	zucc_stands3();

	glPushMatrix();
	glTranslatef(0, 18.7325, -0.025356);
	glRotatef(zucc_stands3_headRot, 0, 1, 0);
	glTranslatef(0, -18.7325, 0.025356);
	zucc_stands3_head(tex_zucch, tex_zucchX, tex_zucchY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saoRot, 0, 1, 0);
	glTranslatef(0, saoY, 0);
	draw(tri_sao, nor_sao, uvm_sao, vcl_sao, vtx_sao);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, base_behindY, 0);
	draw(tri_base_behind, nor_base_behind, uvm_base_behind, vcl_base_behind, vtx_base_behind);
	glPopMatrix();
}

void sceneC4()
{
	clear;

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(zuccrotY, 0, 1, 0);
	zucc_stand();

	glPushMatrix();
	glTranslatef(0, saoY, saoZ);
	glRotatef(saoRot, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 15.0192, 0.18202);
	glRotatef(saoRot2, 1, 0, 0);
	glTranslatef(0, -15.0192, -0.18202);
	glPushMatrix();
	glTranslatef(0, saoY2, 0);
	draw(tri_sao, nor_sao, uvm_sao, vcl_sao, vtx_sao);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void sceneC5()
{
	clear;

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, base_throwZ);
	draw(tri_base_throw, nor_base_throw, uvm_base_throw, vcl_base_throw, vtx_base_throw);
	glPushMatrix();
	glTranslatef(0, 0, shieldZ);
	shield(tex_shield, tex_shieldX, tex_shieldY);
	glPopMatrix();
	glPopMatrix();
}

void sceneC6()
{
	clear;

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(shieldLX, 0, 0);
	shieldL(tex_shield, tex_shieldX, tex_shieldY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(shieldRX, 0, 0);
	shieldR(tex_shield, tex_shieldX, tex_shieldY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.57769, 0, -13.1311);
	glRotatef(-31.9344, 0, 1, 0);
	glTranslatef(9.57769, 0, 13.1311);
	glPushMatrix();
	glTranslatef(0, saoY, saoZ);
	draw(tri_elucidator, nor_elucidator, uvm_elucidator, vcl_elucidator, vtx_elucidator);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(9.55687, 0, -13.1311);
	glRotatef(32.0502, 0, 1, 0);
	glTranslatef(-9.55687, 0, 13.1311);
	glPushMatrix();
	glTranslatef(0, saoY, saoZ);
	draw(tri_repulsor, nor_repulsor, uvm_repulsor, vcl_repulsor, vtx_repulsor);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	draw(tri_base_charge, nor_base_charge, uvm_base_charge, vcl_base_charge, vtx_base_charge);
	glPopMatrix();
}

void sceneC7()
{
	clear;

	glPushMatrix();
	glScalef(1.5, 1.5, 1.5);
	glRotatef(180, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zucc_descendY, 0);
	glRotatef(180, 0, 1, 0);
	zucc_stand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, char7Z);
	draw(tri_base_charge2, nor_base_charge2, uvm_base_charge2, vcl_base_charge2, vtx_base_charge2);

	glPushMatrix();
	glTranslatef(0, 17.4203, -286.219);
	glRotatef(base_charge2_armRot, 1, 0, 0);
	glTranslatef(0, -17.4203, 286.219);
	draw(tri_base_charge2_arm, nor_base_charge2_arm, uvm_base_charge2_arm, vcl_base_charge2_arm, vtx_base_charge2_arm);
	glColor3f(0.058642, 0.34095, 0.8);
	draw(tri_beam, nor_beam, uvm_beam, vtx_beam);
	glColor3f(1, 0.684244, 0.239977);
	draw(tri_beamin, nor_beamin, uvm_beamin, vtx_beamin);
	glColor3f(255, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, -283.219);
	glRotatef(beam_coreRot, 0, 1, 0);
	glTranslatef(0, 0, 283.219);
	draw(tri_beam_core, nor_beam_core, uvm_beam_core, vtx_beam_core);
	glPopMatrix();
	draw(tri_beam_ring, nor_beam_ring, uvm_beam_ring, vtx_beam_ring);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 14.4, 0);
	glScalef(explosionS, explosionS, explosionS);
	glTranslatef(0, -14.4, 0);
	glTranslatef(0, explosionY, 0);
	draw(tri_explosion, nor_explosion, uvm_explosion, vcl_explosion, vtx_explosion);
	glPopMatrix();
	clear;
}

void sceneC8()
{
	clear;

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	draw(tri_base_stab, nor_base_stab, uvm_base_stab, vcl_base_stab, vtx_base_stab);

	glPushMatrix();
	glTranslatef(0, 43.0108, -299.479);
	glRotatef(stabRot, 1, 0, 0);
	glTranslatef(0, -43.0108, 299.479);
	draw(tri_sword_stab, nor_sword_stab, uvm_sword_stab, vcl_sword_stab, vtx_sword_stab);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -288.23);
	glRotatef(decapRot, 0, 1, 0);
	glTranslatef(0, 0, 288.23);
	draw(tri_sword_decap, nor_sword_decap, uvm_sword_decap, vcl_sword_decap, vtx_sword_decap);
	glPopMatrix();
}

void sceneC9()
{
	clear;

	glPushMatrix();
	glScalef(.5, .5, .5);
	glRotatef(180, 0, 1, 0);
	stage_final(tex_final_stage, tex_final_stageX, tex_final_stageY);
	glPopMatrix();

	draw(tri_zucc_final, nor_zucc_final, uvm_zucc_final, vcl_zucc_final, vtx_zucc_final);
	zucc_finalh(tex_zucch, tex_zucchX, tex_zucchY);

	glPushMatrix();
	glTranslatef(0, base_finalY, base_finalZ);
	glTranslatef(0, 11.968, -286.032);
	glRotatef(base_finalRot, 1, 0, 0);
	glTranslatef(0, -11.968, 286.032);
	draw(tri_base_final, nor_base_final, uvm_base_final, vcl_base_final, vtx_base_final);

	glPushMatrix();
	glTranslatef(0, 6.75944, -287.011);
	glRotatef(base_finalKneeRot, 1, 0, 0);
	glTranslatef(0, -6.75944, 287.011);
	draw(tri_base_final_leg, nor_base_final_leg, uvm_base_final_leg, vcl_base_final_leg, vtx_base_final_leg);
	glPopMatrix();
	glPopMatrix();
}

//-------------------------------------------------------------- lighting
void scene1Light()
{
	GLfloat dir[] = { 0, 0.0, 1.0, 0.0 };
	GLfloat ambient[] = { .3,.3,.3, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0);
}

void scene4Light()
{
	GLfloat dir[] = { 0, 0.0, -1.0, 0.0 };
	GLfloat ambient[] = { .3,.3,.3, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0);
}

//-------------------------------------------------------------- animate stuff here
void animator(int)
{
	glutTimerFunc(30, animator, 0);
	cout << "Scene: " << scene << " Elapsed time: " << elapsed_time << endl;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.77, 0.1, 2000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (scene)
	{
	case 0:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		break;
	case 1:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (elapsed_time > 3000)
		{
			if (stage_dkpRot < 0)
			{
				stage_dkpRot += 10;
			}
			if (truckX < 2.8)
			{
				truckX += .1;
			}
			if (truckZ < 100)
			{
				truckZ += 3;
			}

		}
		break;
	case 2:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		bruh_ringH += 5, bruh_ringV += 5, item_Rot += 2;

		if (elapsed_time > 1000 && elapsed_time < 1500)
		{
			bruh_stageRotY = 1;
			if (bruh_stageRot > -90)
			{
				bruh_stageRot -= 5;
			}
		}
		else if (elapsed_time > 2500 && elapsed_time < 6500)
		{
			if (bruh_stageRot < 180)
			{
				bruh_stageRot += 5;
			}
		}
		else if (elapsed_time > 12000 && elapsed_time < 15000)
		{
			if (item_swordY < -1)
			{
				item_swordY += .2;
			}
		}
		break;
	case 3:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (hand_rotationL <= 57)
		{
			hand_rotationL += 1;
		}
		if (hand_rotationR >= -100)
		{
			hand_rotationR -= 1;
		}

		//cout << hand_rotationL;
		break;

	case 4:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		if (hand_rotationL >= -42)
		{
			hand_rotationL -= 1;
		}
		if (hand_rotationR <= -9)
		{
			hand_rotationR += 1;
		}//cout << hand_rotationL;
		break;
	case 5:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		if (hand_rotationL >= -42)
		{
			hand_rotationL -= 1;
		}
		if (hand_rotationR <= -9)
		{
			hand_rotationR += 1;
		}//cout << hand_rotationL;
		break;

	case 6:
		gluLookAt(eyeXcase2, 20, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (eyeZ <= 100)
		{
			eyeZ += 0.8;

		}

		//cout << eyeZ;
		break;
	case 7:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		shootWeapon1 += 5.0;
		shootWeapon2 += 4.4;
		shootWeapon3 += 5.7;
		shootWeapon4 += 5.2;
		shootWeapon5 += 5.9;
		if (eyeX <= 100) {
			eyeX -= -1;
		}
		break;
	case 8:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		shootWeapon1 -= 3.0;
		shootWeapon2 -= 2.4;
		shootWeapon3 -= 2.7;
		shootWeapon4 -= 3.2;
		shootWeapon5 -= 3.9;
		break;
	case 9:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (explosionM <= 5) {
			explosionM += 1;
		}
		//cout << explosionM;
		break;
	case 10:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		explosionM -= 1;
		break;
	case 11:
		gluLookAt(selectchar, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		charFlyUp += 1;

		if (textGup <= 95) {
			textGup += 1;
		}
		if (screenCleared <= 5) {
			screenCleared += 1;
		}
		//cout << textGup;
		break;	
	case 12:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (elapsed_time < 3500)
		{
			if (eyeY > 52.82)
			{
				eyeY -= .1;
				if (lookAtY > 58.953)
				{
					lookAtY -= .1;
				}
			}
		}
		else if (elapsed_time > 3500)
		{
			if (eyeZ < 24.2854)
			{
				eyeZ += .3;
			}
			if (eyeY > 19.9701)
			{
				eyeY -= 1;
			}
			if (lookAtY > 14.2141)
			{
				lookAtY -= 1;
			}
			if (zucc_descendY >= -40.363)
			{
				zucc_descendY -= .9;
				if (zucc_descendY < -40.363)
				{
					zucc_descendY = -40.363;
				}
			}
		}
		break;
	case 13:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (elapsed_time < 3400)
		{
			if (eyeX < 6.72623)
			{
				eyeX += 1;
			}
			if (eyeY < 21.5679)
			{
				eyeY += 1;
			}
			if (eyeZ < 106.939)
			{
				eyeZ += 1;
			}
			if (lookAtY > -12.321)
			{
				lookAtY -= .5;
			}
		}
		else if (elapsed_time > 4000 && elapsed_time < 5000)
		{
			laserY = 0;
		}
		else if (elapsed_time > 5000 && elapsed_time < 5600)
		{
			if (laserrot > -90)
			{
				laserrot -= 4;
			}
			if (elapsed_time > 5200)
			{
				baseHoverY = 0;
				baseStandY = -100;
			}
			if (elapsed_time > 5300)
			{
				zuccrotY += 2;
			}
		}
		else if (elapsed_time > 6000 && elapsed_time < 6100)
		{
			laserY = -999;
			laserrot = 90;
		}
		else if (elapsed_time > 6300 && elapsed_time < 6699)
		{
			baseHoverY = -100;
			baseAtt1Y = 0;
			slashY = 0;
			slashZ -= 6;
		}
		else if (elapsed_time >= 6699 && elapsed_time <= 6799)
		{
			slashZ = 0;
		}
		else if (elapsed_time > 6800 && elapsed_time < 7199)
		{
			slashRot = 29.2686;
			baseAtt1Y = -100;
			baseAtt2Y = 0;
			slashZ -= 6;
		}
		else if (elapsed_time >= 7199 && elapsed_time <= 7299)
		{
			slashZ = 0;
		}
		else if (elapsed_time > 7300 && elapsed_time < 7699)
		{
			slashRot = -32.9279;
			baseAtt2Y = -100;
			baseAtt3Y = 0;
			slashZ -= 6;
		}
		else if (elapsed_time >= 7699 && elapsed_time <= 7799)
		{
			slashY = -999;
		}
		else if (elapsed_time > 8200)
		{
			baseAtt3Y = -100;
		}
		break;
	case 14:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (zucc_stands3_headRot >= -55)
		{
			zucc_stands3_headRot -= 10;
		}
		if (elapsed_time < 1000)
		{
			if (saoY < 0)
			{
				saoY += 3.35;
			}
		}
		else if (elapsed_time >= 1000 && elapsed_time < 1099)
		{
			base_behindY = 0;
		}
		break;
	case 15:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (elapsed_time < 1300)
		{
			if (zuccrotY >= -180)
			{
				zuccrotY -= 5;
			}
			if (saoRot >= -180)
			{
				saoRot -= 5;
			}
			if (saoY <= 3.6)
			{
				saoY += .1;
			}
		}
		else if (elapsed_time > 1300 && elapsed_time < 2500)
		{
			//saoY2 = 2;
			if (saoRot2 >= -90)
			{
				saoRot2 -= 5;
			}
		}
		else if (elapsed_time >= 2500)
		{
			saoY2 += 15;
		}
		break;
	case 16:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
		if (elapsed_time < 2000)
		{
			base_throwZ -= 1;
			if (base_throwZ <= -21)
			{
				shieldZ += 2;
			}
		}
		break;
	case 17:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (saoZ >= -7.2)
		{
			saoZ -= .5;
			if (saoZ < -7.2)
			{
				saoZ = -7.2;
			}
		}
		if (elapsed_time > 480)
		{
			saoY = -100;
			if (lookAtY < 17.2164)
			{
				lookAtY += .2;
			}
			shieldLX -= 1;
			shieldRX += 1;
		}
		break;
	case 18:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		beam_coreRot += 20;

		if (elapsed_time < 4300)
		{
			if (char7Z >= 0)
			{
				char7Z -= 2;
			}

			if (eyeZ < 226.387)
			{
				eyeZ += 2;
				if (eyeZ > 50)
				{
					if (lookAtY < 217.329)
					{
						lookAtY += 2;
					}
					if (lookAtZ > -282.636)
					{
						lookAtZ -= 2;
					}
				}
			}
		}
		else if (elapsed_time >= 4300 && elapsed_time <= 4399)
		{
			eyeX = 154.244, eyeZ = -310.561, eyeY = 175.496;
			lookAtX = 6.06187, lookAtZ = -169.307, lookAtY = 26.1932;
		}
		else if (elapsed_time > 4399)
		{
			if (base_charge2_armRot < 90)
			{
				base_charge2_armRot += 7;
			}
			if (base_charge2_armRot > 88)
			{
				zucc_descendY = -999;
			}
			if (base_charge2_armRot > 88 && explosionS < 44)
			{
				explosionY = 14.4;
				explosionS += 5;
			}
		}
		break;
	case 19:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (elapsed_time > 2000 && elapsed_time < 3000)
		{
			if (stabRot >= -10)
			{
				stabRot -= 5;
			}
		}
		else if (elapsed_time >= 3000 && elapsed_time < 4000)
		{
			if (stabRot < 0)
			{
				stabRot += 5;
			}
		}
		else if (elapsed_time >= 4000 && elapsed_time < 5000)
		{
			if (decapRot >= -110)
			{
				decapRot -= 15;
			}
		}
		break;
	case 20:
		gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

		if (elapsed_time < 800)
		{
			if (base_finalY >= -6.15713 && base_finalZ <= 5.56143 && base_finalKneeRot < 93)
			{
				base_finalY -= .69;
				base_finalZ += .6;
				base_finalKneeRot += 10.6;
				if (base_finalKneeRot > 93)
				{
					base_finalKneeRot = 93;
				}
			}
		}
		else if (elapsed_time > 800)
		{
			if (base_finalY >= -10.89 && base_finalZ <= 9.79643 && base_finalKneeRot > 0)
			{
				base_finalY -= .69;
				base_finalZ += .6;
				base_finalKneeRot -= 13;
				base_finalRot += 13;
				if (base_finalRot > 90)
				{
					base_finalRot = 90;
				}
			}
		}


	default:
		break;
	}
}

//-------------------------------------------------------------- display the scene
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	switch (scene)
	{
	case 0:
		elapsed_time -= sceneZaku_timer;
		scene1Light();
		break;
	case 1:
		elapsed_time -= sceneA1_timer;
		sceneA1();
		break;
	case 2:
		elapsed_time -= sceneA2_timer;
		sceneA2();
		break;
	case 3:
		scene1Light();
		sceneB1();
		break;
	case 4:
		scene1Light();
		sceneB2();
		break;
	case 5:
		//scene1Light();
		sceneB3();
		break;
	case 6:
		scene1Light();
		sceneB4();
		break;
	case 7:
		scene1Light();
		sceneB5();
		break;
	case 8:
		scene1Light();
		sceneB6();
		break;
	case 9:
		scene1Light();
		sceneB7();
		break;
	case 10:
		scene1Light();
		sceneB8();
		break;
	case 11:
		scene1Light();
		sceneB9();
		break;	
	case 12:
		elapsed_time -= sceneC1_timer;
		sceneC1();
		break;
	case 13:
		elapsed_time -= sceneC2_timer;
		sceneC2();
		break;
	case 14:
		elapsed_time -= sceneC3_timer;
		scene1Light();
		sceneC3();
		break;
	case 15:
		elapsed_time -= sceneC4_timer;
		scene4Light();
		sceneC4();
		break;
	case 16:
		elapsed_time -= sceneC5_timer;
		scene1Light();
		sceneC5();
		break;
	case 17:
		elapsed_time -= sceneC6_timer;
		sceneC6();
		break;
	case 18:
		elapsed_time -= sceneC7_timer;
		sceneC7();
		break;
	case 19:
		elapsed_time -= sceneC8_timer;
		sceneC8();
		break;
	case 20:
		elapsed_time -= sceneC9_timer;
		sceneC9();
		break;
	default:
		break;
	}

	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------------- switch between scenes using arrow key left/right
void keyboard_input(int key, int x, int y)
{
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
	case 0:
		sceneZaku_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 50, eyeY = 30, eyeZ = 50;
		lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		break;
	case 1:
		sceneA1_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 0, eyeY = 0, eyeZ = 0;
		lookAtX = 0, lookAtY = -0.015349, lookAtZ = -42.9051;
		stage_dkpRot = -90, truckX = 0, truckZ = 0;
		break;
	case 2:
		sceneA2_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 0, eyeY = 0, eyeZ = 0;
		lookAtX = 0, lookAtY = -0.015349, lookAtZ = -10;
		bruh_ringH = 0, bruh_ringV = 0, bruh_stageRot = 0, bruh_stageRot2 = 0, bruh_stageRotX = 0, bruh_stageRotX = 0;
		item_swordY = -10, item_Rot = 0;
		break;
	case 3:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		hand_rotationL = 0;
		hand_rotationR = 0;
		break;
	case 4:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		hand_rotationL = 0;
		hand_rotationR = 0;
		break;
	case 5:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		hand_rotationL = 0;
		hand_rotationR = 0;
		break;
	case 6:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		break;
	case 7:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		eyeX = 50;
		shootWeapon1 = 0;
		shootWeapon2 = 0;
		shootWeapon3 = 0;
		shootWeapon4 = 0;
		shootWeapon5 = 0;
		break;
	case 8:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		shootWeapon1 = 0;
		shootWeapon2 = 0;
		shootWeapon3 = 0;
		shootWeapon4 = 0;
		shootWeapon5 = 0;
		explosionM = 0;
		break;
	case 9:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		explosionM = 0;
		break;
	case 10:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		break;
	case 11:
		eyeX = 50, eyeY = 30, eyeZ = 50, lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		charFlyUp = 0;
		screenCleared = 0;
		textGup = 0;
		break;	
	case 12:
		sceneC1_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 0, eyeY = 62.82, eyeZ = 12.0009;
		lookAtX = 0, lookAtY = 67.2141, lookAtZ = 0;
		zucc_descendY = 0;
		break;
	case 13:
		sceneC2_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeY = 19.9701, eyeZ = 24.2854;
		lookAtY = 14.2141;
		zucc_descendY = -40.363, laserY = -999, slashY = -999, baseHoverY = -100, baseStandY = 0, baseAtt1Y = -100, baseAtt2Y = -100, baseAtt3Y = -100, slashZ = 0, slashRot = 0, zuccrotY = 0;
		laserrot = 0;
		break;
	case 14:
		sceneC3_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = -5.00634, eyeY = 20.2572, eyeZ = 13.6719;
		lookAtX = -1.56047, lookAtY = 15.4261;
		zuccrotY = 18, saoY = -100, base_behindY = -100, zucc_stands3_headRot = 0, saoRot = 180;
		break;
	case 15:
		sceneC4_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 19.071, eyeY = 10.0823, eyeZ = -17.4246;
		lookAtX = -1.55527, lookAtY = 11.5406, lookAtZ = -6.14334;
		zuccrotY = -138, saoY = 0, saoRot = 0, saoZ = 0, saoRot2 = 0, saoY2 = 0;
		break;
	case 16:
		sceneC5_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 3.98826, eyeY = 17.0232, eyeZ = -25.8591;
		lookAtX = 3.86324, lookAtY = 16.9556, lookAtZ = -26.0528;
		base_throwZ = 0, shieldZ = 0, saoY = 0;
		break;
	case 17:
		sceneC6_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 0, eyeY = 17.0232, eyeZ = -25.6565;
		lookAtX = 0, lookAtY = 16.4164, lookAtZ = -28.2133;
		saoZ = 0, shieldLX = 0, shieldRX = 0, saoY = 0;
		break;
	case 18:
		sceneC7_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 0, eyeY = 17.0232, eyeZ = -15.1216;
		lookAtX = 0, lookAtY = 23.336, lookAtZ = -30.5996;
		char7Z = 251, base_charge2_armRot = 0, zucc_descendY = 0;
		explosionS = 1, explosionY = -999;
		break;
	case 19:
		sceneC8_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = 0, eyeY = 19.8854, eyeZ = -286.904;
		lookAtX = 0, lookAtY = 17.5042, lookAtZ = -281.351;
		stabRot = 0, decapRot = 0;
		break;
	case 20:
		sceneC9_timer = glutGet(GLUT_ELAPSED_TIME);
		eyeX = -15.0246, eyeY = 0.569592, eyeZ = -272.514;
		lookAtX = -1.58326, lookAtY = 10.5921, lookAtZ = -289.64;
		base_finalY = 0, base_finalZ = 0, base_finalKneeRot = 0, base_finalRot = 0;
		break;
	default:
		break;
	}
}

//-------------------------------------------------------------- loaders
void load_textures()
{
	tex_shield = tex_loader("textures/shield.png");
	tex_shieldX = tex_X;
	tex_shieldY = tex_Y;

	tex_final_stage = tex_loader("textures/lilienstein2k.png");
	tex_final_stageX = tex_X;
	tex_final_stageY = tex_Y;

	tex_dkp = tex_loader("textures/dkp.png");
	tex_dkpX = tex_X;
	tex_dkpY = tex_Y;

	tex_zucc = tex_loader("textures/zucc.png");
	tex_zuccX = tex_X;
	tex_zuccY = tex_Y;

	tex_zucch = tex_loader("textures/zucch.png");
	tex_zucchX = tex_X;
	tex_zucchY = tex_Y;

	tex_dom = tex_loader("textures/dom.png");
	tex_domX = tex_X;
	tex_domY = tex_Y;

	tex_bruh = tex_loader("textures/bruh.png");
	tex_bruhX = tex_X;
	tex_bruhY = tex_Y;

	tex_void = tex_loader("textures/void.png");
	tex_voidX = tex_X;
	tex_voidY = tex_Y;

	tex_cc = tex_loader("textures/cc.png");
	tex_ccX = tex_X;
	tex_ccY = tex_Y;

	tex_map = tex_loader("textures/map.png");
	tex_mapX = tex_X;
	tex_mapY = tex_Y;

	tex_map2 = tex_loader("textures/map2.png");
	tex_map2X = tex_X;
	tex_map2Y = tex_Y;

	tex_sky = tex_loader("textures/puresky.png");
	tex_skyX = tex_X;
	tex_skyY = tex_Y;
}

void load_models()
{
	//Q: Can we use models from other sources, such as models from video games or 3d model websites?
	//A: You cannot use models made by other people. The work must be your own.

	obj_loader("models/zucc-descend.obj", tri_zucc_descend, nor_zucc_descend, uvm_zucc_descend, vcl_zucc_descend, vtx_zucc_descend);
	obj_loader("models/zucc-descendh.obj", tri_zucc_descendh, nor_zucc_descendh, uvm_zucc_descendh, vcl_zucc_descendh, vtx_zucc_descendh);
	obj_loader("models/zucc_stand.obj", tri_zucc_stand, nor_zucc_stand, uvm_zucc_stand, vcl_zucc_stand, vtx_zucc_stand);
	obj_loader("models/zucc_standh.obj", tri_zucc_standh, nor_zucc_standh, uvm_zucc_standh, vcl_zucc_standh, vtx_zucc_standh);
	obj_loader("models/laser.obj", tri_laser, nor_laser, uvm_laser, vcl_laser, vtx_laser);
	obj_loader("models/base_stand.obj", tri_baseStand, nor_baseStand, uvm_baseStand, vcl_baseStand, vtx_baseStand);
	obj_loader("models/base_hover.obj", tri_baseHover, nor_baseHover, uvm_baseHover, vcl_baseHover, vtx_baseHover);
	obj_loader("models/base_att1.obj", tri_baseAtt1, nor_baseAtt1, uvm_baseAtt1, vcl_baseAtt1, vtx_baseAtt1);
	obj_loader("models/base_att2.obj", tri_baseAtt2, nor_baseAtt2, uvm_baseAtt2, vcl_baseAtt2, vtx_baseAtt2);
	obj_loader("models/base_att3.obj", tri_baseAtt3, nor_baseAtt3, uvm_baseAtt3, vcl_baseAtt3, vtx_baseAtt3);
	obj_loader("models/slash.obj", tri_slash, nor_slash, uvm_slash, vcl_slash, vtx_slash);

	obj_loader("models/zucc_stands3.obj", tri_zucc_stands3, nor_zucc_stands3, uvm_zucc_stands3, vcl_zucc_stands3, vtx_zucc_stands3);
	obj_loader("models/zucc_stands3_head.obj", tri_zucc_stands3_head, nor_zucc_stands3_head, uvm_zucc_stands3_head, vcl_zucc_stands3_head, vtx_zucc_stands3_head);
	obj_loader("models/base_behind.obj", tri_base_behind, nor_base_behind, uvm_base_behind, vcl_base_behind, vtx_base_behind);
	obj_loader("models/sao.obj", tri_sao, nor_sao, uvm_sao, vcl_sao, vtx_sao);

	obj_loader("models/shield.obj", tri_shield, nor_shield, uvm_shield, vcl_shield, vtx_shield);
	obj_loader("models/base_throw.obj", tri_base_throw, nor_base_throw, uvm_base_throw, vcl_base_throw, vtx_base_throw);

	obj_loader("models/elucidator.obj", tri_elucidator, nor_elucidator, uvm_elucidator, vcl_elucidator, vtx_elucidator);
	obj_loader("models/repulsor.obj", tri_repulsor, nor_repulsor, uvm_repulsor, vcl_repulsor, vtx_repulsor);
	obj_loader("models/shieldL.obj", tri_shieldL, nor_shieldL, uvm_shieldL, vcl_shieldL, vtx_shieldL);
	obj_loader("models/shieldR.obj", tri_shieldR, nor_shieldR, uvm_shieldR, vcl_shieldR, vtx_shieldR);
	obj_loader("models/base_charge.obj", tri_base_charge, nor_base_charge, uvm_base_charge, vcl_base_charge, vtx_base_charge);

	obj_loader("models/base_charge2.obj", tri_base_charge2, nor_base_charge2, uvm_base_charge2, vcl_base_charge2, vtx_base_charge2);
	obj_loader("models/base_charge2_arm.obj", tri_base_charge2_arm, nor_base_charge2_arm, uvm_base_charge2_arm, vcl_base_charge2_arm, vtx_base_charge2_arm);
	obj_loader("models/beam.obj", tri_beam, nor_beam, uvm_beam, vcl_beam, vtx_beam);
	obj_loader("models/beamin.obj", tri_beamin, nor_beamin, uvm_beamin, vcl_beamin, vtx_beamin);
	obj_loader("models/beam_core.obj", tri_beam_core, nor_beam_core, uvm_beam_core, vcl_beam_core, vtx_beam_core);
	obj_loader("models/beam_ring.obj", tri_beam_ring, nor_beam_ring, uvm_beam_ring, vcl_beam_ring, vtx_beam_ring);

	obj_loader("models/base_stab.obj", tri_base_stab, nor_base_stab, uvm_base_stab, vcl_base_stab, vtx_base_stab);
	obj_loader("models/sword_stab.obj", tri_sword_stab, nor_sword_stab, uvm_sword_stab, vcl_sword_stab, vtx_sword_stab);
	obj_loader("models/sword_decap.obj", tri_sword_decap, nor_sword_decap, uvm_sword_decap, vcl_sword_decap, vtx_sword_decap);

	obj_loader("models/zucc_final.obj", tri_zucc_final, nor_zucc_final, uvm_zucc_final, vcl_zucc_final, vtx_zucc_final);
	obj_loader("models/zucc_finalh.obj", tri_zucc_finalh, nor_zucc_finalh, uvm_zucc_finalh, vcl_zucc_finalh, vtx_zucc_finalh);
	obj_loader("models/base_final.obj", tri_base_final, nor_base_final, uvm_base_final, vcl_base_final, vtx_base_final);
	obj_loader("models/base_final_leg.obj", tri_base_final_leg, nor_base_final_leg, uvm_base_final_leg, vcl_base_final_leg, vtx_base_final_leg);
	obj_loader("models/final_stage.obj", tri_final_stage, nor_final_stage, uvm_final_stage, vcl_final_stage, vtx_final_stage);

	obj_loader("models/stage_dkp.obj", tri_stage_dkp, nor_stage_dkp, uvm_stage_dkp, vcl_stage_dkp, vtx_stage_dkp);
	obj_loader("models/truck.obj", tri_truck, nor_truck, uvm_truck, vcl_truck, vtx_truck);
	obj_loader("models/dom.obj", tri_dom, nor_dom, uvm_dom, vcl_dom, vtx_dom);

	obj_loader("models/bruh.obj", tri_bruh, nor_bruh, uvm_bruh, vcl_bruh, vtx_bruh);
	obj_loader("models/bruh_ring.obj", tri_bruh_ring, nor_bruh_ring, uvm_bruh_ring, vcl_bruh_ring, vtx_bruh_ring);
	obj_loader("models/bruh_ring2.obj", tri_bruh_ring2, nor_bruh_ring2, uvm_bruh_ring2, vcl_bruh_ring2, vtx_bruh_ring2);
	obj_loader("models/item_sword.obj", tri_item_sword, nor_item_sword, uvm_item_sword, vcl_item_sword, vtx_item_sword);
	obj_loader("models/item_cc.obj", tri_item_cc, nor_item_cc, uvm_item_cc, vcl_item_cc, vtx_item_cc);
	obj_loader("models/explosion.obj", tri_explosion, nor_explosion, uvm_explosion, vcl_explosion, vtx_explosion);

	obj_loader("models/Charselection.obj", tri_Charselection, nor_Charselection, uv_Charselection, vc_Charselection, vt_Charselection);
	obj_loader("models/Charselection2.obj", tri_Charselection2, nor_Charselection2, uv_Charselection2, vc_Charselection2, vt_Charselection2);
	obj_loader("models/selectLefthand.obj", tri_selectLefthand, nor_selectLefthand, uv_selectLefthand, vc_selectLefthand, vt_selectLefthand);
	obj_loader("models/selectRighthand.obj", tri_selectRighthand, nor_selectRighthand, uv_selectRighthand, vc_selectRighthand, vt_selectRighthand);
	obj_loader("models/p2wcharStatic.obj", tri_p2wcharStatic, nor_p2wcharStatic, uv_p2wcharStatic, vc_p2wcharStatic, vt_p2wcharStatic);
	obj_loader("models/p2wcharStaticv2.obj", tri_p2wcharStaticv2, nor_p2wcharStaticv2, uv_p2wcharStaticv2, vc_p2wcharStaticv2, vt_p2wcharStaticv2);
	obj_loader("models/p2wcharStaticv3.obj", tri_p2wcharStaticv3, nor_p2wcharStaticv3, uv_p2wcharStaticv3, vc_p2wcharStaticv3, vt_p2wcharStaticv3);
	obj_loader("models/weapon2Re.obj", tri_weapon2Re, nor_weapon2Re, uv_weapon2Re, vc_weapon2Re, vt_weapon2Re);
	obj_loader("models/weapon3Re.obj", tri_weapon3Re, nor_weapon3Re, uv_weapon3Re, vc_weapon3Re, vt_weapon3Re);
	obj_loader("models/weapon2.obj", tri_weapon2, nor_weapon2, uv_weapon2, vc_weapon2, vt_weapon2);
	obj_loader("models/weapon3.obj", tri_weapon3, nor_weapon3, uv_weapon3, vc_weapon3, vt_weapon3);
	obj_loader("models/1.obj", tri_1, nor_1, uv_1, vc_1, vt_1);
	obj_loader("models/1Re.obj", tri_1Re, nor_1Re, uv_1Re, vc_1Re, vt_1Re);
	obj_loader("models/4Re.obj", tri_4Re, nor_4Re, uv_4Re, vc_4Re, vt_4Re);
	obj_loader("models/4.obj", tri_4, nor_4, uv_4, vc_4, vt_4);
	obj_loader("models/skyGlobe.obj", tri_skyGlobe, nor_skyGlobe, uv_skyGlobe, vc_skyGlobe, vt_skyGlobe);
	obj_loader("models/expeloson.obj", tri_expeloson, nor_expeloson, uv_expeloson, vc_expeloson, vt_expeloson);
	obj_loader("models/blackScreen.obj", tri_blackScreen, nor_blackScreen, uv_blackScreen, vc_blackScreen, vt_blackScreen);
	obj_loader("models/blackScreenText.obj", tri_blackScreenText, nor_blackScreenText, uv_blackScreenText, vc_blackScreenText, vt_blackScreenText);
}

//-------------------------------------------------------------- init
void initGL()
{
	glEnable(GL_COLOR_MATERIAL); // cheat!!!! 
	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glLineWidth(2);
	glClearColor(0, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	stbi_set_flip_vertically_on_load(true);
}

//-------------------------------------------------------------- main
int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Another World");
	glutDisplayFunc(display);
	glutTimerFunc(30, animator, 0);
	glutSpecialFunc(keyboard_input);
	initGL();
	load_textures();
	load_models();

	HWND win_handle = FindWindow(0, L"Another World");
	ShowWindowAsync(win_handle, SW_SHOWMAXIMIZED);

	glutMainLoop();
}