#include "pixelram.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH  320
#define HEIGHT 180

#define LIT_BASE     16
#define HUE_STEPS    16
#define VALUE_STEPS  14

#define ASTEROID_COUNT 18
#define ENEMY_COUNT    3
#define STAR_COUNT     200
#define SPEEDLINE_COUNT 45
#define PARTICLE_COUNT  180
#define SHRAPNEL_COUNT  48
#define MAX_FACES       1400

/* --- Interpolation & Math Helpers ------------------------------------- */

static float lerpf(float a, float b, float t) {
    return a + (b - a) * t;
}

static void vec3_lerp(float *out, const float *a, const float *b, float t) {
    out[0] = lerpf(a[0], b[0], t);
    out[1] = lerpf(a[1], b[1], t);
    out[2] = lerpf(a[2], b[2], t);
}

static void vec3_normalize(float *v) {
    float len = sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (len > 0.0001f) { v[0] /= len; v[1] /= len; v[2] /= len; }
}

static float vec3_dot(const float *a, const float *b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

static void vec3_cross(float *out, const float *a, const float *b) {
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

static void rotate_vec3(float *v, float ax, float ay, float az) {
    float y = v[1] * cosf(ax) - v[2] * sinf(ax);
    float z = v[1] * sinf(ax) + v[2] * cosf(ax);
    v[1] = y; v[2] = z;

    float x = v[0] * cosf(ay) + v[2] * sinf(ay);
    z = -v[0] * sinf(ay) + v[2] * cosf(ay);
    v[0] = x; v[2] = z;

    x = v[0] * cosf(az) - v[1] * sinf(az);
    y = v[0] * sinf(az) + v[1] * cosf(az);
    v[0] = x; v[1] = y;
}

/* --- Camera Matrix with Roll ------------------------------------------- */

static void calc_lookat_roll(const float *cam_pos, const float *target, float roll_angle, float *R, float *U, float *F) {
    F[0] = target[0] - cam_pos[0];
    F[1] = target[1] - cam_pos[1];
    F[2] = target[2] - cam_pos[2];
    vec3_normalize(F);

    float world_up[3] = { sinf(roll_angle), cosf(roll_angle), 0.0f };
    vec3_cross(R, world_up, F);
    if (vec3_dot(R, R) < 0.0001f) { R[0] = 1; R[1] = 0; R[2] = 0; }
    else { vec3_normalize(R); }

    vec3_cross(U, F, R);
    vec3_normalize(U);
}

static void world_to_cam(float *out, const float *p, const float *cam_pos, const float *R, const float *U, const float *F) {
    float dx = p[0] - cam_pos[0];
    float dy = p[1] - cam_pos[1];
    float dz = p[2] - cam_pos[2];
    out[0] = dx * R[0] + dy * R[1] + dz * R[2];
    out[1] = dx * U[0] + dy * U[1] + dz * U[2];
    out[2] = dx * F[0] + dy * F[1] + dz * F[2];
}

/* --- Color & Palette -------------------------------------------------- */

static void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b) {
    h = fmodf(h, 360.0f);
    if (h < 0.0f) h += 360.0f;
    float c = v * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;
    float rf = 0, gf = 0, bf = 0;
    if (h < 60.0f)       { rf = c; gf = x; bf = 0; }
    else if (h < 120.0f) { rf = x; gf = c; bf = 0; }
    else if (h < 180.0f) { rf = 0; gf = c; bf = x; }
    else if (h < 240.0f) { rf = 0; gf = x; bf = c; }
    else if (h < 300.0f) { rf = x; gf = 0; bf = c; }
    else                 { rf = c; gf = 0; bf = x; }
    *r = (int)((rf + m) * 255.0f);
    *g = (int)((gf + m) * 255.0f);
    *b = (int)((bf + m) * 255.0f);
}

static int lit_color(float hue, float value) {
    if (value < 0.0f) value = 0.0f;
    if (value > 1.0f) value = 1.0f;
    int hu = (int)(hue / (360.0f / HUE_STEPS) + 0.5f) % HUE_STEPS;
    if (hu < 0) hu += HUE_STEPS;
    int va = (int)(value * (VALUE_STEPS - 1) + 0.5f);
    if (va < 0) va = 0;
    if (va > VALUE_STEPS - 1) va = VALUE_STEPS - 1;
    return LIT_BASE + hu * VALUE_STEPS + va;
}

/* --- Software Rasterizer Helpers -------------------------------------- */

static inline void fill_scanline(int x0, int x1, int y, uint8_t color) {
    if (y < 0 || y >= HEIGHT) return;
    if (x0 > x1) { int t = x0; x0 = x1; x1 = t; }
    if (x0 < 0) x0 = 0;
    if (x1 >= WIDTH) x1 = WIDTH - 1;
    if (x0 > x1) return;
    memset((uint8_t *)framebuffer() + y * WIDTH + x0, color, (size_t)(x1 - x0 + 1));
}

static void draw_line_2d(int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    for (;;) {
        set_pixel(x0, y0, (uint8_t)color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

static void draw_line_3d(const float *p0, const float *p1, int color) {
    if (p0[2] < 0.1f || p1[2] < 0.1f) return;
    float inv0 = 250.0f / p0[2];
    float inv1 = 250.0f / p1[2];
    int x0 = WIDTH/2 + (int)(p0[0] * inv0);
    int y0 = HEIGHT/2 - (int)(p0[1] * inv0);
    int x1 = WIDTH/2 + (int)(p1[0] * inv1);
    int y1 = HEIGHT/2 - (int)(p1[1] * inv1);

    draw_line_2d(x0, y0, x1, y1, color);
}

static void draw_filled_circle(int cx, int cy, int radius, int color) {
    if (radius < 1) return;
    int y0 = cy - radius, y1 = cy + radius;
    if (y1 < 0 || y0 >= HEIGHT) return;
    if (y0 < 0) y0 = 0;
    if (y1 >= HEIGHT) y1 = HEIGHT - 1;
    int rr = radius * radius;
    for (int y = y0; y <= y1; y++) {
        int dy = y - cy;
        int remain = rr - dy * dy;
        if (remain < 0) continue;
        int dx = (int)sqrtf((float)remain);
        fill_scanline(cx - dx, cx + dx, y, (uint8_t)color);
    }
}

static float edge_xf(float x0, float y0, float x1, float y1, float y) {
    if (y0 == y1) return x0;
    return x0 + (x1 - x0) * (y - y0) / (y1 - y0);
}

static void fill_trianglef(float x0, float y0, float x1, float y1, float x2, float y2, int color) {
    if (y0 > y1) { float t = x0; x0 = x1; x1 = t; t = y0; y0 = y1; y1 = t; }
    if (y1 > y2) { float t = x1; x1 = x2; x2 = t; t = y1; y1 = y2; y2 = t; }
    if (y0 > y1) { float t = x0; x0 = x1; x1 = t; t = y0; y0 = y1; y1 = t; }
    if (y0 == y2) return;

    int sy = (int)ceilf(y0);
    int ey = (int)floorf(y2);
    for (int y = sy; y <= ey; y++) {
        float yy = (float)y;
        float xa = edge_xf(x0, y0, x2, y2, yy);
        float xb = (yy <= y1) ? edge_xf(x0, y0, x1, y1, yy) : edge_xf(x1, y1, x2, y2, yy);
        fill_scanline((int)ceilf(xa), (int)floorf(xb), y, (uint8_t)color);
    }
}

static void fill_quadf(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, int color) {
    fill_trianglef(x0, y0, x1, y1, x2, y2, color);
    fill_trianglef(x0, y0, x2, y2, x3, y3, color);
}

/* --- Robust 3x5 Font Table ------------------------------------------- */

static uint8_t get_char_row(char c, int row) {
    if (row < 0 || row > 4) return 0;
    if (c >= 'A' && c <= 'Z') {
        static const uint8_t font[26][5] = {
            {2, 5, 7, 5, 5}, // A
            {6, 5, 6, 5, 6}, // B
            {3, 4, 4, 4, 3}, // C
            {6, 5, 5, 5, 6}, // D
            {7, 4, 6, 4, 7}, // E
            {7, 4, 6, 4, 4}, // F
            {3, 4, 5, 5, 3}, // G
            {5, 5, 7, 5, 5}, // H
            {7, 2, 2, 2, 7}, // I
            {1, 1, 1, 5, 2}, // J
            {5, 5, 6, 5, 5}, // K
            {4, 4, 4, 4, 7}, // L
            {5, 7, 5, 5, 5}, // M
            {5, 7, 7, 5, 5}, // N
            {2, 5, 5, 5, 2}, // O
            {6, 5, 6, 4, 4}, // P
            {2, 5, 5, 6, 3}, // Q
            {6, 5, 6, 5, 5}, // R
            {3, 4, 2, 1, 6}, // S
            {7, 2, 2, 2, 2}, // T
            {5, 5, 5, 5, 2}, // U
            {5, 5, 5, 5, 2}, // V
            {5, 5, 5, 7, 5}, // W
            {5, 5, 2, 5, 5}, // X
            {5, 5, 2, 2, 2}, // Y
            {7, 1, 2, 4, 7}  // Z
        };
        return font[c - 'A'][row];
    }
    if (c >= '0' && c <= '9') {
        static const uint8_t nums[10][5] = {
            {2, 5, 5, 5, 2}, // 0
            {2, 6, 2, 2, 7}, // 1
            {6, 1, 2, 4, 7}, // 2
            {6, 1, 2, 1, 6}, // 3
            {5, 5, 7, 1, 1}, // 4
            {7, 4, 6, 1, 6}, // 5
            {3, 4, 6, 5, 2}, // 6
            {7, 1, 2, 4, 4}, // 7
            {2, 5, 2, 5, 2}, // 8
            {2, 5, 3, 1, 6}  // 9
        };
        return nums[c - '0'][row];
    }
    if (c == ':') { static const uint8_t s[5] = {0, 2, 0, 2, 0}; return s[row]; }
    if (c == '-') { static const uint8_t s[5] = {0, 0, 7, 0, 0}; return s[row]; }
    if (c == '[') { static const uint8_t s[5] = {6, 4, 4, 4, 6}; return s[row]; }
    if (c == ']') { static const uint8_t s[5] = {3, 1, 1, 1, 3}; return s[row]; }
    if (c == '!') { static const uint8_t s[5] = {2, 2, 2, 0, 2}; return s[row]; }
    return 0;
}

static void draw_char_3x5(int x, int y, char c, int color) {
    for (int row = 0; row < 5; row++) {
        uint8_t bits = get_char_row(c, row);
        if ((bits >> 2) & 1) set_pixel(x + 0, y + row, (uint8_t)color);
        if ((bits >> 1) & 1) set_pixel(x + 1, y + row, (uint8_t)color);
        if ((bits >> 0) & 1) set_pixel(x + 2, y + row, (uint8_t)color);
    }
}

static void draw_string(int x, int y, const char *str, int color) {
    while (*str) {
        draw_char_3x5(x, y, *str, color);
        x += 4;
        str++;
    }
}

/* --- Data Structures -------------------------------------------------- */

typedef struct {
    float pts[4][2];
    float depth;
    int color;
    int is_quad;
} ProjectedFace;

typedef struct {
    float verts[12][3];
    float pos[3];
    float rot[3];
    float rot_vel[3];
    float scale[3];
    float hue;
} Asteroid;

typedef struct {
    float pos[3];
    float vel[3];
    int active;
    float life;
    int color;
} Particle;

typedef struct {
    float pos[3];
    float rot[3];
    float rot_vel[3];
    float scale;
    int active;
    int color;
} Shrapnel;

typedef struct {
    float pos[3];
    float length;
    float speed;
} SpeedLine;

typedef struct { float pos[3]; } Vertex;
typedef struct { int v[4]; int is_quad; int hue_type; } TexturedFace;

/* 20-Face Icosahedron Base */
static const float ICO_BASE_VERTS[12][3] = {
    { -0.525731f, 0.0f, 0.850651f }, { 0.525731f, 0.0f, 0.850651f },
    { -0.525731f, 0.0f, -0.850651f }, { 0.525731f, 0.0f, -0.850651f },
    { 0.0f, 0.850651f, 0.525731f }, { 0.0f, 0.850651f, -0.525731f },
    { 0.0f, -0.850651f, 0.525731f }, { 0.0f, -0.850651f, -0.850651f },
    { 0.850651f, 0.525731f, 0.0f }, { -0.850651f, 0.525731f, 0.0f },
    { 0.850651f, -0.525731f, 0.0f }, { -0.850651f, -0.525731f, 0.0f }
};

static const int ICO_FACES[20][3] = {
    {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
    {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
    {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
    {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
};

/* Hero Ship Geometry */
static const Vertex HERO_VERTS[] = {
    { {  0.0f,  0.0f,  2.2f } }, { { -0.3f, -0.2f,  0.8f } }, { {  0.3f, -0.2f,  0.8f } },
    { {  0.0f,  0.3f,  0.6f } }, { { -1.3f, -0.3f, -1.0f } }, { {  1.3f, -0.3f, -1.0f } },
    { { -0.4f, -0.2f, -1.2f } }, { {  0.4f, -0.2f, -1.2f } }, { {  0.0f,  0.6f, -0.8f } },
    { {  0.0f,  0.2f, -1.1f } }, { {  0.0f, -0.2f, -1.2f } }
};

static const TexturedFace HERO_FACES[] = {
    { { 0, 3, 1, 0 }, 0, 1 }, { { 0, 2, 3, 0 }, 0, 1 }, { { 3, 8, 1, 0 }, 0, 0 },
    { { 3, 2, 8, 0 }, 0, 0 }, { { 1, 8, 4, 0 }, 0, 1 }, { { 2, 5, 8, 0 }, 0, 1 },
    { { 1, 4, 6, 0 }, 0, 2 }, { { 2, 7, 5, 0 }, 0, 2 }, { { 3, 9, 8, 0 }, 0, 3 },
    { { 4, 8, 6, 0 }, 0, 0 }, { { 5, 6, 8, 0 }, 0, 0 }, { { 0, 1, 6, 2 }, 1, 0 },
    { { 6, 8, 7, 10 }, 1, 4 }
};

/* Enemy Fighter Geometry */
static const Vertex ENEMY_VERTS[] = {
    { {  0.0f,  0.0f, -1.6f } }, { { -0.9f, -0.2f,  0.8f } }, { {  0.9f, -0.2f,  0.8f } },
    { {  0.0f,  0.4f,  0.2f } }, { { -0.3f, -0.2f,  1.1f } }, { {  0.3f, -0.2f,  1.1f } },
    { {  0.0f,  0.6f, -0.4f } }
};

static const TexturedFace ENEMY_FACES[] = {
    { { 0, 6, 1, 0 }, 0, 6 }, { { 0, 2, 6, 0 }, 0, 6 }, { { 6, 3, 1, 0 }, 0, 2 },
    { { 6, 2, 3, 0 }, 0, 2 }, { { 1, 3, 4, 0 }, 0, 6 }, { { 2, 5, 3, 0 }, 0, 6 },
    { { 0, 1, 4, 0 }, 0, 9 }, { { 0, 5, 2, 0 }, 0, 9 }, { { 4, 3, 5, 0 }, 0, 4 }
};

/* Detailed 3D Missile Geometry */
static const Vertex MISSILE_VERTS[] = {
    { {  0.0f,  0.0f,  0.8f } },
    { { -0.15f,-0.15f, 0.2f } },
    { {  0.15f,-0.15f, 0.2f } },
    { {  0.15f, 0.15f, 0.2f } },
    { { -0.15f, 0.15f, 0.2f } },
    { {  0.0f,  0.0f, -0.6f } }
};
static const TexturedFace MISSILE_FACES[] = {
    { { 0, 1, 2, 0 }, 0, 1 }, { { 0, 2, 3, 0 }, 0, 1 },
    { { 0, 3, 4, 0 }, 0, 1 }, { { 0, 4, 1, 0 }, 0, 1 },
    { { 1, 5, 2, 0 }, 0, 9 }, { { 2, 5, 3, 0 }, 0, 9 },
    { { 3, 5, 4, 0 }, 0, 9 }, { { 4, 5, 1, 0 }, 0, 9 }
};

static float stars[STAR_COUNT][3];
static SpeedLine speed_lines[SPEEDLINE_COUNT];
static Asteroid asteroids[ASTEROID_COUNT];
static Particle particles[PARTICLE_COUNT];
static Shrapnel shrapnels[SHRAPNEL_COUNT];
static ProjectedFace render_queue[MAX_FACES];
static int queue_count = 0;

static float randf(void) { return (float)rand() / (float)RAND_MAX; }

static void respawn_asteroid(Asteroid *a, float min_z) {
    float angle = randf() * 6.28318f;
    float dist = 10.0f + randf() * 25.0f;
    a->pos[0] = cosf(angle) * dist;
    a->pos[1] = sinf(angle) * dist;
    a->pos[2] = min_z + randf() * 60.0f;

    a->rot[0] = randf() * 6.28f; a->rot[1] = randf() * 6.28f; a->rot[2] = randf() * 6.28f;
    a->rot_vel[0] = (randf() - 0.5f) * 1.5f;
    a->rot_vel[1] = (randf() - 0.5f) * 1.5f;
    a->rot_vel[2] = (randf() - 0.5f) * 1.5f;

    a->scale[0] = randf() * 1.8f + 0.6f;
    a->scale[1] = randf() * 1.8f + 0.6f;
    a->scale[2] = randf() * 1.8f + 0.6f;
    a->hue = (15.0f + randf() * 35.0f); /* More color variety */

    for (int i = 0; i < 12; i++) {
        float noise = 0.65f + randf() * 0.7f;
        a->verts[i][0] = ICO_BASE_VERTS[i][0] * noise;
        a->verts[i][1] = ICO_BASE_VERTS[i][1] * noise;
        a->verts[i][2] = ICO_BASE_VERTS[i][2] * noise;
    }
}

static inline void clear_particles(void) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].active = 0;
        particles[i].life = 0.0f;
    }
    for (int i = 0; i < SHRAPNEL_COUNT; i++) {
        shrapnels[i].active = 0;
    }
}

static void trigger_explosion(const float *pos, int color) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].pos[0] = pos[0];
        particles[i].pos[1] = pos[1];
        particles[i].pos[2] = pos[2];
        particles[i].vel[0] = (randf() - 0.5f) * 22.0f;
        particles[i].vel[1] = (randf() - 0.5f) * 22.0f;
        particles[i].vel[2] = (randf() - 0.5f) * 22.0f;
        particles[i].active = 1;
        particles[i].life = 1.2f;
        particles[i].color = color;
    }
    for (int i = 0; i < SHRAPNEL_COUNT; i++) {
        shrapnels[i].pos[0] = pos[0];
        shrapnels[i].pos[1] = pos[1];
        shrapnels[i].pos[2] = pos[2];
        shrapnels[i].rot[0] = randf() * 6.28f; shrapnels[i].rot[1] = randf() * 6.28f;
        shrapnels[i].rot_vel[0] = (randf() - 0.5f) * 7.0f;
        shrapnels[i].rot_vel[1] = (randf() - 0.5f) * 7.0f;
        shrapnels[i].scale = randf() * 0.6f + 0.2f;
        shrapnels[i].active = 1;
        shrapnels[i].color = color;
    }
}

static void init_scene(void) {
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i][0] = (randf() - 0.5f) * 160.0f;
        stars[i][1] = (randf() - 0.5f) * 160.0f;
        stars[i][2] = randf() * 120.0f;
    }
    for (int i = 0; i < SPEEDLINE_COUNT; i++) {
        speed_lines[i].pos[0] = (randf() - 0.5f) * 25.0f;
        speed_lines[i].pos[1] = (randf() - 0.5f) * 18.0f;
        speed_lines[i].pos[2] = randf() * 50.0f;
        speed_lines[i].length = 3.0f + randf() * 5.0f;
        speed_lines[i].speed = 30.0f + randf() * 20.0f;
    }
    for (int i = 0; i < ASTEROID_COUNT; i++) {
        respawn_asteroid(&asteroids[i], 0.0f);
    }
}

