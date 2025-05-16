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
    int gold, level;
    vector<enemy> enemies;
    Cave(int level)
        : name(autoName()), gold()
    {

    }
    string autoName(){ //generate name for cave
        srand(time(0)); //så rand() faktisk er random
        string verbs[10] = {"Enchanted", "Bewitched", "Cursed", "Blessed", "Hallowed", "Haunted", "Shrouded", "Defiled", "Forsaken", "Entombed"};
        string nouns[10] = {"Grotto","Hollow","Chasm","Cavern","Abyss","Vault","Sanctum","Catacomb","Labyrinth","Crypt"};
        return verbs[rand() % 11] + " " + nouns[rand() % 11];
    }
};
void fightIndividually(const vector<enemy> enemies, Hero hero){
    int choice;
    cout << "choose an enemy to fight!" <<endl;
    for (int i = 1; i < enemies.size()+1; i++){
        cout << i << ": " << enemies[i-1].name << " hp: " <<enemies[i-1].hp << " damage: " << enemies[i-1].damage << endl;
    }
    cin >> choice;
    cout << endl << "you have chosen to fight: " << enemies[choice-1].name << endl << "let the battle commence!" <<endl <<endl;
    if(Battle(hero, enemies[choice-1])){
        hero.xp += enemies[choice-1].xpReward;
        hero.tryLevelUp();
    }
}
void enterCave(const vector<enemy> enemies, Hero hero){


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

    const vector<enemy> enemies = {
        {"Hest",               4, 1,  100},
        {"Weak Goblin",        4, 2,  200},
        {"Strong Goblin",      8, 3,  400},
        {"Stronger Goblin",   10, 4,  500},
        {"Den staerkeste Goblin",15,5,  800},
        {"Abe Kongen",        30, 5, 1000},
        {"Enhjoorning",         5, 8, 1500}
    };

    while(true){
        cout << "do you want to save and exit your game [0], fight monsters individually? [1] or enter a cave and fight many monsters? [2]" <<endl;
        // cin.ignore();
        cin >> choice;

        switch(choice){
        case 0:
            hero.showStats();
            hero.saveCharacter();
            game();
        case 1:
            fightIndividually(enemies, hero);
            break;
        case 2:
            //enterCave(enemies, hero);
            break;
        default:
            cout << "ugyldigt valg" << endl;
        }





    }
}
int main()
{
    game();
    //Cave cave(10);
    //cout << cave.name;
}
