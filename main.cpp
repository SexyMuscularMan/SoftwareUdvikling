#include <iostream>
#include <vector>
#include <cstdlib> //for rand
#include <ctime> //for time
#include "Hero.h"
#include <unistd.h>  // For sleep()
#include "enemy.h"
#include "Battle.cpp"
#include "databaseManager.cpp"

using namespace std;
vector<weapon> lockedWeapons = { //global vector
    {"Knife",5,1,10,200},
    {"Sword",10,2,10,1000},
    {"Morningstar",10,3,20,2000},
    {"Stormbringer",20,3,50,5000}
};
int choice;
class Cave {
public:
    string name;
    int reward, weaponReward;
    vector<enemy> enemies;
    Cave()
        : name(autoName()), reward(), weaponReward(){}

    //add enemies to vector
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

    void showEnemies(){
        cout << "Locals say the cave contains: \n";
         for(int i = 0; i < enemies.size(); i++){
             cout <<"a " << enemies[i].name << endl;
         }
    }
    bool enterCave(Hero& hero){
        for (int i = 0; i < enemies.size(); i++){
            if(Battle(hero, enemies[i])){
                hero.xp += enemies[i].xpReward;
                hero.tryLevelUp();
                cout << "Press enter to continue\n";
            }
            else{
                return false;
            }
        }
        return true;
    }
};
void fightIndividually(Hero& hero) {
    int choice;
    const vector<enemy> enemies = {
        {"Horse",              4, 1,  100},
        {"Weak Goblin",        4, 2,  200},
        {"Strong Goblin",      8, 3,  400},
        {"Stronger Goblin",    10, 4,  500},
        {"Strongest Goblin",   15,5,  800},
        {"Monkey King",        30, 5, 1000},
        {"Unicorn",            5, 8, 1500}
    };
    cout << "choose an enemy to fight!" <<endl;
    for (int i = 1; i < enemies.size()+1; i++){
        cout << i << ": " << enemies[i-1].name << " hp: " <<enemies[i-1].hp << " damage: " << enemies[i-1].damage << endl;
    }
    cin >> choice;
    if (choice > enemies.size() || choice < 1){
        cout << "Invalid choice!\n";
        return;
    }
    cout << endl << "you have chosen to fight: " << enemies[choice-1].name << endl << "let the battle commence!" <<endl <<endl;
    if(Battle(hero, enemies[choice-1])){
        hero.xp += enemies[choice-1].xpReward;
        hero.tryLevelUp();
    }
    // else{
    //     return;
    // }
}
void enterCave(Hero& hero){
    int choice;
    cout << "Choose to enter one of the following caves:\n1: goblin cave [easy]\n2: spider cave [medium]\n3: skeleton cave [hard]\n4: dragon cave [hardest]\n";
    cin >> choice;
    /*
    if (choice > 4 || choice < 1){
        std::cout << "Invalid choice!\n";
        enterCave(hero);
    }*/
    Cave cave;
    //switch creates enemies based on cave type and hero level
    switch(choice) {
    case 1: { //goblin cave
        enemy weakGoblin({"Weak Goblin", 4+(hero.level/3), 2+(hero.level/4),  200});
        cave.addEnemy(weakGoblin,2+(hero.level/3));
        enemy strongGoblin({"Strong Goblin", 8+(hero.level/3), 3+(hero.level/4),  400});
        cave.addEnemy(strongGoblin,1+(hero.level/2));
        enemy strongerGoblin({"Stronger Goblin", 10+(hero.level/2), 4+(hero.level/3),  500});
        cave.addEnemy(strongerGoblin,(hero.level/3)); //one for every 3 levels
        enemy strongestGoblin({"Strongest Goblin", 20,5,1000});
        cave.addEnemy(strongestGoblin,(hero.level/10)); //unlocks at level 10
        cave.reward = 200;
        cave.weaponReward = 0;
        break;
    }
    case 2: { //spider cave
        enemy smallSpider({"venomous Spider",3+(hero.level/2), 6+(hero.level/5), 400});
        cave.addEnemy(smallSpider,2+(hero.level/2));
        enemy biggerSpider({"Tarantula",10+5*(hero.level/2), 8+(hero.level/5), 1000});
        cave.addEnemy(biggerSpider,1+(hero.level/3));
        cave.reward = 500;
        cave.weaponReward = 1;

        break;
    }
    case 3: { //skeleton cave
        enemy skeleton({"skeleton",15+5*(hero.level/4), 5+5*(hero.level/5), 1500});
        cave.addEnemy(skeleton,2+2*(hero.level/4));
        enemy wraith({"wraith",30+10*(hero.level/4), 3+3*(hero.level/5), 2000});
        cave.addEnemy(wraith,1+(hero.level/2));
        enemy bigskeleton({"Bone Guardian",50+10*(hero.level/2), 10+5*(hero.level/4), 4000});
        cave.addEnemy(bigskeleton,(hero.level/10));
        cave.reward = 1000;
        cave.weaponReward = 2;

        break;
    }
    case 4: { //dragon cave
        enemy hors({"Horse", 4, 1,  100});
        cave.addEnemy(hors,4);
        enemy dragon({"Dragon",100+20*(hero.level/5), 20+5*(hero.level/4), 10000});
        cave.addEnemy(dragon,1);
        cave.reward = 2000;
        cave.weaponReward = 3;
        break;
    }
    default:
        cout << "Invalid choice!\n";
        return;
    }
    cout << "You head towards the cave known by locals as: " << cave.name << endl;
    sleep(2);
    cave.showEnemies();
    sleep(2);
    cout << "You enter the cave...\n";
    sleep(3);
    if(cave.enterCave(hero)){
        hero.gold += cave.reward;
        cout << "You have cleared the cave!\nThe locals are ecstatic and have given you a reward of: " << cave.reward <<
                "gold!\nYou now have: " << hero.gold <<" gold" << endl;
        hero.unlockedWeapons.push_back(lockedWeapons[cave.weaponReward]); //unlocks weapon based on cleared cave
        cout << "You've unlocked the " << lockedWeapons[cave.weaponReward].name <<endl << endl;
    }
    else{
        return;
    }
}

