


#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
int rc=0,gc=125,bc=125;
int q ;
bool flag ;
struct Vector2
{
    double x,y;
    Vector2(double a=0,double b=0)
    {
        x=a;
        y=b;
    }
};

Vector2 points[7] {Vector2(0, 100),
                   Vector2(50, 80),
                   Vector2(100, 20),
                   Vector2(150, 80),
                   Vector2(200, 20),
                   Vector2(250, 80),
                   Vector2(300, 100)
};

int n=7;
int nump=7;
#include <tchar.h>
#include <windows.h>
#include <tchar.h>
#include <windows.h>
#include<cmath>
#include<iostream>
#include<bits/stdc++.h>
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")
///defines
#define DDALINE 1
#define MID_POINT 2
#define PARAMETRIC 3
#define DIRECT 4
#define POLAR 5
#define ITPOLAR 6
#define CIRCLE_MID_POINT 7
#define MODIFIED_MID_POINT 8
#define RED 9
#define BLACK 10
#define WHITE 11
#define MOUSEARROW 12
#define SAVE 13
#define LOAD 14
#define DRAW_SQUARE 15
#define FILL_HERMITE 16
#define FILL_BEZIER 17
#define DRAW_REC 18
#define CLEAR 19
#define POLAR_ELIPSE 20
#define MIDPOINT_ELIPSE 21
#define DIRECT_ELIPSE 22
#define FILLINGLINE 23
#define FILLINGCIRCLE 24
#define CARDINALSPLINE 25
#define RECUESIVEFLOODFILL 26
#define NONRECUESIVEFLOODFILL 27
#define MOUSEHAND 28
#define CLIPPINGLINESQ 29
#define CLIPPINGPOINTSQ 30
#define CLIPPINGLINERECT 31
#define CLIPPINGPOINTRECT 32
#define CLIPPINGPOLYGONRECT 33
#define CONVEX 34
#define NON_CONVEX 35
#define DRAW_INTERSECTION 36

///end defines
using namespace std;
HMENU hmenu;
void addmenus(HWND hwnd);
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
WNDCLASSEX wincl;
LPCSTR mouse=IDC_ARROW;
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL,mouse);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Code::Blocks Template Windows App"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            700,                 /* The programs width */
            500,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 1, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

typedef struct {
    int xleft, xright;
} table[1000];

void init_table(table t) {
    for (int i = 0; i < 1000; i++) {
        t[i].xleft = 10000;
        t[i].xright = -10000;
    }
}

struct point1 {
    int x, y;
    point1(int x = 0, int y = 0) :x(x), y(y) {}

};

void swap(point1& p1, point1& p2) {
    point1 temp = p1;
    p1 = p2;
    p2 = temp;
}

void edgetable5(point1 p1, point1 p2, table t, int& ymin1, int& ymax1) {
    if (p1.y > p2.y) {
        swap(p1, p2);
    }
    if (p1.y == p2.y) {
        // Handle horizontal edges separately
        if (p1.x < p2.x) {
            if (p1.y < ymin1) {
                ymin1 = p1.y;
            }
            if (p1.y > ymax1) {
                ymax1 = p1.y;
            }
            if (p1.x < t[p1.y].xleft) {
                t[p1.y].xleft = p1.x;
            }
            if (p1.x > t[p1.y].xright) {
                t[p1.y].xright = p1.x;
            }
        }
        else {
            if (p2.y < ymin1) {
                ymin1 = p2.y;
            }
            if (p2.y > ymax1) {
                ymax1 = p2.y;
            }
            if (p2.x < t[p2.y].xleft) {
                t[p2.y].xleft = p2.x;
            }
            if (p2.x > t[p2.y].xright) {
                t[p2.y].xright = p2.x;
            }
        }
        return;
    }
    double dx = (double)(p2.x - p1.x) / (p2.y - p1.y);
    double x = p1.x;
    for (int y = p1.y; y <= p2.y; y++) {
        if (y < ymin1) {
            ymin1 = y;
        }
        if (y > ymax1) {
            ymax1 = y;
        }
        if (x < t[y].xleft) {
            t[y].xleft = (int)x;
        }
        if (x > t[y].xright) {
            t[y].xright = (int)x;
        }
        x += dx;
    }
}

void scanline(HDC hdc, table t, int ymin1, int ymax1, COLORREF c) {
    for (int y = ymin1; y <= ymax1; y++) {
        if (t[y].xleft <= t[y].xright) {
            for (int x = t[y].xleft; x <= t[y].xright; x++) {
                SetPixel(hdc, x, y, c);
            }
        }
    }
}

void draw_convex_polygon(HDC hdc, point1* vertices, int n, COLORREF c) {
    table t;
    init_table(t);
    int ymin1 = 10000, ymax1 = -10000;
    for (int i = 0; i < n; i++) {
        edgetable5(vertices[i], vertices[(i + 1) % n], t, ymin1, ymax1);
    }
    scanline(hdc, t, ymin1, ymax1,c);
}
class Vector4
{
    double v[4];
public:
    Vector4(double a=0,double b=0,double c=0,double d=0)
    {
        v[0]=a;
        v[1]=b;
        v[2]=c;
        v[3]=d;
    }
    Vector4(double a[])
    {
        memcpy(v,a,4*sizeof(double));
    }
    double& operator[](int i)
    {
        return v[i];
    }
};

void InitEdgeTable(vector<vector<int>> &t)
{
    t.clear();
    t.resize(1000);
}

struct Point3
{
    int x,y;
    Point3 (int x=0 , int y=0):x(x),y(y){}
};

void Edge2Table (Point3 p1 , Point3 p2, vector<vector<int>> &t)
{
    if (p1.y == p2.y) return ;
    if (p1.y > p2.y )
        swap(p1,p2);
    double x = p1.x;
    int y = p1.y ;
    double m_inverse =(double)(p2.x - p1.x) / (p2.y-p1.y);
    while (y<p2.y)
    {
        t[y].push_back((int)ceil(x));
        y++;
        x+=m_inverse;
    }
}

void Polygon2Table(Point3 p[] , int n , vector<vector<int>> &t)
{
    Point3 v1 = p[n-1];
    for (int i = 0 ; i<n ; i++)
    {
        Point3 v2 = p[i];
        Edge2Table(v1,v2,t);
        v1=v2;
    }
}

void Table2Screen (HDC hdc ,vector<vector<int>> &t , COLORREF c)
{
    for (int i = 0 ; i<1000 ; i++)
    {
        if (!t[i].empty())
        {
            sort(t[i].begin(), t[i].end());
            int j = 0;
            while(j<t[i].size()-1)
            {
                for(int x=t[i][j] ; x<=t[i][j+1] ; x++)
                    SetPixel(hdc,x,i,c);
                j += 2;
            }
        }
    }
}

void Fill (HDC hdc , Point3 p[] , int n , COLORREF c)
{
    vector<vector<int>> t;
    InitEdgeTable(t);
    Polygon2Table(p,n,t);
    Table2Screen(hdc,t,c);
}


