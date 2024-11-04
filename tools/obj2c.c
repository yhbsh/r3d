#include <stdio.h>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "[USAGE]: main <file.obj>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    char *line = NULL;
    size_t line_len = 0;

    int vertices_count = 0;
    int faces_count = 0;
    int normals_count = 0;
    int texture_coords_count = 0;

    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (line[0] == 'v' && line[1] == ' ') vertices_count++;
        if (line[0] == 'f' && line[1] == ' ') faces_count++;
        if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') normals_count++;
        if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') texture_coords_count++;
    }

    printf("#define VERTICES_COUNT %d\n", vertices_count);
    printf("#define NORMALS_COUNT %d\n", normals_count);
    printf("#define TEXTURE_COORDS_COUNT %d\n", texture_coords_count);
    printf("#define FACES_COUNT %d\n", faces_count);

    printf("static const float vertices[%d] = {\n", vertices_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (line[0] != 'v' || line[1] != ' ') continue;

        float x, y, z;
        sscanf(line, "v %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    printf("static const float normals[%d] = {\n", normals_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (line[0] != 'v' || line[1] != 'n' || line[2] != ' ') continue;

        float x, y, z;
        sscanf(line, "vn %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    printf("static const float texture_coords[%d] = {\n", texture_coords_count * 2);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (line[0] != 'v' || line[1] != 't' || line[2] != ' ') continue;

        float x, y;
        sscanf(line, "vt %f %f", &x, &y);
        printf("    %+10f,%+10f,\n", x, y);
    }
    printf("};\n");

    printf("static const unsigned int faces[%d] = {\n", faces_count * 9);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (line[0] != 'f' || line[1] != ' ') continue;

        int v_idx1 = 0, t_idx1 = 0, n_idx1 = 0;
        int v_idx2 = 0, t_idx2 = 0, n_idx2 = 0;
        int v_idx3 = 0, t_idx3 = 0, n_idx3 = 0;

        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v_idx1, &t_idx1, &n_idx1, &v_idx2, &t_idx2, &n_idx2, &v_idx3, &t_idx3, &n_idx3);

        v_idx1 -= 1;
        v_idx2 -= 1;
        v_idx3 -= 1;
        t_idx1 -= 1;
        t_idx2 -= 1;
        t_idx3 -= 1;
        n_idx1 -= 1;
        n_idx2 -= 1;
        n_idx3 -= 1;

        printf("    %4d,%4d,%4d, %4d,%4d,%4d, %4d,%4d,%4d,\n", v_idx1, v_idx2, v_idx3, t_idx1, t_idx2, t_idx3, n_idx1, n_idx2, n_idx3);
        // printf("    %4d,%4d,%4d,\n", v_idx1, v_idx2, v_idx3);
    }
    printf("};\n");

    fclose(file);

    return 0;
}
