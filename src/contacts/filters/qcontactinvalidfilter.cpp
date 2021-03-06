/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtContacts module of the Qt Toolkit.
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

#include "qcontactinvalidfilter.h"

#include "qcontactfilter_p.h"

/*!
  \class QContactInvalidFilter
  \brief The QContactInvalidFilter class matches no contacts.

  \inmodule QtContacts

  \ingroup contacts-filters

  This class provides a filter which will never match any contacts
 */

QT_BEGIN_NAMESPACE_CONTACTS

class QContactInvalidFilterPrivate : public QContactFilterPrivate
{
public:
    QContactInvalidFilterPrivate()
       : QContactFilterPrivate()
    {
    }

    bool compare(const QContactFilterPrivate*) const
    {
        return true; // all invalid filters are alike
    }

    QDataStream& outputToStream(QDataStream& stream, quint8 formatVersion) const
    {
        Q_UNUSED(formatVersion)
        return stream;
    }

    QDataStream& inputFromStream(QDataStream& stream, quint8 formatVersion)
    {
        Q_UNUSED(formatVersion)
        return stream;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactInvalidFilter()";
        return dbg.maybeSpace() ;
    }
#endif

    /* There is no way this can be called - d is never detached */
    QContactFilterPrivate* clone() const
    {
        return new QContactInvalidFilterPrivate();
    }

    QContactFilter::FilterType type() const
    {
        return QContactFilter::InvalidFilter;
    }
};

/*!
 * Constructs a new invalid filter
 */
QContactInvalidFilter::QContactInvalidFilter()
    : QContactFilter(new QContactInvalidFilterPrivate)
{
}

/*!
 * Constructs a new invalid filter, ignoring the \a other filter
 */
QContactInvalidFilter::QContactInvalidFilter(const QContactFilter& other)
    : QContactFilter(new QContactInvalidFilterPrivate)
{
    // Initializing a QCIF from anything is the same as just constructing a QCIF
    Q_UNUSED(other);
}

QT_END_NAMESPACE_CONTACTS