class Matrix4
{
    Vector4 M[4];
public:
    Matrix4(double A[])
    {
        memcpy(M,A,16*sizeof(double));
    }
    Vector4& operator[](int i)
    {
        return M[i];
    }
};
Vector4 operator*(Matrix4 M,Vector4& b) // right multiplication of M by b
{
    Vector4 res;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            res[i]+=M[i][j]*b[j];

    return res;
}
double DotProduct(Vector4& a,Vector4& b) //multiplying a raw vector by a column vector
{
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3];
}
Vector4 GetHermiteCoeff(double x0,double s0,double x1,double s1)
{
    static double H[16]= {2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0};
    static Matrix4 basis(H);
    Vector4 v(x0,s0,x1,s1);
    return basis*v;
}
void DrawHermiteCurve (HDC hdc,Vector2& P0,Vector2& T0,Vector2& P1,Vector2& T1,int numpoints)
{
    Vector4 xcoeff=GetHermiteCoeff(P0.x,T0.x,P1.x,T1.x);
    Vector4 ycoeff=GetHermiteCoeff(P0.y,T0.y,P1.y,T1.y);
    if(numpoints<2)return;
    double dt=1.0/(numpoints-1);
    for(double t=0; t<=1; t+=dt)
    {
        Vector4 vt;
        vt[3]=1;
        for(int i=2; i>=0; i--)vt[i]=vt[i+1]*t;
        int x=round(DotProduct(xcoeff,vt));
        int y=round(DotProduct(ycoeff,vt));
        if(t==0)MoveToEx(hdc,x,y,NULL);
        else LineTo(hdc,x,y);
    }
}
void DrawCardinalSpline(HDC hdc,Vector2 p[],int n,double c,int nump)
{
    double ct=1-c;
    Vector2 T0(ct*(p[1].x-p[0].x),ct*(p[1].y-p[0].y));
    for(int i=2; i<n-1; i++)
    {
        Vector2 T1(ct*(p[i+1].x-p[i-1].x),ct*(p[i+1].y-p[i-1].y));
        DrawHermiteCurve(hdc,p[i-1],T0,p[i],T1,nump);
        T0=T1;
    }
}
void vline(HDC hdc,int xc,int yc,COLORREF c)
{
    int y=yc+100;
    while(yc<y)
    {
        yc++;
        SetPixel(hdc,xc,yc,RGB(rc,gc,bc));
    }

}
void hline(HDC hdc,int xc,int yc,COLORREF c)
{
    int x=xc+100;
    while(xc<x)
    {
        xc++;
        SetPixel(hdc,xc,yc,RGB(rc,gc,bc));
    }
}
void rec_hline(HDC hdc,int xc,int yc,COLORREF c)
{
    int x=xc+200;
    while(xc<x)
    {
        xc++;
        SetPixel(hdc,xc,yc,RGB(rc,gc,bc));
    }
}
void drawsquare(HDC hdc,int xc,int yc,COLORREF c)
{
    int x=xc+100;
    int x1=xc;
    int y1=yc;
    int y=yc+100;

    while(x1<=x)
    {
        if (x1=xc)
        {
//            if(y1==y)
            hline(hdc,x1,y,c);
            vline(hdc,x1,y1,c);
        }
        if(x1<x)
        {
            // cout<<"XC"<<x1<<"X"<<x;

            hline(hdc,x1,y1,c);
            x1++;

        }

        if(x1=x)
        {
            vline(hdc,x1,y1,c);
            break;

        }

    }
}
void drawrectangle(HDC hdc,int xc,int yc,COLORREF c)
{
    int x=xc+200;
    int x1=xc;
    int y1=yc;
    int y=yc+100;

    while(x1<=x)
    {
        if (x1=xc)
        {
//            if(y1==y)
            rec_hline(hdc,x1,y,c);
            vline(hdc,x1,y1,c);
        }
        if(x1<x)
        {
            // cout<<"XC"<<x1<<"X"<<x;

            rec_hline(hdc,x1,y1,c);
            x1++;

        }

        if(x1=x)
        {
            vline(hdc,x1,y1,c);
            break;

        }

    }
}
void filling_hermite(HDC hdc,int xc,int yc,int
numpoints,COLORREF c)
{
    int x=xc+100;
    int x1=xc;
    int y1=yc;
    int y=yc+100;
    Vector2 P0(x1, y1), T0(1, 10), P1(x1, y1+100), T1(10, 20);
    while(x1<=x)
    {
        Vector2 P0(x1,y1);
        Vector2 P1(x1,y1+100);
        DrawHermiteCurve(hdc, P0, T0, P1, T1, numpoints);
        x1+=5;


    }

}
void DrawBezierCurve(HDC hdc,Vector2& P0,Vector2& P1,Vector2& P2,Vector2& P3,int numpoints)
{
    Vector2 T0(3*(P1.x-P0.x),3*(P1.y-P0.y));
    Vector2 T1(3*(P3.x-P2.x),3*(P3.y-P2.y));
    DrawHermiteCurve(hdc,P0,T0,P3,T1,numpoints);
}
void fillBezier(HDC hdc,int xc,int yc,int wid,int len,COLORREF c)
{
    int x1=xc;
    int y1=yc;
    int y=yc+wid;
    while(y1<=y-5)
    {
        Vector2 P0(x1, y1), P1(x1+len, y1), P2(x1, y1+5), P3(x1+len, y1+5);
        DrawBezierCurve(hdc,P0,P1,P2,P3,1000);
        y1+=5;

    }

}
void drawelipse(HDC hdc, int xc, int yc, int a, int b)
{
    double dtheta = 1.0 / max(a,b);
    COLORREF color = RGB(0, 0, 0);
    for (double theta = 0; theta < 6.28; theta += dtheta)
    {
        double x = xc + a * cos(theta);
        double y = yc + b * sin(theta);
        SetPixel(hdc, round(x), round(y), color);
    }

//   drawpoint(hdc, xc, yc, 0, r);

}
void draw4points(HDC hdc,int xc, int yc, int x, int y)
{

    COLORREF c = RGB(0, 0, 0);
    SetPixel(hdc, xc + x, yc + y,RGB(rc,gc,bc));
    SetPixel(hdc, xc + x, yc - y,RGB(rc,gc,bc));
    SetPixel(hdc, xc - x, yc - y, RGB(rc,gc,bc));
    SetPixel(hdc, xc -x, yc + y, RGB(rc,gc,bc));

}
void drawelipse_polar(HDC hdc, int xc, int yc, int a, int b)
{
    double dtheta = 1.0 / max(a, b);
    int x = a;
    int y = 0;
    COLORREF color = RGB(0, 0, 0);
    draw4points(hdc,xc, yc, x, y);
    for (double theta = 0; theta < 1.57; theta += dtheta)
    {
        double x =  b * cos(theta);
        double y =  a * sin(theta);
        draw4points(hdc,xc, yc, round(x), round(y));
    }

    //   drawpoint(hdc, xc, yc, 0, r);

}
void drawellipse_midpoint(HDC hdc, int xc, int yc, int a, int b)
{
    int x = 0;
    int y = b;
    int d1 = b * b - a * a * b + a * a / 4;
    draw4points(hdc, xc, yc, x, y);

    while (a * a * (y - 0.5) > b * b * (x + 1))
    {
        if (d1 < 0)
        {
            d1 += b * b * (2 * x + 3);
        }
        else
        {
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y--;
        }
        x++;
        draw4points(hdc, xc, yc, x, y);
    }

    int d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y > 0)
    {
        if (d2 < 0)
        {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        }
        else
        {
            d2 += a * a * (-2 * y + 3);
        }
        y--;
        draw4points(hdc, xc, yc, x, y);
    }
}

void drawellipse_direct(HDC hdc, int xc, int yc, int a, int b)
{
    int x = 0;
    int y = b;
    double d = (double)b * b - (double)a * a * b + 0.25 * (double)a * a;
    int dx = 2 * b * b * x;
    int dy = 2 * a * a * y;
    draw4points(hdc, xc, yc, x, y);

    while (dx < dy)
    {
        if (d < 0)
        {
            x++;
            dx += 2 * b * b;
            d += dx + b * b;
        }
        else
        {
            x++;
            y--;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d += dx - dy + b * b;
        }
        draw4points(hdc, xc, yc, x, y);
    }

    d = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y >= 0)
    {
        if (d < 0)
        {
            x++;
            y--;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d += dx - dy + a * a;
        }
        else
        {
            y--;
            dy -= 2 * a * a;
            d += -dy + a * a;
        }
        draw4points(hdc, xc, yc, x, y);
    }
}

