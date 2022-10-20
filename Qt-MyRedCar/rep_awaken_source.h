#ifndef REP_AWAKEN_SOURCE_H
#define REP_AWAKEN_SOURCE_H

// This is an autogenerated file.
// Do not edit this file, any changes made will be lost the next time it is generated.

#include <QtCore/qobject.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qvariant.h>
#include <QtCore/qmetatype.h>

#include <QtRemoteObjects/qremoteobjectnode.h>
#include <QtRemoteObjects/qremoteobjectsource.h>


class awakenSource : public QObject
{
    Q_OBJECT
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_TYPE, "awaken")
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_SIGNATURE, "4c4c86c06dd2ba86416463260a92055c7487992a")

public:
    explicit awakenSource(QObject *parent = nullptr) : QObject(parent)
    {
    }

public:
    ~awakenSource() override = default;


public Q_SLOTS:
    virtual void awaken() = 0;

private:
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};


class awakenSimpleSource : public awakenSource
{
    Q_OBJECT

public:
    explicit awakenSimpleSource(QObject *parent = nullptr) : awakenSource(parent)
    {
    }

public:
    ~awakenSimpleSource() override = default;


private:
};


template <class ObjectType>
struct awakenSourceAPI : public SourceApiMap
{
    awakenSourceAPI(ObjectType *object, const QString &name = QLatin1String("awaken"))
        : SourceApiMap(), m_name(name)
    {
        Q_UNUSED(object);
        m_enums[0] = 0;
        m_properties[0] = 0;
        m_signals[0] = 0;
        m_methods[0] = 1;
        m_methods[1] = QtPrivate::qtro_method_index<ObjectType>(&ObjectType::awaken, static_cast<void (QObject::*)()>(0),"awaken()",m_methodArgCount+0,&m_methodArgTypes[0]);
    }

    QString name() const override { return m_name; }
    QString typeName() const override { return QStringLiteral("awaken"); }
    int enumCount() const override { return m_enums[0]; }
    int propertyCount() const override { return m_properties[0]; }
    int signalCount() const override { return m_signals[0]; }
    int methodCount() const override { return m_methods[0]; }
    int sourceEnumIndex(int index) const override
    {
        if (index < 0 || index >= m_enums[0])
            return -1;
        return m_enums[index+1];
    }
    int sourcePropertyIndex(int index) const override
    {
        if (index < 0 || index >= m_properties[0])
            return -1;
        return m_properties[index+1];
    }
    int sourceSignalIndex(int index) const override
    {
        if (index < 0 || index >= m_signals[0])
            return -1;
        return m_signals[index+1];
    }
    int sourceMethodIndex(int index) const override
    {
        if (index < 0 || index >= m_methods[0])
            return -1;
        return m_methods[index+1];
    }
    int signalParameterCount(int index) const override { Q_UNUSED(index); return -1; }
    int signalParameterType(int sigIndex, int paramIndex) const override
    { Q_UNUSED(sigIndex); Q_UNUSED(paramIndex); return -1; }
    int methodParameterCount(int index) const override
    {
        if (index < 0 || index >= m_methods[0])
            return -1;
        return m_methodArgCount[index];
    }
    int methodParameterType(int methodIndex, int paramIndex) const override
    {
        if (methodIndex < 0 || methodIndex >= m_methods[0] || paramIndex < 0 || paramIndex >= m_methodArgCount[methodIndex])
            return -1;
        return m_methodArgTypes[methodIndex][paramIndex];
    }
    int propertyIndexFromSignal(int index) const override
    {
        Q_UNUSED(index);
        return -1;
    }
    int propertyRawIndexFromSignal(int index) const override
    {
        Q_UNUSED(index);
        return -1;
    }
    const QByteArray signalSignature(int index) const override
    {
        Q_UNUSED(index);
        return QByteArrayLiteral("");
    }
    QList<QByteArray> signalParameterNames(int index) const override
    {
        if (index < 0 || index >= m_signals[0])
            return QList<QByteArray>();
        return ObjectType::staticMetaObject.method(m_signals[index + 1]).parameterNames();
    }
    const QByteArray methodSignature(int index) const override
    {
        switch (index) {
        case 0: return QByteArrayLiteral("awaken()");
        }
        return QByteArrayLiteral("");
    }
    QMetaMethod::MethodType methodType(int) const override
    {
        return QMetaMethod::Slot;
    }
    QList<QByteArray> methodParameterNames(int index) const override
    {
        if (index < 0 || index >= m_methods[0])
            return QList<QByteArray>();
        return ObjectType::staticMetaObject.method(m_methods[index + 1]).parameterNames();
    }
    const QByteArray typeName(int index) const override
    {
        switch (index) {
        case 0: return QByteArrayLiteral("void");
        }
        return QByteArrayLiteral("");
    }
    QByteArray objectSignature() const override { return QByteArray{"4c4c86c06dd2ba86416463260a92055c7487992a"}; }

    int m_enums[1];
    int m_properties[1];
    int m_signals[1];
    int m_methods[2];
    const QString m_name;
    int m_methodArgCount[1];
    const int* m_methodArgTypes[1];
};

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE


#endif // REP_AWAKEN_SOURCE_H