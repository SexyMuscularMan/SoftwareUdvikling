#include "Hero.h"
#include "enemy.h"
#include <unistd.h>  // For sleep()

//non referential hero function, hp gets restored
bool battle(Hero hero, enemy enemy){
    cin.ignore ();
    cout << "you encounter a " << enemy.name << endl;
    sleep(1);
    while (true) {
        enemy.hp -= hero.calculateDamage();
        cout << "You damage the " << enemy.name << " for " << hero.calculateDamage() <<" hp!\n";
        cout << enemy.name << " has " << enemy.hp << " hp remaining" << endl;
        sleep(1);
        if (enemy.hp <= 0) {
            cout << enemy.name << " defeated! You won!" << endl << "you have gained: " << enemy.xpReward << "xp!" <<endl;
            return true;
            break;
        }
        hero.hp -= enemy.damage;
        cout << enemy.name << " damages you for " << enemy.damage << " hp!\n";
        cout << hero.name  << " has " << hero.hp  << " hp remaining" << endl;
        if (hero.hp <= 0){
            cout << hero.name << " has fallen in battle and must retreat." << endl << endl;
            return false;
            break;
        }
        cout << "Press enter to continue"<< endl;

        cin.ignore();
    }
}

//referential hero
bool Battle(Hero& hero, enemy enemy){
    if (battle(hero, enemy)){
        hero.kills++;
        hero.usedWeapon.kills++;
        return true;
    }
    return false;
}
