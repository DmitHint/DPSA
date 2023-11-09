#include <vector>
#include <string>
#include <iostream>


using namespace std;

struct Token {
    int offset;
    int len;
    char symbol;
};


void lz77Encode(const string& phrase) {
    vector<Token> encoded;

    int phraseLength = phrase.length();
    int currentIndex = 0;

    while (currentIndex < phraseLength) {
        Token currentToken;
        currentToken.offset = 0;
        currentToken.len = 0;
        currentToken.symbol = '\0';

        for (int i = currentIndex - 1; i >= 0; i--) {
            int j = 0;
            while (j < phraseLength - currentIndex && phrase[i + j] == phrase[currentIndex + j]) {
                j++;
            }

            if (j > currentToken.len) {
                currentToken.offset = currentIndex - i - 1;
                currentToken.len = j;
                currentToken.symbol = phrase[currentIndex + j];
            }
        }

        encoded.push_back(currentToken);
        currentIndex += currentToken.len + 1;
    }

    for (const Token& pair : encoded) {
        cout << "<" << pair.offset << ", " << pair.len << ", " << (char)pair.symbol << "> ";
    }
    cout << endl;

}
int main() {
    lz77Encode("000101110110100111");
    return 0;
}
