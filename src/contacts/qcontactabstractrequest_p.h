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

#ifndef QCONTACTABSTRACTREQUEST_P_H
#define QCONTACTABSTRACTREQUEST_P_H

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

#include <qcontactmanager.h>
#include "qcontactmanager_p.h"
#include <qcontactabstractrequest.h>

#include <QList>
#include <QPointer>
#include <QMutex>

#ifndef QT_NO_DEBUG_STREAM
#include <QDebug>
#endif

QTCONTACTS_BEGIN_NAMESPACE

class QContactAbstractRequestPrivate
{
public:
    QContactAbstractRequestPrivate()
        : m_error(QContactManager::NoError),
            m_state(QContactAbstractRequest::InactiveState),
            m_manager(0)
    {
    }

    virtual ~QContactAbstractRequestPrivate()
    {
    }

    virtual QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::InvalidRequest;
    }

    static void notifyEngine(QContactAbstractRequest* request)
    {
        Q_ASSERT(request);
        QContactAbstractRequestPrivate* d = request->d_ptr;
        if (d) {
            QMutexLocker ml(&d->m_mutex);
            QContactManagerEngine *engine = QContactManagerData::engine(d->m_manager);
            ml.unlock();
            if (engine) {
                engine->requestDestroyed(request);
            }
        }
    }

    QContactManager::Error m_error;
    QContactAbstractRequest::State m_state;
    QPointer<QContactManager> m_manager;
    // stored separately so (friend) QContactManagerEngineV2Wrapper can set it directly:
    QPointer<QContactManagerEngine> m_engine;

    mutable QMutex m_mutex;

#ifndef QT_NO_DEBUG_STREAM
    // NOTE: on platforms where Qt is built without debug streams enabled, vtable will differ!
    virtual QDebug& debugStreamOut(QDebug& dbg) const = 0;
#endif
};

QTCONTACTS_END_NAMESPACE

#endif
