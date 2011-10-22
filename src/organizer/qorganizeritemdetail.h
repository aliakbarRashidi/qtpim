/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
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
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QORGANIZERITEMDETAIL_H
#define QORGANIZERITEMDETAIL_H

#include <qorganizerglobal.h>

#include <QtCore/qshareddata.h>
#include <QtCore/qvariant.h>

QTORGANIZER_BEGIN_NAMESPACE

class QOrganizerItemDetailPrivate;

// MSVC needs the function declared before the friend declaration
#ifndef QT_NO_DATASTREAM
class QOrganizerItemDetail;
Q_ORGANIZER_EXPORT QDataStream &operator<<(QDataStream &out, const QOrganizerItemDetail &detail);
Q_ORGANIZER_EXPORT QDataStream &operator>>(QDataStream &in, QOrganizerItemDetail &detail);
#endif // QT_NO_DATASTREAM

class Q_ORGANIZER_EXPORT QOrganizerItemDetail
{
public:
    QOrganizerItemDetail();
    QOrganizerItemDetail(const QString &definitionName);
    QOrganizerItemDetail(const QOrganizerItemDetail &other);
    ~QOrganizerItemDetail();

    QOrganizerItemDetail &operator=(const QOrganizerItemDetail &other);

    enum AccessConstraint {
        NoConstraint = 0,
        ReadOnly = 0x01,
        Irremovable = 0x02
    };
    Q_DECLARE_FLAGS(AccessConstraints, AccessConstraint)

    AccessConstraints accessConstraints() const;

    bool operator==(const QOrganizerItemDetail &other) const;
    bool operator!=(const QOrganizerItemDetail &other) const {return !(other == *this);}

    QString definitionName() const;
    bool isEmpty() const;

    int key() const;
    void resetKey();

    bool setValue(const QString &key, const QVariant &value);
    bool removeValue(const QString &key);
    bool hasValue(const QString &key) const;

    QVariantMap values() const;
    QVariant value(const QString &key) const;
    template <typename T> T value(const QString &key) const
    {
        return value(key).value<T>();
    }

protected:
    QOrganizerItemDetail(const QOrganizerItemDetail &other, const QString &expectedDefinitionId);
    QOrganizerItemDetail &assign(const QOrganizerItemDetail &other, const QString &expectedDefinitionId);

private:
    friend class QOrganizerItem;
    friend class QOrganizerItemDetailPrivate;

#ifndef QT_NO_DATASTREAM
    Q_ORGANIZER_EXPORT friend QDataStream &operator>>(QDataStream &in, QOrganizerItemDetail &detail);
#endif // QT_NO_DATASTREAM

    QSharedDataPointer<QOrganizerItemDetailPrivate> d;
};

Q_ORGANIZER_EXPORT uint qHash(const QOrganizerItemDetail &key);
#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerItemDetail &detail);
#endif // QT_NO_DEBUG_STREAM

Q_DECLARE_OPERATORS_FOR_FLAGS(QOrganizerItemDetail::AccessConstraints)

#define Q_DECLARE_CUSTOM_ORGANIZER_DETAIL(className, definitionNameString) \
    className() : QOrganizerItemDetail(DefinitionName) {} \
    className(const QOrganizerItemDetail &field) : QOrganizerItemDetail(field, DefinitionName) {} \
    className &operator=(const QOrganizerItemDetail &other) {assign(other, DefinitionName); return *this;} \
    const static QString DefinitionName;

QTORGANIZER_END_NAMESPACE

Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItemDetail), Q_MOVABLE_TYPE);

#endif // QORGANIZERITEMDETAIL_H
