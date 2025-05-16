#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
    //kunne også have lavet en superklasse til hero og enemy hvor variabler som "name" og "damage" er under.
class Hero {
public:
    string name;
    int xp;
    int level;
    int hp;
    int damage;
    int requiredxp;

    Hero(const string& name)
        : name(name), xp(0),level(1),hp(10), damage(2){
    }

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
             << "level: " << level << endl << "damage: " << damage << endl;
    }
    void saveCharacter() {
        ofstream file(name + ".txt", ios::out | ios::trunc);
        if (!file.is_open()) {
            cerr << "ERROR: could not open file for writing\n";
            return;
        }
        file << level << endl << damage << endl << xp << endl << hp << endl;
        cout << "character saved" << endl;
    }
};
class enemy{
public:
    string name;
    int hp;
    int damage;
    int xpReward;
};

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

int main()
{
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

    vector<enemy> enemies = {
        {"Hest",               4, 1,  100},
        {"Weak Goblin",        4, 2,  200},
        {"Strong Goblin",      8, 3,  400},
        {"Stronger Goblin",   10, 4,  500},
        {"Den staerkeste Goblin",15,5,  800},
        {"Abe Kongen",        30, 5, 1000},
        {"Enhjoorning",         5, 8, 1500}
    };
    while(true){
        cout << "do you want to save and exit your game [0] or fight monsters? [1]" <<endl;
       // cin.ignore();
        cin >> choice;
        if (choice == 0){
            hero.showStats();
            hero.saveCharacter();
            break;
        }

        if (choice != 1){
            cout << "ugyldigt valg" << endl;
            continue;
        }

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
        else{
            break; //maybe main();
        }



    }


}
