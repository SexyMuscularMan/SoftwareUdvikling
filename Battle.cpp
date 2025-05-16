#include "Hero.h"
#include "enemy.h"
bool Battle(Hero hero, enemy enemy){
    cin.ignore ();
    while (true) {
        std::cout << enemy.name << " has " << enemy.hp << " hp remaining" << endl
                  << hero.name  << " has " << hero.hp  << " hp remaining" << endl
                  << "enter any button to continue"<< endl ;
        cin.ignore();

        enemy.hp -= hero.damage;
        if (enemy.hp <= 0) {
            cout << enemy.name << " defeated! You won!" << endl << "you have gained: " << enemy.xpReward << "xp!" <<endl;
            return 1;
            break;
        }

        hero.hp -= enemy.damage;
        if (hero.hp <= 0){
            cout << hero.name << " has fallen in battle. Game over." << endl;
            return 0;
            break;
        }

    }

}
