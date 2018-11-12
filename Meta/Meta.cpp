#include "Meta.h"
#include "Library.h"

namespace Meta
{
    
namespace Internal
{

const char *QualifiedTypeFormatString = "%s%s";

}

Type *Meta::GetType(StringParam name, Library *library)
{
    if (library == nullptr)
    {
        library = gLibrary;
    }
    return library->GetType(name);
}

}