/* --- Human Cockpit Frame with High-Detail HUD Styling --- */

static void draw_human_cockpit(float lock_x, float lock_y, int locked) {
    fill_trianglef(0, 0, 45, 0, 0, 180, 7);
    fill_trianglef(WIDTH, 0, WIDTH - 45, 0, WIDTH, 180, 7);
    fill_quadf(0, 0, WIDTH, 0, WIDTH, 14, 0, 14, 7);

    draw_line_2d(45, 0, 105, 180, 7);
    draw_line_2d(WIDTH - 45, 0, WIDTH - 105, 180, 7);

    int rx = (int)lock_x, ry = (int)lock_y;
    int ret_col = locked ? 2 : 3;

    if (rx >= 20 && rx < WIDTH - 20 && ry >= 20 && ry < HEIGHT - 20) {
        draw_line_2d(rx - 8, ry, rx - 3, ry, ret_col);
        draw_line_2d(rx + 3, ry, rx + 8, ry, ret_col);
        draw_line_2d(rx, ry - 8, rx, ry - 3, ret_col);
        draw_line_2d(rx, ry + 3, rx, ry + 8, ret_col);
    }
}

/* --- High-Fidelity Photorealistic Gas Giant Planet --- */

static void draw_background_planet(const float *cam_pos, const float *R, const float *U, const float *F) {
    float planet_world[3] = { 45.0f, 25.0f, 130.0f };
    float cp[3];
    world_to_cam(cp, planet_world, cam_pos, R, U, F);

    if (cp[2] < 2.0f) return;

    float invz = 250.0f / cp[2];
    int cx = WIDTH/2 + (int)(cp[0] * invz);
    int cy = HEIGHT/2 - (int)(cp[1] * invz);
    int r = (int)(28.0f * (100.0f / cp[2]));
    if (r < 5) r = 5;

    /* Atmospheric glow layers for depth */
    for (int i = 3; i >= 1; i--) {
        int glow_r = r + i * 2;
        int alpha = 14 - i * 3;
        if (alpha > 0) {
            for (int angle = 0; angle < 360; angle += 10) {
                float rad = (float)angle * 0.0174533f;
                int px = cx + (int)(cosf(rad) * glow_r);
                int py = cy + (int)(sinf(rad) * glow_r * 0.4f);
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    set_pixel(px, py, 14);
                }
            }
        }
    }

    /* Main planet body with shading */
    draw_filled_circle(cx, cy, r, 12);
    draw_filled_circle(cx - r/6, cy - r/6, r - r/6, 13);
    
    /* Enhanced highlights */
    draw_filled_circle(cx - r/5, cy - r/4, r - r/4, 14);
    draw_filled_circle(cx - r/8, cy - r/7, r - r/6, 13);

    /* Detailed ring system with multiple layers */
    int ring_span = r * 2;
    for (int rx = -ring_span; rx <= ring_span; rx++) {
        int ry = rx / 3;
        if (abs(rx) > r * 2 / 3) {
            int px = cx + rx;
            int py = cy + ry;
            if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                set_pixel(px, py, 14);
                if (py + 1 < HEIGHT) set_pixel(px, py + 1, 15);
            }
        }
    }
    
    /* Inner ring detail */
    for (int rx = -r; rx <= r; rx++) {
        int ry = rx / 4;
        if (abs(rx) > r / 2 && abs(rx) < r) {
            int px = cx + rx;
            int py = cy + ry - 1;
            if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                set_pixel(px, py, 13);
            }
        }
    }

    /* Moon rendering with enhanced detail */
    float moon_world[3] = { planet_world[0] - 25.0f, planet_world[1] - 8.0f, planet_world[2] - 15.0f };
    float m_cp[3];
    world_to_cam(m_cp, moon_world, cam_pos, R, U, F);
    if (m_cp[2] > 2.0f) {
        float m_invz = 250.0f / m_cp[2];
        int mcx = WIDTH/2 + (int)(m_cp[0] * m_invz);
        int mcy = HEIGHT/2 - (int)(m_cp[1] * m_invz);
        int m_radius = 4;
        draw_filled_circle(mcx, mcy, m_radius, 8);
        draw_filled_circle(mcx - 1, mcy - 1, m_radius - 1, 11);
    }
}


