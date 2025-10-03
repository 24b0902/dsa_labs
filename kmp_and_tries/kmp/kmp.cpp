#include "kmp.h"

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(const std::string &pat, std::vector<int> &lps) {
    int M = pat.length();
    lps.resize(M);
    lps[0] = 0; 
    int len = 0; 
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search: returns vector of starting indices of pattern in text
std::vector<int> KMPSearch(const std::string &pat, const std::string &txt) {
//Implement here
    std::vector<int> lps;
    computeLPSArray(pat, lps);
    std::vector<int> result;

    int M = pat.length();
    int N = txt.length();
    int i = 0; 
    int j = 0; 

    while (i < N) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
            
        }

        if (j == M) {
            result.push_back(i - j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return result;
}
