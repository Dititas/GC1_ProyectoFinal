#include <Math.h>
#include "GL.h"
class MatrixOp {
public:
	typedef GLfloat Matriz[4][4];
	typedef float Puntos[3];

	GLfloat raiz[4][4];
	GLfloat MC[16];
	GLfloat tempo[4][4];
	MatrixOp() {
	}
	void lmadComp_OGL()
	{
		int i = 0;
		for (int filas = 0; filas < 4; filas++)
		{
			for (int columnas = 0; columnas < 4; columnas++)
			{
				MC[i] = raiz[columnas][filas];
				i++;
			}
		}
	}
	void lmadCargaIdentidad(GLfloat Identidad[4][4])
	{
		for (int filas = 0; filas < 4; filas++) {
			for (int columnas = 0; columnas < 4; columnas++) {
				Identidad[filas][columnas] = (filas == columnas);
			}
		}
	}
	void lmadProdMatrices(GLfloat factor1[4][4], GLfloat factor2[4][4])
	{
		float MCTran[4][4];
		float resul[4][4];
		float* p, * q, * r;
		lmadCargaIdentidad(MCTran);
		lmadCargaIdentidad(resul);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				MCTran[i][j] = factor2[j][i];
			}
		}

		for (int i = 0; i < 4; i++)
		{
			p = &factor1[0][0];
			q = &MCTran[i][0];
			r = &resul[i][0];

			__asm {
				mov esi, p
				mov edi, q

				movlps xmm7, [edi]
				movhps xmm7, [edi + 8]

				movlps xmm0, [esi]
				movhps xmm0, [esi + 8]
				mulps  xmm0, xmm7

				movlps xmm1, [esi + 16]
				movhps xmm1, [esi + 24]
				mulps  xmm1, xmm7

				movlps xmm2, [esi + 32]
				movhps xmm2, [esi + 40]
				mulps  xmm2, xmm7

				movlps xmm3, [esi + 48]
				movhps xmm3, [esi + 56]
				mulps  xmm3, xmm7

				haddps xmm0, xmm1
				haddps xmm2, xmm3
				haddps xmm0, xmm2

				mov esi, r
				movlps[esi], xmm0
				movhps[esi + 8], xmm0
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					factor2[i][j] = resul[j][i];
				}
			}
		}

	}
	void lmadEscala(float sx, float sy, float sz)
	{
		GLfloat MCEscala[4][4];
		lmadCargaIdentidad(MCEscala);
		MCEscala[0][0] = sx;
		MCEscala[1][1] = sy;
		MCEscala[2][2] = sz;
		lmadProdMatrices(MCEscala, raiz);
		lmadComp_OGL();
	}
	void lmadTranslacion(float tx, float ty, float tz)
	{
		GLfloat MCTraslacion[4][4];
		lmadCargaIdentidad(MCTraslacion);
		MCTraslacion[0][3] = tx;
		MCTraslacion[1][3] = ty;
		MCTraslacion[2][3] = tz;
		lmadProdMatrices(MCTraslacion, raiz);
		lmadComp_OGL();


	}
	void lmadRotacion(float angx, float angy, float angz)
	{
		GLfloat MCRotX[4][4], MCRotY[4][4], MCRotZ[4][4];

		angx = (angx * 3.14159) / 180;
		angy = (angy * 3.14159) / 180;
		angz = (angz * 3.14159) / 180;

		lmadCargaIdentidad(MCRotX);
		lmadCargaIdentidad(MCRotY);
		lmadCargaIdentidad(MCRotZ);

		MCRotX[1][1] = cos(angx);
		MCRotX[2][1] = sin(angx);
		MCRotX[1][2] = -1 * (sin(angx));
		MCRotX[2][2] = cos(angx);

		MCRotY[0][0] = cos(angy);
		MCRotY[0][2] = sin(angy);
		MCRotY[2][0] = -1 * (sin(angy));
		MCRotY[2][2] = cos(angy);

		MCRotZ[0][0] = cos(angz);
		MCRotZ[1][0] = sin(angz);
		MCRotZ[0][1] = -1 * (sin(angz));
		MCRotZ[1][1] = cos(angz);

		lmadProdMatrices(MCRotX, raiz);
		lmadProdMatrices(MCRotY, raiz);
		lmadProdMatrices(MCRotZ, raiz);

		lmadComp_OGL();
	}
};