/* --- Enhanced HUD & Cockpit Display ---------------------------------------------- */

static inline void draw_hud_frame(void) {
    /* Minimal clean UI - just a subtle border */
    draw_line_2d(8, 8, WIDTH - 9, 8, 3);
    draw_line_2d(8, HEIGHT - 9, WIDTH - 9, HEIGHT - 9, 3);
    draw_line_2d(8, 8, 8, HEIGHT - 9, 3);
    draw_line_2d(WIDTH - 9, 8, WIDTH - 9, HEIGHT - 9, 3);
}


static void render_subtitles(float timeline) {
    const char *speaker = "";
    const char *msg = "";

    if      (timeline >= 0.5f  && timeline < 3.0f)  { speaker = "[BASE COMMAND]";   msg = "VANGUARD-1, APPROACHING NEXUS SECTOR..."; }
    else if (timeline >= 3.0f  && timeline < 6.0f)  { speaker = "[VANGUARD-1]";     msg = "COPY THAT. ALL SYSTEMS GREEN."; }
    else if (timeline >= 6.0f  && timeline < 9.0f)  { speaker = "[BASE COMMAND]";   msg = "WARNING! UNIDENTIFIED CONTACTS!"; }
    else if (timeline >= 9.0f  && timeline < 12.0f) { speaker = "[XENOS ALPHA]";    msg = "KRZZZT-KK! HUMAN VESSEL DETECTED!"; }
    else if (timeline >= 12.0f && timeline < 15.0f) { speaker = "[VANGUARD-1]";     msg = "EVADING! WEAPONS LIVE! ENGAGING!"; }
    else if (timeline >= 15.0f && timeline < 18.0f) { speaker = "[BASE COMMAND]";   msg = "VANGUARD, INCOMING FIRE! EVASIVE!"; }
    else if (timeline >= 18.0f && timeline < 21.0f) { speaker = "[VANGUARD-1]";     msg = "HIT! PORT WING COMPROMISED!"; }
    else if (timeline >= 21.0f && timeline < 24.0f) { speaker = "[XENOS ALPHA]";    msg = "KILL IT! KILL IT NOW!"; }
    else if (timeline >= 24.0f && timeline < 27.0f) { speaker = "[VANGUARD-1]";     msg = "FIRST CONTACT DOWN! TWO MORE!"; }
    else if (timeline >= 27.0f && timeline < 30.0f) { speaker = "[BASE COMMAND]";   msg = "EXCELLENT SHOOTING, VANGUARD!"; }
    else if (timeline >= 30.0f && timeline < 33.0f) { speaker = "[XENOS BETA]";     msg = "VRZZK-VZZK! WE WILL NOT FALL!"; }
    else if (timeline >= 33.0f && timeline < 36.0f) { speaker = "[VANGUARD-1]";     msg = "SECOND TARGET NEUTRALIZED!"; }
    else if (timeline >= 36.0f && timeline < 39.0f) { speaker = "[BASE COMMAND]";   msg = "ONE HOSTILE REMAINS. FINAL PUSH!"; }
    else if (timeline >= 39.0f && timeline < 42.0f) { speaker = "[XENOS GAMMA]";    msg = "THIS ENDS HERE, HUMAN!"; }
    else if (timeline >= 42.0f && timeline < 45.0f) { speaker = "[VANGUARD-1]";     msg = "THREAT ELIMINATED! ALL CLEAR."; }
    else if (timeline >= 45.0f && timeline < 48.0f) { speaker = "[BASE COMMAND]";   msg = "STELLAR WORK. INITIATING QUANTUM JUMP."; }
    else if (timeline >= 48.0f && timeline < 51.0f) { speaker = "[VANGUARD-1]";     msg = "ENGAGING HYPERDRIVE... SEE YOU HOME."; }
    else if (timeline >= 51.0f && timeline < 60.0f) { speaker = "[BASE COMMAND]";   msg = "WELCOME BACK, VANGUARD-1. MISSION SUCCESS."; }

    if (msg[0] != 0) {
        fill_quadf(15, HEIGHT - 22, WIDTH - 15, HEIGHT - 22, WIDTH - 15, HEIGHT - 8, 15, HEIGHT - 8, 7);
        draw_string(20, HEIGHT - 19, speaker, 3);
        draw_string(20 + (int)strlen(speaker) * 4 + 4, HEIGHT - 19, msg, 1);
    }
}


