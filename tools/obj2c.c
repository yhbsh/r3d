#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "[USAGE]: main <file.obj>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    char *line = NULL;
    size_t line_len = 0;

    int vertices = 0, faces = 0, texcoords = 0, normals = 0;

    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "v ", 2) == 0)
            vertices++;
        if (strncmp(line, "f ", 2) == 0)
            faces++;
        if (strncmp(line, "vt ", 3) == 0)
            texcoords++;
        if (strncmp(line, "vn ", 3) == 0)
            normals++;
    }

    printf("static float p_vertices[%d] = {\n", vertices * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "v ", 2) != 0)
            continue;

        float x, y, z;
        sscanf(line, "v %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    printf("static float p_texcoords[%d] = {\n", texcoords * 2);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "vt ", 3) != 0)
            continue;

        float u, v;
        sscanf(line, "vt %f %f", &u, &v);
        printf("    %+10f,%+10f,\n", u, v);
    }
    printf("};\n");

    printf("static float p_normals[%d] = {\n", normals * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "vn ", 3) != 0)
            continue;

        float x, y, z;
        sscanf(line, "vn %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    printf("static unsigned int p_indices[%d] = {\n", faces * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "f ", 2) != 0)
            continue;

        int v_idx1 = 0, v_idx2 = 0, v_idx3 = 0;
        sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v_idx1, &v_idx2, &v_idx3);

        v_idx1 -= 1;
        v_idx2 -= 1;
        v_idx3 -= 1;

        printf("    %4d,%4d,%4d,\n", v_idx1, v_idx2, v_idx3);
    }
    printf("};\n");

    fclose(file);

    return 0;
}
