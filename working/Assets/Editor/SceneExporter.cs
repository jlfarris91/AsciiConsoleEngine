using UnityEngine;
using System.Collections;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using UnityEditor;

public class SceneExportProcessor : UnityEditor.AssetModificationProcessor
{
    public static Dictionary<System.Type, SceneObjectExportHandlerBase> ExportHandlers;

    static SceneExportProcessor()
    {
        ExportHandlers = new Dictionary<System.Type, SceneObjectExportHandlerBase>();
        RegisterExportHandler(new MeshFilterExportHandler());
        RegisterExportHandler(new MeshRendererExportHandler());
        RegisterExportHandler(new MonoBehaviourExportHandler());
    }

    public static void RegisterExportHandler(SceneObjectExportHandlerBase handler)
    {
        ExportHandlers.Add(handler.TargetType, handler);
    }

    public static string[] OnWillSaveAssets(string[] paths)
    {
        using (var writer = new StreamWriter("Assets/Resources/Scenes/main.assets", false))
        {
            var builder = new AssetDatabaseBuilder();
            builder.Writer = writer;

            writer.WriteLine("%YAML 1.1");
            writer.WriteLine("% TAG !u!tag:unity3d.com, 2011:");

            WriteAllGameObjectAssets(builder);
        }
        return paths;
    }

    private static void WriteAllGameObjectAssets(AssetDatabaseBuilder builder)
    {
        foreach (var gameObject in Object.FindObjectsOfType<GameObject>())
        {
            if (!gameObject.activeInHierarchy)
            {
                continue;
            }
            foreach (var component in gameObject.GetComponents<Component>())
            {
                var componentType = component.GetType();
                SceneObjectExportHandlerBase handler = null;
                if (ExportHandlers.TryGetValue(componentType, out handler))
                {
                    handler.Export(builder, component);
                }
                else
                {
                    foreach (var a in ExportHandlers.Values)
                    {
                        if (componentType.IsSubclassOf(a.TargetType))
                        {
                            a.Export(builder, component);
                            break;
                        }
                    }
                }
            }
        }
    }
}

public class AssetDatabaseBuilder
{
    public StreamWriter Writer;
    public HashSet<int> FileIds = new HashSet<int>();

    public void WriteHeader<T>(int fileId)
    {
        var typeName = typeof(T).Name;
        Writer.WriteLine("--- !u!0 &" + fileId);
        Writer.WriteLine(typeName + ":");
    }

    public void WriteProperty(string name, object value)
    {
        Writer.WriteLine("  " + name + ": " + value.ToString());
    }

    public void WriteFileIdProperty(string name, int value)
    {
        Writer.WriteLine("  " + name + ": {fileID: " + value.ToString() + "}");
    }

    public bool ContainsFileId(int fileId)
    {
        return FileIds.Contains(fileId);
    }
}

public abstract class SceneObjectExportHandlerBase
{
    public readonly System.Type TargetType;

    protected SceneObjectExportHandlerBase(System.Type targetType)
    {
        this.TargetType = targetType;
    }

    public abstract void Export(AssetDatabaseBuilder builder, Object target);
}

public class MeshFilterExportHandler : SceneObjectExportHandlerBase
{
    public MeshFilterExportHandler()
        : base(typeof(MeshFilter))
    {
    }

    public override void Export(AssetDatabaseBuilder builder, Object target)
    {
        var meshFilter = target as MeshFilter;

        var mesh = meshFilter.sharedMesh;
        var fileId = mesh.GetLocalFileId();

        if (builder.ContainsFileId(fileId))
        {
            return;
        }

        var path = AssetDatabase.GetAssetPath(mesh);
        var ext = Path.GetExtension(path);
        path = PathEx.GetPathWithoutExtension(path);

        builder.WriteHeader<Mesh>(fileId);
        builder.WriteProperty("name", mesh.name);
        builder.WriteProperty("path", path);
        builder.WriteProperty("ext", ext);

        builder.FileIds.Add(fileId);
    }
}

public class MeshRendererExportHandler : SceneObjectExportHandlerBase
{
    public MeshRendererExportHandler()
        : base(typeof(MeshRenderer))
    {
    }

    public override void Export(AssetDatabaseBuilder builder, Object target)
    {
        var meshRenderer = target as MeshRenderer;
        foreach (var material in meshRenderer.sharedMaterials)
        {
            ExportTexture(builder, material);
        }
    }

    private void ExportTexture(AssetDatabaseBuilder builder, Material material)
    {
        var texture = material.mainTexture;
        if (texture == null)
        {
            return;
        }

        var textureFileId = texture.GetLocalFileId();
        if (builder.ContainsFileId(textureFileId))
        {
            return;
        }

        var path = AssetDatabase.GetAssetPath(texture);
        var ext = Path.GetExtension(path);
        path = PathEx.GetPathWithoutExtension(path);

        builder.WriteHeader<Texture>(textureFileId);
        builder.WriteProperty("name", texture.name);
        builder.WriteProperty("path", path);
        builder.WriteProperty("ext", ext);

        var materialFileId = material.GetLocalFileId();
        if (builder.ContainsFileId(materialFileId))
        {
            return;
        }

        builder.WriteHeader<Material>(materialFileId);
        builder.WriteProperty("name", material.name);
        builder.WriteFileIdProperty("texture", textureFileId);

        builder.FileIds.Add(textureFileId);
        builder.FileIds.Add(materialFileId);
    }
}

public class MonoBehaviourExportHandler : SceneObjectExportHandlerBase
{
    public MonoBehaviourExportHandler()
        : base(typeof(MonoBehaviour))
    {
    }

    public override void Export(AssetDatabaseBuilder builder, Object target)
    {
        var behaviour = target as MonoBehaviour;
        var type = behaviour.GetType();
        var asset = Resources.Load(type.Name);
        var fileId = asset.GetLocalFileId();

        if (builder.ContainsFileId(fileId))
        {
            return;
        }

        builder.WriteHeader<MonoBehaviour>(fileId);
        builder.WriteProperty("name", behaviour.GetType().Name);
        builder.WriteProperty("ext", ".cs");

        builder.FileIds.Add(fileId);
    }
}