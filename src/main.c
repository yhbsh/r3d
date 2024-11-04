#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "data.h"

#define WIDTH 500
#define HEIGHT 500

void plot(int x, int y, unsigned char *image) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int index = (y * WIDTH + x) * 3;
        image[index] = 255;
        image[index + 1] = 255;
        image[index + 2] = 255;
    }
}

int transform_x(float x) { return (int)((x + 1.0f) * WIDTH / 2.0f); }
int transform_y(float y) { return (int)((1.0f - y) * HEIGHT / 2.0f); }

void draw_line(int x0, int y0, int x1, int y1, unsigned char *image) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        plot(x0, y0, image);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int main(void) {
    unsigned char image[WIDTH * HEIGHT * 3] = {0};

    for (int i = 0; i < FACE_COUNT; i++) {
        int x1 = transform_x(faces[i].v1->x);
        int y1 = transform_y(faces[i].v1->y);
        int x2 = transform_x(faces[i].v2->x);
        int y2 = transform_y(faces[i].v2->y);
        int x3 = transform_x(faces[i].v3->x);
        int y3 = transform_y(faces[i].v3->y);

        draw_line(x1, y1, x2, y2, image);
        draw_line(x2, y2, x3, y3, image);
        draw_line(x3, y3, x1, y1, image);
    }

    stbi_write_png("image.png", WIDTH, HEIGHT, 3, image, WIDTH * 3);

    return 0;
}
