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


#ifndef QCONTACTMANAGERENGINEFACTORY_H
#define QCONTACTMANAGERENGINEFACTORY_H

#include <QtPlugin>
#include <QMap>
#include <QString>

#include <qcontactmanager.h>

QTCONTACTS_BEGIN_NAMESPACE
/* Backend plugin API interface, creates engines for us */
class QContactManagerEngine;
class Q_CONTACTS_EXPORT QContactManagerEngineFactory
{
public:
    // engine factory functions
    virtual QList<int> supportedImplementationVersions() const;
    virtual ~QContactManagerEngineFactory();
    virtual QContactManagerEngine* engine(const QMap<QString, QString> &parameters, QContactManager::Error *error) = 0;
    virtual QContactEngineId* createContactEngineId(const QMap<QString, QString> &parameters, const QString &engineIdString) const = 0;
    virtual QString managerName() const = 0;
};
QTCONTACTS_END_NAMESPACE

QT_BEGIN_NAMESPACE
#define QT_CONTACTS_BACKEND_INTERFACE "org.qt-project.Qt.QContactManagerEngineFactory"
Q_DECLARE_INTERFACE(QtContacts::QContactManagerEngineFactory, QT_CONTACTS_BACKEND_INTERFACE)
QT_END_NAMESPACE

#endif
