#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

struct Receipt {
    string movie;
    string CinemaScreen;
    string timeslot;
    string fooddrinks;
    string foodpopcorn;
    string seat;
};

void printReceipt(const Receipt& receipt) {
    cout << "\n========== Receipt ==========\n";
    cout << "Movie: " << receipt.movie << endl;
    cout << "Cinema Screen: " << receipt.CinemaScreen << endl;
    cout << "Time Slot: " << receipt.timeslot << endl;
    cout << "Drinks: " << receipt.fooddrinks << endl;
    cout << "Popcorn: " << receipt.foodpopcorn << endl;
    cout << "Seat: " << receipt.seat << endl;
    cout << "\n=============================\n";

    //open the reciept file in append mode
    ofstream myFile("Receipt.txt", ios::app);

    //write the contents of that specific reciept in the file
    if (myFile.is_open()) {

        myFile << "\n";
        myFile << "==================================="<<endl;
        myFile << "Movie: " << receipt.movie << "\n";
        myFile << "Cinema Screen: " << receipt.CinemaScreen << "\n";
        myFile << "Time Slot: " << receipt.timeslot << "\n";
        myFile << "Drinks: " << receipt.fooddrinks << "\n";
        myFile << "Popcorn: " << receipt.foodpopcorn << "\n";
        myFile << "Seats: " << receipt.seat << "\n";
        myFile << "===================================";
        myFile << "\n";

    }
    else {
        cout << "reciept was unable to be stored as the reciept file could not be opened.";
    }
}

void printarray(string array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << "  (Press  " << (i + 1) << ")\n";
    }
}
void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor() {
    setTextColor(7);  // Set back to default color
}

string timeslots(Receipt& receipt) {

    int userinput;
    string result;
    string usertimeslot;

    string timeslot[10] = { "10:00 PM","12:00PM","2:00PM","4:00PM","6:00PM","8:00PM","10:00PM","12:00AM","1:00AM","2:00AM" };

    cout << "\nPlease select from one of the timeslots below(choose a number from 1 to 10:)\n";
    cout << "\n----------Timeslots----------\n" << endl;

    for (int i = 0; i < 10; i++) {
        cout << (i + 1) << ".    " << timeslot[i] << endl;
        cout << "-----------------";
        cout << "\n";
    }

    cout << "\nNow choose one accordingly: \n";
    cin >> userinput;

    while (userinput < 1 && userinput>10) {
        cout << "\nPlease try again wrong number has been input: \n";
        cin >> userinput;
    }

    result = timeslot[userinput - 1];
    receipt.timeslot = result;

    cout << "\nyour time slot has been selected.\n";
    cout << "\nThankyou for choosing ABD&RAFAY Cinemas!\n";
    cout << "\nWe hope you have a wonderful experience with us!\n";

    return result;
}
void seats(int seatclass,Receipt& receipt){
    string array[3][3];
    ifstream fileread;
    fileread.open("seats.txt");
    if (fileread.is_open()) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                fileread >> array[i][j];
            }
        }
        fileread.close();
    } else {
        cout << "Unable to open file: seats.txt" << endl;
        return;
    }

    bool seatselection = false;
    while (!seatselection){
    setTextColor(12);
    for (int i = 0; i < 3; i++) {
        cout << "   " << "(" << i + 1 << ")";
    }
    cout << endl;
    resetTextColor();
        for (int i = 0; i < 3; i++) {
            setTextColor(12);
            cout << "(" << i + 1 << ")";
            resetTextColor();
            for (int j = 0; j < 3; j++) {
                if ((seatclass == 1 && i == 0) || (seatclass == 2 && i == 1) || (seatclass == 3 && i == 2)) {
                    // Mark seats from which the user can select with pink color
                    setTextColor(13);
                }
                cout << "[" << array[i][j] << "]" << " ";
                resetTextColor();
            }
            cout << endl;
        }

        int row, col;
        cout << "\nChoose a seat number (row and col): ";
        cin >> row >> col;

        if ((row >= 1 && row <= 3) && (col >= 1 && col <= 3) &&
            ((seatclass == 1 && row == 1) || (seatclass == 2 && row == 2) || (seatclass == 3 && row == 3))&& (array[row-1][col-1]!="X")) {
            seatselection = true;
            receipt.seat = array[row-1][col-1];
            array[row-1][col-1] = "X";
        } else {
            cout << "Invalid seat selection. Please enter again." << endl;
        }
    }
    ofstream writebackseats;
    writebackseats.open("seats.txt");
    if (writebackseats.is_open()) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                writebackseats << array[i][j] << " ";
            }
            writebackseats << endl;
        }
        writebackseats.close();
    } 
    else {
        cout << "Unable to open file: seats.txt" << endl;
    }
    timeslots(receipt);
    

}
int CinemaScreen(Receipt& receipt) {

    //choose the type of screen to view the movie
    int screenselector;
    string userscreen;

    cout << "\nchoose your cinema screen.\n";
    cout << "\nStandard (press 1)\n";
    cout << "\nGold (press 2)\n";
    cout << "\nPlatinum (press 3)\n";

    cin >> screenselector;

    while (screenselector < 1 || screenselector > 3) {
        cout << "\nyou have chosen an invalid number.\n";
        cout << "\nlook at the options again and choose again: \n";
        cin >> screenselector;
    }

    if (screenselector == 1) {
        userscreen = "Standard";
    }
    else if (screenselector == 2) {
        userscreen = "Gold";
    }
    else if (screenselector == 3) {
        userscreen = "Platinum";
    }

    receipt.CinemaScreen = userscreen;

    cout << "\nYour selection has been saved.\n";
    seats(screenselector,receipt);

    return 0;
}

