#include "Path.h"

string Path::GetExtension(StringParam path)
{
    size_t index = path.Find('.');
    if (index == string::npos)
    {
        return string();
    }
    return path.Substring(index);
}

string Path::GetPathWithoutExtension(StringParam path)
{
    auto &&ext = Path::GetExtension(path);
    if (ext == string())
    {
        return path;
    }
    return path.Remove(ext);
}

string Path::GetFileName(StringParam path)
{
    auto &&start = path.Find('/');
    if (start == string::npos)
    {
        start = -1;
    }
    ++start;
    auto &&end = path.Find('.', start);
    if (end == string::npos)
    {
        end = path.Length();
    }
    return path.Substring(start, end - start);
}