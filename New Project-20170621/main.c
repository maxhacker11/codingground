#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef
    struct vector{
        float x;
        float y;
    }Vector;

float cross(Vector A,Vector B,Vector C){
    Vector AB, AC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    return (AB.x * AC.y) - (AB.y * AC.x);
}

float dot(Vector A,Vector B,Vector C){
    Vector AB, AC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    return (AB.x * AC.x) + (AB.y * AC.y);
}

float dist(Vector A,Vector B){
    float d1 = A.x - B.x;
    float d2 = A.y - B.y;
    return sqrt(d1 * d1 + d2 * d2);
}

float linePointDistance(Vector A,Vector B,Vector C, bool isSegment){
    float d = cross(A, B, C) / dist(A, B);
    if(isSegment){
        float d1 = dot(A, B, C);
        if(d1 <= 0) return dist(A, C);
        float d2 = dot(B, A, C);
        if(d2 <= 0) return dist(B, C);
    }
    return fabs(d);
}

float polygonArea(float *p, int n){
    float area = 0;
    int i;
    for(i = 1; i + 1 < n; i++){
        float x1 = p[i * 2 + 0] - p[0];
        float y1 = p[i * 2 + 1] - p[1];
        float x2 = p[(i+1) * 2 + 0] - p[0];
        float y2 = p[(i+1) * 2 + 1] - p[1];
        area += (x1 * y2) - (x2 * y1);
    }
    return fabs(area/2);
}

void lineLineIntersection(Vector A, Vector B, Vector C, Vector D){
    float A1 = A.y - B.y;
    float B1 = B.x - A.x;
    float C1 = A.x * B.y - B.x * A.y;
    
    float A2 = C.y - D.y;
    float B2 = D.x - C.x;
    float C2 = C.x * D.y + D.x * C.y;
    
    float det = A1 * B2 - A2 * B1;
    
    if(det == 0)
        printf("Lines are parallel!\n");
    else
        printf("%.2f %.2f\n", (B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det);
}

void circle(Vector X, Vector Y, Vector Z){
    Vector M1, M2;
    //First line
    M1.x = (X.x + Y.x) / 2;
    M1.y = (X.y + Y.y) / 2;
    
    float A1 = X.x - Y.x;
    float B1 = X.y - Y.y;
    float D1 = A1 * M1.x + B1 * M1.y;
    
    //Second line
    M2.x = (Y.x + Z.x) / 2;
    M2.y = (Y.y + Z.y) / 2;
    
    float A2 = Y.x - Z.x;
    float B2 = Y.y - Z.y;
    float D2 = A2 * M2.x + B2 * M2.y;
    
    //Intersection
    float det = A1 * B2 - A2 * B1;
    
    if(det == 0)
        printf("The points are collinear!\n");
    else
        printf("Center: %.2f %.2f\n", (B2 * D1 - B1 * D2) / det, (A1 * D2 - A2 * D1) / det);
}

int main()
{
    Vector A, B, C;
    scanf("%f %f", &A.x, &A.y);
    scanf("%f %f", &B.x, &B.y);
    scanf("%f %f", &C.x, &C.y);

    circle(A, B, C);
    
    return 0;
}

