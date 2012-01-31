/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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

#ifndef MALICIOUSPLUGINTARGET
#define MALICIOUSPLUGINTARGET contacts_maliciousplugin
#endif

#ifndef MALICIOUSPLUGINNAME
#define MALICIOUSPLUGINNAME maliciousplugin
#endif

#define makestr(x) (#x)
#define makename(x) makestr(x)

#include "maliciousplugin_p.h"
#include "qcontactmanager.h"

#include <QThread>
#include <QMutex>
#include <QSet>
#include <QDebug>

class MaliciousThreadObject : public QObject
{
    Q_OBJECT
public:
    MaliciousThreadObject() {}

public slots:
    void activateRequest(QContactAbstractRequest* req)
    {
        mutex.lock();
        if (activeRequests.contains(req)) {
            QContactManagerEngine::updateRequestState(req, QContactAbstractRequest::ActiveState);
        }
        mutex.unlock();
    }

    void finishRequest(QContactAbstractRequest* req)
    {
        QContactManager::Error errorResult = QContactManager::NoError;
        QMap<int, QContactManager::Error> errorsResult;
        QList<QContactId> idResult;
        QList<QContact> contactResult;
        QList<QContactRelationship> relResult;

        mutex.lock();
        if (activeRequests.contains(req)) {
            switch(req->type()) {
                case QContactAbstractRequest::ContactIdFetchRequest:
                    QContactManagerEngine::updateContactIdFetchRequest(static_cast<QContactIdFetchRequest*>(req), idResult, errorResult, QContactAbstractRequest::FinishedState);
                    break;

                case QContactAbstractRequest::ContactFetchRequest:
                    QContactManagerEngine::updateContactFetchRequest(static_cast<QContactFetchRequest*>(req), contactResult, errorResult, QContactAbstractRequest::FinishedState);
                    break;

                default:
                    QContactManagerEngine::updateRequestState(req, QContactAbstractRequest::FinishedState);
                    break;
            }
        }
        activeRequests.remove(req);
        mutex.unlock();
    }
public:
    QMutex mutex;

    QSet<QContactAbstractRequest*> activeRequests;
};

class MaliciousThread : public QThread
{
    Q_OBJECT;
public:
    MaliciousThread();
    ~MaliciousThread();
    QObject* eventLoopQuitHack;
};

MaliciousThread::MaliciousThread()
{
    eventLoopQuitHack = new QObject;
    eventLoopQuitHack->moveToThread(this);
    connect(eventLoopQuitHack, SIGNAL(destroyed(QObject*)), SLOT(quit()), Qt::DirectConnection);
}

MaliciousThread::~MaliciousThread()
{
    eventLoopQuitHack->deleteLater();
    wait();
}

MaliciousAsyncManagerEngine::MaliciousAsyncManagerEngine()
        : QContactManagerEngine()
{
    thread = new MaliciousThread();
    threadObject = new MaliciousThreadObject();
    threadObject->moveToThread(thread);

    connect(this, SIGNAL(doStartRequest(QContactAbstractRequest*)), threadObject, SLOT(activateRequest(QContactAbstractRequest*)));
    connect(this, SIGNAL(doFinishRequest(QContactAbstractRequest*)), threadObject, SLOT(finishRequest(QContactAbstractRequest*)));

    thread->start();
}

MaliciousAsyncManagerEngine::~MaliciousAsyncManagerEngine()
{
    delete thread;
    delete threadObject;
}

QString MaliciousAsyncManagerEngine::synthesizedDisplayLabel(const QContact& contact, QContactManager::Error* error) const
{
    Q_UNUSED(contact);
    *error = QContactManager::NotSupportedError;
    return QString();
}

QString MaliciousAsyncManagerEngine::managerName() const
{
    return QString(makename(MALICIOUSPLUGINNAME));
}

bool MaliciousAsyncManagerEngine::startRequest(QContactAbstractRequest* req)
{
    threadObject->mutex.lock();
    threadObject->activeRequests.insert(req);
    threadObject->mutex.unlock();

    // Spawn a thread to do stuff on another thread
    emit doStartRequest(req);
    emit doFinishRequest(req);

    return true;
}

bool MaliciousAsyncManagerEngine::cancelRequest(QContactAbstractRequest *req)
{
    updateRequestState(req, QContactAbstractRequest::CanceledState);
    QContactManagerEngine::cancelRequest(req);
    return true;
}

void MaliciousAsyncManagerEngine::requestDestroyed(QContactAbstractRequest *req)
{
    threadObject->mutex.lock();
    threadObject->activeRequests.remove(req);
    threadObject->mutex.unlock();
    QContactManagerEngine::requestDestroyed(req);
}

QString MaliciousEngineFactory::managerName() const
{
    return QString(makename(MALICIOUSPLUGINNAME));
}

QContactManagerEngine* MaliciousEngineFactory::engine(const QMap<QString, QString>& parameters, QContactManager::Error* error)
{
    Q_UNUSED(parameters);
    *error = QContactManager::NoError;
    return new MaliciousAsyncManagerEngine();
}

QContactEngineId* MaliciousEngineFactory::createContactEngineId(const QMap<QString, QString>& parameters, const QString& engineIdString) const
{
    Q_UNUSED(parameters);
    Q_UNUSED(engineIdString);
    return 0;
}

Q_EXPORT_PLUGIN2(MALICIOUSPLUGINTARGET, MaliciousEngineFactory);

#include "maliciousplugin.moc"
