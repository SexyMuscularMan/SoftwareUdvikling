#ifndef HERO_H
#define HERO_H
#include "weapon.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Hero {
public:
    string name;
    int xp, level, hp, damage, requiredxp, gold;
    vector<weapon> weapons;
    Hero(const string& name)
        : name(name), xp(0),level(1),hp(10), damage(2), gold(200){
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
    void buy(weapon weapon){
        if (gold > weapon.price){
            gold -= weapon.price;
            weapons.push_back(weapon);
        }
        else{
            cout << "You don't have enough gold to purchase this weapon, get your money up brokie!\n";
        }
    }
    int calculateDamage(weapon weapon){
        return weapon.damage + damage * weapon.strength;
    }
};
#endif // HERO_H
