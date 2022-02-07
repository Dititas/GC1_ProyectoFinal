#ifndef textu
#define textu


#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "glext.h"
#include "cargaImgs.h"

class SkyBox {

protected:
	unsigned int m_texturas[7];
	unsigned int m_grassTexture;
	unsigned int m_waterTexture;

	float     m_size;
	GLubyte   mapa_de_alturas[260 * 260];

public:
	SkyBox()
	{
		for (int i = 0; i < 6; i++)
			m_texturas[i] = 0;
	}

	~SkyBox()
	{
		Libera();
	}

public:
	void Tamaño(float tam)
	{
		m_size = tam;
	}

	void Libera()
	{

		for (int i = 0; i < 6; ++i)
			glDeleteTextures(6, &m_texturas[0]);
		glDeleteTextures(1, &m_grassTexture);

	}

	bool CargaTextura(WCHAR* top, WCHAR* bottom, WCHAR* front, WCHAR* back, WCHAR* left, WCHAR* right, WCHAR* terreno_mapa, WCHAR* mater, WCHAR* water)
	{
		Imagenes texturas;

		texturas.Carga(terreno_mapa);
		unsigned char* mapa = texturas.Dir_Imagen();
		for (unsigned int i = 0; i < texturas.Alto(); i++)
			for (unsigned int j = 0; j < texturas.Ancho(); j++)
				mapa_de_alturas[(i * 260 + j)] = mapa[(i * 260 + j) * 3];
		texturas.Descarga();

		texturas.Carga(mater);
		glGenTextures(1, &m_grassTexture);
		glBindTexture(GL_TEXTURE_2D, m_grassTexture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();


		texturas.Carga(top);
		glGenTextures(1, &m_texturas[SKY_TOP]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_TOP]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();

		texturas.Carga(bottom);
		glGenTextures(1, &m_texturas[SKY_BOTTOM]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_BOTTOM]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();

		texturas.Carga(front);
		glGenTextures(1, &m_texturas[SKY_FRONT]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_FRONT]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();

		texturas.Carga(back);
		glGenTextures(1, &m_texturas[SKY_BACK]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_BACK]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();

		texturas.Carga(left);
		glGenTextures(1, &m_texturas[SKY_LEFT]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_LEFT]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();

		texturas.Carga(right);
		glGenTextures(1, &m_texturas[SKY_RIGHT]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_RIGHT]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();

		texturas.Carga(water);
		glGenTextures(1, &m_texturas[WATER]);
		glBindTexture(GL_TEXTURE_2D, m_texturas[WATER]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturas.Ancho(), texturas.Alto(), GL_RGB, GL_UNSIGNED_BYTE, texturas.Dir_Imagen());
		texturas.Descarga();


		return true;
	}

	void Traza(float cameraX, float cameraY, float cameraZ)
	{
		glPushMatrix();

		//glTranslatef(cameraX, cameraY, cameraZ);

		glPushAttrib(GL_FOG_BIT | GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// Top
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_TOP]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, m_size, m_size);
		glEnd();

		// Bottom
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_BOTTOM]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, -m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glEnd();

		// Front
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_FRONT]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
		glEnd();

		// Back
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_BACK]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
		glEnd();

		// Right
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_RIGHT]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, -m_size, -m_size);
		glEnd();

		// Left
		glBindTexture(GL_TEXTURE_2D, m_texturas[SKY_LEFT]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, m_size, m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glEnd();



		glPopAttrib();
		glEndList();
		glPopMatrix();

	}

	void DibujaTerreno()
	{

		glBindTexture(GL_TEXTURE_2D, m_grassTexture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		for (int z = 0; z < 260 - 1; ++z)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glScalef(50, 50, 50);
			for (int x = 0; x < 260; ++x)
			{
				// render two vertices of the strip at once
				float scaledHeight = mapa_de_alturas[z * 260 + x] / 8.53;
				float nextScaledHeight = mapa_de_alturas[(z + 1) * 260 + x] / 8.53;
				float color = 0.5f + 0.5f * scaledHeight / 30;
				float nextColor = 0.5f + 0.5f * nextScaledHeight / 30;

				glColor3f(color, color, color);
				glTexCoord2f((GLfloat)x / 260 * 8, (GLfloat)z / 260 * 8);
				glVertex3f(static_cast<GLfloat>(x - 260 / 2), scaledHeight, static_cast<GLfloat>(z - 260 / 2));

				glColor3f(nextColor, nextColor, nextColor);
				glTexCoord2f((GLfloat)x / 260 * 8, (GLfloat)(z + 1) / 260 * 8);
				glVertex3f(static_cast<GLfloat>(x - 260 / 2), nextScaledHeight, static_cast<GLfloat>(z + 1 - 260 / 2));
			}
			glEnd();
		}
	}

	void DibujaAGUATerreno()
	{
		glPushMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		// Water-------------------------------------
		glBindTexture(GL_TEXTURE_2D, m_texturas[WATER]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, 16, 100);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-100, 16, -100);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 16, -100);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(100, 16, 100);
		glEnd();

		glDisable(GL_BLEND);

		glPopAttrib();
		glEndList();
		glPopMatrix();
	}
	enum {
		SKY_TOP,
		SKY_BOTTOM,
		SKY_FRONT,
		SKY_BACK,
		SKY_LEFT,
		SKY_RIGHT,
		WATER
	};
};

#endif