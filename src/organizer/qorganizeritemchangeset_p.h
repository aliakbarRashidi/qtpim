/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QORGANIZERITEMCHANGESET_P_H
#define QORGANIZERITEMCHANGESET_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qorganizerglobal.h>
#include <qorganizeritemid.h>

#include <QtCore/qset.h>
#include <QtCore/qshareddata.h>

QTORGANIZER_BEGIN_NAMESPACE

class QOrganizerItemChangeSetData : public QSharedData
{
public:
    QOrganizerItemChangeSetData()
        : QSharedData(),
        m_dataChanged(false)
    {
    }

    QOrganizerItemChangeSetData(const QOrganizerItemChangeSetData& other)
        : QSharedData(other),
        m_dataChanged(other.m_dataChanged),
        m_addedItems(other.m_addedItems),
        m_changedItems(other.m_changedItems),
        m_removedItems(other.m_removedItems)
    {
    }

    ~QOrganizerItemChangeSetData()
    {
    }

    bool m_dataChanged;
    QSet<QOrganizerItemId> m_addedItems;
    QSet<QOrganizerItemId> m_changedItems;
    QSet<QOrganizerItemId> m_removedItems;
};

QTORGANIZER_END_NAMESPACE

#endif
