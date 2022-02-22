// StructSaveExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


//Lets create a struct to hold a weapon
struct Weapon
{
    string weaponType;
    int attackMod;
};

//Lets create a struct to hold our Game Save structure. Anything that should
//be part of the Game State taht needs saving and loading needs to be added here.
struct GameSave
{
    int HP;
    int positionX;
    int positionY;
    vector<Weapon> weaponVect;
};

void populateGameState(GameSave&);
void outputGameState(const GameSave&);

int main()
{
    //Our struct variable
    GameSave myGameSave;
    //Our file variable
    fstream gameSaveFile;

    //This will expect the file with the name to exists in the same folder where .cpp is located.
    gameSaveFile.open("SaveData.txt", ios::out | ios::in);

    //Let's Setup the data to populate the save file. This can come from any other object , such as a player object
    populateGameState(myGameSave);

    //With the "myGameSave"variable populated, let's now write the contents to our open.
    cout << "Now writing record "<< endl;
    gameSaveFile.write(reinterpret_cast<char*>(&myGameSave),
        sizeof(myGameSave));

    //We have completed writing to our file in hard disk and close the file.
    gameSaveFile.close();
    cout << "File has been save to disk and closed." << endl << endl;


    //Now Let's suppose that we want to load the game state from the saved file.
    //I create a new struct variable here.
    GameSave readGameSave;
    gameSaveFile.open("SaveData.txt", ios::out | ios::in);
    cout << "Now let's read the data from the disk. " << endl;
    //In the next statement, we read from the file into or struct.
    gameSaveFile.read(reinterpret_cast<char*>(&readGameSave), sizeof(readGameSave));
    //I pass my GameState to printout the values loaded from the file
    outputGameState(readGameSave);
    gameSaveFile.close();
}

/*
* By  passing my GameSave by reference, I could set the values I want to save
*/
void  populateGameState(GameSave &myGameSave) {
    //Let's create 2 weapons to test
    Weapon weap1;
    weap1.weaponType = "Battle Axe";
    weap1.attackMod = 5;

    Weapon weap2;
    weap2.weaponType = "Flaming Sword";
    weap2.attackMod = 7;

    //Let's add the two weapons to the vector
    vector<Weapon> myCurrentWeapons;
    myCurrentWeapons.push_back(weap1);
    myCurrentWeapons.push_back(weap2);

    //Lets save some example values into my game save variable (these values could from a Player object)
    myGameSave.HP = 40;
    myGameSave.positionX = 0;
    myGameSave.positionY = 6;
    myGameSave.weaponVect = myCurrentWeapons;
}

/*
*  Here I pass the Game Save variable and read the data from the struct variable to print to the screen
*/
void outputGameState(const GameSave& readGameSave) {
    cout << "HP " << readGameSave.HP << endl;
    cout << "Position X " << readGameSave.positionX << endl;;
    cout << "Position Y " << readGameSave.positionY << endl;;
    cout << "Weapons found " << readGameSave.weaponVect.size() << endl;
    for (int cnt = 0; cnt < readGameSave.weaponVect.size(); cnt++) {
        cout << "Weapon " << readGameSave.weaponVect[cnt].weaponType << " " << endl;
        cout << "Weapon attack " << readGameSave.weaponVect[cnt].attackMod << " " << endl;
    }
}