int Round(double x)
{
    return int(x+0.5);

}

void Draw8Points(HDC hdc,int xc,int yc, int a,int b)
{

    SetPixel(hdc,xc+a,yc+b,RGB(rc,gc,bc));
    SetPixel(hdc,xc-a,yc+b,RGB(rc,gc,bc));
    SetPixel(hdc,xc-a,yc-b,RGB(rc,gc,bc));
    SetPixel(hdc,xc+a,yc-b,RGB(rc,gc,bc));
    SetPixel(hdc,xc+b,yc+a,RGB(rc,gc,bc));
    SetPixel(hdc,xc-b,yc+a,RGB(rc,gc,bc));
    SetPixel(hdc,xc-b,yc-a,RGB(rc,gc,bc));
    SetPixel(hdc,xc+b,yc-a,RGB(rc,gc,bc));


}
void CircleDirect(HDC hdc,int xc,int yc,int r)
{
    int x = 0;
    int y = r;
    int r2 = r*r;
    Draw8Points(hdc,xc,yc,x,y);
    while(x < y)
    {
        x++;
        double tmp = sqrt(r2-x*x);
        y = Round(tmp);
        Draw8Points(hdc,xc,yc,x,y);
    }


}
void CirclePolar(HDC hdc,int xc,int yc,int r)
{
    int x = r;
    int y = 0;
    double theta =0, dtheta = 1.0/r;
    Draw8Points(hdc,xc,yc,x,y);
    while(x > y)
    {
        theta += dtheta;
        x = Round(r*cos(theta));
        y = Round(r*sin(theta));
        Draw8Points(hdc,xc,yc,x,y);
    }


}

void CircleIterativePolar(HDC hdc,int xc,int yc,int r)
{
    double x = r,y = 0;
    double dtheta = 1.0/r;
    double Cdtheta = cos(dtheta);
    double Sdtheta = sin(dtheta);
    Draw8Points(hdc,xc,yc,x,y);
    while(x > y)
    {
        double x1 = x*Cdtheta - y*Sdtheta;
        double y1 = x*Sdtheta + y*Cdtheta;
        y = y1;
        x = x1;
        Draw8Points(hdc,xc,yc,Round(x),Round(y));
    }


}
void CircleMidPoint(HDC hdc,int xc,int yc,int r)
{
    int x = 0;
    int y = r;
    int d = 1-r;

    Draw8Points(hdc,xc,yc,x,y);
    while(x < y)
    {
        double ch1 = 2*x+2;
        double ch2 = 2*(x-y)+5;
        if(d < 0)
        {
            d+=ch1;
        }
        else
        {
            d+=ch2;
            y--;
        }
        x++;
        Draw8Points(hdc,xc,yc,x,y);
    }


}
void CircleModfiyMidPoint(HDC hdc,int xc,int yc,int r)
{
    int x = 0;
    int y = r;
    int d = 1-r;
    int ch1 = 3, ch2 = 5-2*r;

    Draw8Points(hdc,xc,yc,x,y);
    while(x < y)
    {
        if(d < 0)
        {
            d+=ch1;
            ch2 += 2;
        }
        else
        {
            d+=ch2;
            ch2+=4;
            y--;
        }
        ch1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y);
    }


}
void drawpoint(HDC hdc, int x, int y)
{

    COLORREF color = RGB(1, 1, 1);
    SetPixel(hdc, x, y, color);
}
void drawline_dda(HDC hdc, int x1, int y1, int x2, int y2)
{

    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));
    float xinc = dx / steps;
    float yinc = dy / steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        // plot pixel at (x,y) with red color
        SetPixel(hdc, round(x), round(y), RGB(rc, gc, bc));

        // increment x and y
        x += xinc;
        y += yinc;
    }
}

