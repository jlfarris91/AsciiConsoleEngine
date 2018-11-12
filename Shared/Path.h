#pragma once

class Path
{
public:
    static string GetExtension(StringParam path);
    static string GetPathWithoutExtension(StringParam path);
    static string GetFileName(StringParam path);
};