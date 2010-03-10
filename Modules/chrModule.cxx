#include "chrModule.h"

void chrModule::toggleActivation( )
{
   if( this->Activated )
      this->Deactivate( );
   else
      this->Activate( );
}
