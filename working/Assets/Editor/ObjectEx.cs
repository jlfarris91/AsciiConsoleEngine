using UnityEngine;
using UnityEditor;
using System.Reflection;

public static class ObjectEx
{
    public static int GetLocalFileId(this Object unityObject)
    {
        var inspectorModeInfo = typeof(SerializedObject).GetProperty("inspectorMode", BindingFlags.NonPublic | BindingFlags.Instance);

        var serializedObject = new SerializedObject(unityObject);
        inspectorModeInfo.SetValue(serializedObject, InspectorMode.Debug, null);

        var localIdProp = serializedObject.FindProperty("m_LocalIdentfierInFile"); // note the misspelling!
        if (localIdProp == null)
        {
            throw new System.Exception("Local id property does not exist on object of type " + unityObject.GetType().Name);
        }

        return localIdProp.intValue;
    }
}