int main(void) {
    if (!screen_open(WIDTH, HEIGHT, pixel_indexed8, "Narrative 3D Space Engine"))
        return 1;

    set_palette(0, 1, 2, 6);       // Deep space ambient
    set_palette(1, 255, 255, 255); // Star white
    set_palette(2, 255, 40, 30);   // High-intensity red
    set_palette(3, 0, 240, 255);   // Cyan HUD
    set_palette(4, 255, 170, 40);  // Plasma flame orange
    set_palette(5, 255, 250, 140); // Ion yellow
    set_palette(6, 255, 20, 40);   // Enemy red - BRIGHT and visible
    set_palette(7, 10, 14, 22);    // Cockpit carbon framing
    set_palette(8, 220, 230, 245); // Polished titanium
    set_palette(9, 255, 100, 20);  // Engine glow - orange-red
    set_palette(10, 0, 190, 255);  // High-gloss stripe
    set_palette(11, 120, 210, 255);// Cockpit canopy glass
    set_palette(12, 170, 110, 50); // Planet crust base
    set_palette(13, 230, 170, 100);// Planet upper clouds
    set_palette(14, 255, 210, 150);// Atmospheric rim highlight

    for (int hu = 0; hu < HUE_STEPS; hu++) {
        float hue = hu * (360.0f / HUE_STEPS);
        for (int va = 0; va < VALUE_STEPS; va++) {
            float v = 0.05f + 0.95f * ((float)va / (VALUE_STEPS - 1));
            int r, g, b;
            hsv_to_rgb(hue, 0.7f, v, &r, &g, &b);
            set_palette(LIT_BASE + hu * VALUE_STEPS + va, (uint8_t)r, (uint8_t)g, (uint8_t)b);
        }
    }

    init_scene();

    float light_dir[3] = { 0.5f, 0.65f, -0.6f };
    vec3_normalize(light_dir);

    double last_time = seconds();
    float fps_display = 60.0f;

    while (!should_close()) {
        double current_time = seconds();
        float dt = (float)(current_time - last_time);
        if (dt <= 0.0001f) dt = 0.001f;
        last_time = current_time;

        fps_display = fps_display * 0.9f + (1.0f / dt) * 0.1f;

        float timeline = fmodf((float)current_time, 60.0f);

        memset(framebuffer(), 0, framebuffer_size());

        float ship_pos[3] = { sinf(timeline * 0.8f) * 2.5f, cosf(timeline * 0.6f) * 1.2f, 0.0f };
        float ship_rot[3] = { -ship_pos[1] * 0.15f, ship_pos[0] * 0.1f, -ship_pos[0] * 0.2f };

        float enemy_positions[ENEMY_COUNT][3] = {
            { ship_pos[0] - 2.0f, ship_pos[1] + 0.8f, ship_pos[2] + 16.0f },
            { ship_pos[0] + 2.5f, ship_pos[1] - 0.5f, ship_pos[2] + 18.0f },
            { ship_pos[0] + 0.5f, ship_pos[1] + 2.2f, ship_pos[2] + 21.0f }
        };
        float enemy_destruct_times[ENEMY_COUNT] = { 27.5f, 35.5f, 44.5f };

        int enemy_alive[ENEMY_COUNT];
        for (int i = 0; i < ENEMY_COUNT; i++) {
            enemy_alive[i] = (timeline < enemy_destruct_times[i]);
            if (timeline >= enemy_destruct_times[i] - 0.1f && timeline <= enemy_destruct_times[i] + 0.1f) {
                trigger_explosion(enemy_positions[i], (i == 0) ? 4 : ((i == 1) ? 5 : 2));
            }
        }

        float enemy_fire_pos[3] = { enemy_positions[0][0], enemy_positions[0][1], enemy_positions[0][2] };
        float player_wing_impact[3] = { ship_pos[0] - 1.1f, ship_pos[1] - 0.3f, ship_pos[2] - 0.8f };
        float hit_missile_pos[3];

        if (timeline >= 8.0f && timeline < 15.0f) {
            float h_t = (timeline - 8.0f) / 7.0f;
            hit_missile_pos[0] = enemy_fire_pos[0] + (player_wing_impact[0] - enemy_fire_pos[0]) * h_t;
            hit_missile_pos[1] = enemy_fire_pos[1] + (player_wing_impact[1] - enemy_fire_pos[1]) * h_t;
            hit_missile_pos[2] = enemy_fire_pos[2] + (player_wing_impact[2] - enemy_fire_pos[2]) * h_t;
        }

        if (timeline >= 14.9f && timeline <= 15.1f) {
            trigger_explosion(player_wing_impact, 4);
        }

        int active_target_idx = 0;
        if (timeline >= 35.5f) active_target_idx = 2;
        else if (timeline >= 27.5f) active_target_idx = 1;

        float counter_missile_pos[3] = { ship_pos[0], ship_pos[1] - 0.5f, ship_pos[2] + 1.0f };
        float *current_target_pos = enemy_positions[active_target_idx];

        float counter_start_t = (active_target_idx == 0) ? 18.0f : ((active_target_idx == 1) ? 29.0f : 39.0f);
        if (timeline >= counter_start_t && timeline < enemy_destruct_times[active_target_idx]) {
            float end_t = enemy_destruct_times[active_target_idx];
            float m_t = (timeline - counter_start_t) / (end_t - counter_start_t);
            if (m_t > 1.0f) m_t = 1.0f;
            counter_missile_pos[0] = ship_pos[0] + (current_target_pos[0] - ship_pos[0]) * m_t;
            counter_missile_pos[1] = ship_pos[1] + (current_target_pos[1] - ship_pos[1]) * m_t + sinf(m_t * 3.14f) * 1.5f;
            counter_missile_pos[2] = ship_pos[2] + (current_target_pos[2] - ship_pos[2]) * m_t;
        }

        float shake[2] = { 0.0f, 0.0f };
        if (timeline >= 14.9f && timeline <= 16.5f) {
            shake[0] = (randf() - 0.5f) * 0.7f;
            shake[1] = (randf() - 0.5f) * 0.7f;
        } else if (timeline >= 50.0f) {
            shake[0] = (randf() - 0.5f) * 0.9f;
            shake[1] = (randf() - 0.5f) * 0.9f;
        }

        float cam_pos[3], cam_target[3];
        float cam_roll = 0.0f;

        float p_chase[3]  = { ship_pos[0] + sinf(timeline*0.5f)*6.5f, ship_pos[1] + 1.8f, ship_pos[2] - 6.5f };
        float t_chase[3]  = { ship_pos[0], ship_pos[1], ship_pos[2] + 1.0f };

        float p_hit[3]    = { ship_pos[0] - 4.5f, ship_pos[1] + 1.2f, ship_pos[2] - 0.5f };
        float t_hit[3]    = { ship_pos[0] - 1.1f, ship_pos[1] - 0.3f, ship_pos[2] - 0.8f };

        float p_cockpit[3]= { ship_pos[0], ship_pos[1] + 0.25f, ship_pos[2] + 0.6f };
        float t_cockpit[3]= { ship_pos[0], ship_pos[1], ship_pos[2] + 20.0f };

        float p_destroy1[3] = { enemy_positions[0][0] + 3.0f, enemy_positions[0][1] + 1.5f, enemy_positions[0][2] - 4.0f };
        float t_destroy1[3] = { enemy_positions[0][0], enemy_positions[0][1], enemy_positions[0][2] };

        float p_destroy2[3] = { enemy_positions[1][0] + 3.0f, enemy_positions[1][1] + 1.5f, enemy_positions[1][2] - 4.0f };
        float t_destroy2[3] = { enemy_positions[1][0], enemy_positions[1][1], enemy_positions[1][2] };

        float p_destroy3[3] = { enemy_positions[2][0] + 3.0f, enemy_positions[2][1] + 1.5f, enemy_positions[2][2] - 4.0f };
        float t_destroy3[3] = { enemy_positions[2][0], enemy_positions[2][1], enemy_positions[2][2] };

        float p_warp[3]   = { ship_pos[0], ship_pos[1] + 1.0f, ship_pos[2] - 7.0f };
        float t_warp[3]   = { ship_pos[0], ship_pos[1], ship_pos[2] + 10.0f };

        if (timeline < 3.0f) {
            /* Opening: Dramatic zoom towards planet */
            float zoom_in = timeline / 3.0f;
            vec3_lerp(cam_pos, p_chase, p_chase, 1.0f);
            cam_pos[2] -= zoom_in * 8.0f;
            vec3_lerp(cam_target, t_chase, t_chase, 1.0f);
            cam_target[2] += zoom_in * 15.0f;
        } else if (timeline < 7.0f) {
            /* Pursuit: Dynamic circular motion around ship */
            float orbit_t = (timeline - 3.0f) / 4.0f;
            float orbit_angle = orbit_t * 3.14f * 0.5f;
            vec3_lerp(cam_pos, p_chase, p_chase, 1.0f);
            cam_pos[0] += sinf(orbit_angle) * 5.0f;
            cam_pos[2] -= cosf(orbit_angle) * 3.0f;
            vec3_lerp(cam_target, t_chase, t_chase, 1.0f);
            cam_roll = sinf(timeline * 0.5f) * 0.15f;
        } else if (timeline < 11.0f) {
            /* Incoming fire: Camera banks hard to the side */
            float alpha = (timeline - 7.0f) / 4.0f;
            vec3_lerp(cam_pos, p_chase, p_hit, alpha);
            vec3_lerp(cam_target, t_chase, t_hit, alpha);
            cam_roll = lerpf(0.0f, -0.25f, alpha);
            cam_pos[1] += sinf(alpha * 3.14f) * 0.8f;
        } else if (timeline < 15.0f) {
            vec3_lerp(cam_pos, p_hit, p_hit, 1.0f);
            vec3_lerp(cam_target, t_hit, t_hit, 1.0f);
            cam_roll = -0.15f;
        } else if (timeline < 18.0f) {
            /* Transition to cockpit: Dramatic pull into ship */
            float alpha = (timeline - 15.0f) / 3.0f;
            vec3_lerp(cam_pos, p_hit, p_cockpit, alpha);
            vec3_lerp(cam_target, t_hit, t_cockpit, alpha);
            cam_roll = lerpf(-0.25f, ship_rot[2] * 0.5f, alpha);
            cam_pos[2] -= alpha * 2.0f;
        } else if (timeline < 24.0f) {
            /* Cockpit view: Intense targeting sequences */
            vec3_lerp(cam_pos, p_cockpit, p_cockpit, 1.0f);
            vec3_lerp(cam_target, t_cockpit, t_cockpit, 1.0f);
            cam_roll = ship_rot[2] * 0.5f + sinf((timeline - 18.0f) * 2.0f) * 0.08f;
        } else if (timeline < 27.5f) {
            float alpha = (timeline - 24.0f) / 3.5f;
            vec3_lerp(cam_pos, p_cockpit, p_destroy1, alpha);
            vec3_lerp(cam_target, t_cockpit, t_destroy1, alpha);
        } else if (timeline < 29.0f) {
            float alpha = (timeline - 27.5f) / 1.5f;
            vec3_lerp(cam_pos, p_destroy1, p_chase, alpha);
            vec3_lerp(cam_target, t_destroy1, t_chase, alpha);
        } else if (timeline < 34.0f) {
            float alpha = (timeline - 29.0f) / 5.0f;
            vec3_lerp(cam_pos, p_chase, p_destroy2, alpha);
            vec3_lerp(cam_target, t_chase, t_destroy2, alpha);
        } else if (timeline < 35.5f) {
            float alpha = (timeline - 34.0f) / 1.5f;
            vec3_lerp(cam_pos, p_destroy2, p_chase, alpha);
            vec3_lerp(cam_target, t_destroy2, t_chase, alpha);
        } else if (timeline < 43.0f) {
            float alpha = (timeline - 35.5f) / 7.5f;
            vec3_lerp(cam_pos, p_chase, p_destroy3, alpha);
            vec3_lerp(cam_target, t_chase, t_destroy3, alpha);
        } else if (timeline < 45.0f) {
            float alpha = (timeline - 43.0f) / 2.0f;
            vec3_lerp(cam_pos, p_destroy3, p_warp, alpha);
            vec3_lerp(cam_target, t_destroy3, t_warp, alpha);
        } else if (timeline < 50.0f) {
            vec3_lerp(cam_pos, p_warp, p_warp, 1.0f);
            vec3_lerp(cam_target, t_warp, t_warp, 1.0f);
        } else {
            /* Cinematic hyperspace jump effect */
            clear_particles();
            float warp_t = timeline - 50.0f;
            if (warp_t > 10.0f) warp_t = 10.0f;
            float warp_progress = warp_t / 10.0f;
            
            /* Camera pulls back and banks while jumping to lightspeed */
            float bank_angle = warp_progress * 3.14f * 0.4f;
            cam_pos[0] = p_warp[0] + sinf(bank_angle) * (2.0f + warp_progress * 8.0f);
            cam_pos[1] = p_warp[1] + warp_progress * 1.5f;
            cam_pos[2] = p_warp[2] - (6.0f + warp_progress * 25.0f);
            
            cam_target[0] = ship_pos[0];
            cam_target[1] = ship_pos[1];
            cam_target[2] = ship_pos[2] + (15.0f + warp_progress * 150.0f);
            
            cam_roll = sinf(warp_progress * 3.14f) * 0.4f;
            ship_pos[2] += warp_t * warp_t * 11.0f;
        }

        cam_pos[0] += shake[0];
        cam_pos[1] += shake[1];

        float R[3], U[3], F[3];
        calc_lookat_roll(cam_pos, cam_target, cam_roll, R, U, F);

        if (timeline < 50.0f) {
            draw_background_planet(cam_pos, R, U, F);
        }

        float star_speed = (timeline >= 50.0f) ? 150.0f : 20.0f;
        for (int i = 0; i < STAR_COUNT; i++) {
            stars[i][2] -= star_speed * dt;
            if (stars[i][2] < 1.0f) stars[i][2] += 120.0f;

            float cp0[3], cp1[3];
            world_to_cam(cp0, stars[i], cam_pos, R, U, F);

            if (cp0[2] > 0.1f) {
                if (timeline >= 50.0f) {
                    float p_back[3] = { stars[i][0], stars[i][1], stars[i][2] + 16.0f };
                    world_to_cam(cp1, p_back, cam_pos, R, U, F);
                    draw_line_3d(cp0, cp1, (i % 3 == 0) ? 3 : 1);
                } else {
                    float invz = 250.0f / cp0[2];
                    int sx = WIDTH/2 + (int)(cp0[0] * invz);
                    int sy = HEIGHT/2 - (int)(cp0[1] * invz);
                    if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT) {
                        set_pixel(sx, sy, (i % 5 == 0) ? 3 : 1);
                    }
                }
            }
        }

        for (int i = 0; i < SPEEDLINE_COUNT; i++) {
            speed_lines[i].pos[2] -= speed_lines[i].speed * dt;
            if (speed_lines[i].pos[2] < cam_pos[2]) speed_lines[i].pos[2] += 50.0f;

            float p0[3] = { cam_pos[0] + speed_lines[i].pos[0], cam_pos[1] + speed_lines[i].pos[1], speed_lines[i].pos[2] };
            float p1[3] = { p0[0], p0[1], p0[2] + speed_lines[i].length };
            float cp0[3], cp1[3];
            world_to_cam(cp0, p0, cam_pos, R, U, F);
            world_to_cam(cp1, p1, cam_pos, R, U, F);
            draw_line_3d(cp0, cp1, (timeline >= 50.0f) ? 3 : 1);
        }

        queue_count = 0;

        if (timeline < 50.0f) {
            for (int i = 0; i < ASTEROID_COUNT; i++) {
                asteroids[i].pos[2] -= 10.0f * dt;
                if (asteroids[i].pos[2] < cam_pos[2] - 10.0f) respawn_asteroid(&asteroids[i], cam_pos[2] + 45.0f);

                asteroids[i].rot[0] += asteroids[i].rot_vel[0] * dt;
                asteroids[i].rot[1] += asteroids[i].rot_vel[1] * dt;

                float world_verts[12][3];
                for (int v = 0; v < 12; v++) {
                    world_verts[v][0] = asteroids[i].verts[v][0] * asteroids[i].scale[0];
                    world_verts[v][1] = asteroids[i].verts[v][1] * asteroids[i].scale[1];
                    world_verts[v][2] = asteroids[i].verts[v][2] * asteroids[i].scale[2];
                    rotate_vec3(world_verts[v], asteroids[i].rot[0], asteroids[i].rot[1], asteroids[i].rot[2]);
                    world_verts[v][0] += asteroids[i].pos[0];
                    world_verts[v][1] += asteroids[i].pos[1];
                    world_verts[v][2] += asteroids[i].pos[2];
                }

                for (int f = 0; f < 20; f++) {
                    float c_verts[3][3];
                    for (int k = 0; k < 3; k++) world_to_cam(c_verts[k], world_verts[ICO_FACES[f][k]], cam_pos, R, U, F);

                    if (c_verts[0][2] < 0.2f || c_verts[1][2] < 0.2f || c_verts[2][2] < 0.2f) continue;

                    float u_v[3] = { c_verts[1][0]-c_verts[0][0], c_verts[1][1]-c_verts[0][1], c_verts[1][2]-c_verts[0][2] };
                    float v_v[3] = { c_verts[2][0]-c_verts[0][0], c_verts[2][1]-c_verts[0][1], c_verts[2][2]-c_verts[0][2] };
                    float norm[3];
                    vec3_cross(norm, u_v, v_v);
                    vec3_normalize(norm);

                    float view[3] = { -c_verts[0][0], -c_verts[0][1], -c_verts[0][2] };
                    if (vec3_dot(norm, view) <= 0.0f) continue;

                    float dot = vec3_dot(norm, light_dir);
                    float rim = 0.15f * (1.0f - fabs(vec3_dot(norm, view)));
                    float val = 0.05f + (dot > 0.0f ? dot * 0.90f : 0.0f) + rim * 0.15f;

                    if (queue_count < MAX_FACES) {
                        ProjectedFace *face = &render_queue[queue_count++];
                        face->depth = (c_verts[0][2] + c_verts[1][2] + c_verts[2][2]) / 3.0f;
                        face->is_quad = 0;
                        /* Enhanced color with more saturation */
                        int hue_var = asteroids[i].hue + ((i % 3) * 20);
                        face->color = lit_color(hue_var, val * 1.1f);
                        for (int k = 0; k < 3; k++) {
                            float invz = 250.0f / c_verts[k][2];
                            face->pts[k][0] = WIDTH/2 + c_verts[k][0] * invz;
                            face->pts[k][1] = HEIGHT/2 - c_verts[k][1] * invz;
                        }
                    }
                }
            }
        }

        for (int e = 0; e < ENEMY_COUNT; e++) {
            if (!enemy_alive[e]) continue;

            for (int f = 0; f < 9; f++) {
                float c_verts[4][3];
                int n_verts = ENEMY_FACES[f].is_quad ? 4 : 3;

                for (int k = 0; k < n_verts; k++) {
                    float temp[3] = { ENEMY_VERTS[ENEMY_FACES[f].v[k]].pos[0], ENEMY_VERTS[ENEMY_FACES[f].v[k]].pos[1], ENEMY_VERTS[ENEMY_FACES[f].v[k]].pos[2] };
                    temp[0] += enemy_positions[e][0]; temp[1] += enemy_positions[e][1]; temp[2] += enemy_positions[e][2];
                    world_to_cam(c_verts[k], temp, cam_pos, R, U, F);
                }

                if (c_verts[0][2] < 0.2f || c_verts[1][2] < 0.2f || c_verts[2][2] < 0.2f) continue;

                if (queue_count < MAX_FACES) {
                    ProjectedFace *face = &render_queue[queue_count++];
                    face->depth = (c_verts[0][2] + c_verts[1][2] + c_verts[2][2]) / 3.0f;
                    face->is_quad = ENEMY_FACES[f].is_quad;
                    /* Use simple palette colors like starship.c - faces have hue_type already set */
                    face->color = ENEMY_FACES[f].hue_type;
                    for (int k = 0; k < n_verts; k++) {
                        float invz = 250.0f / c_verts[k][2];
                        face->pts[k][0] = WIDTH/2 + c_verts[k][0] * invz;
                        face->pts[k][1] = HEIGHT/2 - c_verts[k][1] * invz;
                    }
                }
            }
        }

        if (timeline >= 8.0f && timeline < 15.0f) {
            for (int f = 0; f < 8; f++) {
                float c_verts[4][3];
                int n_verts = MISSILE_FACES[f].is_quad ? 4 : 3;
                for (int k = 0; k < n_verts; k++) {
                    float temp[3] = { MISSILE_VERTS[MISSILE_FACES[f].v[k]].pos[0], MISSILE_VERTS[MISSILE_FACES[f].v[k]].pos[1], MISSILE_VERTS[MISSILE_FACES[f].v[k]].pos[2] };
                    temp[0] += hit_missile_pos[0]; temp[1] += hit_missile_pos[1]; temp[2] += hit_missile_pos[2];
                    world_to_cam(c_verts[k], temp, cam_pos, R, U, F);
                }
                if (c_verts[0][2] < 0.2f || c_verts[1][2] < 0.2f || c_verts[2][2] < 0.2f) continue;

                if (queue_count < MAX_FACES) {
                    ProjectedFace *face = &render_queue[queue_count++];
                    face->depth = (c_verts[0][2] + c_verts[1][2] + c_verts[2][2]) / 3.0f;
                    face->is_quad = MISSILE_FACES[f].is_quad;
                    face->color = 2;
                    for (int k = 0; k < n_verts; k++) {
                        float invz = 250.0f / c_verts[k][2];
                        face->pts[k][0] = WIDTH/2 + c_verts[k][0] * invz;
                        face->pts[k][1] = HEIGHT/2 - c_verts[k][1] * invz;
                    }
                }
            }
        }

        if (timeline >= counter_start_t && timeline < enemy_destruct_times[active_target_idx]) {
            for (int f = 0; f < 8; f++) {
                float c_verts[4][3];
                int n_verts = MISSILE_FACES[f].is_quad ? 4 : 3;
                for (int k = 0; k < n_verts; k++) {
                    float temp[3] = { MISSILE_VERTS[MISSILE_FACES[f].v[k]].pos[0], MISSILE_VERTS[MISSILE_FACES[f].v[k]].pos[1], MISSILE_VERTS[MISSILE_FACES[f].v[k]].pos[2] };
                    temp[0] += counter_missile_pos[0]; temp[1] += counter_missile_pos[1]; temp[2] += counter_missile_pos[2];
                    world_to_cam(c_verts[k], temp, cam_pos, R, U, F);
                }
                if (c_verts[0][2] < 0.2f || c_verts[1][2] < 0.2f || c_verts[2][2] < 0.2f) continue;

                if (queue_count < MAX_FACES) {
                    ProjectedFace *face = &render_queue[queue_count++];
                    face->depth = (c_verts[0][2] + c_verts[1][2] + c_verts[2][2]) / 3.0f;
                    face->is_quad = MISSILE_FACES[f].is_quad;
                    face->color = 5;
                    for (int k = 0; k < n_verts; k++) {
                        float invz = 250.0f / c_verts[k][2];
                        face->pts[k][0] = WIDTH/2 + c_verts[k][0] * invz;
                        face->pts[k][1] = HEIGHT/2 - c_verts[k][1] * invz;
                    }
                }
            }
        }

        if (timeline >= 15.0f) {
            float wing_local[3] = { -1.1f, -0.3f, -0.8f };
            float wing_world[3];
            rotate_vec3(wing_local, ship_rot[0], ship_rot[1], ship_rot[2]);
            wing_world[0] += ship_pos[0]; wing_world[1] += ship_pos[1]; wing_world[2] += ship_pos[2];

            for (int k = 0; k < 4; k++) {
                int p_idx = rand() % PARTICLE_COUNT;
                particles[p_idx].pos[0] = wing_world[0] + (randf() - 0.5f) * 0.3f;
                particles[p_idx].pos[1] = wing_world[1] + (randf() - 0.5f) * 0.3f;
                particles[p_idx].pos[2] = wing_world[2] + (randf() - 0.5f) * 0.3f;
                particles[p_idx].vel[0] = (randf() - 0.5f) * 3.5f;
                particles[p_idx].vel[1] = randf() * 2.5f + 1.0f;
                particles[p_idx].vel[2] = -15.0f;
                particles[p_idx].active = 1;
                particles[p_idx].life = 0.8f + randf() * 0.3f;
                particles[p_idx].color = (randf() > 0.4f) ? 4 : 5;
            }
        }

        for (int f = 0; f < 13; f++) {
            float c_verts[4][3];
            int n_verts = HERO_FACES[f].is_quad ? 4 : 3;

            for (int k = 0; k < n_verts; k++) {
                float temp[3] = { HERO_VERTS[HERO_FACES[f].v[k]].pos[0], HERO_VERTS[HERO_FACES[f].v[k]].pos[1], HERO_VERTS[HERO_FACES[f].v[k]].pos[2] };
                rotate_vec3(temp, ship_rot[0], ship_rot[1], ship_rot[2]);
                temp[0] += ship_pos[0]; temp[1] += ship_pos[1]; temp[2] += ship_pos[2];
                world_to_cam(c_verts[k], temp, cam_pos, R, U, F);
            }

            if (c_verts[0][2] < 0.2f || c_verts[1][2] < 0.2f || c_verts[2][2] < 0.2f) continue;

            int color = 8;
            if (HERO_FACES[f].hue_type == 1) color = 10;
            else if (HERO_FACES[f].hue_type == 2) color = 9;
            else if (HERO_FACES[f].hue_type == 3) color = 11;
            else if (HERO_FACES[f].hue_type == 4) color = 3;

            if (timeline >= 15.0f && (f == 4 || f == 6 || f == 9)) {
                color = (randf() > 0.3f) ? 9 : 4;
            }

            if (queue_count < MAX_FACES) {
                ProjectedFace *face = &render_queue[queue_count++];
                face->depth = (c_verts[0][2] + c_verts[1][2] + c_verts[2][2]) / 3.0f;
                face->is_quad = HERO_FACES[f].is_quad;
                face->color = color;
                for (int k = 0; k < n_verts; k++) {
                    float invz = 250.0f / c_verts[k][2];
                    face->pts[k][0] = WIDTH/2 + c_verts[k][0] * invz;
                    face->pts[k][1] = HEIGHT/2 - c_verts[k][1] * invz;
                }
            }
        }

        for (int i = 1; i < queue_count; i++) {
            ProjectedFace key = render_queue[i];
            int j = i - 1;
            while (j >= 0 && render_queue[j].depth < key.depth) {
                render_queue[j + 1] = render_queue[j];
                j--;
            }
            render_queue[j + 1] = key;
        }

        for (int i = 0; i < queue_count; i++) {
            ProjectedFace *f = &render_queue[i];
            if (f->is_quad) {
                fill_quadf(f->pts[0][0], f->pts[0][1], f->pts[1][0], f->pts[1][1],
                           f->pts[2][0], f->pts[2][1], f->pts[3][0], f->pts[3][1], f->color);
            } else {
                fill_trianglef(f->pts[0][0], f->pts[0][1], f->pts[1][0], f->pts[1][1],
                               f->pts[2][0], f->pts[2][1], f->color);
            }
        }

        for (int i = 0; i < SHRAPNEL_COUNT; i++) {
            if (!shrapnels[i].active) continue;
            shrapnels[i].pos[0] += shrapnels[i].rot_vel[0] * dt;
            shrapnels[i].pos[1] += shrapnels[i].rot_vel[1] * dt;
            shrapnels[i].pos[2] += shrapnels[i].rot_vel[0] * 0.5f * dt;

            float cp[3];
            world_to_cam(cp, shrapnels[i].pos, cam_pos, R, U, F);
            if (cp[2] > 0.2f) {
                float invz = 250.0f / cp[2];
                int sx = WIDTH/2 + (int)(cp[0] * invz);
                int sy = HEIGHT/2 - (int)(cp[1] * invz);
                fill_trianglef(sx - 3, sy - 2, sx + 3, sy - 2, sx, sy + 3, shrapnels[i].color);
            }
        }

        for (int i = 0; i < PARTICLE_COUNT; i++) {
            if (!particles[i].active) continue;
            particles[i].pos[0] += particles[i].vel[0] * dt;
            particles[i].pos[1] += particles[i].vel[1] * dt;
            particles[i].pos[2] += particles[i].vel[2] * dt;
            particles[i].life -= dt * 1.5f;
            if (particles[i].life <= 0.0f) { particles[i].active = 0; continue; }

            float cp[3];
            world_to_cam(cp, particles[i].pos, cam_pos, R, U, F);
            if (cp[2] > 0.2f) {
                float invz = 250.0f / cp[2];
                int sx = WIDTH/2 + (int)(cp[0] * invz);
                int sy = HEIGHT/2 - (int)(cp[1] * invz);
                if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT) set_pixel(sx, sy, particles[i].color);
            }
        }

        if (timeline >= 18.0f && timeline < 24.0f) {
            float enemy_cam[3];
            world_to_cam(enemy_cam, current_target_pos, cam_pos, R, U, F);
            float invz = 250.0f / enemy_cam[2];
            draw_human_cockpit(WIDTH/2 + enemy_cam[0] * invz, HEIGHT/2 - enemy_cam[1] * invz, timeline > 21.0f);
        }

        render_subtitles(timeline);

        /* Simple FPS counter */
present();
    }

    screen_close();
    return 0;
}