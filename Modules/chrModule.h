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
 
//! \class chrModule
//! \brief Chiron base interface for module. 
//!
//! A chrModule is intended to be instanciate by a ParaView plugin
//! (Toolbar or AutoStart plugin). This is a design concept, the interface
//! is quite empty. It derives from QObject in order to declare slots and
//! signals.
//!
//! \author Jerome Velut
//! \date 26 nov 2009

#ifndef __CHRMODULE_H__
#define __CHRMODULE_H__

// QT includes
#include <QObject>

// ParaView includes
#include "pqApplicationCore.h"

class chrModule : public QObject
{
Q_OBJECT

public:
   //! Constructor:
   //! initialize this->Core to the current ParaView instance
   chrModule( ){this->Activated = 0;};

   //! Destructor:
   virtual ~chrModule( ){};

   //! Pure virtual function. Implement the processus of activation such as
   //! graphic object creation, Qt/VTK event dispatcher, etc.
   virtual void Activate( )=0;

   //! Pure virtual function. Implement the processus of deactivation.
   virtual void Deactivate( )=0;

protected:
   pqApplicationCore* Core; //!< Application instance
   int Activated; //!< Module is activated or not. Could be used in Activate() to avoid
                  //!< multiple activations
};

#endif //__CHRMODULE_H__