int MovieWithDirector(Receipt& receipt) {

    string directors[29];
    ifstream myfile;

    int i = 0;
    myfile.open("directors.txt");

    if (!myfile.is_open()) {
        cout << "Error opening directors.txt" << endl;
        return -1;
    }

    while (i < 29 && getline(myfile, directors[i])) {
        i = i + 1;
    }

    myfile.close();

    cout << "Here is a list of all the movies,sorted with the Directors name: \n";
    printarray(directors, 29);

    int directorchoice;
    cout << "Choose the director by entering the corresponding number: ";
    cin >> directorchoice;

    while (directorchoice < 1 || directorchoice>29) {
        cout << "Invalid input. Please enter a valid number: ";
        cin >> directorchoice;
    }

    cout << "\nShowing all the movies for " << directors[directorchoice - 1] << ": ";
    ifstream filemovies;
    filemovies.open("films.txt");

    string line;
    string chosenmovies[5];  // Array to store up to 5 chosen movies
    int movieCount = 0;

    while (getline(filemovies, line)) {
        int directorNumber = stoi(line.substr(0, line.find('-')));

        if (directorNumber == directorchoice) {
            string movieName = line.substr(line.find('-') + 1);
            // Store the matching movie in the array
            if (movieCount < 5) {
                chosenmovies[movieCount] = movieName;
                movieCount++;
            }
        }
    }
    filemovies.close();

    int usermoviechoice;
    cout << "\n";
    printarray(chosenmovies, movieCount);
    cout << "\nChoose the movies from the ones labeled above : ";
    cin >> usermoviechoice;

    string choosenmovie;
    choosenmovie = chosenmovies[usermoviechoice - 1];
    receipt.movie = choosenmovie;
    cout << "The movie \"" << choosenmovie << "\" has been choosen successfully!\n";
    CinemaScreen(receipt);

    return 0;
}

