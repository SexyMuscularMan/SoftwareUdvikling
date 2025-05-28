#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <QSqlDatabase>

void alphabet(QSqlDatabase db);
void monstersKilled(QSqlDatabase db);
void weaponKillsHero(QSqlDatabase db);
void weaponKillsWeapon(QSqlDatabase db);
void Analytics(QSqlDatabase db);

#endif
