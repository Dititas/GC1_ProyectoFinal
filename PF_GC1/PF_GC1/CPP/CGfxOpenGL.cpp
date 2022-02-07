
#include <windows.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "../Headers/Matrices.h"
#include "../Headers/CGfxOpenGL.h"
#include "../Headers/Texture.h"
#include "../Headers/glm.h"
#include "../Headers/cargaOps.h"

SkyBox m_skybox;
MatrixOp operacion, operacion2;
float puntos[3][3], vector[3];
float tempang, tempang2, tempang3, xx, yy, zz, Puntoseparado[3];
bool unavez = true;
GLMmodel* Modelo = NULL;
GLMmodel* pmodel2 = NULL;
GLMmodel* pmodel3 = NULL;
GLMmodel* respmodelo = NULL;
GLMmodel* ModeloCSA = NULL;


GLfloat density = 0.0075;
GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };
GLuint texture;
Texture treeTexture;
GLUquadricObj* quadratic;
float translacionesx, translacionesy, translacionesz, angulox, anguloy, anguloz;
float trasfera_X, trasfera_Y, trasfera_Z;
// disable implicit float-double casting
#pragma warning(disable:4305)
CGfxOpenGL::CGfxOpenGL()
{
	grad_rad = 3.141592 / 180;
	y = 0;	x = 0; z = -10;
	xs = 0; ys = 0; zs = 0;
	Angulo2 = 0;	Angulo = 0;	Angulo3 = 0;
	mov1 = 0;
	mov2 = 0;
	mov3 = 0;
	mov4 = 0;
	mov5 = 0;
	mov6 = 0;
	scale1 = 0;
	scale2 = 0;
	giro = 0;
	R_bote = 0;
	R_boot = 0;
	R_beet = 0;

	trasfera_X = 0;	trasfera_Y = 0;	trasfera_Z = -5;
	camera.camx = 0;
	camera.camy = 0;
	camera.camz = -10;
	camera.centerx = 0;
	camera.centery = 0;
	camera.centerz = 0;
	camera.grados = 0;
	rotx = 0; rotz = -10;
}


CGfxOpenGL::~CGfxOpenGL()
{
}


bool CGfxOpenGL::Init()
{
	// clear to black background
	m_skybox.Tamaño(190.0);
	m_skybox.CargaTextura(L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\top.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\bottom.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\front.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\back.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\left.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\right.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\mapaTerrenoOGR.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\zacatito.bmp",
		L"C:\\Users\\Ditit\\OneDrive\\Escritorio\\Abdias\\7_Semestre\\Materias\\Gráficas Computacionales 1\\ProyectoFinal_GC1\\PF_GC1\\PF_GC1\\Bmp\\zacatito.bmp");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_NICEST);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat mat_shininess[] = { 100.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_NORMALIZE);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	m_angle = 0.0f;
	return true;
}


bool CGfxOpenGL::Shutdown()
{
	m_skybox.Libera();
	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0) // don’t want a divide by zero
	{
		height = 1;
	}

	glViewport(0, 0, width, height); // reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION); // set projection matrix current matrix
	glLoadIdentity(); // reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW); // set modelview matrix
	glLoadIdentity(); // reset modelview matrix
	m_windowWidth = width;
	m_windowHeight = height;
}
//estableces modo matriz

void CGfxOpenGL::Prepare(float dt)
{
	m_angle += 0.1f;
}



//bool Carga_texturas()
//{
//	if (LoadTGA(&treeTexture, "blacksmith.tga"))
//	{
//		glGenTextures(1, &treeTexture.texID);
//		glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
//		glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glEnable(GL_TEXTURE_2D);
//
//		if (treeTexture.imageData)
//		{
//			free(treeTexture.imageData);
//		}
//		return true;
//	}
//	else return false;
//
//	if (LoadTGA(&treeTexture, "blacksmith_texture.tga"))
//	{
//		glGenTextures(1, &treeTexture.texID);
//		glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
//		glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glEnable(GL_TEXTURE_2D);
//
//		if (treeTexture.imageData)
//		{
//			free(treeTexture.imageData);
//		}
//		return true;
//	}
//	else return false;
//}








//void Carga_Nave() {
//	if (!pmodel2) {
//		pmodel2 = glmReadOBJ("2naveazul.obj");
//		if (!pmodel2)
//			exit(0);
//		glmUnitize(pmodel2);
//		glmFacetNormals(pmodel2);
//		glmVertexNormals(pmodel2, 90.0);
//	}
//	glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
//}


