#include "Time.h"
#include <chrono>

float Time::deltaTime = 0.0f;
float Time::elapsedTime = 0.0f;
float Time::fps = 0.0f;
float Time::fpsTimer = 0.0f;
unsigned Time::fpsCount = 0;

std::chrono::steady_clock::time_point prev = std::chrono::steady_clock::now();

void Time::Update()
{
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev);
    float seconds = delta.count() / 1000.0f;

    deltaTime = seconds;
    elapsedTime += deltaTime;

    fpsTimer += deltaTime;
    if (fpsTimer > 1.0f)
    {
        fps = fpsCount / fpsTimer;
        fpsTimer -= 1.0f;
        fpsCount = 0;
    }

    fpsCount++;
    prev = now;
}