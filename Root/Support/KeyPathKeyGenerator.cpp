/**********************************************************\
Copyright Brandon Haynes
http://code.google.com/p/indexeddb
GNU Lesser General Public License
\**********************************************************/

#include "KeyPathKeyGenerator.h"
#include "../Implementation/Key.h"
#include "Convert.h"

namespace BrandonHaynes {
namespace IndexedDB { 

	using class Implementation::Key;
	using class Implementation::Data;
	
namespace API { 
namespace Support {

Key KeyPathKeyGenerator::generateKey(const Data& context) const
	// TODO Does the spec support a keypath that looks like path1.path2?
	{ return Convert::toKey(host, generateKey(Convert::toVariant(host, context))); }

const FB::variant KeyPathKeyGenerator::generateKey(const FB::variant& value) const
	{
	return value.can_be_type<FB::JSObjectPtr>()
		? generateKey(value.convert_cast<FB::JSObjectPtr>())
		: FB::variant();
	}

const FB::variant KeyPathKeyGenerator::generateKey(const FB::JSObjectPtr& object) const
	{ return object->GetProperty(keyPath); }

}
}
}
}