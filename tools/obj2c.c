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

    int vertices_count = 0, faces_count = 0, normals_count = 0, texture_coords_count = 0;
    float shininess = 0.0, ambient[3] = {0.0, 0.0, 0.0}, specular[3] = {0.0, 0.0, 0.0};
    float emissive[3] = {0.0, 0.0, 0.0}, index_of_refraction = 0.0, opacity = 1.0;
    int illum_model = 0;
    char texture_map[32] = {0};

    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "v ", 2) == 0) vertices_count++;
        if (strncmp(line, "vn", 2) == 0) normals_count++;
        if (strncmp(line, "vt", 2) == 0) texture_coords_count++;
        if (strncmp(line, "f ", 2) == 0) faces_count++;
        if (strncmp(line, "Ns", 2) == 0) sscanf(line, "Ns %f", &shininess);
        if (strncmp(line, "Ka", 2) == 0) sscanf(line, "Ka %f %f %f", &ambient[0], &ambient[1], &ambient[2]);
        if (strncmp(line, "Ks", 2) == 0) sscanf(line, "Ks %f %f %f", &specular[0], &specular[1], &specular[2]);
        if (strncmp(line, "Ke", 2) == 0) sscanf(line, "Ke %f %f %f", &emissive[0], &emissive[1], &emissive[2]);
        if (strncmp(line, "Ni", 2) == 0) sscanf(line, "Ni %f", &index_of_refraction);
        if (strncmp(line, "d", 1) == 0) sscanf(line, "d %f", &opacity);
        if (strncmp(line, "illum", 5) == 0) sscanf(line, "illum %d", &illum_model);
        if (strncmp(line, "map_Kd", 6) == 0) sscanf(line, "map_Kd %31s", texture_map);
    }

    printf("#define VERTICES_COUNT %d\n", vertices_count);
    printf("#define NORMALS_COUNT %d\n", normals_count);
    printf("#define TEXTURE_COORDS_COUNT %d\n", texture_coords_count);
    printf("#define MATERIAL_SHININESS %f\n", shininess);
    printf("static const float MATERIAL_AMBIENT[3] = { %f, %f, %f };\n", ambient[0], ambient[1], ambient[2]);
    printf("static const float MATERIAL_SPECULAR[3] = { %f, %f, %f };\n", specular[0], specular[1], specular[2]);
    printf("static const float MATERIAL_EMISSIVE[3] = { %f, %f, %f };\n", emissive[0], emissive[1], emissive[2]);
    printf("#define MATERIAL_IOR %f\n", index_of_refraction);
    printf("#define MATERIAL_OPACITY %f\n", opacity);
    printf("#define MATERIAL_ILLUM %d\n", illum_model);
    printf("static const char *MATERIAL_TEXTURE_MAP = \"%s\";\n", texture_map);

    printf("static const float vertices[%d] = {\n", vertices_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "v ", 2) != 0) continue;

        float x, y, z;
        sscanf(line, "v %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    printf("static const float normals[%d] = {\n", normals_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "vn", 2) != 0) continue;

        float x, y, z;
        sscanf(line, "vn %f %f %f", &x, &y, &z);
        printf("    %+10f,%+10f,%+10f,\n", x, y, z);
    }
    printf("};\n");

    printf("static const float texture_coords[%d] = {\n", texture_coords_count * 2);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "vt", 2) != 0) continue;

        float x, y;
        sscanf(line, "vt %f %f", &x, &y);
        printf("    %+10f,%+10f,\n", x, y);
    }
    printf("};\n");

    printf("static const unsigned int vertex_indices[%d] = {\n", faces_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "f ", 2) != 0) continue;

        int v_idx1 = 0, v_idx2 = 0, v_idx3 = 0;
        sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v_idx1, &v_idx2, &v_idx3);

        v_idx1 -= 1;
        v_idx2 -= 1;
        v_idx3 -= 1;

        printf("    %4d,%4d,%4d,\n", v_idx1, v_idx2, v_idx3);
    }
    printf("};\n");

    printf("static const unsigned int texture_indices[%d] = {\n", faces_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "f ", 2) != 0) continue;

        int t_idx1 = 0, t_idx2 = 0, t_idx3 = 0;
        sscanf(line, "f %*d/%d/%*d %*d/%d/%*d %*d/%d/%*d", &t_idx1, &t_idx2, &t_idx3);

        t_idx1 -= 1;
        t_idx2 -= 1;
        t_idx3 -= 1;

        printf("    %4d,%4d,%4d,\n", t_idx1, t_idx2, t_idx3);
    }
    printf("};\n");

    printf("static const unsigned int normal_indices[%d] = {\n", faces_count * 3);
    for (rewind(file); getline(&line, &line_len, file) != -1;) {
        if (strncmp(line, "f ", 2) != 0) continue;

        int n_idx1 = 0, n_idx2 = 0, n_idx3 = 0;
        sscanf(line, "f %*d/%*d/%d %*d/%*d/%d %*d/%*d/%d", &n_idx1, &n_idx2, &n_idx3);

        n_idx1 -= 1;
        n_idx2 -= 1;
        n_idx3 -= 1;

        printf("    %4d,%4d,%4d,\n", n_idx1, n_idx2, n_idx3);
    }
    printf("};\n");

    fclose(file);

    return 0;
}