int MovieWithGenre(Receipt& receipt) {

    const int Numofgenres = 5;
    const int maxmoviespergenre = 12;
    string genres[] = { "Action","Animation","Comedy","Science Fiction","Horror" };
    cout << "Here is a  list of all the genres to choose the movie from: " << endl;

    for (int i = 0; i < 5; i++) {
        char key = toupper(genres[i][0]);
        if (i == 1) {
            key = 'N';
        }
        cout << genres[i] << "(Press " << key << ")" << endl;
    }

    char genreselector;
    cin >> genreselector;
    int actualarraynum;

    switch (genreselector) {
    case 'A':
        actualarraynum = 1;
        break;
    case 'N':
        actualarraynum = 2;
        break;
    case 'C':
        actualarraynum = 3;
        break;
    case 'S':
        actualarraynum = 4;
        break;
    case 'H':
        actualarraynum = 5;
        break;
    default:
        cout << "Invalid genre choice. Exiting.... \n";
        exit(1);
    }

    cout << "The " << genres[actualarraynum - 1] << " movies available are : \n ";
    ifstream filemovies;
    filemovies.open("films.txt");

    if (!filemovies.is_open()) {
        cout << "Error opening films.txt" << endl;
        return 1;
    }

    string moviesgenre[maxmoviespergenre];
    int movieCount = 0;
    string line;

    while (getline(filemovies, line)) {
        char genreCode = line[line.find('-') - 1];
        if (toupper(genreCode) == toupper(genreselector)) {
            string movieName = line.substr(line.find('-') + 1);
            moviesgenre[movieCount] = movieName;
            movieCount++;
        }
    }

    filemovies.close();
    printarray(moviesgenre, movieCount);

    int moviesselection;
    cout << "\nChoose the movie with its corresponding number: ";
    cin >> moviesselection;

    while (moviesselection<1 || moviesselection >maxmoviespergenre) {
        cout << "\n Invalid input entered.Please enter a valid number and reenter: ";
        cin >> moviesselection;
    }

    string choosenmovie = moviesgenre[moviesselection - 1];
    cout << "\nThe movie has been choosen succesfully: " << choosenmovie << "!\n";
    receipt.movie = choosenmovie;
    CinemaScreen(receipt);

    return 0;
}

int MovieWithTitle(Receipt& receipt) {
    string arr[33];
    string movie;

    cout << "Here is a list of all the available movies, sorted with the title: \n";

    ifstream myfile;
    myfile.open("films.txt");
    int i = 0;
    if (!myfile.is_open()){
        cout << "Unable to open file films.txt";
        return 1;
    }
    int k = 1;
    while (getline(myfile,arr[i])){
        int pos = arr[i].find('-');
        cout << k <<" . "<<(arr[i].substr(pos+1))<<endl;
        k++;
        i++;
    }
    myfile.close();
    int movieselection = 0;
    cout << "choose the movie with its corresponding number: ";
    cin >> movieselection;

    while (movieselection < 1 || movieselection > 33) {
        cout << "\ninvalid input entered, check the valid numbers again and re-enter your choice: ";
        cin >> movieselection;
    }

    string chosenMovie;
    chosenMovie = arr[movieselection-1];
    cout << "\nThe movie \"" << chosenMovie << "\" has been choosen succesfully!\n";
    receipt.movie = chosenMovie;

    CinemaScreen(receipt);

    return 0;
}

int MovieSelection(Receipt& receipt) {

    cout << "> Choose movie by Title.\n";
    cout << "> Choose movie by Director.\n";
    cout << "> Choose movie by Genre.\n";

    int movieSelector;
    cout << "press 1 for choosing by title, 2 for choosing by director, 3 for choosing by genre.\n";
    cin >> movieSelector;

    //handling invalid input
    while (movieSelector != 1 && movieSelector != 2 && movieSelector != 3) {
        cout << "you have entered an invalid selection.\n";
        cout << "press 1 for choosing by title, 2 for choosing by director, 3 for choosing by genre.\n";
        cin >> movieSelector;
    }

    if (movieSelector == 1) {
        cout << "you have selected: choose movie with title.\n";
        MovieWithTitle(receipt);
    }
    if (movieSelector == 2) {
        cout << "you have selected: choose movie with director.\n";
        MovieWithDirector(receipt);
    }
    if (movieSelector == 3) {
        cout << "you have selected: choose movie with genre.\n";
        MovieWithGenre(receipt);
    }

    return 0;
}

