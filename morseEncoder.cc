using namespace std;
#include <iomanip>
#include <iostream>
#include <fstream>

void displayMenu();
void setKey(int &key);
void encryptFile(int key);
void decryptFile(int key);

int main() {
    int choice, key;
    key = 3; //Default shift key
    do {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            encryptFile(key); // Call the encryption function
        }
        else if (choice == 2) {
            decryptFile(key); // Call the decryption function
        }
    } while (choice != 3);
    return 0;
}

// Displays main menu
void displayMenu(){
    cout << endl;
    cout << "(1) Encrypt a file" << endl;
    cout << "(2) Decrypt a file" << endl;
    cout << "(3) Quit" << endl;
}

// Sets the shift key
void setKey(int &key){
    cout << endl;
    cout << "Enter the desired shift key: ";
    cin >> key;
    while(key < 1 || key > 10){
        cout << "Shift key needs to be between 1 and 10" << endl;
        cout << "Enter the desired shift key: ";
        cin >> key;
    }
}

// Encrypts the file using the shift key
void encryptFile(int key){
    // Declaring variables
    string inputFile;
    string outputFile;
    char ch;
    ifstream inStream;
    ofstream outStream;

    // Morse code arrays
    string morseCodeAlpha[] = {".-","-...","-.-.","-..",".","..-.","--.","....",
                        "..",".---","-.-",".-..","--","-.","---",".--.","--.-",
                        ".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

    string morseCodeDigit[] = {"-----",".----","..---","...--","....-",".....","-....",
                        "--...","---..","----."};

    // Get file names
    cout << endl;
    cout << "Enter the name of the file you would like to encrypt: ";
    cin >> inputFile;
    cout << endl;
    cout << "Enter the name of the file to output to: ";
    cin >> outputFile;

    inStream.open(inputFile);
    outStream.open(outputFile);

    // Check for errors
    if(inStream.fail()){
        cout << endl;
        cout << "Input file failed to open" << endl;
        return;
    }
    if(outStream.fail()){
        cout << endl;
        cout << "Output file failed to open" << endl;
        return;
    }

    // Encrypt file
    inStream.get(ch);
    while(!inStream.eof()){
        int i;

        if(isalpha(ch)){
            if(islower(ch)){
                ch = toupper(ch);
            }

            ch -= 65;
            i = ch;
        
            outStream << morseCodeAlpha[i];
        }
        else if(isdigit(ch)){
            ch -= 48;
            i = ch;
            outStream << morseCodeDigit[i];
        }
        else{
            outStream << "\t";
        }
        
        outStream << " ";
        inStream.get(ch);
    }

    // Close file streams
    outStream.close();
    inStream.close();

    // Tell user it was successful
    cout << endl;
    cout << "Your file has been encrypted into " << outputFile;
    cout << endl;
}

// Decrypts the file using the shift key
void decryptFile(int key){
    // Declaring variables
    string inputFile;
    string outputFile;
    char ch;
    ifstream inStream;
    ofstream outStream;

    // Morse code arrays
    string morseCodeAlpha[] = {".-","-...","-.-.","-..",".","..-.","--.","....",
                        "..",".---","-.-",".-..","--","-.","---",".--.","--.-",
                        ".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

    string morseCodeDigit[] = {"-----",".----","..---","...--","....-",".....","-....",
                        "--...","---..","----."};

    char alphaChars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
                        'O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    char digitChars[] = {'0','1','2','3','4','5','6','7','8','9'};

    // Getting names of files
    cout << endl;
    cout << "Enter the name of the file you would like to decrypt: ";
    cin >> inputFile;
    cout << endl;
    cout << "Enter the name of the file to output to: ";
    cin >> outputFile;

    inStream.open(inputFile);
    outStream.open(outputFile);

    // Checking for errors opening files
    if(inStream.fail()){
        cout << endl;
        cout << "Input file failed to open" << endl;
        return;
    }
    if(outStream.fail()){
        cout << endl;
        cout << "Output file failed to open" << endl;
        return;
    }

    // Decrypting file
    inStream.get(ch);
    while(!inStream.eof()){
        int i = 0;
        string morseCodeString = "";
        bool correctCode = false;
        bool isAlpha;
        bool isSpace = false;

        if(!isspace(ch)){
            while(!isspace(ch) && !inStream.eof()){
                morseCodeString = morseCodeString + ch;
                inStream.get(ch);
            }
        }
        else{
            correctCode = true;
            isSpace = true;
        }

        while(!correctCode){
            if(morseCodeString == morseCodeAlpha[i]){
                correctCode = true;
                isAlpha = true;
            }
            else if(morseCodeString == morseCodeDigit[i]){
                correctCode = true;
                isAlpha = false;
            }
            else{
                i += 1;
            }
        }
        
        if((ch == '\t') || (ch == '\n')){
            outStream << "";
        }
        else if(isSpace){
            outStream << ch;
        }
        else if(isAlpha){
            outStream << alphaChars[i];
        }
        else if(!isAlpha){
            outStream << digitChars[i];
        }

        inStream.get(ch);
    }

    // Closing file streams
    outStream.close();
    inStream.close();

    // Tell user it was successful
    cout << endl;
    cout << "Your file has been decrypted into " << outputFile;
    cout << endl;
}