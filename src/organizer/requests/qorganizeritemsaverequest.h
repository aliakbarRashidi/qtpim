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

#ifndef QORGANIZERITEMSAVEREQUEST_H
#define QORGANIZERITEMSAVEREQUEST_H

#include "qorganizerglobal.h"
#include "qorganizerabstractrequest.h"
#include "qorganizeritem.h"

#include <QList>

QTORGANIZER_BEGIN_NAMESPACE

class QOrganizerItemSaveRequestPrivate;
class Q_ORGANIZER_EXPORT QOrganizerItemSaveRequest : public QOrganizerAbstractRequest
{
    Q_OBJECT

public:
    QOrganizerItemSaveRequest(QObject* parent = 0);
    ~QOrganizerItemSaveRequest();

    /* Selection */
    void setItem(const QOrganizerItem& organizeritem);
    void setItems(const QList<QOrganizerItem>& organizeritems);

    void setDetailMask(const QList<QOrganizerItemDetail::DetailType> &detailMask);
    QList<QOrganizerItemDetail::DetailType> detailMask() const;

    /* Results */
    QList<QOrganizerItem> items() const;
    QMap<int, QOrganizerManager::Error> errorMap() const;

    // to be removed
    void setDefinitionMask(const QList<QOrganizerItemDetail::DetailType> &definitionMask);
    QList<QOrganizerItemDetail::DetailType> definitionMask() const;

private:
    Q_DISABLE_COPY(QOrganizerItemSaveRequest)
    friend class QOrganizerManagerEngine;
    Q_DECLARE_PRIVATE_D(d_ptr, QOrganizerItemSaveRequest)
};

QTORGANIZER_END_NAMESPACE

#endif
