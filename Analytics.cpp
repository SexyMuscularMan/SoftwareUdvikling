#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <iostream>
#include "Analytics.h"

using namespace std;

void alphabet(QSqlDatabase db){
    QSqlQuery q(db);
    if (!q.exec("SELECT name FROM Heroes ORDER BY name")) {
        cerr << "Error fetching heroes: " << q.lastError().text().toStdString() << endl;
        return;
    }
    cout << "-- Heroes (A to Z) --" << endl;
    while (q.next()) {
        cout << q.value(0).toString().toStdString() << endl;
    }
}
void monstersKilled(QSqlDatabase db){
    QSqlQuery q(db);
    q.prepare(R"(
        SELECT id, kills, name
        FROM Heroes
)");
    if (!q.exec()) {
        cerr << "Error fetching monster kills: " << q.lastError().text().toStdString() << endl;
        return;
    }
    cout << "-- Monsters defeated per Hero --" << endl;
    while (q.next()) {
        int heroId = q.value(0).toInt();
        int kills  = q.value(1).toInt();
        string name  = q.value(2).toString().toStdString();

        cout << heroId << ": " << name << " has defeated " << kills << " monsters" << endl;
    }
}
void weaponKillsHero(QSqlDatabase db){
    //How many monsters a heroes weapons has killed
    cout << "Selects the character you want to load: " <<endl;
    QSqlQuery q(db);
    q.exec("SELECT id, name, level FROM Heroes ORDER BY id");
    while(q.next()){
        cout << q.value(0).toInt() << ": " << q.value(1).toString().toStdString() << " level: " << q.value(2).toInt() << endl;
    }

    uint heroId;
    cout << "Enter hero ID: ";
    cin >> heroId;

    cout << "-- Kills by Weapon for " << q.value(1).toString().toStdString() << " --\n"; //prints name of heroid

    q.finish();
    q.prepare(R"(
        SELECT id,kills,name
        FROM weapons
        WHERE heroID = :choice
)");
    q.bindValue(":choice", heroId);
    if (!q.exec()) {
        cerr << "Error fetching weapon kills for hero: " << q.lastError().text().toStdString() << endl;
        return;
    }
    while (q.next()) {
        cout << q.value(0).toInt()<<": " << q.value(2).toString().toStdString()
        << " - " << q.value(1).toInt() << " kills" << endl;
    }
}
void weaponKillsWeapon(QSqlDatabase db){
    //Every weapon and what hero has killed most monsters with it
    QSqlQuery q(db);
    q.exec("SELECT id, heroID, name, kills FROM weapons ORDER BY id");
    while(q.next()){
        cout << q.value(0).toInt() << ": " << q.value(2).toString().toStdString() << " - " << " most kills: " << q.value(3).toInt() << " by heroID: " << q.value(1).toInt() << endl;
    }
}

void Analytics(QSqlDatabase db){
    while(true){
        cout << "Choose what you want to view!\n\n[1] All heroes in alphabetical order\n[2] How many monsters each hero has killed\n"
             << "[3] How many monsters a heroes weapons has killed\n[4] Every weapon and what hero has killed most monsters with it\n"
             << "[5] Exit analytics\n";

        uint choice;
        cin >> choice;
        switch(choice){
        case 1:
            alphabet(db);
            break;
        case 2:
            monstersKilled(db);
            break;
        case 3:
            weaponKillsHero(db);
            break;
        case 4:
            weaponKillsWeapon(db);
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice!\n" << endl;
        }
    }
}
