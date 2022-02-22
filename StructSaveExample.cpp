// StructSaveExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Weapon
{
    string weaponType;
    int attackMod;
};

struct GameSave
{
    int HP;
    int positionX;
    int positionY;
    vector<Weapon> weaponVect;
};

int main()
{
    GameSave myGameSave;
    fstream gameSaveFile;

    gameSaveFile.open("SaveData.txt", ios::out | ios::in);

    
    //My Player's weapons
    Weapon weap1;
    weap1.weaponType = "Battle Axe";
    weap1.attackMod = 5;

    Weapon weap2;
    weap2.weaponType = "Flaming Sword";
    weap2.attackMod = 7;
    vector<Weapon> myCurrentWeapons;

    myCurrentWeapons.push_back(weap1);
    myCurrentWeapons.push_back(weap2);

    //Load my Game Save Struct with the game state info
    myGameSave.HP = 40;
    myGameSave.positionX = 0;
    myGameSave.positionY = 6;
    myGameSave.weaponVect = myCurrentWeapons;

    cout << "Now writing record "<< endl;
    gameSaveFile.write(reinterpret_cast<char*>(&myGameSave),
        sizeof(myGameSave));

    gameSaveFile.close();

    GameSave readGameSave;
    gameSaveFile.open("SaveData.txt", ios::out | ios::in);
    gameSaveFile.read(reinterpret_cast<char*>(&readGameSave), sizeof(readGameSave));
    cout << "HP " << readGameSave.HP << endl;
    cout << "Position X " << readGameSave.positionX << endl;;
    cout << "Position Y " << readGameSave.positionY << endl;;
    cout << "Weapons found " << readGameSave.weaponVect.size() << endl;
    for(int cnt = 0; cnt < readGameSave.weaponVect.size(); cnt++) {
        cout << "Weapon " << readGameSave.weaponVect[cnt].weaponType << " " << endl;
        cout << "Weapon attack " << readGameSave.weaponVect[cnt].attackMod << " " << endl;
    }
 
    

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
