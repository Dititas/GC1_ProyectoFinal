#ifndef imageness
#define imageness



#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gdiplus.h>




using namespace Gdiplus;

class Imagenes {
public:
	Imagenes()
	{
	}

	~Imagenes()
	{
	}
private:
	unsigned char* dir_imagen, * primero;
	unsigned int ancho;
	unsigned int alto;

public:
	void Carga(WCHAR nombre[])
	{
		GdiplusStartupInput gdiplusStartupInput;
		//gdiplusStartupInput.GdiplusVersion = 1;
		//gdiplusStartupInput.DebugEventCallback = NULL;
		//gdiplusStartupInput.SuppressBackgroundThread = FALSE;
		//gdiplusStartupInput.SuppressExternalCodecs = FALSE;
		ULONG_PTR     gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


		Bitmap* bitmap = new Bitmap(nombre);
		BitmapData* bitmapData = new BitmapData;

		ancho = bitmap->GetWidth();
		alto = bitmap->GetHeight();

		Rect rect(0, 0, ancho, alto);

		bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, bitmapData);

		unsigned char* pixels = (unsigned char*)bitmapData->Scan0;

		int tamaño;
		tamaño = ancho * alto * 3;

		dir_imagen = new unsigned char[tamaño];
		primero = dir_imagen;

		//tenemos que invertir el blue por el red
		//el green se conserva en posicion
		for (unsigned int i = 0; i < (alto * ancho * 3); i += 3)
		{
			dir_imagen[i + 2] = pixels[i];
			dir_imagen[i + 1] = pixels[i + 1];
			dir_imagen[i] = pixels[i + 2];
		}

		bitmap->UnlockBits(bitmapData);

		delete bitmapData;
		delete bitmap;

		GdiplusShutdown(gdiplusToken);
	}

	void Descarga()
	{
		delete[] dir_imagen;
	}

	unsigned char* Dir_Imagen()
	{
		return primero;
	}

	unsigned int Ancho()
	{
		return ancho;
	}

	unsigned int Alto()
	{
		return alto;
	}
};
#endif