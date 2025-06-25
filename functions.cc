#include "functions.hpp"

#include <iostream>
#include <string>
/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  std::cout << "Input to StringToLower() : " << word << std::endl;
  std::string result;
  char ch = 0;
  for (char c : word) {
    ch = (char)(tolower(c));
    result += ch;
  }
  return result;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
  std::cout << "Input to IsVowelGroup() : \"" << v1 << "\" \"" << v2 << "\""
            << std::endl;
  if (v1 == 'a') {
    if (v2 == 'i' || v2 == 'e' || v2 == 'o' || v2 == 'u') {
      return true;
    }
  }
  if (v1 == 'e') {
    if (v2 == 'i' || v2 == 'u') {
      return true;
    }
  }
  if (v1 == 'i') {
    if (v2 == 'u') {
      return true;
    }
  }
  if (v1 == 'o') {
    if (v2 == 'u' || v2 == 'i') {
      return true;
    }
  }
  if (v1 == 'u') {
    if (v2 == 'i') {
      return true;
    }
  }
  return false;
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  std::cout << "Input to IsVowel() : \"" << v << "\"" << std::endl;
  return v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u';
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
  std::cout << "Input to IsConsonant() : \"" << c << "\"" << std::endl;
  return c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n' ||
         c == 'w';
}

/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  std::cout << "Input to IsValidCharacter() : \"" << c << "\"" << std::endl;
  return c == ' ' || c == '\'' || c == 'a' || c == 'e' || c == 'i' ||
         c == 'o' || c == 'u' || c == 'p' || c == 'k' || c == 'h' || c == 'l' ||
         c == 'm' || c == 'n' || c == 'w';
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  std::cout << "Input to IsValidWord() : " << word << std::endl;
  for (char c : word) {
    if (!(IsValidCharacter(c))) {
      return false;
    }
  }
  return true;
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a char
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  std::cout << "Input to ConsonantPronunciation() : \"" << c << "\" \"" << prev
            << "\"" << std::endl;
  if (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n') {
    return c;
  }
  if (c == 'w') {
    if (prev == 'a' || prev == 'u' || prev == 'o') {
      return 'w';
    }
    if (prev == 'i' || prev == 'e') {
      return 'v';
    }
    return 'w';
  }
  return '\0';
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  std::cout << "Input to VowelGroupPronunciation() : \"" << v1 << "\" \"" << v2
            << "\"" << std::endl;
  if (v1 == 'a') {
    if (v2 == 'i' || v2 == 'e') {
      return "eye";
    }
    if (v2 == 'o' || v2 == 'u') {
      return "ow";
    }
  }
  if (v1 == 'e') {
    if (v2 == 'i') {
      return "ay";
    }
    if (v2 == 'u') {
      return "eh-oo";
    }
  }
  if (v1 == 'i') {
    if (v2 == 'u') {
      return "ew";
    }
  }
  if (v1 == 'o') {
    if (v2 == 'u') {
      return "ow";
    }
    if (v2 == 'i') {
      return "oy";
    }
  }
  if (v1 == 'u') {
    if (v2 == 'i') {
      return "ooey";
    }
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  std::cout << "Input to SingleVowelPronunciation() : \"" << v << "\""
            << std::endl;
  if (v == 'a') {
    return "ah";
  }
  if (v == 'e') {
    return "eh";
  }
  if (v == 'i') {
    return "ee";
  }
  if (v == 'o') {
    return "oh";
  }
  if (v == 'u') {
    return "oo";
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev,
                             const char& curr,
                             const char& next) {
  std::cout << "Input to ProcessCharacter() : \"" << prev << "\" \"" << curr
            << "\" \"" << next << "\"" << std::endl;
  std::string s;
  if (IsVowelGroup(curr, next)) {
    return VowelGroupPronunciation(curr, next);
  }
  if (IsVowel(curr)) {
    return SingleVowelPronunciation(curr);
  }
  if (IsConsonant(curr)) {
    s += ConsonantPronunciation(curr, prev);
    return s;
  }
  if (curr == '\'') {
    return s += '\'';
  }
  if (curr == ' ') {
    return s += ' ';
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
std::string Pronunciation(const std::string& word) {
  std::string result;
  for (size_t i = 0; i < word.size(); ++i) {
    char pre = 0;
    if (i > 0) {
      pre = word[i - 1];
    }
    char curr = word[i];
    char next = 0;
    if (i < word.size() - 1) {
      next = word[i + 1];
    }
    if (IsVowelGroup(curr, next)) {
      if (next == '\'' || next == ' ') {
        result += VowelGroupPronunciation(curr, next);
      } else {
        result += VowelGroupPronunciation(curr, next) + "-";
      }
      i++;
    } else if (IsVowel(curr)) {
      if (next == '\'' || next == ' ') {
        result += SingleVowelPronunciation(curr);
      } else {
        result += SingleVowelPronunciation(curr) + "-";
      }
    } else if (IsConsonant(curr)) {
      result += ConsonantPronunciation(curr, pre);
    } else if (curr == '\'' || curr == ' ') {
      result += curr;
    } else {
      result += ProcessCharacter(pre, curr, next) + "-";
    }
  }
  if (result[result.length() - 1] == '-') {
    result = result.erase(result.length() - 1);
  }
  return result;
}
/* {
  std::cout << "Input to Pronunciation() : " << word << std::endl;
  std::string result;
  result += ProcessCharacter('\0', word[0], word[1]);
  if (IsVowelGroup(word[0], word[1])) {
    result += "-";
  } else if (IsVowel(word[0])) {
    if (word[1] == '\'' || word[1] == ' ') {
      result += "";
    } else {
      result += "-";
    }
  }
  for (size_t i = 1; i < word.size() - 1; ++i) {
    char pre = word[i - 1];
    char curr = word[i];
    char next = word[i + 1];
    if (IsVowelGroup(curr, next)) {
      if (next == '\'' || next == ' ') {
        result += VowelGroupPronunciation(curr, next);
      } else {
        result += VowelGroupPronunciation(curr, next) + "-";
      }
      i++;

    } else if (IsVowel(curr)) {
      if (next == '\'' || next == ' ') {
        result += SingleVowelPronunciation(curr);
      } else {
        result += SingleVowelPronunciation(curr) + "-";
      }

    } else if (IsConsonant(curr)) {
      result += ConsonantPronunciation(curr, pre);
    } else if (curr == '\'') {
      result += '\'';
    } else if (curr == ' ') {
      result += ' ';
    } else {
      result += ProcessCharacter(pre, curr, next) + "-";
    }
  }
  if (IsVowelGroup(word[word.size() - 2], word[word.size() - 1])) {
    if (!(IsVowelGroup(word[word.size() - 3], word[word.size() - 2]))) {
      result += "";
      result = result.erase(result.length() - 1);
    } else {
      result +=
          ProcessCharacter(word[word.size() - 2], word[word.size() - 1], '\0');
    }
  } else if (IsVowel(word[word.size() - 1])) {
    result += SingleVowelPronunciation(word[word.size() - 1]);
  } else {
    result +=
        ProcessCharacter(word[word.size() - 2], word[word.size() - 1], '\0');
  }

  return result;
}
*/
/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
  std::cout << "Input to GetPronunciation() : " << hawaiian_word << std::endl;
  if (IsValidWord(StringToLower(hawaiian_word))) {
    return Pronunciation(StringToLower(hawaiian_word));
  }
  throw std::invalid_argument("exception");
}