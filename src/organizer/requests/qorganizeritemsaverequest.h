/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QORGANIZERITEMSAVEREQUEST_H
#define QORGANIZERITEMSAVEREQUEST_H

#include <QtCore/qlist.h>
#include <QtCore/qmap.h>

#include <QtOrganizer/qorganizerabstractrequest.h>
#include <QtOrganizer/qorganizeritem.h>
#include <QtOrganizer/qorganizeritemdetail.h>

QT_BEGIN_NAMESPACE_ORGANIZER

class QOrganizerItemSaveRequestPrivate;

/* Leaf class */

class Q_ORGANIZER_EXPORT QOrganizerItemSaveRequest : public QOrganizerAbstractRequest
{
    Q_OBJECT

public:
    QOrganizerItemSaveRequest(QObject *parent = nullptr);
    ~QOrganizerItemSaveRequest();

    void setItem(const QOrganizerItem &item);
    void setItems(const QList<QOrganizerItem> &items);
    QList<QOrganizerItem> items() const;

    void setDetailMask(const QList<QOrganizerItemDetail::DetailType> &detailMask);
    QList<QOrganizerItemDetail::DetailType> detailMask() const;

    QMap<int, QOrganizerManager::Error> errorMap() const;

private:
    Q_DISABLE_COPY(QOrganizerItemSaveRequest)
    friend class QOrganizerManagerEngine;
    Q_DECLARE_PRIVATE_D(d_ptr, QOrganizerItemSaveRequest)
};

QT_END_NAMESPACE_ORGANIZER

#endif // QORGANIZERITEMSAVEREQUEST_H
