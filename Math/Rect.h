#pragma once
#include "Vector2.h"
#include <string>

class Rect
{
public:
    Rect(float left = 0.0f, float top = 0.0f, float right = 0.0f, float bottom = 0.0f);
    Rect(const Rect &other);
    Rect(const Rect &&other);

    Rect &operator=(const Rect &rhs);
    bool operator==(const Rect &rhs);
    bool operator!=(const Rect &rhs);

    float width() const;
    float height() const;
    void expand(float size);
    bool overlaps(const Rect &other);
    bool contains(const Rect &other);
    bool contains(Vec2Param point);

    float top = 0.0f;
    float left = 0.0f;
    float bottom = 0.0f;
    float right = 0.0f;
};
