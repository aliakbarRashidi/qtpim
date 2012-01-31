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

#ifndef QORGANIZERCOLLECTIONREMOVEREQUEST_H
#define QORGANIZERCOLLECTIONREMOVEREQUEST_H

#include "qorganizerglobal.h"
#include "qorganizerabstractrequest.h"
#include "qorganizercollection.h"

#include <QList>
#include <QStringList>

QTORGANIZER_BEGIN_NAMESPACE

class QOrganizerCollectionRemoveRequestPrivate;
class Q_ORGANIZER_EXPORT QOrganizerCollectionRemoveRequest : public QOrganizerAbstractRequest
{
    Q_OBJECT

public:
    QOrganizerCollectionRemoveRequest(QObject* parent = 0);
    ~QOrganizerCollectionRemoveRequest();

    /* Selection */
    void setCollectionId(const QOrganizerCollectionId& collectionId);
    void setCollectionIds(const QList<QOrganizerCollectionId>& collectionIds);
    QList<QOrganizerCollectionId> collectionIds() const;

    /* Results */
    QMap<int, QOrganizerManager::Error> errorMap() const;

private:
    Q_DISABLE_COPY(QOrganizerCollectionRemoveRequest)
    friend class QOrganizerManagerEngine;
    Q_DECLARE_PRIVATE_D(d_ptr, QOrganizerCollectionRemoveRequest)
};

QTORGANIZER_END_NAMESPACE

#endif
