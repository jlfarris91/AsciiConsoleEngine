using UnityEngine;
using System.Collections;
using System.IO;

public static class PathEx
{
    public static string GetPathWithoutExtension(string path)
    {
        if (!Path.HasExtension(path))
        {
            return path;
        }
        var extension = Path.GetExtension(path);
        var index = path.IndexOf(extension);
        if (index < 0)
        {
            return path;
        }
        return path.Remove(index, extension.Length);
    }
}