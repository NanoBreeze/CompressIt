#include "lz77.h"

LZ77::LZ77() : sbStartIndex(0), text(""), encodedText("")
{

}

void LZ77::compress()
{
    text = "aabacacacdba"; //"cabracadabrarrarrad";
    searchBuffer = "aabac"; //"abaabc";
    lookaheadBuffer = "acacd"; //"abcae";

    encodedText = searchBuffer;

    while (!lookaheadBuffer.isEmpty())
    {
        int longestLength = encodeLongestMatch(searchBuffer, lookaheadBuffer);
        shiftWindow(longestLength);
    }
}

void LZ77::readFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            QString line = textStream.readLine();
            text += line;	//store the text so it can be encoded after finding the canonical Huffman code associated with each character.
            qDebug() << line;
        }
        file.close();
    }
    else {
        qDebug() << "The specified file can't be opened";
    }
}

/* Three cases:
 *   1. no match...{0,0,nextChar}
 *   2. match within the searchBuffer
 *   3. match within the searchBuffer AND extend into lookahead buffer
 */
int LZ77::encodeLongestMatch(const QString &searchBuffer, const QString &lookaheadBuffer)
{
    //Continuously try to find longest matching substring within searchBuffer.
    //If a substring can extend into lookaheadBuffer, do so and record its total length
    //Compare the longest lengths

    int longestLength = 0;
    int offset = 0;
    int i = 0;

    for (i = 0; i < lookaheadBuffer.length(); ++i)
    {
        QString substring = lookaheadBuffer.left(i + 1);

        //find all occurrences of substring
        if (searchBuffer.contains(substring))
        {
            //find all occurences of substring
            QList<int> indices;

            int previousIndex = searchBuffer.indexOf(substring, 0);

            while ( previousIndex != -1)
            {
                //check if any substrings in searchBuffer can extend to lookaheadBuffer.
                //extensions exist only if the searchBuffer's substring's last index is also the searchBuffer's last index
                //If there are, extend and record its total length

                indices.append(previousIndex);
                previousIndex = searchBuffer.indexOf(substring, previousIndex+1);
            }

            //check if substring extends into lookahead. Record longestLength and its associated offset
            foreach (int index, indices)
            {
                int length = substring.length() + findExtensionLength(searchBuffer, index, substring.length(), lookaheadBuffer);

                if (length > longestLength) //since the indices are in smallest-index first order, in case of length tie, choose smaller index (thus, closer to start of searchBuffer)
                {
                    longestLength = length;
                    offset = searchBuffer.length() - index;
                }
            }
        }
        else { //if substring doesn't exist, then encode this and move window
            break;
        }
    }
    //acount for extension, eg, adabrar | rarrad should be {3, 5, d}, not {3, 5, r}
    if (longestLength > i)
    {
        i = (longestLength - i) + i;
    }
    if (i >= lookaheadBuffer.length()) //this is bad temporal coupling but prevents the case where loop exists because no more i exists.
    {
        i = lookaheadBuffer.length() - 1;
    }

    encodedText += QString("{%1,%2,%3}").arg(offset).arg(longestLength).arg(lookaheadBuffer.at(i));

    return longestLength;
}

int LZ77::findExtensionLength(const QString &searchBuffer, const int &substringIndex, const int &substringLength, const QString &lookaheadBuffer) const
{
    //extensions can only exist if the specified substring is at the end of searchBuffer (thus, possible to go over to lookaheadBuffer)
    if (isSubstringAtEnd(searchBuffer, substringIndex, substringLength))
    {
        return findLookaheadMatchingLength(substringLength, lookaheadBuffer);
    }
    return 0;
}

bool LZ77::isSubstringAtEnd(const QString &searchBuffer, const int &substringIndex, const int &substringLength) const
{
    //the specified substring's last index matches the last index of searchBuffer. aka, it's at the end
    int searchBufferLastIndex = searchBuffer.length() - 1;
    int substringLastIndex = substringIndex + substringLength - 1;

    return searchBufferLastIndex == substringLastIndex;
}

int LZ77::findLookaheadMatchingLength(const int &substringLength, const QString &lookaheadBuffer) const
{
    //compare lookaheadBuffer index 0 with index 0+substringLength = substringLength.
    //If match compare index 1 with index substringLength + 1, and repeat until not match
    //If not match, return the matching length

    int matchLength = 0;
    for (int i = 0; i < lookaheadBuffer.length() - substringLength; ++i) //endpoint to prevent overflow, eg, abcabca, with length 3, stop matching after index 3
    {
        if (lookaheadBuffer.at(i) == lookaheadBuffer.at(i + substringLength))
        {
            matchLength++;
        }
        else { break; }
    }
    return matchLength;
}

void LZ77::shiftWindow(const int &longestLength)
{
    //moves the search and lookaheadbuffer by longestLength+1
    sbStartIndex += longestLength + 1;
    searchBuffer = text.mid(sbStartIndex, searchBuffer.length()); //if searchbuffer were initially indices 0 to 4 (of original text), it now becomes 1 to 5

    //lookaheadBuffer also shifts. If the end is already at text's end, only shift its start
    lookaheadBuffer = text.mid(sbStartIndex + searchBuffer.length(), lookaheadBuffer.length());
}
