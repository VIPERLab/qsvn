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
#ifndef SVNCLIENT_H
#define SVNCLIENT_H

//Qt
#include <qobject.h>
#include <qstring.h>

class QProcess;

class SvnClient : public QObject{
    Q_OBJECT
public:
    static SvnClient* Exemplar();
    
    QString getProcessStdout();
    QString getProcessStderr();
    
    bool isWorkingCopy( const QString &path );

    
public slots:
    void readStdoutSlot(); //!< read out the Stdout written from running process
    void readStderrSlot(); //!< read out the Stderr written form running process
    
protected:    
    SvnClient();
    ~SvnClient();

private:
    static SvnClient* _exemplar;
    
    QProcess *process;
    QString svnCommand; //!< a contains the command line command vor subversion - svn even ;)
    QString processStdout;
    QString processStderr;
    
    void prepareNewProcess(); //!< initialies all for a new process
};

#endif