void drawline_p(HDC hdc, int x1, int y1, int x2, int y2)
{

    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = sqrt(dx * dx + dy * dy);

    float x = x1;
    float y = y1;

    for (float t = 0; t <= 1; t += 0.0001)
    {
        // calculate pixel position using parametric equation
        x = x1 + t * dx;
        y = y1 + t * dy;

        // plot pixel at (x,y) with black color
        SetPixel(hdc, round(x), round(y), RGB(rc, gc, bc));
    }
}
void drawline_m(HDC hdc, int x1, int y1, int x2, int y2)
{

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;

    int err = dx - dy;

    while (x1 != x2 || y1 != y2)
    {
        // plot pixel at (x1,y1) with black color
        SetPixel(hdc, x1, y1, RGB(100, 30, 30));

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
void MidPointLine(HDC hdc,int xs,int ys,int xe,int ye)
{
    int dx = xe-xs;
    int dy = ye-ys;
    if(abs(dx) > abs(dy))
    {
        double x = xs;
        double y = ys;
        double d = dx-2*dy;
        double ch1 = 2*(dx-dy);
        double ch2 = -2*dy;
        while(x < xe)
        {
            if(d > 0)
            {
                d+=ch1;
                y+=1;
            }
            else
            {
                d+=ch2;

            }
            x+=1;
            SetPixel(hdc,round(x),round(y),RGB(255,0,0));
        }
    }
    else
    {
        double x = xs;
        double y = ys;
        double d = 2*dx-dy;
        double ch1 = 2*(dx-dy);
        double ch2 = 2*dx;
        while(y < ye)
        {
            if(d < 0)
            {
                d+=ch1;
                x+=1;
            }
            else
            {
                d+=ch2;

            }
            y+=1;
            SetPixel(hdc,round(x),round(y),RGB(255,0,0));
        }
    }



}
// simple DDA function for drawing line
void drawLine(HDC hdc,int xs,int ys,int xe,int ye)
{
    int dx=xe-xs;
    int dy=ye-ys;
    SetPixel(hdc,xs,ys,RGB(rc,gc,bc));
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc= dx>0?1:-1;
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,x,round(y),RGB(rc,gc,bc));
        }
    }
    else
    {
        int y=ys,yinc= dy>0?1:-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,round(x),y,RGB(rc,gc,bc));
        }
    }
}
void draw2points(HDC hdc, int xc, int yc, int x, int y )
{
    if(q ==4)
    {
        SetPixel(hdc, xc+x, yc+y, RGB(rc,gc,bc));
        SetPixel(hdc, xc+y, yc+x, RGB(rc,gc,bc));
    }
    else if (q ==3)
    {
        SetPixel(hdc, xc-x, yc+y, RGB(rc,gc,bc));
        SetPixel(hdc, xc-y, yc+x, RGB(rc,gc,bc));
    }
    else if (q ==2)
    {
        SetPixel(hdc, xc-x, yc-y, RGB(rc,gc,bc));
        SetPixel(hdc, xc-y, yc-x, RGB(rc,gc,bc));
    }
    else
    {
        SetPixel(hdc, xc+x, yc-y, RGB(rc,gc,bc));
        SetPixel(hdc, xc+y, yc-x, RGB(rc,gc,bc));
    }
}
void drawQuarter(HDC hdc, int xc, int yc, int r )
{
    int x = 0, y = r ;
    int d = 1-r ;
    int c1=3, c2 =5-2*r ;
    draw2points(hdc,  xc,  yc,  x, y ) ;
    while(x<y)
    {
        if(d<0)
        {
            d+= c1 ;
            c2+= 2 ;
        }
        else
        {
            d+= c2 ;
            c2+= 4 ;
            y-- ;
        }
        x++, c1+= 2 ;
        draw2points(hdc,  xc,  yc,  x, y ) ;
    }
}
void fun(HDC hdc, int xc, int yc, int r )
{
    if(flag)
    {
        int x = 0, y = r ;
        int d = 1-r ;
        int c1=3, c2 =5-2*r ;
        while(x<y)
        {
            if(d<0)
            {
                d+= c1 ;
                c2+= 2 ;
            }
            else
            {
                d+= c2 ;
                c2+= 4 ;
                y-- ;
            }
            x++, c1+= 2 ;
            switch(q)
            {
                case 4 :
                    drawLine(hdc, xc, yc,xc+x, yc+y );
                    drawLine(hdc, xc, yc,xc+y, yc+x );
                    break ;
                case 3 :
                    drawLine(hdc, xc, yc,xc-x, yc+y );
                    drawLine(hdc, xc, yc,xc-y, yc+x );
                    break ;
                case 2 :
                    drawLine(hdc, xc, yc,xc-x, yc-y );
                    drawLine(hdc, xc, yc,xc-y, yc-x );
                    break ;
                case 1 :
                    drawLine(hdc, xc, yc,xc+x, yc-y );
                    drawLine(hdc, xc, yc,xc+y, yc-x );
                    break ;
            }
        }

    }
    else
    {
        int i ;
        for (i=1 ; i<=r ; i++)
        {
            drawQuarter(hdc, xc, yc, i);
        }
    }
}
void SaveScreenShapes(const char* filename)
{
    // Get the dimensions of the screen
    int screenX = GetSystemMetrics(SM_CXSCREEN);
    int screenY = GetSystemMetrics(SM_CYSCREEN);

    // Create a device context for the screen
    HDC hScreenDC = GetDC(NULL);

    // Create a device context for a bitmap to hold the captured image
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenX, screenY);
    SelectObject(hMemoryDC, hBitmap);

    // Copy the contents of the screen to the bitmap
    BitBlt(hMemoryDC, 0, 0, screenX, screenY, hScreenDC, 0, 0, SRCCOPY);

    // Save the bitmap to a file
    ofstream outFile(filename, ios::binary);
    BITMAPFILEHEADER fileHeader = { 0 };
    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + screenX * screenY * 4;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    outFile.write((const char*)&fileHeader, sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER infoHeader = { 0 };
    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = screenX;
    infoHeader.biHeight = screenY;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 32;
    infoHeader.biCompression = BI_RGB;
    infoHeader.biSizeImage = screenX * screenY * 4;
    outFile.write((const char*)&infoHeader, sizeof(BITMAPINFOHEADER));
    char* data = new char[screenX * screenY * 4];
    GetBitmapBits(hBitmap, screenX * screenY * 4, data);
    outFile.write(data, screenX * screenY * 4);
    delete[] data;
    outFile.close();

    // Clean up
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
}
void LoadDataFromFile(const char* filename)
{
    ifstream inFile(filename, ios::binary);
    if (!inFile)
    {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    // Read data from the file
    char* data = nullptr;
    int size = 0;
    inFile.seekg(0, ios::end);
    size = (int)inFile.tellg();
    inFile.seekg(0, ios::beg);
    data = new char[size];
    inFile.read(data, size);

    // Process the data
    // ...

    // Clean up
    delete[] data;
    inFile.close();
}

void RFloodFill(HDC hdc,int x,int y,int fillcolor,int bordercolor)
{
    COLORREF c = GetPixel(hdc,x,y);
    if(c ==bordercolor || c ==fillcolor)return;

    SetPixel(hdc,x,y,fillcolor);
    RFloodFill(hdc,x+1,y,fillcolor,bordercolor);
    RFloodFill(hdc,x-1,y,fillcolor,bordercolor);
    RFloodFill(hdc,x,y+1,fillcolor,bordercolor);
    RFloodFill(hdc,x,y-1,fillcolor,bordercolor);

}

struct point
{
public:
    int x,y;
    point(int x=0,int y=0):x(x),y(y) {}
};
// A function to perform flood fill non recursively using stack based
void NRFloodFill(HDC hdc,int x,int y,COLORREF fillcolor,COLORREF bordercolor)
{
    stack<point>s;
    s.push(point(x,y));
    while(!s.empty())
    {
        point p=s.top(); //first point
        s.pop();
        COLORREF c = GetPixel(hdc,p.x,p.y);
        if ((c == bordercolor) || (c == fillcolor))continue;
        SetPixel(hdc,p.x,p.y,fillcolor);
        s.push(point(p.x+1,p.y) );
        s.push(point(p.x-1,p.y) );
        s.push(point(p.x,p.y+1));
        s.push(point(p.x,p.y-1));

    }



}

bool HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24)
{
    uint32_t Width = Area.right - Area.left;
    uint32_t Height = Area.bottom - Area.top;

    BITMAPINFO Info;
    BITMAPFILEHEADER Header;
    memset(&Info, 0, sizeof(Info));
    memset(&Header, 0, sizeof(Header)); // bnsfrhom

    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //set el size
    Info.bmiHeader.biWidth = Width; // set el width
    Info.bmiHeader.biHeight = Height; //set el height
    Info.bmiHeader.biPlanes = 1; //1 for non-multilayered images.
    Info.bmiHeader.biBitCount = BitsPerPixel; //number of bits per pixel in the image.
    Info.bmiHeader.biCompression = BI_RGB; //uncompressed
    Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3); //24=>> 8+8+8 , r+g+b
    Header.bfType = 0x4D42; //0x4D42 represents the ASCII characters 'BM'
    Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    char* Pixels = NULL;
    HDC MemDC = CreateCompatibleDC(Context);
    HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
    DeleteObject(SelectObject(MemDC, Section));
    BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
    DeleteDC(MemDC);
    std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
    if (hFile.is_open())
    {
        hFile.write((char*)&Header, sizeof(Header));
        hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
        hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
        hFile.close();
        DeleteObject(Section);
        return true; //saved
    }
    DeleteObject(Section);
    return false; //failed
}
void load(HWND hWnd, HDC &hdc)
{
    string fileName = "picture.bmp";
    if (fileName == "")
        return ;
    HBITMAP hBitmap; // handle to the actual bitmap image
    hBitmap = (HBITMAP)::LoadImage(NULL, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC hLocalDC;
    hLocalDC = CreateCompatibleDC(hdc);
    BITMAP qBitmap; // save retrieved data && holds information about the bitmap
    int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),reinterpret_cast<LPVOID>(&qBitmap)); // retrieve el data w nsavhaa fl qbitmap
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
    BOOL qRetBlit = BitBlt(hdc, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight,hLocalDC, 0, 0, SRCCOPY);
    SelectObject (hLocalDC, hOldBmp);
    DeleteDC(hLocalDC);
    DeleteObject(hBitmap);
}
void save(HWND &hWnd)
{
    HDC hdc = GetDC(hWnd);
    string fileName = "picture.bmp";
    if (fileName == "")
        return ;
    int windowWidth ;
    int windowHeight;
    RECT rect; //The Rect class holds the four borders of a rectangle:
    // left, top, right, and bottom.
    if(GetWindowRect(hWnd, &rect))
    {
        windowWidth = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;
    }
    RECT rect1 = {0, 0, windowWidth, windowHeight};
    HDCToFile(fileName.c_str(),hdc,rect1);
}
///clipping
void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}
class OutCode
{
public:
    int top,bottom,right,left,all;
    OutCode()
    {
        top=0;
        bottom=0;
        right= 0;
        left = 0;
        all=0;
    }
    void calc(int x)
    {
        all+=x;
    }
    void sub(int x)
    {
        all -=x;
    }
};

