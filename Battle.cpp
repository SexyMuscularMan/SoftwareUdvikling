#include "Hero.h"
#include "enemy.h"
#include <unistd.h>  // For sleep()
bool Battle(Hero hero, enemy enemy){
    cin.ignore ();
    cout << "you encounter a " << enemy.name << endl;
    sleep(1);
    while (true) {
        enemy.hp -= hero.damage;
        cout << "You damage the " << enemy.name << " for " << hero.damage <<" hp!\n";
        cout << enemy.name << " has " << enemy.hp << " hp remaining" << endl;
        sleep(1);
        if (enemy.hp <= 0) {
            cout << enemy.name << " defeated! You won!" << endl << "you have gained: " << enemy.xpReward << "xp!" <<endl;
            return 1;
            break;
        }
        hero.hp -= enemy.damage;
        cout << enemy.name << " damages you for " << enemy.damage << " hp!\n";
        cout << hero.name  << " has " << hero.hp  << " hp remaining" << endl;
        if (hero.hp <= 0){
            cout << hero.name << " has fallen in battle and must retreat." << endl;
            return 0;
            break;
        }
        cout << "Press enter to continue"<< endl;

        cin.ignore();

    }

}
