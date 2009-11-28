//    Copyright Jerome Velut 2009
//
//    This file is part of Chiron.
//
//    Chiron is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Chiron is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You have received a copy of the GNU General Public License
//    along with Chiron in the file COPYING.  
//    If not, see <http://www.gnu.org/licenses/>.
 
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

