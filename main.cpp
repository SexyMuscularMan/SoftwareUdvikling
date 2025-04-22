#include <iostream>

using namespace std;
class hero {
public:
    string name;
    int xp;
    int level;
    int hp;
    int damage;

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

    // Resultat
    if (hero.hp <= 0) {
        std::cout << "\n" << hero.name << " er faldet i kamp. Game over.\n";
        break;
    } else {
        std::cout << "\n" << enemy.name << " defeated! You won!\n";
        hero.xp += enemy.xpReward;
        hero.tryLevelUp();
    }

}
int main()
{

    return 0;
}
