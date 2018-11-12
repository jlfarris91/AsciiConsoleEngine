#pragma once

class Time
{
public:
    static float deltaTime;
    static float elapsedTime;
    static float fps;

    static void Update();

private:
    static float fpsTimer;
    static unsigned fpsCount;
};