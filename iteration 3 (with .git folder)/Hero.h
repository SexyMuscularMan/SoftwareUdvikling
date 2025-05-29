#ifndef HERO_H
#define HERO_H
#include "weapon.h"
#include <iostream>
#include <vector>
using namespace std;
class Hero {
public:
    string name;
    int xp, level, hp, damage, requiredxp, gold, kills;
    vector<weapon> weapons = {weapon("Bare Hands", 0, 1 ,INT_MAX,0,0)};
    vector<weapon> unlockedWeapons = {{"Stick",0,2,5,0,100}};
    weapon &usedWeapon;
    Hero(const string& name)
        : name(name), xp(0),level(1),hp(10), damage(2), requiredxp(1000),
        gold(0), kills(0), usedWeapon(weapons[0]){}

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
             << "level: " << level << endl << "damage: " << damage << endl
             << "gold: " << gold << endl << "kills: " << kills << endl << endl
             << "equipped weapon: " << usedWeapon.name << endl
             << "weapon durability: " << usedWeapon.durability << endl
             << "weapon damage: " << usedWeapon.damage << endl
             << "weapon damage amplifier: "<< usedWeapon.strength <<endl<<endl;
    }
    void buy(weapon &weapon){
        if (gold > weapon.price){
            gold -= weapon.price;
            weapons.push_back(weapon);
        }
        else{
            cout << "You don't have enough gold to purchase this weapon, get your money up brokie!\n";
        }
    }
    int calculateDamage(){
        if (usedWeapon.use()){ //remove from vector if broken
            //weapons.erase(weapons.begin()+1);
            usedWeapon = weapons[0];
        }
        return usedWeapon.damage + damage * usedWeapon.strength;
    }
    vector<weapon> lockedWeapons = { //global vector
        {"Knife",5,1,10,0,200},
        {"Sword",10,2,10,0,1000},
        {"Morningstar",10,3,20,0,2000},
        {"Stormbringer",20,3,50,0,5000}
    };
};
#endif // HERO_H
