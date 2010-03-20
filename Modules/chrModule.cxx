#include "chrModule.h"

chrModule::chrModule( )
{
   this->Activated = 0;
   this->Core = pqApplicationCore::instance();
}

void chrModule::toggleActivation( )
{
   if( this->Activated )
      this->Deactivate( );
   else
      this->Activate( );
}
