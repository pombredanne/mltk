
#include <string>
#include <algorithm>

#include "../ext/murmur3.c"

uint32_t const SEED = 5;

/// Use murmurhash as a custom has for the string
uint64_t murmurhash3(const std::string& key)
{
    uint64_t ret[2];   // need 128 bits of space to hold result
    MurmurHash3_x64_128(key.c_str(), key.length(), SEED, ret);
    return ret[0];
}

std::string normalize(std::string const & word)
{
    /**< normalize a word.
     - All words are lower cased
     - 4 letter digits are represented as !YEAR
     - Other digits are represented as !DIGITS
    */
    if (word.find("-") != std::string::npos && word != "-")
        return "!HYPHEN";
    else if (word.find_first_not_of("0123456789") == std::string::npos &&
        word.length() == 4)
        return "!YEAR";
    else if (std::isdigit(word[0]))
        return "!DIGITS";
    else
    {
        // lowercase
        std::string ret;
        ret.assign(word);
        std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
        return ret;
    }
}

const std::string SPACE = " ";

std::string join(std::string& s1, std::string& s2)
{
    /**< join with a space in the center
     find the length of the final string, reserve it then append */
    std::string sout;
    sout.reserve(s1.length() + s2.length() + 1);
    sout.append(s1);
    sout.append(SPACE);
    sout.append(s2);
    return sout;
}

