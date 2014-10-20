#ifndef _AMUS_NOTES_H
#define _AMUS_NOTES_H

#include <string>   // std::string
#include <cstddef>  // std::size_t

#define INVALID_CHAR 'x'

enum letters {A, B, C, D, E, F, G, NUM_LETTERS};

class Note
{
    public:
        std::string tone;
};

// frequency -> letter representation (concatenate options)

// frequency & key signature -> letter representation

Note* parseTone(Note *n, std::string s);
float tone2freq(Note *n);

#endif