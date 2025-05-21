#include <iostream>
#include <vector>
#include <cstdlib> //for rand
#include <ctime> //for time
#include "Hero.h"
#include "enemy.h"
#include "Battle.cpp"
using namespace std;

class Cave {
public:
    string name;
    int reward, level;
    vector<enemy> enemies;
    Cave(int level)
        : name(autoName()), reward(){}

    //funkion der lægger enemy til enemies tager input af enemien og hvor mange der er (antal er int antal gange 1.5*lvl eller s¨ådan noget pis)
    void addEnemy(enemy enemy, int number){
        for (int i = 0; i < number; i++){
        enemies.push_back(enemy);
        }
    }
    string autoName(){ //generate name for cave
        srand(time(0)); //så rand() faktisk er random
        string verbs[10] = {"Enchanted", "Bewitched", "Cursed", "Blessed", "Hallowed", "Haunted", "Shrouded", "Defiled", "Forsaken", "Entombed"};
        string nouns[10] = {"Grotto","Hollow","Chasm","Cavern","Abyss","Vault","Sanctum","Catacomb","Labyrinth","Crypt"};
        return verbs[rand() % 11] + " " + nouns[rand() % 11];
    }

};
void fightIndividually(Hero& hero) {
    int choice;
    const vector<enemy> enemies = {
        {"Hest",               4, 1,  100},
        {"Weak Goblin",        4, 2,  200},
        {"Strong Goblin",      8, 3,  400},
        {"Stronger Goblin",   10, 4,  500},
        {"Den staerkeste Goblin",15,5,  800},
        {"Abe Kongen",        30, 5, 1000},
        {"Enhjoorning",         5, 8, 1500}
    };
    cout << "choose an enemy to fight!" <<endl;
    for (int i = 1; i < enemies.size()+1; i++){
        cout << i << ": " << enemies[i-1].name << " hp: " <<enemies[i-1].hp << " damage: " << enemies[i-1].damage << endl;
    }
    cin >> choice;
    if (choice > enemies.size() || choice < 1){
        std::cout << "Invalid choice!\n";
        return;
    }
    cout << endl << "you have chosen to fight: " << enemies[choice-1].name << endl << "let the battle commence!" <<endl <<endl;
    if(Battle(hero, enemies[choice-1])){
        hero.xp += enemies[choice-1].xpReward;
        hero.tryLevelUp();
    }
}
void enterCave(Hero& hero){
    int choice;
    cout << "Choose to enter one of the following caves:\n1: goblin cave [easy]\n2: spider cave [medium]\n3: skeleton cave [hard]\n4: dragon cave [hardest]\n";
    cin >> choice;
    if (choice > 4 || choice < 1){
        std::cout << "Invalid choice!\n";
        enterCave(hero);
    }

    Cave cave(hero.level);
    switch(choice) {
    case 1: { //goblin cave
        enemy weakGoblin({"Weak Goblin", 4+(hero.level/3), 2+(hero.level/4),  200*hero.level});
        cave.addEnemy(weakGoblin,2+(hero.level/3));
        enemy strongGoblin({"Strong Goblin", 8+(hero.level/3), 3+(hero.level/4),  400*hero.level});
        cave.addEnemy(strongGoblin,1+(hero.level/2));
        enemy strongerGoblin({"Stronger Goblin", 10+(hero.level/2), 4+(hero.level/3),  500*hero.level});
        cave.addEnemy(strongerGoblin,(hero.level/3)); //one for every 3 levels
        enemy strongestGoblin({"Strongest Goblin", 20,5,1000});
        cave.addEnemy(strongestGoblin,(hero.level/10)); //unlocks at level 10
        break;
    }
    case 2: { //spider cave

        break;
     }
    case 3: { //skeleton cave

         break;
     }
    case 4: { //dragon cave

        break;
     }
    default:
        std::cout << "Invalid choice!\n";
        return;
    }

}
void chooseWeapon(){

}
void game(){
    int choice;
    int hp, str, lvl, xp;
    string name;
    cout << "type '0' to load a previous character or press '1' to create a new character" << endl;
    cin >> choice;

    if (choice == 1){
        cout << "Please enter the name of your new character!" <<endl;
        cin >> name;
    };
    Hero hero(name);
    if (choice == 0){
        cout << "please enter the name of the character you wish to load" <<endl;
        cin >> name;
        fstream file(name + ".txt");
        string line;
        getline(file, line);
        file >> hp >> xp >>str >> lvl;

        hero.name = name;
        hero.damage = str;
        hero.level = lvl;
        hero.xp = xp;
        hero.hp = hp;

    };
    cout << "A hero named " << hero.name << " has arrived!" <<endl;
    hero.showStats();



    while(true){
        cout << "do you want to save and exit your game [0]\nfight monsters individually? [1]\nenter a cave and fight many monsters? [2]" <<endl;
        // cin.ignore();
        cin >> choice;

        switch(choice){
        case 0:
            hero.showStats();
            hero.saveCharacter();
            return;
        case 1:
            fightIndividually(hero);
            break;
        case 2:
            enterCave(hero);
            break;
        default:
            cout << "Invalid choice!\n" << endl;
        }





    }
}
int main()
{
    game();
    //Cave cave(10);
    //cout << cave.name;
}
