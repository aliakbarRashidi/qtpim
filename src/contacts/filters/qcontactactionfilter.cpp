/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtContacts module of the Qt Toolkit.
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

#include "qcontactactionfilter.h"
#include "qcontactactionfilter_p.h"
#include "qcontactfilter_p.h"
#include "qcontactmanager.h"

QTCONTACTS_BEGIN_NAMESPACE

/*!
  \class QContactActionFilter
  \brief The QContactActionFilter class provides a filter based around an
  action availability criterion.
 
  
  \inmodule QtContacts
  
  \ingroup contacts-filters
    
  It may be used to select contacts for which a particular action is
  available, or contacts which contain a detail of a particular value for
  which the action is available.
 */

Q_IMPLEMENT_CONTACTFILTER_PRIVATE(QContactActionFilter);

/*!
 * \fn QContactActionFilter::QContactActionFilter(const QContactFilter& other)
 * Constructs a copy of \a other if possible, otherwise constructs a new action filter
 */

/*!
 * Constructs a new action filter
 */
QContactActionFilter::QContactActionFilter()
    : QContactFilter(new QContactActionFilterPrivate)
{
}

/*!
 * Sets the name of the action whose availability is required to \a action
 * \sa actionName()
 */
void QContactActionFilter::setActionName(const QString& action)
{
    Q_D(QContactActionFilter);
    d->m_action = action;
}

/*!
 * Returns the action name criterion of the filter
 * \sa setActionName()
 */
QString QContactActionFilter::actionName() const
{
    Q_D(const QContactActionFilter);
    return d->m_action;
}

QTCONTACTS_END_NAMESPACE
