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
 
#include "chrContextMenuModifier.h"

chrContextMenuModifier::chrContextMenuModifier( )
{
}


chrContextMenuModifier::~chrContextMenuModifier( )
{

}


void chrContextMenuModifier::AddContextMenuItemToView( pqRenderViewBase* view,
                                                     const char* itemText,
                                                     chrModule* chironModule,
                                                     const char* slot )
{
   QWidget* contextMenu = view->getWidget( );
   QAction* action = new QAction( itemText, view );
   contextMenu->addAction( action );
   QObject::connect(action, SIGNAL(triggered(bool)),
                    chironModule, 
                    (!slot?SLOT(toggleActivation()):slot));

}