//void Carga_Casa() {
//	if (!ModeloCSA) {
//		ModeloCSA = glmReadOBJ("CSA.obj");
//		if (!ModeloCSA)
//			exit(0);
//		glmUnitize(ModeloCSA);
//		glmFacetNormals(ModeloCSA);
//		glmVertexNormals(ModeloCSA, 90.0);
//	}
//	glmDraw(ModeloCSA, GLM_SMOOTH | GLM_TEXTURE);
//}













//void Carga_place() {
//	if (!pmodel3) {
//		pmodel3 = glmReadOBJ("casa.obj");
//		if (!pmodel3)
//			exit(0);
//		glmUnitize(pmodel3);
//		glmFacetNormals(pmodel3);
//		glmVertexNormals(pmodel3, 90.0);
//	}
//	//glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
//	glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
//}


void CGfxOpenGL::Render()
{
	tempang = Angulo;
	tempang2 = Angulo2;
	tempang3 = Angulo3;
	translacionesx = x;
	translacionesy = y;
	translacionesz = z;
	angulox = Angulo;
	anguloy = Angulo2;
	anguloz = Angulo3;
	trasfera_X = xs;
	trasfera_Y = ys;
	trasfera_Z = zs;
	if (Angulo >= 360)
	{
		Angulo = 0;
	}
	else
	{
		if (Angulo2 >= 360)
		{
			Angulo = 0;
		}
		else
		{
			if (Angulo3 >= 360)
			{
				Angulo = 0;
			}
		}
	}
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position[] = { 0,-33,0.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLoadIdentity();
	glClearColor(-1.7, 0.2, 0.4, 0.5f);
	/*gluLookAt(camera.camx,  camera.camy,  camera.camz,
			  camera.centerx,  camera.centery-2.5,  camera.centerz,
			  0.0, 1.0, 0.0);
	operacion.lmadCargaIdentidad(operacion.raiz);
	operacion.lmadComp_OGL();

	operacion.lmadTranslacion(camera.camx,0,-camera.camz);

	operacion.lmadEscala(1.5,1,1.5);
	operacion.lmadRotacion(0,Angulo2,0);

	glMultMatrixf(operacion.MC);*/
	gluLookAt(0, 0, +10, 0, 0, 0, 0, 1, 0);

	m_skybox.Traza(camera.camx, camera.camy, camera.camz);


	glPushMatrix();
	operacion.lmadCargaIdentidad(operacion.raiz);
	operacion.lmadTranslacion(6 + mov1, -36 + mov5, -75 + mov6);
	operacion.lmadRotacion(0, giro, 0);

	glLoadMatrixf(operacion.MC);

	m_skybox.DibujaTerreno();
	m_skybox.DibujaAGUATerreno();
	glPopMatrix();

	glLoadMatrixf(operacion.MC);
	glPushMatrix();
	operacion.lmadCargaIdentidad(operacion.raiz);
	operacion.lmadComp_OGL();
	operacion.lmadEscala(1.5, 1.5, 1.5);
	operacion.lmadRotacion(0, 180, 0);
	operacion.lmadTranslacion(0/*x*/, -.95, z);
	operacion.lmadRotacion(0, giro, 0);


	glLoadMatrixf(operacion.MC);

	////________________________________________________OBJETOS_________________________________________________________

	//glPushMatrix();
	//operacion.lmadCargaIdentidad(operacion.raiz);
	//operacion.lmadTranslacion(0, 0, 3);
	//operacion.lmadRotacion(0, giro, 0);
	//operacion.lmadEscala(-2, -2, -2);
	//glLoadMatrixf(operacion.MC);



	//Carga_Nave();
	//glPopMatrix();

	//glPushMatrix();
	//operacion.lmadCargaIdentidad(operacion.raiz);

	//operacion.lmadTranslacion(-2 + (mov1 / 16), .5 + (mov5 / 16), -6 + (mov6 / 16));
	//operacion.lmadRotacion(0, giro, 0);
	//operacion.lmadEscala(16, 16, 16);
	//glLoadMatrixf(operacion.MC);

	//Carga_Casa();
	//glPopMatrix();




	////________________________________________________________________________________________________________________	

	//glPopMatrix();


}
