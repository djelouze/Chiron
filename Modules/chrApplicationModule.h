// Copyright (c) 2010, Jérôme Velut
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER ``AS IS'' AND ANY EXPRESS 
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN 
// NO EVENT SHALL THE COPYRIGHT OWNER BE LIABLE FOR ANY DIRECT, INDIRECT, 
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
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

// Chiron includes
#include "chrModule.h"

// ParaView includes
#include "pqApplicationCore.h"

class chrApplicationModule : public chrModule
{
Q_OBJECT

public:
   //! Constructor:
   //! initialize this->Core to the current ParaView instance
   chrApplicationModule( );

   //! Destructor:
   virtual ~chrApplicationModule( );
};

#endif //__CHRAPPLICATIONMODULE_H__

