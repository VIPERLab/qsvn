/********************************************************************************
 *   This file is part of QSvn Project http://www.anrichter.net/projects/qsvn   *
 *   Copyright (c) 2004-2008 Andreas Richter <ar@anrichter.net>                 *
 *                                                                              *
 *   This program is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License Version 2             *
 *   as published by the Free Software Foundation.                              *
 *                                                                              *
 *   This program is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *   GNU General Public License for more details.                               *
 *                                                                              *
 *   You should have received a copy of the GNU General Public License          *
 *   along with this program; if not, write to the                              *
 *   Free Software Foundation, Inc.,                                            *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                  *
 *                                                                              *
 *******************************************************************************/

#ifndef MERGE_H
#define MERGE_H

//QSvn
#include "svnclient.h"
#include "ui_merge.h"

//Qt
#include <QDialog>
class QPushButton;


class Merge : public QDialog, public Ui::Merge
{
    Q_OBJECT

    public:
        static void doMerge(const QString fromURL, const svn::Revision fromRevision,
                            const QString toURL, const svn::Revision toRevision);
        static void doMerge(const QString wc);

    private:
        Merge();
        ~Merge();

        QPushButton *buttonDryRun;

    public slots:
        void on_buttonWcPath_clicked();
        void on_buttonDryRun_clicked();
        void accept();
};

#endif