void buyWeapon(Hero& hero){
    cout << "You have entered the weaponsmith!\n";
    /*if (unlockedWeapons.size() == 0){
        cout << "You have not unlocked any weapons to purchase yet.\n";
        return;
    }*/
    cout << "Choose a weapon to purchase: \n";
    for (int i = 0; i < hero.unlockedWeapons.size(); i++){
        cout << i+1 << ": " << hero.unlockedWeapons[i].name << ", price: " << hero.unlockedWeapons[i].price << endl;
    }
    cin >> choice;
    if (!cin ||choice > hero.unlockedWeapons.size()+3 || choice < 1){
        cout << "Invalid choice!\n";
        cout.clear();
        cin.ignore();
        return;
    }
    hero.buy(hero.unlockedWeapons[choice-1]);
    cout << "You have purchased a " << hero.unlockedWeapons[choice-1].name << "\nYou head back to your armory \n";
}
void enterArmory(Hero& hero){
    cout << "\nYou have entered your armory...\n";
    cout << "Your weapon stash includes:\n";
    for (int i = 0; i < hero.weapons.size(); i++){
        cout << i+1 << ": " << hero.weapons[i].name << endl;
    }
    cout << "Do you want to equip a new weapon [1] or head to the weaponsmith to buy a new weapon? [2]\n";
    cin >> choice;
    if (choice == 1){
        cout << "Choose the weapon you want to equip by number\n";
        cin >> choice;
        hero.usedWeapon = hero.weapons[choice-1];
        cout << "You have equipped a " << hero.weapons[choice-1].name << endl;
        return;
    }
    if (choice == 2){
        buyWeapon(hero);
        enterArmory(hero);
    }
    if (!cin || choice > 2 || choice < 0){
        cout << "Invalid choice \n";
        cin.clear();
        cin.ignore();
        enterArmory(hero);
    }
}
void game(QSqlDatabase db){
    cin.clear();
    string name;
    cout << ">>>ADVENTURE GAME WOOOOO<<<\n";
    cout << "type '1' to load a previous character or press '2' to create a new character" << endl;
    cin >> choice;

    if (choice == 2){
        cout << "Please enter the name of your new character!" <<endl;
        cin >> name;
    };
    Hero hero(name);

    if (choice == 1){
        cout << "Selects the character you want to load: " <<endl;

        QSqlQuery q(db);
        q.exec("SELECT id, name, level FROM Heroes ORDER BY id");
        while(q.next()){
            cout << q.value(0).toInt() << ": " << q.value(1).toString().toStdString() << " level: " << q.value(2).toInt() << endl;
        }
        cin >> choice;
        if (!loadHero(hero, db, choice)){
            cout << "\nFailed to load hero\n";
            return;
        }
    };
    if (!cin || choice > 2 || choice < 1){ //checks for over and under number wise and also if not an int
        cout << "Invalid choice \n";
        cin.clear();
        cin.ignore();
        return;
    }
    cout << "A hero named " << hero.name << " has arrived!" <<endl;
    hero.showStats();
    while(true){
        cin.clear();
        cout << "do you want to save and exit your game [0]\nfight monsters individually? [1]\nenter a cave and fight many monsters? [2]\nEnter your armory [3]\nSee your stats [4]" <<endl;
        cin >> choice;

        switch(choice){
        case 0:
            hero.showStats();
            saveCharacter(hero, db);
            saveWeapons(hero, db);
            return;
        case 1:
            fightIndividually(hero);
            break;
        case 2:
            enterCave(hero);
            break;
        case 3:
            enterArmory(hero);
            break;
        case 4:
            hero.showStats();
            break;
        default:
            cout << "Invalid choice!\n" << endl;
        }
    }
}
int main(int argc, char *argv[])
{
    //database setup
    QCoreApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("game.db");

    if (!db.open()) {
        qCritical() << "DB open error:" << db.lastError().text();
        return false;
    }

    while(true){
    game(db);
    }
    //Cave cave(10);
    //cout << cave.name;
}
