#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

string choisirMot(const vector<string>& words){
    int index = rand() % words.size();
    return words[index];
}

string afficheMot(const string& word, const vector<char>& lettersFound){
    string affichage = "";
    bool firstLetter = false;
    for (char letter : word){
        if(!firstLetter && letter != ' '){
            affichage += letter;
            firstLetter = true;
        }else if(find(lettersFound.begin(), lettersFound.end(), letter) != lettersFound.end()){
            affichage += letter;
        }else{
            affichage += " _ ";
        }
    }
    return affichage;
}

int main(){
    srand(static_cast<unsigned>(time(0)));

    vector<string> words;
    ifstream wordFile("word.txt");
    if(!wordFile.is_open()){
        cout << "Erreur lors de l'ouverture du fichier word.txt" << endl;
        return 1;
    }

    string word;
    while(getline(wordFile, word)){
        words.push_back(word);
    }
    wordFile.close();

    string designedWord = choisirMot(words);
    vector<char> lettresTrouvees;
    int erreurs = 0;
    const int maxErreurs = 6;

    cout << "Bienvenue au jeu du pendu !" << endl;
    cout << "Le mot commence par la lettre : " << designedWord[0] << endl;
    cout << "Le mot a " << designedWord.size() << " lettres." << endl;

    while(true){
        cout << "\nMot Actuel : " << afficheMot(designedWord, lettresTrouvees) << endl;
        char guessLetter;
        cout << "Entrer une lettre : ";
        cin >> guessLetter;

        if(find(lettresTrouvees.begin(), lettresTrouvees.end(), guessLetter) != lettresTrouvees.end()){
            cout << "Vous avez deja devine cette lettre !" << endl;
            continue;
        }

        lettresTrouvees.push_back(guessLetter);

        if (designedWord.find(guessLetter) == string::npos) {
            cout << "La lettre n'est pas dans le mot." << endl;
            erreurs++;
            cout << "Erreurs : " << erreurs << "/" << maxErreurs << endl;
        }

        if(erreurs >= maxErreurs){
            cout << "\nVous avez atteint le nombre d'erreur max, vous avez perdu." << endl;
            cin.get();
            break;
        }

        bool completeWord = true;
        for (char lettre : designedWord) {
            if (lettre != ' ' && find(lettresTrouvees.begin(), lettresTrouvees.end(), lettre) == lettresTrouvees.end()) {
                completeWord = false;
                break;
            }
        }

        if (completeWord) {
            cout << "\nFelicitations, vous avez devine le mot : " << designedWord << endl;
            cin.get();
            break;
        }
    }

    cin.get();
    return 0;
}