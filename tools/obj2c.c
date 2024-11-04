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

    printf("typedef struct {\n");
    printf("    float x, y, z;\n");
    printf("} Vertex;\n");
    printf("static Vertex vertices[%d] = {\n", vert_count);

    while (getline(&line, &line_len, file) != -1) {
        if (line[0] != 'v' || line[1] != ' ') continue;

        float x, y, z;
        sscanf(line, "v %f %f %f", &x, &y, &z);
        printf("    {%+9f,%+9f,%+9f},\n", x, y, z);
    }
    printf("};\n");

    rewind(file);

    printf("typedef struct {\n");
    printf("    Vertex *v1, *v2, *v3;\n");
    printf("} Face;\n");
    printf("static Face faces[%d] = {\n", face_count);

    while (getline(&line, &line_len, file) != -1) {
        if (line[0] != 'f' || line[1] != ' ') continue;

        int v_idx1, v_idx2, v_idx3;
        sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v_idx1, &v_idx2, &v_idx3);

        v_idx1 -= 1;
        v_idx2 -= 1;
        v_idx3 -= 1;

        printf("    {&vertices[%d], &vertices[%d], &vertices[%d]},\n", v_idx1, v_idx2, v_idx3);
    }
    printf("};\n");

    return 0;
}