int popcorns2(Receipt& receipt) {

    string flavour[] = { "Caramel","Salty","Normal" };
    cout << "\nSelect your flavour of popcorn :  \n";
    printarray(flavour, 3);

    int flavourselector;
    cin >> flavourselector;

    while (flavourselector != 1 && flavourselector != 2 && flavourselector != 3) {
        cout << "\nPlease select a valid number: ";
        printarray(flavour, 3);
        cin >> flavourselector;
    }

    string userpopcornflavour = flavour[flavourselector - 1];
    cout << "\n The flavour " << userpopcornflavour << " Has been selected for you \n";

    ifstream stockfile;
    stockfile.open("stock.txt");
    string line;
    int stock[3] = { 0 };

    for (int i = 0; i < 3; i++) {
        getline(stockfile, line);
        int pos = line.find('=');
        stock[i] = stoi(line.substr(pos + 1));
    }

    stockfile.close();

    while (stock[flavourselector - 1] == 0) {
        cout << "\nWe do not have this flavour stock right now please choose another flavour";
        printarray(flavour, 3);
        cin >> flavourselector;
    }

    stock[flavourselector - 1]--;
    cout << "\nStock Remaining: " << endl;

    for (int i = 0; i < 3; i++) {
        cout << i + 1 << "-" << flavour[i] << "=" << stock[i] << endl;
    }

    ofstream outfile;
    outfile.open("stock.txt");

    for (int i = 0; i < 3; i++) {
        outfile << i + 1 << "-" << flavour[i] << "=" << stock[i] << endl;
    }

    outfile.close();
    receipt.foodpopcorn = userpopcornflavour;

    cout << "\n Going to movies now.......\n";
    MovieSelection(receipt);

    return 0;
}

int drinks(Receipt& receipt) {

    string drinks[9];
    ifstream drinksfile;
    drinksfile.open("drinksstock.txt");

    if (!drinksfile) {
        cout << "Error opening file." << endl;
        return -1;
    }

    string drinkstext;
    int index = 0;

    while (getline(drinksfile, drinkstext) && index < 9) {
        int dashpos = drinkstext.find("-");
        int equalpos = drinkstext.find("=");
        string drinkName = drinkstext.substr(dashpos + 1, equalpos - dashpos - 1); 
        drinks[index] = drinkName;
        index = index + 1;
    }

    drinksfile.close();

    cout << "\n Here is the list of available drinks: " << endl;
    printarray(drinks, 9);
    cout << "\n Choose from the ones above" << endl;

    int userdrink;
    cin >> userdrink;

    while (userdrink < 1 && userdrink>9) {
        cout << "\nChoose valid Num" << endl;
        printarray(drinks, 9);
        cin >> userdrink;
    }

    ifstream drinksfile2("drinksstock.txt");
    string line;
    int drinkstock[9] = { 0 };

    for (int i = 0; i < 9; i++) {
        getline(drinksfile2, line);
        int equal_pos = line.find('=');
        drinkstock[i] = stoi(line.substr(equal_pos + 1));
    }

    drinksfile2.close();

    while (drinkstock[userdrink - 1] == 0) {
        cout << "\nWe do not have this flavour stock right now please choose another flavour";
        printarray(drinks, 3);
        cin >> userdrink;
    }

    cout << "\n The drink " << drinks[userdrink - 1] << " Has been succesfully choosen for you " << endl;
    drinkstock[userdrink - 1]--;
    cout << "\nStock Remaining: " << endl;

    for (int i = 0; i < 9; i++) {
        cout << i + 1 << "-" << drinks[i] << "=" << drinkstock[i] << "\n";
    }
    ofstream writefile;
    writefile.open("drinksstock.txt");

    for (int i = 0; i < 9; i++) {
        writefile << i + 1 << "-" << drinks[i] << "=" << drinkstock[i] << endl;
    }

    writefile.close();
    receipt.fooddrinks = drinks[userdrink - 1];

    cout << "\n Do you want to buy Popcorn(Press 1) or go to movies(Press 2)";
    int userselection;
    cin >> userselection;

    while (userselection != 1 && userselection != 2) {
        cout << "Invalid selection.\n";
        cin >> userselection;
    }

    if (userselection == 1) {
        popcorns2(receipt);
    }
    else if (userselection == 2) {
        MovieSelection(receipt);
    }

    return 0;
}