OutCode getout(double xs,double ys,int ytop,int ybottom,int xleft,int xright)
{
    OutCode out;
    if(xs < xleft)
    {
        out.left =1;
        out.calc(1);

    }
    if(xs > xright)
    {
        out.right =1;
        out.calc(1);
    }
    if (ys > ytop)
    {
        out.top = 1;
        out.calc(1);

    }
    if (ys < ybottom)
    {
        out.bottom = 1;
        out.calc(1);
    }
    return out;
}
void getintersectionX(double x1,double y1,double x2,double y2,int y, double *ynew,double *xnew)
{
    *ynew = y;
    double islope =(x2-x1)/(y2-y1);
    *xnew = x1+(y-y1)*islope;


}
void getintersectionY(double x1,double y1,double x2,double y2,int x, double *ynew,double *xnew)
{
    *xnew = x;
    double slope = (y2-y1)/(x2-x1);
    *ynew = y1+(x-x1)*slope;
}
void Clipping_Line(HDC hdc,int Xstart,int Xend,int Ystart,int Yend,int ytop,int ybottom,int xleft,int xright)
{
    double x1 = Xstart, x2 = Xend,y1 = Ystart,y2 = Yend;
    OutCode out1 = getout(x1,y1,ytop,ybottom,xleft,xright);
    OutCode out2 = getout(x2,y2,ytop,ybottom,xleft,xright);

    // cout<<out1.top<<" "<<out1.bottom<<" "<<out1.left<<" "<<out1.right<<endl;
    //cout<<out2.top<<" "<<out2.bottom<<" "<<out2.left<<" "<<out2.right<<endl;
    double xnew,ynew;
    double xnew2,ynew2;
    while (out1.all > 0)
    {
        if (out1.top == 1)
        {
            getintersectionX(x1,y1,x2,y2,ytop,&ynew,&xnew);
            out1.sub(1);
            xnew = Round(xnew);
        }
        else if (out1.bottom == 1)
        {
            getintersectionX(x1,y1,x2,y2,ybottom,&ynew,&xnew);
            out1.sub(1);
            xnew = Round(xnew);
        }
        else if (out1.right == 1)
        {
            getintersectionY(x1,y1,x2,y2,xright,&ynew,&xnew);
            out1.sub(1);
            ynew = Round(ynew);

        }
        else if (out1.left == 1)
        {
            getintersectionY(x1,y1,x2,y2,xleft,&ynew,&xnew);
            out1.sub(1);
            ynew = Round(ynew);
        }
        else
        {
            out1.sub(1);
        }
        out1 = getout(xnew,ynew,ytop,ybottom,xleft,xright);
    }
    x1 = xnew,y1=ynew;
    while (out2.all > 0)
    {
        if (out2.top == 1)
        {
            getintersectionX(x1,y1,x2,y2,ytop,&ynew2,&xnew2);
            out2.sub(1);
            xnew2 = Round(xnew2);
        }
        else if (out2.bottom == 1)
        {
            getintersectionX(x1,y1,x2,y2,ybottom,&ynew2,&xnew2);
            out2.sub(1);
            xnew2 = Round(xnew2);
        }
        else if (out2.right == 1)
        {
            getintersectionY(x1,y1,x2,y2,xright,&ynew2,&xnew2);
            out2.sub(1);
            ynew2 = Round(ynew2);

        }
        else if (out2.left == 1)
        {
            getintersectionY(x1,y1,x2,y2,xleft,&ynew2,&xnew2);
            out2.sub(1);
            ynew2 = Round(ynew2);
        }
        else
        {
            out2.sub(1);
        }
        out2 = getout(xnew2,ynew2,ytop,ybottom,xleft,xright);
    }
    x2 = xnew2, y2 = ynew2;
    /*cout<<x1<<"   "<<y1<<endl;
    cout<<x2<<"   "<<y2<<endl;*/
    drawLine(hdc, x1, y1, x2, y2);
}
void Clipping_Point(HDC hdc,int x,int y,int top,int bottom,int left,int right)
{
    if(y <= top && y >= bottom && x >= left && x <= right)
        SetPixel(hdc,x,y,RGB(0,120,120));
}
struct Vector
{
    double v[2];
    Vector(double x = 0, double y = 0)
    {
        v[0] = x;
        v[1] = y;
    }
    double& operator[](int i)
    {
        return v[i];
    }
};
struct Vertex
{
    double x, y;
    Vertex(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
};
typedef vector<Vertex> VertexList;
typedef bool (*IsInFunc)(Vertex& v, int edge);
typedef Vertex(*IntersectFunc)(Vertex& v1, Vertex& v2, int edge);
VertexList ClipWithEdge(VertexList p, int edge, IsInFunc In, IntersectFunc Intersect)
{
    VertexList OutList;
    Vertex v1 = p[p.size() - 1];
    bool v1_in = In(v1, edge);
    for (int i = 0; i < (int)p.size(); i++)
    {
        Vertex v2 = p[i];
        bool v2_in = In(v2, edge);
        if (!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1, v2, edge));
            OutList.push_back(v2);
        }
        else if (v1_in && v2_in) OutList.push_back(v2);
        else if (v1_in) OutList.push_back(Intersect(v1, v2, edge));
        v1 = v2;
        v1_in = v2_in;
    }
    return OutList;
}
bool InLeft(Vertex& v, int edge)
{
    return v.x >= edge;
}
bool InRight(Vertex& v, int edge)
{
    return v.x <= edge;
}
bool InTop(Vertex& v, int edge)
{
    return v.y >= edge;
}
bool InBottom(Vertex& v, int edge)
{
    return v.y <= edge;
}
Vertex VIntersect(Vertex& v1, Vertex& v2, int xedge)
{
    Vertex res;
    res.x = xedge;
    res.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return res;
}
Vertex HIntersect(Vertex& v1, Vertex& v2, int yedge)
{
    Vertex res;
    res.y = yedge;
    res.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return res;
}



