#ifndef LZ77_H
#define LZ77_H

#include <QString>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class LZ77
{
public:
    LZ77();
    void compress();

private:
    QString searchBuffer;
    int sbStartIndex; //searchBuffer start index, determines what its first element with respect to the text
    QString lookaheadBuffer;
    QString text; //original text
    QString encodedText;

    void readFile(const QString& filePath);

    //finds the longest substring in searchBuffer that matches with the substring starting at lookaheadBuffer
    int encodeLongestMatch(const QString& searchBuffer, const QString& lookaheadBuffer); //returns the length of the longest match
    int findExtensionLength(const QString& searchBuffer, const int& substringIndex, const int& substringLength, const QString& lookaheadBuffer) const; //returns the length of the extension. Thus, returns 0 if no extension
    bool isSubstringAtEnd(const QString& searchBuffer, const int& substringIndex, const int& substringLength) const; //returns whether the substring's last index matches searchBuffer's last index. If so, then an extension might exist. If not, no extension
    int findLookaheadMatchingLength(const int& substringLength, const QString& lookaheadBuffer) const; //returns the number of element at index 0 and index substringLength repetitively that match.

    void shiftWindow(const int& longestLength); //moves the searchBuffer and lookaheadBuffer by the longestLength + 1
};

#endif // LZ77_H
