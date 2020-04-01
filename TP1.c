#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_LENGHT 255
#define SIZE 20
#define FILE_NAME "cloud20-2"

double theta(double x1, double y1, double x2, double y2);
void swap(double points[][2], int i, int j);
int wrap(double points[][2], int dim);
void exportPoint(double points[][2], int nbPoints);
void readFile(double [][2] points);

int main(int argc, char **argv)
{
    double points[1290][2];

    readFile(double [][2] points);

    int i_conv = wrap(points, SIZE);
    printf("number of points : %d\n", i_conv);
    for (int k = 0; k < i_conv; k++)
    {
        printf("point %d (%f,%f)\n", k, points[k][0], points[k][1]);
    }
}

double theta(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double ax = fabs(dx);
    double dy = y2 - y1;
    double ay = fabs(dy);
    double ang;
    if (dx == 0.0 && dy == 0.0)
    {
        ang = 0.0;
    }
    else
    {
        ang = (double)(dy / (ax + ay));
    }
    if (dx < 0.0)
    {
        ang = 2.0 - ang;
    }
    else if (dy < 0.0)
    {
        ang = 4.0 + ang;
    }
    return ang;
}

void swap(double points[][2], int i, int j)
{
    size_t lenght = sizeof(points[i]);
    double p[2];
    memcpy(p, points[i], lenght);
    memcpy(points[i], points[j], lenght);
    memcpy(points[j], p, lenght);
}

int wrap(double points[][2], int dim)
{
    int imin = 0;
    for (int i = 0; i < dim; i++)
    {
        if (points[i][1] < points[imin][1])
        {
            imin = i;
        }
    }
    size_t length = sizeof(points[imin]);
    memcpy(points[dim], points[imin], length);
    double thetamin = 0.0;
    int i = 0;
    int ang;
    double p[2];
    double q[2];
    while (i < dim)
    {
        swap(points, i, imin);
        size_t p_length = sizeof(points[i]);
        memcpy(p, points[i], p_length);
        ang = thetamin;
        thetamin = 4.1;
        for (int j = i + 1; j < dim + 1; j++)
        {
            size_t q_length = sizeof(points[j]);
            memcpy(q, points[j], q_length);
            double th = theta(p[0], p[1], q[0], q[1]);
            if (th > ang && th < thetamin)
            {
                imin = j;
                thetamin = th;
            }
        }
        if (thetamin > 4.0)
        {
            exportPoint(points, i);
            return i;
        }
        i = i + 1;
    }
}

void exportPoint(double points[][2], int nbPoints)
{
    FILE *fp = fopen("Results/" FILE_NAME ".sol", "w+");

    for (int i = 0; i < nbPoints; i++)
    {
        fprintf(fp, "%f,%f \n", points[i][0], points[i][1]);
    }
    fclose(fp);
}

double [][2] readFile(double [][2] points){
    char buffer[BUFFER_LENGHT];

    FILE *filePointer = fopen("Benchmark/" FILE_NAME ".txt", "r");
    if (filePointer == NULL)
    {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    int i = 0;
    while (fgets(buffer, BUFFER_LENGHT, filePointer))
    {
        char *token = strtok(buffer, ",");
        int j = 0;
        while (token != NULL)
        {
            points[i][j] = atof(token);
            j++;
            token = strtok(NULL, ",");
        }
        i++;
    }
    fclose(filePointer);
    return points;
}