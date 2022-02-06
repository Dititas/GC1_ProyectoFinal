#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <mmsystem.h>

#include "../Headers/CGfxOpenGL.h"


bool exiting = false;
const int windowWidth = 1920;
const int long windowHeight = 1080;
const int windowBits = 32;
const char APP_NAME[] = "Plantilla OpenGL CG1";

float grados = 0;
float MOVER = 0;
float SKLA = 0;
float RX = 0, RY = 0, RZ = 0;
int MX = 0, MY = 0, MZ = 0;
float TX = 0, TY = 0, TZ = 0;
float R_aspa = 0, R_boya = 0, R_otro = 0;
float INDC = 1;

float art = 1;
bool BN = true;
bool BF = true;
bool BB = true;

GLfloat COLIS[600][600][3];

bool BNDRA = true;

bool fullscreen = false;
HDC hDC;

CGfxOpenGL* g_glRender = NULL;

//esta funcion hace lo de siempre, inicializa el formato en que se
//interpretaran los datos de la pantalla, pixeles.
void SetupPixelFormat(HDC hDC)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{
	  sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HGLRC hRC;
	int height, width;
	int xPos, yPos, fwButtons;

	switch (uMsg)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		SetupPixelFormat(hDC);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		if (joySetCapture(hWnd, JOYSTICKID1, NULL, FALSE))
		{
			//MessageBeep(MB_ICONEXCLAMATION); 
			MessageBox(hWnd, L"NO HAY UN GAMEPAD CONECTADO, FAVOR DE CONECTARLO", NULL, MB_OK | MB_ICONEXCLAMATION);
			//PostMessage(hWnd,WM_CLOSE,0,0L); 
		}

		break;
	case WM_DESTROY:
	case WM_QUIT:
	case WM_CLOSE:
		KillTimer(hWnd, 100);
		//FreeDirectInput();   
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		break;

	case WM_SIZE://este se activa cuando se cambia el tamaño de la pantalla
		height = HIWORD(lParam);
		width = LOWORD(lParam);
		g_glRender->SetupProjection(width, height);
		break;


	case MM_JOY1MOVE:
		fwButtons = wParam;
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);

		switch (lParam)
		{
		case 32511:			//UP--------------------------------
			g_glRender->mov6 += art;

			break;

		case 2130706431:		//RIGHT-----------------------------
			g_glRender->mov1 -= art;

			break;

		case -33025:			//DOWN------------------------------
			g_glRender->mov6 -= art;

			break;

		case 2130640896:		//LEFT------------------------------
			g_glRender->mov1 += art;

			break;
		}
		if (fwButtons == 128)
		{
			INDC = 40;
		}
		else
		{
			INDC = 1;
		}

		switch (fwButtons)
		{

		case 1:				//TRIANGULO-------------------------

			break;

		case 2:				//CIRCULO---------------------------
			g_glRender->giro += art;

			break;

		case 4:				//EQUIS-----------------------------

			break;

		case 8:				//CUADRADO--------------------------
			g_glRender->giro -= art;


			break;

		case 64:				//-L1-------------------------------
			g_glRender->mov5 += art;

			break;

		case 16:				//-L2-------------------------------

			break;

		case 128:				//-R1-------------------------------
			g_glRender->mov5 -= art;

			break;

		case 32:				//-R2-------------------------------

			break;

		case 256:				//-SELECT---------------------------

			break;

		case 512:				//-START----------------------------

			break;
		}
		break;

	case WM_CHAR:
		int dato;
		LPARAM tecla;
		dato = (char)wParam;
		tecla = lParam;
		switch (dato)
		{
			//---------------------------------------------------
		case 'q':

			break;
		case 'w':


			break;

		case 'a':

			break;
		case 's':

			break;

		case 'z':

			break;
		case 'x':

			break;

		case 'o':


			break;
		case 'p':

			break;

		}
		break;

	case WM_ACTIVATEAPP:
		break;


	case WM_ACTIVATE:
		return TRUE;

	case WM_PAINT://hay que ponerlo para que funcione el timer aunque haga nada				
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:// aqui activa los eventos del timer

		if (BN == true)
		{
			g_glRender->R_bote += 1;
			if (g_glRender->R_bote >= 5)

			{
				BN = false;
			}
		}
		else
		{
			g_glRender->R_bote -= 1;
			if (g_glRender->R_bote <= -5)
			{
				BN = true;
			}
		}

		if (BF == true)
		{
			g_glRender->R_boot += 1;
			if (g_glRender->R_boot >= 0)

			{
				BF = false;
			}
		}
		else
		{
			g_glRender->R_boot -= 1;
			if (g_glRender->R_boot <= -90)
			{
				BF = true;
			}
		}
		if (BB == true)
		{
			g_glRender->R_beet += 1;
			if (g_glRender->R_beet >= 0)

			{
				BB = false;
			}
		}
		else
		{
			g_glRender->R_beet -= 1;
			if (g_glRender->R_beet <= -90)
			{
				BB = true;
			}
		}



		g_glRender->Render();
		SwapBuffers(hDC);
		break;
	case WM_LBUTTONDOWN:

		break;

	case WM_RBUTTONDOWN:
		KillTimer(hWnd, 100);
		PostQuitMessage(0);
		break;

	case WM_XBUTTONDOWN:

		KillTimer(hWnd, 100);
		PostQuitMessage(0);

		break;

	case WM_MOUSEMOVE:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_RBUTTONUP:
		break;

	case WM_KEYUP:
		break;

	case WM_KEYDOWN:
		int fwKeys;
		LPARAM keyData;
		fwKeys = (int)wParam;
		keyData = lParam;

		switch (fwKeys)
		{
		case VK_ESCAPE:
			KillTimer(hWnd, 100);
			PostQuitMessage(0);
			break;

		case VK_DOWN:


			break;

		case VK_UP:

			break;

		case VK_LEFT:

			break;

		case VK_RIGHT:

			break;
			//---------------------------------------------------
		case VK_CONTROL:

			break;
		case VK_SHIFT:

			break;


		default:
			break;
		}

		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;
	HWND	   hwnd;
	MSG	   msg;
	DWORD	   dwExStyle;
	DWORD	   dwStyle;
	RECT	   windowRect;

	g_glRender = new CGfxOpenGL; //atencion aqui

	windowRect.left = (long)0;
	windowRect.right = (long)windowWidth;
	windowRect.top = (long)0;
	windowRect.bottom = (long)windowHeight;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = MainWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"GLClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&windowClass))
		return 0;

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = windowWidth;
		dmScreenSettings.dmPelsHeight = windowHeight;
		dmScreenSettings.dmBitsPerPel = windowBits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL, L"Display mode failed", NULL, MB_OK);
			fullscreen = FALSE;
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);


	hwnd = CreateWindowEx(NULL,
		L"GLClass",
		L"Plantilla Graficas Computacionales 1",
		dwStyle | WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	hDC = GetDC(hwnd);


	if (!hwnd)
		return 0;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	if (!g_glRender->Init())
	{
		delete g_glRender;
		return 0;
	}

	SetTimer(hwnd, 100, 50, (TIMERPROC)NULL);//aqui generamos el timer

	while (!exiting)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
			{
				exiting = true;
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete g_glRender;
	g_glRender = NULL;

	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	return (int)msg.wParam;
}