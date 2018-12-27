#include "BasicEObject.hpp"
#include "ecore/BasicEList.hpp"
#include "ecore/EAdapter.hpp"
#include "ecore/EClass.hpp"
#include "ecore/EOperation.hpp"
#include "ecore/EStructuralFeature.hpp"


#include <boost/assert.hpp>
#include <string>
#include <sstream>

using namespace ecore;

BasicEObject::BasicEObject()
    : eDeliver_(false)
    , eAdapters_( new BasicEList<EAdapter*>() )
    , eContainer_()
    , eContainingFeature_()
{

}

BasicEObject::~BasicEObject()
{

}


EList<EAdapter*>& BasicEObject::eAdapters()
{
    return *eAdapters_;
}

bool BasicEObject::eDeliver()
{
    return eDeliver_;
}

void BasicEObject::eSetDeliver( bool deliver )
{
    eDeliver_ = deliver;
}

void BasicEObject::eNotify( const std::shared_ptr<ENotification>& notification )
{
    for( auto eAdapter : *eAdapters_ )
        eAdapter->notifyChanged( notification );
}

bool BasicEObject::eNotificationRequired()
{
    return eDeliver_ && eAdapters_->size() > 0;
}

boost::any ecore::BasicEObject::eGet( const std::shared_ptr<ecore::EStructuralFeature>& feature ) const
{
    return eGet(feature,true);
}

boost::any ecore::BasicEObject::eGet( const std::shared_ptr<ecore::EStructuralFeature>& feature, bool resolve ) const
{
    return eGet( feature, true );
}

int ecore::BasicEObject::eDerivedStructuralFeatureID( const std::shared_ptr<EStructuralFeature>& eStructuralFeature ) const
{
    BOOST_VERIFY_MSG( eClass()->getEAllStructuralFeatures()->contains( eStructuralFeature ), ( static_cast<std::ostringstream&>( std::stringstream() << "The feature '" << eStructuralFeature->getName() << "' is not a valid feature" )).str().c_str() );
    return eStructuralFeature->getFeatureID();
}

int ecore::BasicEObject::eDerivedOperationID( const std::shared_ptr<EOperation>& eOperation ) const
{
    BOOST_VERIFY_MSG( eClass()->getEAllOperations()->contains( eOperation ), ( static_cast<std::ostringstream&>( std::stringstream() << "The operation '" << eOperation->getName() << "' is not a valid operation" ) ).str().c_str() );
    return eOperation->getOperationID();
}

boost::any ecore::BasicEObject::eGet( const std::shared_ptr<ecore::EStructuralFeature>& eFeature, bool resolve, bool coreType ) const
{
    int featureID = eDerivedStructuralFeatureID( eFeature );
    if( featureID >= 0 )
        return eGet( featureID, resolve, coreType );
    throw "The feature '" + eFeature->getName() + "' is not a valid feature";
}

boost::any ecore::BasicEObject::eGet( int featureID, bool resolve, bool coreType ) const
{
    std::shared_ptr<EStructuralFeature> eFeature = eClass()->getEStructuralFeature( featureID );
    BOOST_ASSERT_MSG( eFeature != nullptr, ( static_cast<std::ostringstream&>( std::stringstream() << "Invalid featureID:  " << featureID )).str().c_str() );
    return boost::any();
}

bool ecore::BasicEObject::eIsSet( const std::shared_ptr<ecore::EStructuralFeature>& eFeature ) const
{
    int featureID = eDerivedStructuralFeatureID( eFeature );
    if( featureID >= 0 )
        return eIsSet( featureID );
    throw "The feature '" + eFeature->getName() + "' is not a valid feature";
}

bool ecore::BasicEObject::eIsSet( int featureID ) const
{
    std::shared_ptr<EStructuralFeature> eFeature = eClass()->getEStructuralFeature( featureID );
    BOOST_ASSERT_MSG( eFeature != nullptr, ( static_cast<std::ostringstream&>( std::stringstream() << "Invalid featureID:  " << featureID ) ).str().c_str() );
    return false;
}

void ecore::BasicEObject::eSet( const std::shared_ptr<ecore::EStructuralFeature>& eFeature, const boost::any & newValue )
{
    int featureID = eDerivedStructuralFeatureID( eFeature );
    if( featureID >= 0 )
        eSet( featureID , newValue );
    throw "The feature '" + eFeature->getName() + "' is not a valid feature";
}

void ecore::BasicEObject::eSet( int featureID, const boost::any & newValue )
{
    std::shared_ptr<EStructuralFeature> eFeature = eClass()->getEStructuralFeature( featureID );
    BOOST_ASSERT_MSG( eFeature != nullptr, ( static_cast<std::ostringstream&>( std::stringstream() << "Invalid featureID:  " << featureID ) ).str().c_str() );
}


void ecore::BasicEObject::eUnset( const std::shared_ptr<ecore::EStructuralFeature>& eFeature )
{
    int featureID = eDerivedStructuralFeatureID( eFeature );
    if( featureID >= 0 )
        eUnset( featureID );
    throw "The feature '" + eFeature->getName() + "' is not a valid feature";
}

void ecore::BasicEObject::eUnset( int featureID )
{
    std::shared_ptr<EStructuralFeature> eFeature = eClass()->getEStructuralFeature( featureID );
    BOOST_ASSERT_MSG( eFeature != nullptr, ( static_cast<std::ostringstream&>( std::stringstream() << "Invalid featureID:  " << featureID ) ).str().c_str() );
}

boost::any ecore::BasicEObject::eInvoke( const std::shared_ptr<ecore::EOperation>& eOperation, const std::shared_ptr<EList<boost::any>>& arguments )
{
    int operationID = eDerivedOperationID( eOperation );
    if( operationID >= 0 )
        return eInvoke( operationID , arguments );
    throw "The operation '" + eOperation->getName() + "' is not a valid operation";
}

boost::any ecore::BasicEObject::eInvoke( int operationID, const std::shared_ptr<EList<boost::any>>& arguments )
{
    std::shared_ptr<EOperation> eOperation = eClass()->getEOperation( operationID );
    BOOST_ASSERT_MSG( eOperation != nullptr, ( static_cast<std::ostringstream&>( std::stringstream() << "Invalid operationID:  " << operationID ) ).str().c_str() );
    return boost::any();
}

void ecore::BasicEObject::eInverseAdd( int featureID, const boost::any & newValue )
{
}

void ecore::BasicEObject::eInverseRemove( int featureID, const boost::any & oldValue )
{
}

void ecore::BasicEObject::setEContainer( const std::shared_ptr<EObject>& eContainer, const std::shared_ptr<EStructuralFeature>& eContainingFeature )
{
}








