#include <windows.h>
#include <math.h>
#include <gl/gl.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


struct rgbf {float r; float g; float b;};
//WBL 9 May 2007 Based on
//http://www.codeguru.com/cpp/w-d/dislog/commondialogs/article.php/c1861/
//Common.h
void toRGBf(const float h, const float s, const float v,
	    rgbf* rgb)
{
  /*
RGBType rgb;
	if(!h  && !s)
	{
		rgb.r = rgb.g = rgb.b = v;
	}
  */
  //rgbf* rgb = (rgbf*) out;
double min,max,delta,hue;

	max = v;
	delta = max * s;
	min = max - delta;

	hue = h;
	if(h > 300 || h <= 60)
	{
		rgb->r = max;
		if(h > 300)
		{
			rgb->g = min;
			hue = (hue - 360.0)/60.0;
			rgb->b = ((hue * delta - min) * -1);
		}
		else
		{
			rgb->b = min;
			hue = hue / 60.0;
			rgb->g = (hue * delta + min);
		}
	}
	else
	if(h > 60 && h < 180)
	{
		rgb->g = max;
		if(h < 120)
		{
			rgb->b = min;
			hue = (hue/60.0 - 2.0 ) * delta;
			rgb->r = min - hue;
		}
		else
		{
			rgb->r = min;
			hue = (hue/60 - 2.0) * delta;
			rgb->b = (min + hue);
		}
	}
	else
	{
		rgb->b = max;
		if(h < 240)
		{
			rgb->r = min;
			hue = (hue/60.0 - 4.0 ) * delta;
			rgb->g = (min - hue);
		}
		else
		{
			rgb->g = min;
			hue = (hue/60 - 4.0) * delta;
			rgb->r = (min + hue);
		}
	}
}

//Convert a wide range of data values into nice colours
void colour(const float data, float* out) {
  //convert data to angle
  const float a = atan2(data,1)/(2*atan2(1,1)); // -1 .. +1
  const float angle = (1+a)*180; //red=0 at -1,+1

  const float saturation = 1;

  const float h = (data<-1||data>1)? 1 : fabs(data);

  toRGBf(angle,saturation,h,(rgbf*)out);
}



int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1024,
                          768,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    bool hasRendered = false;

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            if(hasRendered == false)
            {
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                float* pixels = new float[1024*768*3];
                for(int i = 0; i < 768; ++i)
                {
                    for(int j = 0; j < 1024; ++j)
                    {
                        int pos = i * 1024 + j;
                        pixels[pos * 3] = (float)(j) / 1024.0f;
                        pixels[pos * 3 + 1] = (float) (i + j) / (1024.0f + 768.0f);
                        pixels[pos * 3 + 2] = (float) (j) / 768.0f;
                    }

                    float xpos = (0.0f) / 512.0f - 1.0f;
                    float ypos = (float)(i) / 384.0f - 1.0f;
                    glRasterPos2f(xpos, ypos);
                    glDrawPixels(1024, 1, GL_RGB, GL_FLOAT, &pixels[i*3]);
                    glFlush();
                }
                hasRendered = true;
            }
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL;// | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

