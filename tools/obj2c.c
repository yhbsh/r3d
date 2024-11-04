#include <stdio.h>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "[USAGE]: main <file.obj>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    char *line = NULL;
    size_t line_len = 0;

    int vert_count = 0;
    int face_count = 0;

    while (getline(&line, &line_len, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') vert_count++;
        if (line[0] == 'f' && line[1] == ' ') face_count++;
    }

    rewind(file);

    printf("#define VERT_COUNT %d\n", vert_count);
    printf("#define FACE_COUNT %d\n", face_count);

    printf("static float vertices[%d] = {\n", vert_count * 3);

    while (getline(&line, &line_len, file) != -1) {
        if (line[0] != 'v' || line[1] != ' ') continue;

        float x, y, z;
        sscanf(line, "v %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    rewind(file);

    printf("static unsigned int faces[%d] = {\n", face_count * 3);

    while (getline(&line, &line_len, file) != -1) {
        if (line[0] != 'f' || line[1] != ' ') continue;

        int v_idx1, v_idx2, v_idx3;
        sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v_idx1, &v_idx2, &v_idx3);

        v_idx1 -= 1;
        v_idx2 -= 1;
        v_idx3 -= 1;

        printf("    %4d, %4d, %4d,\n", v_idx1, v_idx2, v_idx3);
    }
    printf("};\n");

    return 0;
}
