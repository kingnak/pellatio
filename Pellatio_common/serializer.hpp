#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "pellatio_common_global.h"
#include <QVariant>

// Base types
template <class T>
void operator << (QVariant &data, const T &target) {
    data = QVariant::fromValue<T>(target);
}

template <class T>
void operator >> (const QVariant &data, T &target) {
    target = data.value<T>();
}

// Pair
template <class F, class S>
void operator << (QVariant &data, const QPair<F,S> &target) {
    QVariantMap m;
    m["first"] << target.first;
    m["second"] << target.second;
    data << m;
}

template <class F, class S>
void operator >> (const QVariant &data, QPair<F,S> &target) {
    QVariantMap m;
    data >> m;
    m["first"] >> target.first;
    m["second"] >> target.second;
}

// List
template <class T>
void operator << (QVariant &data, const QList<T> &target) {
    QVariantList l;
    l.reserve(target.size());
    for (int i = 0; i < target.size(); ++i) {
        QVariant v;
        v << target[i];
        l << v;
    }
    data = l;
}

template <class T>
void operator >> (const QVariant &data, QList<T> &target) {
    target.clear();
    QVariantList l = data.toList();
    target.reserve(l.size());
    for (int i = 0; i < l.size(); ++i) {
        T t;
        l[i] >> t;
        target << t;
    }
}

// Enum
#define DECLARE_ENUM_SERIALIZER(E) \
    void operator <<(QVariant &, const E &); \
    void operator >>(const QVariant &, E &)

#define DECLARE_ENUM_SERIALIZER_EXPORT(EXPORTER,E) \
    EXPORTER void operator <<(QVariant &, const E &); \
    EXPORTER void operator >>(const QVariant &, E &)

#define DEFINE_ENUM_SERIALIZER(E) \
    void operator <<(QVariant &data, const E &e) { \
        data << static_cast<qint32> (e); \
    } \
    void operator >>(const QVariant &data, E &e) { \
        qint32 d; \
        data >> d; \
        e = static_cast<E> (d); \
    }

// Marker
#define DECLARE_SERIALIZABLE(cls) \
    friend void operator <<(QVariant &, const cls &);\
    friend void operator >>(const QVariant &, cls &)

#define DECLARE_SERIALIZABLE_EXPORT(EXPORTER, cls) \
    EXPORTER friend void operator <<(QVariant &, const cls &);\
    EXPORTER friend void operator >>(const QVariant &, cls &)

#endif // SERIALIZER_HPP
