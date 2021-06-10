#pragma once

#include "ConnectionsSafeTypes.hpp"

#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <chrono>

namespace Qv2rayPlugin::Connections::_base_types
{
    const static inline ConnectionId NullConnectionId;

    const static inline GroupId NullGroupId;
    const static inline GroupId DefaultGroupId{ "000000000000" };

    const static inline RoutingId NullRoutingId;
    const static inline RoutingId DefaultRoutingId{ "000000000000" };

    struct ConnectionGroupPair
    {
        ConnectionId connectionId = NullConnectionId;
        GroupId groupId = NullGroupId;

        // clang-format off
        ConnectionGroupPair(){};
        ConnectionGroupPair(const ConnectionId &conn, const GroupId &group) { connectionId = conn, groupId = group; }
        inline bool operator==(const ConnectionGroupPair &rhs) const { return connectionId == rhs.connectionId && groupId == rhs.groupId; }
        inline bool operator!=(const ConnectionGroupPair &rhs) const { return !(*this == rhs); }
        inline void clear() { connectionId = NullConnectionId, groupId = NullGroupId; }
        inline bool isNull() const { return groupId == NullGroupId || connectionId == NullConnectionId; }
        // clang-format on
    };

    struct ConfigObjectBase
    {
        QString name;
        QVariantMap attributes;
        system_clock::time_point created = system_clock::now();
        system_clock::time_point updated = system_clock::now();
    };

    struct ConnectionObject : public ConfigObjectBase
    {
        system_clock::time_point last_connected;
        int _group_ref = 0;
    };

    struct GroupObject : public ConfigObjectBase
    {
        QList<ConnectionId> connections;
        RoutingId route_id = NullRoutingId;
    };

    struct RoutingObject : public ConfigObjectBase
    {
        int _group_ref = 0;
    };

} // namespace Qv2rayPlugin::Connections::_base_types

// Expose all basic type decls to global namespace
using namespace Qv2rayPlugin::Connections::_base_types;

Q_DECLARE_METATYPE(ConnectionGroupPair)
Q_DECLARE_METATYPE(ConnectionObject)
Q_DECLARE_METATYPE(GroupObject)
Q_DECLARE_METATYPE(RoutingObject)
