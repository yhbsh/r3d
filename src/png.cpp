#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <data.h>

#define IMG_DIM 800

int transform_x(float x) {
    return (int)((x + 1.0f) * IMG_DIM / 2.0f);
}
int transform_y(float y) {
    return (int)((1.0f - y) * IMG_DIM / 2.0f + IMG_DIM * 0.33);
}

void draw_line(int x0, int y0, int x1, int y1, unsigned char *image) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (x0 >= 0 && x0 < IMG_DIM && y0 >= 0 && y0 < IMG_DIM) {
            image[(y0 * IMG_DIM + x0) * 3 + 0] = 255;
            image[(y0 * IMG_DIM + x0) * 3 + 1] = 255;
            image[(y0 * IMG_DIM + x0) * 3 + 2] = 255;
        }

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
    unsigned char image[IMG_DIM * IMG_DIM * 3] = {0};

    for (int i = 0; i < FACE_COUNT * 3; i += 3) {
        int v1 = faces[i + 0] * 3;
        int v2 = faces[i + 1] * 3;
        int v3 = faces[i + 2] * 3;

        int x1 = transform_x(vertices[v1 + 0]);
        int y1 = transform_y(vertices[v1 + 1]);
        int x2 = transform_x(vertices[v2 + 0]);
        int y2 = transform_y(vertices[v2 + 1]);
        int x3 = transform_x(vertices[v3 + 0]);
        int y3 = transform_y(vertices[v3 + 1]);

        draw_line(x1, y1, x2, y2, image);
        draw_line(x2, y2, x3, y3, image);
        draw_line(x3, y3, x1, y1, image);
    }

    stbi_write_png("image.png", IMG_DIM, IMG_DIM, 3, image, IMG_DIM * 3);

    return 0;
}
