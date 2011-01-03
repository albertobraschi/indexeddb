/**********************************************************\
Copyright Brandon Haynes
http://code.google.com/p/indexeddb
GNU Lesser General Public License
\**********************************************************/

#include "AbstractDatabaseFactory.h"
#include "BerkeleyDatabase/BerkeleyDatabaseFactory.h"

namespace BrandonHaynes {
namespace IndexedDB { 
namespace Implementation { 

	AbstractDatabaseFactory& AbstractDatabaseFactory::getInstance() 
		{ 
		static BerkeleyDB::BerkeleyDatabaseFactory instance;
		return static_cast<AbstractDatabaseFactory&>(instance); 
		}
}
}
}