#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <string>

using namespace std;

class weapon {
public:
    string name;
    int damage, strength, durability, price, kills;
    weapon(const string& name, int damage, int strength, int durability, int kills, int price) :
        name(name),damage(damage),strength(strength),durability(durability), price(price),kills(kills){};

    bool use(){
        durability -= 1;
        if (durability == 0){
            cout << "Your weapon was broken!\n";
            return 1;
        }
        else{
            return 0;
        }
    };
    ~weapon() {
    }

};
#endif // WEAPON_H
