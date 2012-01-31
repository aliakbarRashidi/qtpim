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


#ifndef QDECLARATIVECONTACTPHONENUMBER_H
#define QDECLARATIVECONTACTPHONENUMBER_H

#include "qdeclarativecontactdetail_p.h"
#include "qcontactphonenumber.h"
#include <QSet>

QTCONTACTS_BEGIN_NAMESPACE

class  QDeclarativeContactPhoneNumber : public QDeclarativeContactDetail
{
    Q_OBJECT

    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY valueChanged)
    Q_PROPERTY(QVariant subTypes READ subTypes WRITE setSubTypes NOTIFY valueChanged)
    Q_ENUMS(FieldType)
    Q_ENUMS(PhoneNumberSubType)

    Q_CLASSINFO("DefaultProperty", "number")
public:
    enum FieldType {
        Number = 0,
        SubTypes
    };

    enum PhoneNumberSubType {
        Unknown = 0,
        Landline,
        Mobile,
        Fax,
        Pager,
        Voice,
        Modem,
        Video,
        Car,
        BulletinBoardSystem,
        MessagingCapable,
        Assistant,
        DtmfMenu
    };

    QDeclarativeContactPhoneNumber(QObject* parent = 0)
        :QDeclarativeContactDetail(parent)
    {
        setDetail(QContactPhoneNumber());
        connect(this, SIGNAL(valueChanged()), SIGNAL(detailChanged()));
    }
    ContactDetailType detailType() const
    {
        return QDeclarativeContactDetail::PhoneNumber;
    }
    static QString fieldNameFromFieldType(int fieldType)
    {
        switch (fieldType) {
        case Number:
            return QContactPhoneNumber::FieldNumber;
        case SubTypes:
            return QContactPhoneNumber::FieldSubTypes;
        default:
            break;
        }
        qmlInfo(0) << tr("Unknown field type.");
        return QString();
    }
    void setNumber(const QString& v)
    {
        if (!readOnly() && v != number()) {
            detail().setValue(QContactPhoneNumber::FieldNumber, v);
            emit valueChanged();
        }
    }
    QString number() const {return detail().value(QContactPhoneNumber::FieldNumber).toString();}


    void setSubTypes(const QVariant& v)
    {
        QStringList savedList;
        foreach (const QVariant subType, v.toList()) {
            if (subType.type() != QVariant::String) {
                switch (subType.toInt())
                {
                case Landline:
                    savedList << QContactPhoneNumber::SubTypeLandline;
                    break;
                case Mobile:
                    savedList << QContactPhoneNumber::SubTypeMobile;
                    break;
                case Fax:
                    savedList << QContactPhoneNumber::SubTypeFax;
                    break;
                case Pager:
                    savedList << QContactPhoneNumber::SubTypePager;
                    break;
                case Voice:
                    savedList << QContactPhoneNumber::SubTypeVoice;
                    break;
                case Modem:
                    savedList << QContactPhoneNumber::SubTypeModem;
                    break;
                case Video:
                    savedList << QContactPhoneNumber::SubTypeVideo;
                    break;
                case Car:
                    savedList << QContactPhoneNumber::SubTypeCar;
                    break;
                case BulletinBoardSystem:
                    savedList << QContactPhoneNumber::SubTypeBulletinBoardSystem;
                    break;
                case MessagingCapable:
                    savedList << QContactPhoneNumber::SubTypeMessagingCapable;
                    break;
                case Assistant:
                    savedList << QContactPhoneNumber::SubTypeAssistant;
                    break;
                case DtmfMenu:
                    savedList << QContactPhoneNumber::SubTypeDtmfMenu;
                    break;
                default:
                    qmlInfo(this) << tr("Unknown sub type.");
                    break;

                }
            } else {
                savedList << subType.toString();
            }
        }
        QStringList oldList = detail().value<QStringList>(QContactPhoneNumber::FieldSubTypes);
        if (!readOnly() && oldList.toSet() != savedList.toSet()) {
            detail().setValue(QContactPhoneNumber::FieldSubTypes, savedList);
            emit valueChanged();
        }
    }

    QVariant subTypes() const
    {
        return QVariant::fromValue(detail().value<QStringList>(QContactPhoneNumber::FieldSubTypes));
    }

signals:
    void valueChanged();

};

QTCONTACTS_END_NAMESPACE

QML_DECLARE_TYPE(QTCONTACTS_PREPEND_NAMESPACE(QDeclarativeContactPhoneNumber))

#endif