void PolygonClip(HDC hdc, Vector p[], int n, int xleft, int ytop, int xright, int ybottom)
{
    VertexList vlist;
    for (int i = 0; i < n; i++)vlist.push_back(Vertex(p[i][0], p[i][1]));
    vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);
    Vertex v1 = vlist[vlist.size() - 1];
    for (int i = 0; i < (int)vlist.size(); i++)
    {
        Vertex v2 = vlist[i];
        drawline_dda(hdc, v1.x, v1.y, v2.x, v2.y);
        v1 = v2;
    }
}
void addmenus(HWND hwnd)
{
    hmenu=CreateMenu();
    HMENU hlinemenu=CreateMenu();
    AppendMenu(hlinemenu,MF_STRING,DDALINE,"DDA");
    AppendMenu(hlinemenu,MF_STRING,MID_POINT,"Midpoint");
    AppendMenu(hlinemenu,MF_STRING,PARAMETRIC,"parametric");
    HMENU hcirclemenu=CreateMenu();
    AppendMenu(hcirclemenu,MF_STRING,DIRECT,"Direct");
    AppendMenu(hcirclemenu,MF_STRING,POLAR,"polar");
    AppendMenu(hcirclemenu,MF_STRING,ITPOLAR,"iterativepolar");
    AppendMenu(hcirclemenu,MF_STRING,CIRCLE_MID_POINT,"Midpoint");
    AppendMenu(hcirclemenu,MF_STRING,MODIFIED_MID_POINT,"modifiedMidpoint");
    AppendMenu(hcirclemenu,MF_STRING,DRAW_INTERSECTION,"two circles with filling intersection");
    HMENU Gmenu=CreateMenu();
    HMENU Cmenu=CreateMenu();
    AppendMenu(Cmenu,MF_STRING,RED,"RED");
    AppendMenu(Cmenu,MF_STRING,BLACK,"BLACK");
    HMENU Mmenu = CreateMenu();
    AppendMenu(Mmenu,MF_STRING,MOUSEARROW,"Arrow");
    AppendMenu(Mmenu,MF_STRING,MOUSEHAND,"Hand");
    HMENU helipsemenu=CreateMenu();
    AppendMenu(helipsemenu,MF_STRING,DIRECT_ELIPSE,"Direct");
    AppendMenu(helipsemenu,MF_STRING,POLAR_ELIPSE,"polar");
    AppendMenu(helipsemenu,MF_STRING,MIDPOINT_ELIPSE,"Midpoint");
    HMENU hconvexmenu=CreateMenu();
    AppendMenu(hconvexmenu,MF_STRING,CONVEX,"Convex");
    AppendMenu(hconvexmenu,MF_STRING,NON_CONVEX,"NON Convex");


    AppendMenu(Gmenu,MF_STRING,WHITE,"Change the background of window to be white");
    AppendMenu(Gmenu,MF_STRING,CLEAR,"Clear window");
    AppendMenu(Gmenu,MF_POPUP,(UINT_PTR)Mmenu,"Change Mouse");
    AppendMenu(Gmenu,MF_POPUP,(UINT_PTR)Cmenu,"Change COLOR");
    AppendMenu(Gmenu,MF_STRING,SAVE,"SAVE");
    AppendMenu(Gmenu,MF_STRING,LOAD,"LOAD");
    HMENU hsquaremenu=CreateMenu();
    AppendMenu(hsquaremenu,MF_STRING,DRAW_SQUARE,"Draw");
    AppendMenu(hsquaremenu,MF_STRING,FILL_HERMITE,"FILL_Hermite");
    HMENU hrecmenu=CreateMenu();
    AppendMenu(hrecmenu,MF_STRING,DRAW_REC,"Draw");
    AppendMenu(hrecmenu,MF_STRING,FILL_BEZIER,"FILL_Bezier");
    HMENU quartermenu=CreateMenu();

    AppendMenu(quartermenu,MF_STRING,FILLINGLINE,"Filling with line");
    AppendMenu(quartermenu,MF_STRING,FILLINGCIRCLE,"Filling with circle");

    HMENU cardinlmenu=CreateMenu();
    AppendMenu(cardinlmenu,MF_STRING,CARDINALSPLINE,"Cardinal Spline Curve");

    HMENU floodfillmenu=CreateMenu();
    AppendMenu(floodfillmenu,MF_STRING,RECUESIVEFLOODFILL,"Recursive FloodFill");
    AppendMenu(floodfillmenu,MF_STRING,NONRECUESIVEFLOODFILL,"Non Recursive FloodFill");
    //clipping menu
    HMENU clippingmenu=CreateMenu();
    HMENU squaremenu=CreateMenu();
    HMENU rectgmenu=CreateMenu();
    //FOR MAIN MENU
    AppendMenu(clippingmenu,MF_POPUP,(UINT_PTR)squaremenu,"Clipping Square");
    AppendMenu(clippingmenu,MF_POPUP,(UINT_PTR)rectgmenu,"Clipping Rectangle");
    //FOR SQUARE
    AppendMenu(squaremenu,MF_STRING,CLIPPINGLINESQ,"Line");
    AppendMenu(squaremenu,MF_STRING,CLIPPINGPOINTSQ,"Point");
    //for rectangle
    AppendMenu(rectgmenu,MF_STRING,CLIPPINGLINERECT,"Line");
    AppendMenu(rectgmenu,MF_STRING,CLIPPINGPOINTRECT,"Point");
    AppendMenu(rectgmenu,MF_STRING,CLIPPINGPOLYGONRECT,"Polygon");



    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)Gmenu,"General");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hlinemenu,"LINE");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hsquaremenu,"Square");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hrecmenu,"Rectangle");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hcirclemenu,"Circle");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)helipsemenu,"Elipse");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)quartermenu,"QuarterCircle");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)cardinlmenu,"Spline Curve");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)floodfillmenu,"FloodFill");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)clippingmenu,"Clipping");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hconvexmenu,"POLYGON");




    SetMenu(hwnd,hmenu);

}
void drawRectangle(HDC hdc, Vector& p1, double sideLen, double sidewidth, COLORREF c)
{
    double left = p1[0];
    double right = p1[0] + sideLen;
    double top = p1[1];
    double bottom = p1[1] + sidewidth;

    drawline_m(hdc,left,top,right,top);
    drawline_m(hdc,left,top,left,bottom);
    drawline_m(hdc,right,top,right,bottom);
    drawline_m(hdc,left,bottom,right,bottom);
}
double GetDistanceBetween2Points(int x1,int x2,int y1,int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

}
void drawcircler(HDC hdc, int xc, int yc, int xc2, int yc2) {
    int r = sqrt(pow(xc2 - xc, 2) + pow(yc2 - yc, 2));
    double dtheta = 1.0 / r;
    COLORREF color = RGB(0, 0, 0);
    double ans = xc + r * sin(dtheta);
    int ans1 = yc + r * cos(dtheta);
    for (double theta = 0;theta < 6.28;theta += dtheta) {
        double x = xc + r * cos(theta);
        double y = yc + r * sin(theta);
        SetPixel(hdc, round(x), round(y), color);
    }
    // drawline(hdc, xc - r * cos(40), yc + r * sin(40), xc + r * cos(40), yc - r * sin(40));
    //drawline(hdc, xc - r * cos(40), yc - r * sin(40), xc + r * cos(40), yc + r * sin(40));
    //drawpoint(hdc, xc, yc, 0, r);

}
void FillCircleIntersection(HDC hdc, double x1, double y1, double x11, double y11, double x2, double y2, double x22, double y22) {
    // Calculate distance between the centers of the two circles
    double dx = x2 - x1;
    double dy = y2 - y1;
    double distance = sqrt(dx * dx + dy * dy);
    double r1 = sqrt(pow(x1 - x11, 2) + pow(y1 - y11, 2));
    double r2 = sqrt(pow(x2 - x22, 2) + pow(y2 - y22, 2));

    // Create regions for the two circles
    HRGN region1 = CreateEllipticRgn(Round(x1 - r1), Round(y1 - r1), Round(x1 + r1), Round(y1 + r1));
    HRGN region2 = CreateEllipticRgn(Round(x2 - r2), Round(y2 - r2), Round(x2 + r2), Round(y2 + r2));

    // Create region for intersection
    HRGN region = CreateRectRgn(0, 0, 0, 0);
    CombineRgn(region, region1, region2, RGN_AND);

    // Get bounding box of intersection
    RECT bbox;
    GetRgnBox(region, &bbox);

    // Choose multiple points inside the intersection for flood fill
    int x = bbox.left + (bbox.right - bbox.left) / 2;
    int y = bbox.top + (bbox.bottom - bbox.top) / 2;
    int x222 = bbox.left + 6 * (bbox.right - bbox.left) / 4;
    int y222 = bbox.top + 6 * (bbox.bottom - bbox.top) / 4;

// Fill intersection with flood fill
   // NRFloodFill(hdc, x, y, RGB(255, 0, 0), RGB(0, 0, 0));
   // FloodFill(hdc,x,y,RGB(255,0,0));
    //FloodFill(hdc,x,y,RGB(255,0,0));
   // RFloodFill(hdc,x,y,RGB(255,0,0),RGB(0,0,0));
    NRFloodFill(hdc, x, y, RGB(255, 0, 0), RGB(0, 0, 0));

    // Clean up
    DeleteObject(region1);
    DeleteObject(region2);
    DeleteObject(region);
}
/*  This function is called by the Windows function DispatchMessage()  */
int selected = -1;
int X1,Y1,X2,Y2;//inputs for line
static bool stat = false;
int sides=5; //sides for polygon
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    HDC hdc  = GetDC(hwnd);;
    COLORREF c = RGB(255, 30, 5);
    static int click =0;
    //input for clipping
    static int p1,p2,p3,p4,idx=0;
    static double length,width;
    static Vector T;
    static Vector poly[100];
    static Vector2 points2[7];
    //for draw rect to fill bezier
    static int pp1,pp2,pp3,pp4;
    static double length1,width1;
    static Vector T1;
  static  point1 pp[5];
   static Point3 pp5[5];
    double x11,y11,x2,y2,x3,y3,x4,y4;
    //end
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
        {
            switch(wParam)
            {
                case FILLINGCIRCLE:
                {
                    selected = 24;
                    cout<<"Enter Quarter 1 to 4 : ";
                    cin >> q ;

                    int x ;
                    cout<<"\n Select 1 for line or 0 for circle: ";
                    cin >> x ;
                    if (x==1) flag = true ;
                    else flag = false ;
                    break;
                }
                case FILLINGLINE:
                {
                    selected = 23;
                    cout<<"Enter Quarter 1 to 4 : ";
                    cin >> q ;
                    int x ;
                    cout<<"\n Select 1 for line or 0 for circle: ";
                    cin >> x ;
                    if (x==1) flag = true ;
                    else flag = false ;
                    break;
                }

                case DDALINE:
                {
                    selected = 1;
                    break;

                }
                case MID_POINT:
                {
                    selected = 2;
                    break;

                }
                case PARAMETRIC:
                {
                    selected = 3;
                    break;

                }
                case DIRECT:
                {
                    selected =4;
                    break;

                }
                case POLAR:
                {
                    selected = 5;
                    break;

                }
                case ITPOLAR:
                {
                    selected = 6;
                    break;

                }
                case CIRCLE_MID_POINT:
                {
                    selected = 7;
                    break;

                }
                case MODIFIED_MID_POINT:
                {
                    selected = 8;
                    break;

                }
                case RED:
                {
                    rc=255,gc=0,bc=0;

                    break;

                }
                case BLACK:
                {
                    rc=0,gc=0,bc=0;
                    break;

                }
                case WHITE:
                {
                    RECT rect;
                    GetClientRect(hwnd,&rect);
                    HBRUSH rush =CreateSolidBrush(RGB(255,255,255));
                    FillRect(hdc,&rect,rush);
                    DeleteObject(rush);
                    ReleaseDC(hwnd,hdc);
                    break;

                }
                case MOUSEHAND:
                {
                    mouse = IDC_HAND;
                    break;
                }
                case MOUSEARROW:
                {
                    mouse = IDC_ARROW;
                    break;
                }
                case SAVE:
                {
                    save(hwnd);
                    break;

                }
                case LOAD:
                {
                    load(hwnd,hdc);
                    break;

                }
                case FILL_HERMITE:
                {
                    int numpoints = 1000; // Number of points to draw
                    Vector2 P0(X1, X2), T0(0, 0), P1(X2, X2+Y2), T1(0, 0);
                    filling_hermite(hdc,X2,Y2,numpoints,c);
                    break;
                }
                case DRAW_SQUARE:
                {
                    selected = 15;
                    //drawsquare(hdc,100,100,c);
                    break;


                }
                case FILL_BEZIER:
                {

                    int numpoints = 1000; // Number of points to draw
                    // Vector2 P0(xc, yc), T0(xc+10,yc+10 ), P1(xc+10, yc+10), T1(xc+100, yc);
                    fillBezier(hdc,T1[0],T1[1],width1,length1,1000);
                    break;

                }
                case DRAW_REC:
                {
                    selected = 18;
                    click =0;
                    //drawrectangle(hdc,100,100,c);
                    break;


                }
                case CLEAR:
                {
                    RECT rect;
                    GetClientRect(hwnd,&rect);
                    HBRUSH rush =CreateSolidBrush(RGB(255,255,255));
                    FillRect(hdc,&rect,rush);
                    DeleteObject(rush);
                    ReleaseDC(hwnd,hdc);
                    break;

                }
                case DIRECT_ELIPSE:
                {
                    selected = 22;
                    //drawellipse_direct(hdc,100,100,100,50);
                    break;
                }
                case MIDPOINT_ELIPSE:
                {
                    selected = 21;
                    //drawellipse_midpoint(hdc,100,100,100,50);
                    break;
                }
                case POLAR_ELIPSE:
                {
                    selected = 20;
                    //drawelipse_polar(hdc,100,100,100,50);
                    break;
                }
                case CARDINALSPLINE:
                {
                    selected = 25;
                    click =0;
                    cout<<"CARDINAL SPLINE CURVE  "<<endl;
                    //DrawCardinalSpline(hdc,points, n, 0.5,nump);
                    break;
                }
                case RECUESIVEFLOODFILL:
                {
                    RFloodFill(hdc,101,101,250,0);
                    break;
                }
                case NONRECUESIVEFLOODFILL:
                {
                    NRFloodFill(hdc,101,101,250,0);
                    break;
                }
                case CLIPPINGLINESQ:
                {
                    selected = 29;
                    Rectangle(hdc,250,500,500,250);
                    break;
                }
                case CLIPPINGPOINTSQ:
                {
                    selected = 30;
                    Rectangle(hdc,250,500,500,250);
                    break;
                }
                case CLIPPINGLINERECT:
                {
                    selected = 31;
                    Rectangle(hdc,50,350,350,200);
                    break;
                }
                case CLIPPINGPOINTRECT:
                {
                    selected = 32;
                    Rectangle(hdc,50,350,350,200);
                    break;
                }
                case CLIPPINGPOLYGONRECT:
                {
                    selected = 33;
                    click =0;
                    //Rectangle(hdc,50,350,350,200);
                    break;
                }
                case CONVEX:
                {
                    selected = 34;
                    click =0;
                    //Rectangle(hdc,250,500,500,250);
                    break;
                }
                case NON_CONVEX:{

                    selected=35;
                    click=0;
                    break;

                }
                case DRAW_INTERSECTION:{

                    selected=36;
                    click=0;
                    break;

                }




            }
            break;
        }
        case WM_CREATE:
        {
            addmenus(hwnd);
            break;
        }
        case WM_LBUTTONDOWN:
            X1 = LOWORD(lParam);
            Y1 = HIWORD(lParam);
            break;
        case WM_RBUTTONDOWN:
            X2 = LOWORD(lParam);
            Y2 = HIWORD(lParam);
            ///lines
            if(selected==1)
            {
                cout<<"DDA LINE "<<endl;
                drawline_dda(hdc,X1,Y1,X2,Y2);
            }
            else if(selected==2)
            {
                cout<<"MID POINT LINE "<<endl;
                drawline_m(hdc,X1,Y1,X2,Y2);
            }
            else if(selected==3)
            {
                cout<<"PRAMETRIC LINE "<<endl;
                drawline_p(hdc,X1,Y1,X2,Y2);
            }
                ///circles
            else if(selected == 4)
            {
                cout<<"DIRECT CIRCLE "<<endl;
                CircleDirect(hdc,X2,Y2,100);
            }
            else if(selected == 5)
            {
                cout<<"POLAR CIRCLE "<<endl;
                CirclePolar(hdc,X2,Y2,100);
            }
            else if(selected == 6)
            {
                cout<<"ITERATIVE POLAR CIRCLE "<<endl;
                CircleIterativePolar(hdc,X2,Y2,100);
            }
            else if(selected == 7)
            {
                cout<<"MidPoint CIRCLE "<<endl;
                CircleMidPoint(hdc,X2,Y2,100);
            }
            else if(selected == 8)
            {
                cout<<"Modfiy MidPoint CIRCLE "<<endl;
                CircleModfiyMidPoint(hdc,X2,Y2,100);
            }
                ///filling circle with line or circle
            else if(selected == 23)
            {
                cout<<"FILLING CIRCLE WITH LINES "<<endl;
                CircleMidPoint(hdc,X2,Y2,100);
                fun(hdc,X2,Y2,100);
            }
            else if(selected == 24)
            {
                cout<<"FILLING CIRCLE WITH CIRCLES "<<endl;
                CircleMidPoint(hdc,X2,Y2,100);
                fun(hdc,X2,Y2,100);

            }
                ///draw square
            else if(selected == 15)
            {
                drawsquare(hdc,X2,Y2,c);
            }
                ///draw rectangle
            else if(selected == 18)
            {
                if(stat==false)
                {
                    stat=true;
                }

                if(click==0)
                {
                    click++;
                    T1[0]=LOWORD(lParam);
                    T1[1]=HIWORD(lParam);
                    cout<<"T[0]: "<<T1[0]<<" T[1]: "<<T1[1]<<endl;
                    cout<<click<<endl;
                    break;
                }
                else if(click==1)
                {
                    click++;
                    pp1=LOWORD(lParam);
                    pp2=HIWORD(lParam);
                    cout<<"p1: "<<pp1<<" p2: "<<pp2<<endl;
                    break;
                }
                else if(click==2)
                {
                    pp3 = LOWORD(lParam);
                    pp4 = HIWORD(lParam);
                    cout<<"p1: "<<pp3<<" p2: "<<pp4<<endl;
                    //get width and length
                    length1 = GetDistanceBetween2Points(T1[0],pp1,T1[1],pp2);
                    width1 = GetDistanceBetween2Points(T1[0],pp3,T1[1],pp4);

                    //finally draw rectangle
                    drawRectangle(hdc,T1,length1,width1,RGB(0,0,0));
                    click++;
                    break;
                }

            }
                /// draw ellipse
            else if(selected == 20)
            {
                cout<<"POLAR ELLIPSE "<<endl;
                drawelipse_polar(hdc,X1,Y1,100,50);
            }
            else if(selected == 21)
            {
                cout<<"MidPoint ELLIPSE "<<endl;
                drawellipse_midpoint(hdc,X2,Y2,100,50);
            }
            else if(selected == 22)
            {
                cout<<"DIRECT ELLIPSE  "<<endl;
                drawellipse_direct(hdc,X2,Y2,100,50);
            }
                /// draw cardinal spline curve
            else if(selected == 25 && click ==0)
            {
                if(stat == false)
                {
                    stat = true;
                }
                if(click==0)
                {
                    points2[idx] = Vector2(LOWORD(lParam), HIWORD(lParam));
                    cout<<points2[idx].x<<"   "<<points2[idx].y<<endl;
                    if(idx!=6)
                    {
                        idx++;
                    }
                    else
                    {
                        DrawCardinalSpline(hdc,points2,n,0.5,nump);
                        idx=0;
                        stat=false;
                    }
                    break;
                }
            }
                ///clipping square
            else if(selected == 29)
            {
                cout<<"Clipping Square With Line "<<endl;
                Clipping_Line(hdc,X1,X2,Y1,Y2,500,250,250,500);
            }
            else if(selected == 30)
            {
                cout<<"Clipping Square With Point "<<endl;
                Clipping_Point(hdc,X2,Y2,500,250,250,500);
            }
                ///clipping rectangle
            else if(selected == 31)
            {
                cout<<"Clipping Rectangle With Line "<<endl;
                Clipping_Line(hdc,X1,X2,Y1,Y2,350,200,50,350);
            }
            else if(selected == 32)
            {
                cout<<"Clipping Rectangle With Point "<<endl;
                Clipping_Point(hdc,X2,Y2,350,200,50,350);
            }
                ///clipping polygon rectangle
            else if(selected==33)
            {
                if(stat==false)
                {
                    stat=true;
                }

                if(click==0)
                {
                    click++;
                    T[0]=LOWORD(lParam);
                    T[1]=HIWORD(lParam);
                    cout<<"T[0]: "<<T[0]<<" T[1]: "<<T[1]<<endl;
                    break;
                }
                else if(click==1)
                {
                    click++;
                    p1=LOWORD(lParam);
                    p2=HIWORD(lParam);
                    cout<<"p1: "<<p1<<" p2: "<<p2<<endl;
                    break;
                }
                else if(click==2)
                {
                    p3 = LOWORD(lParam);
                    p4 = HIWORD(lParam);

                    //get width and length
                    length = GetDistanceBetween2Points(T[0],p1,T[1],p2);
                    width = GetDistanceBetween2Points(T[0],p3,T[1],p4);

                    //finally draw rectangle
                    drawRectangle(hdc,T,length,width,RGB(0,0,0));
                    click++;
                    break;
                }
                else if(click==3)
                {
                    poly[idx] = Vector(LOWORD(lParam), HIWORD(lParam));
                    if(idx!=sides-1)
                    {
                        idx++;
                    }
                    else
                    {
                        PolygonClip(hdc,poly,sides,T[0],T[1],T[0]+length,T[1]+width);
                        idx=0;
                        stat=false;
                    }
                    break;
                }
            }
                ///convex polygon
            else if(selected==34)
            {
                if (stat == false) {
                    stat = true;
                }
                if(click==0)
                {

                    pp[click].x=LOWORD(lParam);
                    pp[click].y=HIWORD(lParam);
                    click++;

                    break;
                }
                else if(click==1)
                {
                    pp[click].x=LOWORD(lParam);
                    pp[click].y=HIWORD(lParam);
                 click++;
                    break;
                }
                else if(click==2)
                {
                    pp[click].x = LOWORD(lParam);
                    pp[click].y = HIWORD(lParam);
                    click++;
                    break;
                }
                else if(click==3) {
                    pp[click].x = LOWORD(lParam);
                    pp[click].y = HIWORD(lParam);
                    click++;
                    break;
                }
                else if(click==4){
                    pp[click].x = LOWORD(lParam);
                    pp[click].y = HIWORD(lParam);
                    draw_convex_polygon(hdc,pp,5,RGB(100,0,0));
                    break;
                }
            }
                ///non_convex polygon
            else if(selected==35)
            {
                if (stat == false) {
                    stat = true;
                }
                if(click==0)
                {

                    pp5[click].x=LOWORD(lParam);
                    pp5[click].y=HIWORD(lParam);
                    click++;

                    break;
                }
                else if(click==1)
                {
                    pp5[click].x=LOWORD(lParam);
                    pp5[click].y=HIWORD(lParam);
                    click++;
                    break;
                }
                else if(click==2)
                {
                    pp5[click].x = LOWORD(lParam);
                    pp5[click].y = HIWORD(lParam);
                    click++;
                    break;
                }
                else if(click==3) {
                    pp5[click].x = LOWORD(lParam);
                    pp5[click].y = HIWORD(lParam);
                    click++;
                    break;
                }
                else if(click==4){
                    pp5[click].x = LOWORD(lParam);
                    pp5[click].y = HIWORD(lParam);
                    Fill(hdc,pp5,5,RGB(100,0,0));
                    break;
                }
            }
            else if (selected==36) {
                if (stat == false) {
                    stat = true;
                }

                if (click == 0) {

                    x11= LOWORD(lParam);
                    y11 = HIWORD(lParam);
                    click++;

                    break;
                } else if (click == 1) {
                    x2 = LOWORD(lParam);
                    y2 = HIWORD(lParam);
                    click++;
                    drawcircler(hdc, x11, y11, x2, y2);
                    break;
                } else if (click == 2) {
                    x3 = LOWORD(lParam);
                    y3 = HIWORD(lParam);
                    click++;
                    break;
                } else if (click == 3) {
                    x4 = LOWORD(lParam);
                    y4 = HIWORD(lParam);
                    drawcircler(hdc, x3, y3, x4, y4);
                    click++;
                    break;
                } else if (click == 4) {
                    FillCircleIntersection(hdc, x11, y11, x2, y2, x3, y3, x4, y4);
                    break;
                }
            }
            break;
        case WM_SETCURSOR:
            SetCursor(LoadCursor(NULL,mouse));
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
