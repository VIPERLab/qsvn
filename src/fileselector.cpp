/***************************************************************************
 *   This file is part of QSvn Project http://qsvn.berlios.de              *
 *   Copyright (c) 2004-2005 Andreas Richter <ar@oszine.de>                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   As a special exception, permission is given to link this program      *
 *   with any edition of Qt, and distribute the resulting executable,      *
 *   without including the source code for Qt in the source distribution.  *
 ***************************************************************************/

//QSvn
#include "fileselector.h"
#include "fileselectordlg.h"

//Qt
#include <qlistview.h>
#include <qstringlist.h>
#include <qtextedit.h>


FileSelector::FileSelector( QWidget *parent, const char *name )
        : FileSelectorDlg( parent, name )
{}

FileSelector::~FileSelector()
{}

void FileSelector::setSelectedFiles( QStringList* fileList )
{
    listViewFiles->clear();
    
    if ( fileList )
    {
        for ( QStringList::Iterator it = fileList->begin(); it != fileList->end(); ++it )
        {
            QCheckListItem* _item = new QCheckListItem( listViewFiles, *it, QCheckListItem::CheckBox );
            _item->setOn( TRUE );
        }
    }
}

void FileSelector::setMessageString( QString message )
{
    editLogMessage->setText( message );
}

QStringList* FileSelector::selectedFiles()
{
    QStringList *stringList = new QStringList;
    
    QListViewItemIterator it( listViewFiles );
    while ( it.current() ) 
    {
        QCheckListItem *item = static_cast< QCheckListItem* >( it.current() );
        if ( item->isOn() )
        {
            stringList->append( item->text( 0 ) );
        }
        ++it;
    }    
    return stringList;
}

QString FileSelector::messageString()
{
    return editLogMessage->text();
}