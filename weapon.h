#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <string>

using namespace std;

class weapon {
public:
    std::string name;
    int damage, strength, durability, price;
    weapon(const string& name, int damage, int strength, int durability, int price);

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
};
#endif // WEAPON_H
