#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <fstream>
using namespace std;
class Hero {     //kunne også have lavet en superklasse til hero og enemy hvor variabler som "name" og "damage" er under.
public:
    string name;
    int xp;
    int level;
    int hp;
    int damage;
    int requiredxp;

    Hero(const string& name)
        : name(name), xp(0),level(1),hp(10), damage(2){
    }

    void tryLevelUp(){
        requiredxp = level*1000;
        if (xp >= requiredxp){
            level += 1;
            xp = xp-requiredxp;
            hp += 2;
            damage += 1;
            cout << endl << name << " leveled up!" << endl << name << " is now level " << level << endl;
            showStats();
        }
    }

    void showStats(){
        cout << "your stats are: " << endl << "xp: " << xp << endl
             << "level: " << level << endl << "damage: " << damage << endl;
    }
    void saveCharacter() {
        ofstream file(name + ".txt", ios::out | ios::trunc);
        if (!file.is_open()) {
            cerr << "ERROR: could not open file for writing\n";
            return;
        }
        file << level << endl << damage << endl << xp << endl << hp << endl;
        cout << "character saved" << endl;
    }
};
#endif // HERO_H
