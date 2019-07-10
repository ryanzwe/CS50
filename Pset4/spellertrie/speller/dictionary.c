// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
} node;

// Represents a trie
node *root;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char word)
{
    return tolower(word) - 'a';
}

int totalWordsLoaded = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    node *currentBranch = NULL;
    while (fscanf(file, "%s", word) != EOF)
    {
        currentBranch = root;
        for (int i = 0, len = strlen(word); i < len; i++)
        {
            //obtaining the alpha index & checking if its within the range
            int letterHash;
            //If the letter is an apostraphe, set it to the last node space
            if (word[i] == '\'')
            {
                letterHash = 26;
            }
            else // else obtain the alphanumerical index
            {
                letterHash = hash(word[i]);
            }
                //If the current childs letter is null, malloc it a branch
            if (currentBranch->children[letterHash] == NULL)
            {
                currentBranch->children[letterHash] = malloc(sizeof(node));
                //clearing the memory on the newly malloced pointer
                currentBranch->children[letterHash]->is_word = false;
                for (int j = 0; j < N; j++)
                {
                     currentBranch->children[letterHash]->children[j] = NULL;
                }
                if (currentBranch == NULL)
                {
                    printf("OUT OF MEMORY \n\n\n\n");
                    unload();
                   return false;
                }
            }
            // Set the current branch to the child
            currentBranch = currentBranch->children[letterHash];
        }
        // once we hit the end of the word, set it true
        currentBranch->is_word = true;
        totalWordsLoaded++;
    }
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalWordsLoaded;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Temporary vars
    node *currentBranch = root;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        int letterHash;
        if (word[i] == '\'')
        {
            letterHash = 26;
        }
        else
        {
            letterHash = hash(word[i]);
        }
        //If the trie does not contain the first letter, then we know the word is null and there's no point continuing
        if (currentBranch->children[letterHash] == NULL)
        {
            return false;
        }
        currentBranch = currentBranch->children[letterHash];
    }
    //After the full word has iterated, see if the word was set as a valid word when loading the dictionary
    return currentBranch->is_word;
}

// Unloads dictionary from memory, returning true if successful else false
void freeNodeSet(node *newRoot)
{
    for (int i = 0; i < N; i++)
    {
        // If the current new root has children, traverse down to the end
        if (newRoot->children[i])
        {
            freeNodeSet(newRoot->children[i]);
        }
    }
    //Once this point has been reached, we must be the bottom node
    free(newRoot);
}
bool unload(void)
{
    freeNodeSet(root);
    return true;
}
