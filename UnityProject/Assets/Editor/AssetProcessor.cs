//using UnityEngine;
//using UnityEditor;
//using System.Reflection;
//using System.Collections.Generic;
//using System.IO;

//public class AssetProcessor : UnityEditor.AssetModificationProcessor
//{
//    static HashSet<string> ignoreDirectories;
//    static HashSet<string> ignoreExtensions;
//    static HashSet<System.Type> ignoreTypes;

//    static AssetProcessor()
//    {
//        ignoreDirectories = new HashSet<string>
//        {
//            "ProjectSettings",
//            "Library",
//            "Temp"
//        };
//        ignoreExtensions = new HashSet<string>
//        {
//            ".dll",
//        };
//    }

//    public static string[] OnWillSaveAssets(string[] paths)
//    {
//        using (var writer = new StreamWriter("main.assets"))
//        {
//            WriteAssetsToFile(writer);
//        }
//        return paths;
//    }

//    public static void WriteAssetsToFile(StreamWriter writer)
//    {
//        var assetPaths = AssetDatabase.GetAllAssetPaths();
//        foreach (var path in assetPaths)
//        {
//            var extension = Path.GetExtension(path);
//            if (ignoreExtensions.Contains(extension) || string.IsNullOrEmpty(extension))
//            {
//                continue;
//            }

//            var directoryName = Path.GetDirectoryName(path);
//            if (ignoreDirectories.Contains(directoryName))
//            {
//                continue;
//            }

//            var assets = AssetDatabase.LoadAllAssetsAtPath(path);
//            SerializeAssets(assets, writer);
//        }
//    }

//    static void SerializeAssets(Object[] assetObjects, StreamWriter writer)
//    {
//        Object mainAsset = null;
//        List<Object> subAssets = new List<Object>();

//        foreach (var asset in assetObjects)
//        {
//            var assetType = asset.GetType();
//            if (assetType.IsSubclassOf(typeof(Component)))
//            {
//                continue;
//            }

//            if (AssetDatabase.IsSubAsset(asset))
//            {
//                subAssets.Add(asset);
//            }
//            else if (AssetDatabase.IsMainAsset(asset))
//            {
//                if (mainAsset != null)
//                {
//                    Debug.LogError("Cannot have more than one main asset.");
//                    return;
//                }
//                mainAsset = asset;
//            }
//        }

//        if (mainAsset == null)
//        {
//            Debug.LogWarning("Main asset is null.");
//            return;
//        }

//        var assetTypeName = mainAsset.name;
//        var assetPath = AssetDatabase.GetAssetPath(mainAsset);
//        var assetGuid = AssetDatabase.AssetPathToGUID(assetPath);
//        var assetFileId = GetLocalFileId(mainAsset);

//        if (string.IsNullOrEmpty(assetTypeName))
//        {
//            assetTypeName = mainAsset.GetType().Name;
//        }

//        writer.WriteLine(string.Format("{0}: &{1}", assetTypeName, assetFileId));
//        writer.WriteLine(string.Format("\tguid: {0}", assetGuid));
//        writer.WriteLine(string.Format("\tpath: {0}", assetPath));

//        foreach (var subAsset in subAssets)
//        {
//            assetTypeName = subAsset.GetType().Name;
//            assetFileId = GetLocalFileId(subAsset);

//            if (assetTypeName == "Object" && !string.IsNullOrEmpty(mainAsset.name))
//            {
//                assetTypeName = mainAsset.name;
//            }

//            writer.WriteLine(string.Format("\t{0}: &{1}", assetTypeName, assetFileId));
//        }
//    }

//    static int GetLocalFileId(Object unityObject)
//    {
//        var inspectorModeInfo = typeof(SerializedObject).GetProperty("inspectorMode", BindingFlags.NonPublic | BindingFlags.Instance);

//        var serializedObject = new SerializedObject(unityObject);
//        inspectorModeInfo.SetValue(serializedObject, InspectorMode.Debug, null);

//        var localIdProp = serializedObject.FindProperty("m_LocalIdentfierInFile");   //note the misspelling!
//        if (localIdProp == null)
//        {
//            return 0;
//        }

//        return localIdProp.intValue;
//    }
//}
