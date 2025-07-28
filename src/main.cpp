#include <cmath>
#include <raylib.h>
#include <stdio.h>
#include <raymath.h>
#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>
#include <vector>

struct Particle {
    Vector2 p_0; // Previous Position
    Vector2 p_1; // Current Position
    Vector2 velocity;

    Particle(Vector2 a) : p_0(a), p_1(a) {
        TraceLog(LOG_DEBUG, "%f %f\n", p_0.x, p_0.y);
    };

    void draw() {
        DrawLineEx(p_0, p_1, 1.0f, GREEN);
    }

    void update() {
        p_0 = p_1;
        p_1 = Vector2Add(p_1, Vector2Scale(velocity, GetFrameTime()));

        velocity.x += stb_perlin_noise3(p_1.x / 1280 * 8.0, p_1.y / 1280.0 * 8.0, GetTime() * 0.01f, 0, 0, 0);
        velocity.y += stb_perlin_noise3(p_1.x / 1280 * 8.0, p_1.y / 1280.0 * 8.0, GetTime()  * 0.01f+ 10.0, 0, 0, 0);

        velocity = Vector2Normalize(velocity);
        velocity = Vector2Scale(velocity, 10.0);

        if (p_1.x < 0.0f)
        {
            p_1.x += GetRenderWidth();
            p_0.x += GetRenderWidth(); 
        }
        if (p_1.y < 0.0f)
        {
            p_1.y += GetRenderHeight();
            p_0.y += GetRenderHeight(); 
        }
        if (p_1.x > GetRenderWidth())
        {
            p_1.x -= GetRenderWidth();
            p_0.x -= GetRenderWidth(); 
        }
        if (p_1.y > GetRenderHeight())
        {
            p_1.y -= GetRenderHeight();
            p_0.y -= GetRenderHeight(); 
        }

    }
};

std::vector<Particle> particles;

void init_program() {
    for (int i = 0; i < 10000; i++)
        particles.push_back(Particle(Vector2(GetRandomValue(0, GetRenderWidth()), GetRandomValue(0, GetRenderHeight()))));
}

void draw_particles () {

    for(auto& particle: particles) {
        particle.draw();
    }
}


void update_particles () {

    for(auto& particle: particles) {
        particle.update();
    }
}

int main() {

    InitWindow(GetScreenWidth(), GetScreenHeight(), "vector-fields");
    auto rt = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    BeginTextureMode(rt);
    ClearBackground(BLACK);
    EndTextureMode();

    float last_clear = 0.0f;

    init_program();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(rt);
        if (GetTime() - last_clear >= 0.1f)
        {
            DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Color(0, 0, 0, 2));
            last_clear = GetTime();
        }

        draw_particles();
        update_particles();
        EndTextureMode();

        DrawTexture(rt.texture, 0, 0, WHITE);
        EndDrawing();
    }   

    CloseWindow();

}
