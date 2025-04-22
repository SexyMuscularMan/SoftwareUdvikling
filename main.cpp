#include <iostream>

using namespace std;
    //kunne også have lavet en superklasse til hero og enemy hvor variabler som "name" og "damage" er under.
class hero {
public:
    string name;
    int xp;
    int level;
    int hp;
    int damage;
    int requiredxp;

    void tryLevelUp(){
        requiredxp = level*1000;
        if (xp >= requiredxp){
            level += 1;
            xp = 0;
            hp += 2;
            damage += 1;
            cout << endl << name << "leveled up!" << endl << name << "is now level" << level << endl;
        }

    }
};
class enemy{
public:
    string name;
    int hp;
    int damage;
    int xpReward;



};

void Battle(hero hero, enemy enemy){
    while (true) {
        std::cout << "\n"
        << enemy.name << " with " << enemy.hp << " remaining life\n"
        << hero.name  << " with " << hero.hp  << " hp\n";
        cin;
        // Helten slår først
        enemy.hp -= hero.damage;
        if (enemy.hp <= 0) {
            cout << hero.name << " has fallen in battle. Game over.\n";
            break;
        }

        // Fjenden slår tilbage
        hero.hp -= enemy.damage;
        if (hero.hp <= 0){
            cout << enemy.name << " defeated! You won!\n";
            break;
        }

    }

}
int main()
{

    return 0;
}
