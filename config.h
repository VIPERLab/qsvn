/***************************************************************************
 *   Copyright (C) 2004 by Andreas Richter                                 *
 *   ar@oszine.de                                                          *
 *   http://www.oszine.de                                                  *
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
#ifndef CONFIG_H
#define CONFIG_H

//Qt
#include <qobject.h>

class QString;

/**
this singelton holds the configuration for qsvn
 
@author Andreas Richter
*/

class Config : public QObject
{
    Q_OBJECT
public:
    static Config* Exemplar();
    
    void setSvnExecutable( QString aString ); //!< set the complete path to svn execute
    QString getSvnExecutable(); //!< get the complete path to svn execute
    
public slots:
    void saveChanges();
    
private:
    Config(QObject *parent = 0, const char *name = 0);
    ~Config();
    
    static Config* _exemplar;
    
    bool changed; //!< true, if one or more settings have changed. save changed values in dtor
    QString _svnExecutable;
};

#endif