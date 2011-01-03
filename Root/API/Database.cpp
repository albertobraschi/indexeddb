/**********************************************************\
Copyright Brandon Haynes
http://code.google.com/p/indexeddb
GNU Lesser General Public License
\**********************************************************/

#include "Database.h"

namespace BrandonHaynes {
namespace IndexedDB { 
namespace API { 

Database::Database(const std::string& name, const std::string& description)
	: name(name), description(description)
	{
	registerProperty("name", make_property(this, &Database::getName));
	registerProperty("description", make_property(this, &Database::getDescription));
	registerProperty("version", make_property(this, &Database::getVersionVariant));
	registerProperty("objectStores", make_property(this, &Database::getObjectStoreVariants));
	registerProperty("indexes", make_property(this, &Database::getIndexVariants));
	registerProperty("currentTransaction", make_property(this, &Database::getCurrentTransaction));
	}

std::string Database::getName() const
{
    return name;
}

std::string Database::getDescription() const
{
    return description;
}

}
}
}