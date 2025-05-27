#include "Hero.h"
#include "qdir.h"
#include "weapon.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
bool saveCharacter(const Hero& h, QSqlDatabase &db) {

    QSqlQuery q(db);
    q.prepare(R"(
    INSERT OR REPLACE INTO Heroes
      (name, level, xp, hp, damage, gold, requiredxp, kills, unlockedWeapons)
    VALUES
      (:name, :level, :xp, :hp, :damage, :gold, :requiredxp, :kills, :unlockedWeapons)
  )");
    q.bindValue(":name", QString::fromStdString(h.name));
    q.bindValue(":level", h.level);
    q.bindValue(":xp", h.xp);
    q.bindValue(":hp", h.hp);
    q.bindValue(":damage", h.damage);
    q.bindValue(":gold", h.gold);
    q.bindValue(":requiredxp", h.requiredxp);
    q.bindValue(":kills", h.kills);
    q.bindValue(":unlockedWeapons", h.unlockedWeapons.size());

    if (!q.exec())
        qWarning() << "saveHero failed:" << q.lastError().text();

    return q.isActive();
}

bool saveWeapons(const Hero& h, QSqlDatabase &db) {
    //get ID of last hero
    QSqlQuery q1(db);
    q1.exec("SELECT MAX(id) FROM Heroes");
    q1.next();
    int HeroId = q1.value(0).toInt();
    q1.finish();

    //insert every weapon hero has into db
    if (h.weapons.size() < 1) {return true;};
    for(int w = 1; w < h.weapons.size(); w++){
        QSqlQuery q(db);
        q.prepare(R"(
        INSERT OR REPLACE INTO weapons
          (name, heroID, damage, strength, durability, price)
        VALUES
          (:name, :heroID, :damage, :strength, :durability, :price)
      )");
        q.bindValue(":name", QString::fromStdString(h.weapons[w].name));
        q.bindValue(":heroID", HeroId);
        q.bindValue(":damage", h.weapons[w].damage);
        q.bindValue(":strength", h.weapons[w].strength);
        q.bindValue(":durability", h.weapons[w].durability);
        q.bindValue(":price", h.weapons[w].price);
        if (!q.exec()){
            qWarning() << "saveWeapon failed:" << q.lastError().text();
            return false;
        }
        //q.finish();
    }
    return true;
}

bool loadHero(Hero& h, QSqlDatabase &db, int choice) {

    vector<weapon> lockedWeapons = { //to add to unlockedWeapons vector
        {"Knife",5,1,10,200},
        {"Sword",10,2,10,1000},
        {"Morningstar",10,3,20,2000},
        {"Stormbringer",20,3,50,5000}
    };

    QSqlQuery q(db);
    q.prepare(R"(
        SELECT name, level, xp, hp, damage, gold, requiredxp, kills, unlockedWeapons
        FROM heroes
        WHERE id = :choice
  )");
    q.bindValue(":choice", choice);
    q.exec();
    q.next();

    //insert values
    h.name = q.value(0).toString().toStdString();
    h.level = q.value(1).toInt();
    h.xp = q.value(2).toInt();
    h.hp = q.value(3).toInt();
    h.damage = q.value(4).toInt();
    h.gold = q.value(5).toInt();
    h.requiredxp = q.value(6).toInt();
    h.kills = q.value(7).toInt();

    //unlock weapons
    int unlock = q.value(8).toInt()-1;
    for (int i = 0; i < unlock; i++){
        h.unlockedWeapons.push_back(lockedWeapons[i]);
    }

    //load weapons
    q.finish();
    q.prepare(R"(
        SELECT name, damage, strength, durability, price
        FROM weapons
        WHERE heroID = :choice
)");
    q.bindValue(":choice", choice);
    while (q.next()) {
        h.weapons.push_back({q.value(0).toString().toStdString(),q.value(1).toInt(),q.value(2).toInt(),q.value(3).toInt(),q.value(4).toInt()});    }
    return true;
}
void logCombat(const Hero& h, const QString& weaponName)
{
    QSqlQuery q;
    q.prepare(R"(
    INSERT INTO combat_log (hero, enemy, cave, weapon)
    VALUES (:h, :e, :c, :w)
  )");
    q.bindValue(":h", QString::fromStdString(h.name));
    q.bindValue(":w", weaponName);
    if (!q.exec())
        qWarning() << "logCombat failed:" << q.lastError().text();
}
