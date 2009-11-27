//! \class chrApplicationModule
//! \brief Chiron base class that provides functionalities at application
//! level
//!
//! A chrApplicationModule is intended to be instanciate by a ParaView plugin
//! (Toolbar or AutoStart plugin). This is a design concept, the interface
//! is quite empty. It derives from QObject in order to declare slots and
//! signals.
//!
//! \author Jerome Velut
//! \date 26 nov 2009

#ifndef __CHRAPPLICATIONMODULE_H__
#define __CHRAPPLICATIONMODULE_H__

// QT includes
#include <QObject>

// ParaView includes
#include "pqApplicationCore.h"

class chrApplicationModule : public QObject
{
Q_OBJECT

public:
   //! Constructor:
   //! initialize this->Core to the current ParaView instance
   chrApplicationModule( );

   //! Destructor:
   virtual ~chrApplicationModule( );

protected:
   pqApplicationCore* Core; //!< Application instance
};

#endif //__CHRAPPLICATIONMODULE_H__