int popcorns(Receipt& receipt) {

    string flavour[] = { "Caramel","Salty","Normal" };
    cout << "\nSelect your flavour of popcorn :  \n";
    printarray(flavour, 3);

    int flavourselector;
    cin >> flavourselector;

    while (flavourselector != 1 && flavourselector != 2 && flavourselector != 3) {
        cout << "\nPlease select a valid number: ";
        printarray(flavour, 3);
        cin >> flavourselector;
    }


    ifstream stockfile;
    stockfile.open("stock.txt");
    string line;
    int stock[3] = { 0 };

    for (int i = 0; i < 3; i++) {
        getline(stockfile, line);
        int pos = line.find('=');//finding the "=" position in int 
        stock[i] = stoi(line.substr(pos + 1));//converting to an integer to store in stock
    }
    stockfile.close();

    while (stock[flavourselector - 1] == 0) {
        cout << "\nWe do not have this flavour stock right now please choose another flavour";
        printarray(flavour, 3);
        cin >> flavourselector;
    }

    cout << "\n The flavour " << flavour[flavourselector - 1] << " Has been succesfully choosen for you " << endl;
    stock[flavourselector - 1]--;
    cout << "\nStock Remaining: " << endl;

    for (int i = 0; i < 3; i++) {
        cout << i + 1 << "-" << flavour[i] << "=" << stock[i] << endl;
    }

    ofstream outfile;
    outfile.open("stock.txt");

    for (int i = 0; i < 3; i++) {
        outfile << i + 1 << "-" << flavour[i] << "=" << stock[i] << endl;
    }

    outfile.close();
    receipt.foodpopcorn = flavour[flavourselector - 1];

    cout << "\n Do you want to buy drinks(Press 1) or go to movies(Press 2)\n";
    int userselection;
    cin >> userselection;

    while (userselection != 1 && userselection != 2) {
        cout << "Invalid selection.\n";
        cin >> userselection;
    }

    if (userselection == 1) {
        drinks(receipt);
    }
    else if (userselection == 2) {
        MovieSelection(receipt);
    }

    return 0;
}

int Cafe(Receipt& receipt) {

    int userchoice; //start off with the food part of the system

    cout << "welcome to the cafe!\n";
    cout << "you can choose from a variety of popcorn and drinks.\nPopcorn (Press 1)\n Drinks (Press 2)\n";
    cin >> userchoice;

    while (userchoice != 1 && userchoice != 2) {
        cout << "\nChoose correct option : ";
        cin >> userchoice;
    }

    if (userchoice == 1) {
        popcorns(receipt);
    }
    else if (userchoice == 2) {
        drinks(receipt);
    }

    return 0;
}

int main() {                                                                    //absolute starting

    cout << "Welcome to ABD&RAFAY cinemas!\n";

    Receipt receipt;
    cout << "how may we assist you today?\n";

    int userInput;
    cout << "> Go to the Movie Selection.\n";
    cout << "> Go to the Cafe.\n";
    cout << "> Exit.\n";

    cout << "press 1 for movie selection, 2 for the cafe, and 0 to exit.\n";
    cin >> userInput;

    //handling invalid input
    while (userInput != 1 && userInput != 2 && userInput != 0) {
        cout << "you have entered an invalid selection.\n";
        cout << "press 1 for movie selection, 2 for the cafe, and 0 to exit.\n";
        cin >> userInput;
    }

    if (userInput == 1) { // movie selection
        MovieSelection(receipt);
        printReceipt(receipt);
    }
    else if (userInput == 2) { // cafe
        Cafe(receipt);
        printReceipt(receipt);
    }
    else if (userInput == 0) { // exit
        cout << "We are sorry to see you go, please join us again soon!\n";
        return 0;
    }

    return 0;

}