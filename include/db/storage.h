#pragma once

#include <string>
#include <sqlite_orm/sqlite_orm.h>

#include "entities/Assignment.h"
#include "entities/Research.h"
#include "entities/Action.h"
#include "entities/Sensor.h"
#include "entities/SensorUsage.h"
#include "entities/User.h"

template<class... Args, class T, class R>
constexpr auto resolve(R (T::*m)(Args...)) -> decltype(m) { return m; }

template<class T, class R>
constexpr auto resolve(R (T::*m)()) -> decltype(m) { return m; }

inline auto createStorage(const std::string& path) {
    using namespace sqlite_orm;

    auto storage = make_storage(path,
        make_index("researches_author_id_idx", &Research::authorId),
        make_index("actions_ordinal_idx", &Action::ordinal),
        make_index("actions_research_id_idx", &Action::researchId),

        make_unique_index("researches_start_date_idx", &Research::startDate),
        make_unique_index("users_login_idx", &User::login),

        make_table("actions",
            make_column("action_id", &Action::id, primary_key()),
            make_column("ordinal", &Action::ordinal),
            make_column("title", &Action::title),
            make_column("is_required", &Action::isRequired),
            make_column("is_checked", &Action::isChecked),
            make_column("research_id", &Action::researchId),
            sqlite_orm::unique(&Action::researchId, &Action::ordinal),
            foreign_key(&Action::researchId).references(&Research::id)
                .on_update.cascade().on_delete.cascade()
        ),
        make_table("assignments",
            make_column("research_id", &Assignment::researchId),
            make_column("user_id", &Assignment::userId),
            primary_key(&Assignment::researchId, &Assignment::userId),
            foreign_key(&Assignment::researchId).references(&Research::id)
                .on_update.cascade().on_delete.cascade(),
            foreign_key(&Assignment::userId).references(&User::id)
                .on_update.cascade().on_delete.cascade()
        ),
        make_table("researches",
            make_column("research_id", &Research::id, primary_key()),
            make_column("title", &Research::title),
            make_column("start_date", &Research::startDate, unique()),
            make_column("end_date", &Research::endDate),
            make_column("info", &Research::info),
            make_column("author_id", &Research::authorId),
            foreign_key(&Research::authorId).references(&User::id)
                .on_update.cascade().on_delete.set_null()
        ),
        make_table("sensors",
            make_column("sensor_id", &Sensor::id, primary_key()),
            make_column("label", &Sensor::label),
            make_column("type", &Sensor::type),
            make_column("unit", &Sensor::unit),
            sqlite_orm::unique(&Sensor::label, &Sensor::type, &Sensor::unit)
        ),
        make_table("sensor_usage",
            make_column("action_id", &SensorUsage::actionId),
            make_column("sensor_id", &SensorUsage::sensorId),
            primary_key(&SensorUsage::actionId, &SensorUsage::sensorId),
            foreign_key(&SensorUsage::actionId).references(&Action::id)
                .on_update.cascade().on_delete.cascade(),
            foreign_key(&SensorUsage::sensorId).references(&Sensor::id)
                .on_update.cascade().on_delete.cascade()
        ),
        make_table("users",
            make_column("user_id", &User::id, primary_key()),
            make_column("login", &User::login, unique()),
            make_column("display_name", &User::displayName),
            make_column("password_hash", &User::passwordHash),
            make_column("password_salt", &User::passwordSalt),
            make_column("is_admin", &User::isAdmin)
        )
    );

    storage.sync_schema();

    if (storage.count<User>() == 0) {
        User admin{-1, "admin", "admin", "", "", true};
        admin.hashPassword("admin123");
        storage.insert(admin);
    }

    return storage;
}

using Storage = decltype(createStorage(""));
