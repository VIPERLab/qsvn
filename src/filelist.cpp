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
#include "config.h"
#include "filelist.h"
#include "filelistitem.h"
#include "statustext.h"
#include "svnclient.h"

//Qt
#include <qdir.h>
#include <qlistview.h>
#include <qpixmap.h>


//make FileList a singleton
FileList* FileList::_exemplar = 0;

FileList* FileList::Exemplar()
{
    if ( _exemplar == 0 )
    {
        _exemplar = new FileList;
    }
    return _exemplar;
}

void FileList::releaseExemplar()
{
    if ( _exemplar )
        delete _exemplar;
}


//FileList implementation
FileList::FileList(QObject *parent, const char *name)
        : QObject(parent, name)
{
    listViewFiles = new QListView( 0, "listViewFiles" );
    listViewFiles->addColumn( tr( "Filename" ) );
    listViewFiles->addColumn( tr( "File Status" ) );
    listViewFiles->setShowSortIndicator( TRUE );
    listViewFiles->setAllColumnsShowFocus( TRUE );
    
    connect( listViewFiles, SIGNAL( doubleClicked( QListViewItem* ) ), this, SLOT( doubleClickedSlot( QListViewItem* ) ) );
    
    Config::Exemplar()->restoreListView( listViewFiles );
    stringFullPath = "";
}

FileList::~FileList()
{
    Config::Exemplar()->saveListView( listViewFiles );
}

QWidget *FileList::getWidget()
{
    return listViewFiles;
}

FileListItem* FileList::selectedFileListItem()
{
    if ( listViewFiles->selectedItem() )
        return static_cast< FileListItem* >( listViewFiles->selectedItem() );
    else
        return 0;
}

void FileList::updateListSlot( QString currentDirectory )
{
    if ( listViewFiles && currentDirectory )
    {
        listViewFiles->clear();
        if ( SvnClient::Exemplar()->status( currentDirectory, false ) )
        {
            QStringList statusList( SvnClient::Exemplar()->getProcessStdoutList() );
            QString _lineString;
            QString _fileName;
            QDir _checkDir;
            for ( QStringList::Iterator it = statusList.begin(); it != statusList.end(); ++it )
            {
                _lineString = *it;
                _fileName = _lineString.right( _lineString.length() - 40 );
                _checkDir = QDir( currentDirectory + QDir::separator() + _fileName );
                // add only directories here
                if ( ! _checkDir.exists() )
                {
                    //set Filename
                    QListViewItem* _element = new QListViewItem( listViewFiles, _fileName );
                    //set File Status
                    switch ( int( _lineString.at( 0 ).latin1() ) ) {
                        case int( 'M' ):
                            _element->setText( _COLUMN_STATUS, tr( "Modified File" ) );
                            _element->setPixmap( _COLUMN_FILE, QPixmap::fromMimeSource( "modifiedfile.png" ) );
                            break;
                        case int( '?' ): 
                            _element->setText( _COLUMN_STATUS, tr( "Unknown File" ) );
                            _element->setPixmap( _COLUMN_FILE, QPixmap::fromMimeSource( "unknownfile.png" ) );
                            break;
                        case int( ' ' ): 
                            _element->setText( _COLUMN_STATUS, tr( "File" ) );
                            _element->setPixmap( _COLUMN_FILE, QPixmap::fromMimeSource( "file.png" ) );
                            break;
                        case int( 'A' ):
                            _element->setText( _COLUMN_STATUS, tr( "Added File" ) );
                            _element->setPixmap( _COLUMN_FILE, QPixmap::fromMimeSource( "addedfile.png" ) );
                            break;
                        default: 
                            _element->setText( _COLUMN_STATUS, tr( "Unknown Status" ) );
                            _element->setPixmap( _COLUMN_FILE, QPixmap::fromMimeSource( "unknownfile.png" ) );
                            break;
                    }
                }
            }
        }
        stringFullPath = currentDirectory;
    }
}

void FileList::diffSelected()
{
    if ( listViewFiles->currentItem() )
        SvnClient::Exemplar()->diff( stringFullPath, listViewFiles->currentItem()->text( _COLUMN_FILE ), FALSE );
}

void FileList::doubleClickedSlot( QListViewItem* item )
{
    //todo: switch settings and file status ( added, modified, ... )
    SvnClient::Exemplar()->diff( stringFullPath, item->text( _COLUMN_FILE ), FALSE );
}

