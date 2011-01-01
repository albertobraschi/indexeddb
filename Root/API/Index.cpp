/**********************************************************\
Copyright Brandon Haynes
http://code.google.com/p/indexeddb
GNU Lesser General Public License
\**********************************************************/

#include "Index.h"

using std::string;
using boost::optional;

namespace BrandonHaynes {
namespace IndexedDB { 
namespace API { 

Index::Index(const string& indexName, const string& objectStoreName, const optional<string>& keyPath, const bool unique)
	: indexName(indexName), objectStoreName(objectStoreName), keyPath(keyPath), unique(unique)
	{ initializeMethods(); }

Index::Index(const string& indexName, const string& objectStoreName)
	: indexName(indexName), objectStoreName(objectStoreName), keyPath(optional<string>()), unique(false)
	{ initializeMethods(); }

void Index::initializeMethods()
	{
	registerProperty("name", make_property(this, &Index::getName));
	registerProperty("storeName", make_property(this, &Index::getObjectStoreName));
	registerProperty("keyPath", make_property(this, &Index::getKeyPath));
	registerProperty("unique", make_property(this, &Index::getUnique));
	}

const std::string Index::getName() const
{
    return indexName;
}

boost::optional<std::string> Index::getKeyPath() const
{
    return keyPath;
}

const std::string Index::getObjectStoreName() const
{
    return objectStoreName;
}

}
}
}