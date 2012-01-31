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

#include "qcontactrelationshipsaverequest.h"
#include "qcontactrequests_p.h"

QTCONTACTS_BEGIN_NAMESPACE

/*!
  \class QContactRelationshipSaveRequest
  \brief The QContactRelationshipSaveRequest class allows a client to asynchronously
    request that certain groups be saved to a contacts store.

  For a QContactRelationshipSaveRequest, the resultsAvailable() signal will be emitted when
  either the individual item errors (which may be retrieved by calling errorMap()), or the resultant
  relationships (which may be retrieved by calling relationships()), are updated, as well as if
  the overall operation error (which may be retrieved by calling error()) is updated.

  Please see the class documentation of QContactAbstractRequest for more information about
  the usage of request classes and ownership semantics.


  \inmodule QtContacts

  \ingroup contacts-requests
 */

/*! Constructs a new relationship save request whose parent is the specified \a parent */
QContactRelationshipSaveRequest::QContactRelationshipSaveRequest(QObject* parent)
    : QContactAbstractRequest(new QContactRelationshipSaveRequestPrivate, parent)
{
}

/*! Frees any memory used by this request */
QContactRelationshipSaveRequest::~QContactRelationshipSaveRequest()
{
    QContactAbstractRequestPrivate::notifyEngine(this);
}

/*!
  Sets the relationship to save to be \a contactRelationship.
  Equivalent to calling:
  \code
      setRelationships(QList<QContactRelationship>() << contactRelationships);
  \endcode
 */
void QContactRelationshipSaveRequest::setRelationship(const QContactRelationship& contactRelationship)
{
    Q_D(QContactRelationshipSaveRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_relationships.clear();
    d->m_relationships.append(contactRelationship);
}

/*! Sets the relationships to save to be \a contactRelationships
*/
void QContactRelationshipSaveRequest::setRelationships(const QList<QContactRelationship>& contactRelationships)
{
    Q_D(QContactRelationshipSaveRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_relationships = contactRelationships;
}

/*! Returns the list of relationships that will be saved if called prior to calling \c start(),
    otherwise returns the list of relationships as they were saved in the contacts store
*/
QList<QContactRelationship> QContactRelationshipSaveRequest::relationships() const
{
    Q_D(const QContactRelationshipSaveRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_relationships;
}

/*! Returns the map of input relationship list indices to errors which occurred
*/
QMap<int, QContactManager::Error> QContactRelationshipSaveRequest::errorMap() const
{
    Q_D(const QContactRelationshipSaveRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_errors;
}

#include "moc_qcontactrelationshipsaverequest.cpp"

QTCONTACTS_END_NAMESPACE
