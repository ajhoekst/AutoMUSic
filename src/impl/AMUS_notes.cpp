#include "../incl/notes.hpp"

#include <iostream>
#include <cmath>

#include "SDL2/SDL.h"

using namespace std;

/* parseTone
 * 
 * Description:
 * Parses and cleans the first tone from a string
 *
 * Input:
 * Note object
 * String in the format <L><O><[aa]>
 * 
 * L  - a character from the set {A,B,C,D,E,F,G}
 * O  - a character from the set {0,1,2,3,4,5,6,7,8}
 * a  - a character from the set {b,n,#}
 * b  - represents a flat
 * n  - represents a natural
 * #  - represents a sharp
 * [] - indicates optional characters.
 *      No accidentals defaults to n (added to output).
 *      Conflicting characters in [aa] (e.g. n#) will be
 *      corrected to first accidental only.
 *
 * Output:
 * String in the format <L><O><a[a]>
 *
 * Special Returns:
 * NULL - invalid string
 */
Note* parseTone(Note *n, string s)
{
    char letter,
         octave,
         accidental1,
         accidental2;
         
    // Find the first valid letter in the string
    size_t letter_pos = s.find_first_of("ABCDEFG");
    if (letter_pos == string::npos)
    {
        return NULL;
    }
    else
    {
        letter = s[letter_pos];
    }
    
    // Ensure there is an octave designation
    if (s.size() >= letter_pos + 1)
    {
        octave = s[letter_pos + 1];
    }
    else
    {
        return NULL;
    }
    
    // Ensure the octave is in a valid range
    if (   octave < 48  // 0
        || octave > 56) // 8
    {
        return NULL;
    }
    
    // Check if the string could include accidentals
    // Two possible accidentals
    if (s.size() >= letter_pos + 3)
    {
        accidental1 = s[letter_pos + 2];
        accidental2 = s[letter_pos + 3];
    }
    // One possible accidental
    else if (s.size() == letter_pos + 2)
    {
        accidental1 = s[letter_pos + 2];
        accidental2 = INVALID_CHAR;
    }
    // No possible accidentals
    else
    {
        accidental1 = 'n';
        accidental2 = INVALID_CHAR;
    }
    
    // Ensure accidentals are valid
    switch (accidental1)
    {
        // Valid flat
        case 'b':
            // Remove conflicting second accidental
            if (accidental2 != 'b') accidental2 = INVALID_CHAR;
            break;
        // Valid natural
        case 'n':
            // Remove conflicting second accidental
            accidental2 = INVALID_CHAR;
            break;
        // Valid sharp
        case '#':
            // Remove conflicting second accidental
            if (accidental2 != '#') accidental2 = INVALID_CHAR;
            break;
        // No valid accidental
        default:
            accidental1 = 'n';
            accidental2 = INVALID_CHAR;
    }
    
    // Build note string and return
    if (n == NULL)
    {
        n = new Note();
    }
    n->tone += letter;
    n->tone += octave;
    n->tone += accidental1;
    if (accidental2 != INVALID_CHAR) n->tone += accidental2;
    return n;
}

/* note2freq
 *
 * Description:
 * Converts a tone specified by a string to a frequency
 *
 * Input:
 * Note object
 * 
 * L  - a character from the set {A,B,C,D,E,F,G}
 * O  - a character from the set {0,1,2,3,4,5,6,7,8}
 * a  - a character from the set {b,n,#}
 * b  - represents a flat
 * n  - represents a natural
 * #  - represents a sharp
 * [] - indicates optional characters
 *
 * Output:
 * Float for the corresponding frequency in Hz
 *
 * Special Returns:
 * Negative value - invalid Note
 * Zero - rest
 */
float tone2freq(Note *n)
{
    string tone;
    int octave,
        key;
    
    // Check for a valid Note
    if (n == NULL)
    {
        return -1;
    }
    tone = n->tone;
    
    // Check for valid tone
    if (tone.size() < 3)
    {
        return -1;
    }
    
    // Set key to the correct letter in 0th octave
    switch (tone[0])
    {
        case 'A':
            key = 0;
            break;
        case 'B':
            key = 2;
            break;
        case 'C':
            key = -9;
            break;
        case 'D':
            key = -7;
            break;
        case 'E':
            key = -5;
            break;
        case 'F':
            key = -4;
            break;
        case 'G':
            key = -2;
            break;
        default:
            return -1;
    }
    
    // Adjust key to the correct octave
    octave = tone[1] - 48; // ASCII -> int
    key += 12 * octave;
    
    // Adjust key with the first accidental
    switch (tone[2])
    {
        case 'b':
            key -= 1;
            break;
        case 'n':
            // nothing
            break;
        case '#':
            key += 1;
            break;
        default:
            return -1;
    }
    
    // Adjust key with the second accidental
    if (tone.size() == 4)
    {
        switch (tone[2])
        {
            case 'b':
                key -= 1;
                break;
            case '#':
                key += 1;
                break;
            default:
                return -1;
        }
    }
    cout << "Key: " << key + 1 << endl;
    // Calculate frequency and return
    return (440.000 * pow(2, (key - 48.) / 12.));
}

int main(int argc, char *argv[])
{
    string input;
    float frequency;
    
    while (1)
    {
        Note *n = NULL;
        cin >> input;
        n = parseTone(n, input);
        if (n == NULL)
        {
            cout << "Invalid note!" << endl;
        }
        else
        {
            frequency = tone2freq(n);
            cout << "Frequency: " << frequency << endl;
        }
    }
}