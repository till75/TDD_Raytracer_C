#include "canvas.h"
#include "color.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void canvas_Create(Canvas* c, int width, int height)
{
    Color* pColor;
    c->width = width;
    c->height = height;
    int memory_need = width*height*sizeof(Color);
//    printf("About to allocate %d bytes\n", memory_need );
    if (!(c->pixels = (Color*)malloc(memory_need)))
    {
        printf("malloc(%d) failed!", memory_need);
        return;
    }
//    printf("Memory location of canvas pixel array: %08x\n", c->pixels );
    for (int y = 0; y<height; y++) 
    {
        for (int x = 0; x<width; x++)
        {
            int index = x + y * width;//x*sizeof(Color) + y * c->width * sizeof(Color);
//            printf("Asking for Color at index %d\n", index);
            pColor = (Color*)(c->pixels + index);
            color_Create(pColor, 0.0, 0.0, 0.0);
        }
    }
}

void canvas_Destroy(Canvas* c)
{
    free(c->pixels);
}

Color* canvas_GetColor(Canvas* c, int x, int y)
{
    if (x>=c->width || y >= c->height)
        return NULL;
    int index = x + y * c->width; //x*sizeof(Color) + y * c->width * sizeof(Color);
//    printf("Returning index %d\n", index);
    return (Color*)(c->pixels + index);
}

void canvas_DrawPixel(Canvas* canvas, Color* color, int x, int y)
{
    if (x>=canvas->width || x<0 || y >= canvas->height || y<0)
        return;
    int index = x + y * canvas->width;
    color_Create((Color*)(canvas->pixels + index), color->red, color->green, color->blue);
}

void canvas_HeaderToPPM(Canvas* canvas, char* ppm)
{
    sprintf(ppm, "P3\n%d %d\n255\n\0", canvas->width, canvas->height);
}

void canvas_PixelRowToPPM(Canvas* canvas, char* ppm, int row)
{
    Color* pColor;
    char pixel[11];
    for (int x=0; x<canvas->width; x++)
    {
        pColor = canvas_GetColor(canvas, x, row);
        color_toPPM(pColor, pixel);
        strcat(ppm, pixel);
        if (x != canvas->width-1)
            strcat(ppm, " ");
    }
}

void canvas_PixelsToPPM(Canvas* canvas, char* ppm)
{
    Color* pColor;
    char pixelRow[canvas->width * 3 * 4];   
    for (int y=0; y<canvas->height; y++)
    {
        pixelRow[0] = '\0';
        canvas_PixelRowToPPM(canvas, pixelRow, y);

        strcat(ppm, pixelRow);
        strcat(ppm, "\n");

/*
        if (strlen(pixelRow) <= 70)
        {
            strcat(ppm, pixelRow);
            strcat(ppm, "\n");
        }
        else
        {
            // TODO
            // split up lines that are longer than 70 characters
            // but do not split up a number 
            strcat(ppm, "TODO: split lines >70 characters\n");
        }
*/
    }
}

void canvas_PixelsToPPMFile(Canvas* canvas, char* filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    
    Color* pColor;
    char header[30];
    header[0] = '\0';
    canvas_HeaderToPPM(canvas, header);
    fprintf(fp, "%s\n", header);

    char pixelRow[canvas->width * 3 * 4];   
    for (int y=0; y<canvas->height; y++)
    {
        pixelRow[0] = '\0';
        canvas_PixelRowToPPM(canvas, pixelRow, y);
        fprintf(fp, "%s\n", pixelRow);
    }
    fclose(fp);
}