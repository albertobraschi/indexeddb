/**********************************************************\
Copyright Brandon Haynes
http://code.google.com/p/indexeddb
GNU Lesser General Public License
\**********************************************************/

#include "TransactionSync.h"
#include "DatabaseSync.h"
#include "../DatabaseException.h"
#include "../../Implementation/AbstractDatabaseFactory.h"

using boost::optional;
using boost::mutex;
using boost::lock_guard;


namespace BrandonHaynes {
namespace IndexedDB { 

using Implementation::ObjectStoreImplementationList;
using Implementation::ImplementationException;

namespace API { 

TransactionSync::TransactionSync(const DatabaseSyncPtr& database, TransactionFactory& transactionFactory, const ObjectStoreSyncList& objectStores, const optional<unsigned int>& timeout)
	: Transaction(database, !objectStores.is_initialized() || (objectStores.is_initialized() && !objectStores->empty())),
	  implementation(Implementation::AbstractDatabaseFactory::getInstance()
		  .createTransaction(transactionFactory.getDatabaseContext(), mapObjectStoresToImplementations(objectStores), timeout, Implementation::TransactionContext())),
	  isActive(true)
	{
	registerMethod("commit", make_method(this, &TransactionSync::commit));
	registerMethod("abort", make_method(this, &TransactionSync::abort));
	}

TransactionSync::~TransactionSync()
	{ 
	try
		{ close(); }
	catch(ImplementationException&) { }
	}

void TransactionSync::abort()
	{ 
	lock_guard<mutex> guard(synchronization);

	if(isActive)
		{
		isActive = false;
		Transaction::abort();
		try
			{ implementation->abort(); }
		catch(ImplementationException& e) 
			{ throw DatabaseException(e); }
		}
	else
		throw DatabaseException("NON_TRANSIENT_ERR", DatabaseException::NON_TRANSIENT_ERR);
	}

void TransactionSync::commit()
	{ 
	if(isActive)
		{
		isActive = false;
		Transaction::commit();
		try
			{ implementation->commit(); }
		catch(ImplementationException& e) 
			{ throw DatabaseException(e); }
		}
	else
		throw DatabaseException("NON_TRANSIENT_ERR", DatabaseException::NON_TRANSIENT_ERR);
	}

void TransactionSync::close()
	{
	isActive = false;
	implementation.reset();
	}

const ObjectStoreImplementationList TransactionSync::mapObjectStoresToImplementations(const ObjectStoreSyncList& objectStores)
	{
	if(objectStores.is_initialized())
		{
		ObjectStoreImplementationList objectStoreImplementations;
		for_each(objectStores->begin(), objectStores->end(), 
			MapObjectStoreToImplementationFunctor(objectStoreImplementations));
		return ObjectStoreImplementationList(objectStoreImplementations);
		}
	else
		return ObjectStoreImplementationList();
	}

}
}
}