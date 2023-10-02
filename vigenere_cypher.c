#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    char character;
    int position;
} SpecialCharInfo;


char *filterAndStoreSpecialChars(const char *input, SpecialCharInfo **specialChars, int *numSpecialChars)
{
    int len = strlen(input);

    // Allocate memory for filtered string
    char *filteredStr = (char *)malloc((len + 1) * sizeof(char));
    if (filteredStr == NULL)
    {
        return NULL;
    }

    *specialChars = (SpecialCharInfo *)malloc(len * sizeof(SpecialCharInfo));
    if (*specialChars == NULL)
    {
        free(filteredStr);
        return NULL;
    }

    int filteredIndex = 0;
    *numSpecialChars = 0;

    for (int i = 0; i < len; i++)
    {
        char currentChar = input[i];
        if (isalpha(currentChar))
        {
            filteredStr[filteredIndex] = currentChar;
            filteredIndex++;
        }
        else
        {
            // Store special character information
            (*specialChars)[*numSpecialChars].character = currentChar;
            (*specialChars)[*numSpecialChars].position = filteredIndex;
            (*numSpecialChars)++;
        }
    }

    filteredStr[filteredIndex] = '\0';

    return filteredStr;
}

void reintroduceSpecialChars(char *inputStr, const SpecialCharInfo *specialChars, int numSpecialChars)
{
    for (int i = numSpecialChars - 1; i >= 0; i--)
    {
        int position = specialChars[i].position;
        char character = specialChars[i].character;
        memmove(inputStr + position + 1, inputStr + position, strlen(inputStr) - position + 1);
        inputStr[position] = character;
    }
}

int ascii(int x)
{
    return x + 97;
}

int alphabet(char x)
{
    tolower(x);
    return (int)x - 97;
}

char *cypher(char *message, char *key_string, size_t size)
{
    char *cyphertext = NULL;
    cyphertext = malloc(size);
    for (int i = 0; i < size - 1; i++)
    {
        if (alphabet(key_string[i]) + alphabet(message[i]) > 26)
        {
            cyphertext[i] = ascii(alphabet(key_string[i]) + alphabet(message[i]) - 26);
        }
        else
        {
            cyphertext[i] = ascii(alphabet(key_string[i]) + alphabet(message[i]));
        }
    }
    return cyphertext;
}

char *decypher(char *cypher, char *key_string, size_t size)
{
    char *message = NULL;
    message = malloc(size);
    for (int i = 0; i < size - 1; i++)
    {
        if (alphabet(cypher[i]) - alphabet(key_string[i]) < 0)
        {
            message[i] = ascii(alphabet(cypher[i]) - alphabet(key_string[i]) + 26);
        }
        else
        {
            message[i] = ascii(alphabet(cypher[i]) - alphabet(key_string[i]));
        }
    }
    return message;
}

char *generateKeyString(char *key, size_t string_size, size_t key_size)
{
    int i, j;
    char *key_string = NULL;
    key_string = malloc(string_size);
    for (i = 0, j = 0; i < string_size - 1; i++, j++)
    {
        if (j >= key_size - 1)
        {
            j = 0;
        }
        key_string[i] = tolower(key[j]);
    }
    printf("The key string is: %s\n\n", key_string);
    return key_string;
}

void cypherSetup()
{
    char *message = NULL;
    char *key = NULL;
    size_t size = 0;
    SpecialCharInfo *specialChars;
    int numSpecialChars;
    char lang[] = "en";

    printf("Enter a message: ");
    size_t string_size = getline(&message, &size, stdin);
    printf("You entered: %s", message);
    char *filteredStr = filterAndStoreSpecialChars(message, &specialChars, &numSpecialChars);

    printf("Enter a key: ");
    size_t key_size = getline(&key, &size, stdin);
    printf("You entered: %s", key);

    char *key_string = generateKeyString(key, string_size, key_size);
    char *cyphertext = cypher(filteredStr, key_string, string_size);
    reintroduceSpecialChars(cyphertext, specialChars, numSpecialChars);
    printf("%s", cyphertext);

    free(message);
    free(key);
    free(key_string);
}

void trigramDistance(char *cypher, size_t size)
{
    for (int i = 0; i < size - 3; i++)
    {
        char a = cypher[i];
        char b = cypher[i + 1];
        char c = cypher[i + 2];
        for (int j = i + 3; j < size - 3; j++)
        {
            if (cypher[j] == a && cypher[j + 1] == b && cypher[j + 2] == c)
            {
                int distance = j - i;
                printf("%c%c%c Distance: %d (Divisors:", a, b, c, distance);
                for (int k = 1; k < distance; k++)
                {
                    if (distance % k == 0 > 3)
                    {
                        printf(" %d", k);
                    }
                }
                printf(")\n");
            }
        }
    }
}

void kasiski()
{
    char *cyphertext = NULL;
    size_t size = 0;
    int key_size;
    SpecialCharInfo *specialChars;
    int numSpecialChars;
    char lang[] = "en";

    printf("Enter a cypher: ");
    size_t string_size = getline(&cyphertext, &size, stdin);
    printf("You entered: %s", cyphertext);
    char *filteredStr = filterAndStoreSpecialChars(cyphertext, &specialChars, &numSpecialChars);

    trigramDistance(filteredStr, string_size);
    printf("What do you think the size of the key is?\nAnswer: ");
    scanf("%d", &key_size);
    printf("Assuming key size %d ...\n", key_size);

    char *enKey = (char *)malloc(key_size * (sizeof(char)));
    char *ptKey = (char *)malloc(key_size * (sizeof(char)));
    for (int j = 0; j < key_size; j++)
    {
        int occurrences[26] = {0};
        for (int i = j; i < string_size - 1; i += key_size)
        {
            occurrences[alphabet( filteredStr[i])]++;
        }
        int topthree = 0;
        int total = 0;
        for (int k = j; k < 26; k += key_size)
        {
            int a = k;
            int e = k + 4;
            int o = k + 14;

            if (e > 25)
            {
                e -= 26;
            }
            if (o > 25)
            {
                o -= 26;
            }
            if (occurrences[a] + occurrences[e] + occurrences[o] > total)
            {
                total = occurrences[a] + occurrences[e] + occurrences[o];
                topthree = a;
            }
        }
        ptKey[j] = ascii(topthree);
        printf("Portugues %d: %c\n", j + 1, ptKey[j]);
    }
    for (int j = 0; j < key_size; j++)
    {
        int occurrences[26] = {0};
        for (int i = j; i < string_size - 1; i += key_size)
        {
            occurrences[alphabet( filteredStr[i])]++;
        }
        int topthree = 0;
        int total = 0;
        for (int k = j; k < 26; k += key_size)
        {
            int a = k;
            int e = k + 4;
            int i = k + 8;

            if (e > 25)
            {
                e -= 26;
            }
            if (i > 25)
            {
                i -= 26;
            }
            if (occurrences[a] + occurrences[e] + occurrences[i] > total)
            {
                total = occurrences[a] + occurrences[e] + occurrences[i];
                topthree = a;
            }
        }
        enKey[j] = ascii(topthree);
        printf("Ingles %d: %c\n", j + 1, enKey[j]);
    }

    printf("Choose key:\n1)Portuguese\n2}English\n3)Edit (remember key size %d)\nChoice: ",key_size);
    int choice = 0;
    char newline;
    scanf("%d", &choice);

    while ((newline = getchar()) != '\n' && newline != EOF);

    if (choice == 3)
    {
        printf("Enter a key: ");
        size_t key_size = getline(&ptKey, &size, stdin);
        printf("You entered: %s", ptKey);
        char *key_string = generateKeyString(ptKey, string_size, key_size);
        char *message = decypher(filteredStr, key_string, string_size);
        reintroduceSpecialChars(message, specialChars, numSpecialChars);
        printf("Message: %s", message);
        free(key_string);
    }
    else if (choice == 2)
    {
        char *key_string = generateKeyString(enKey, string_size, key_size);
        char *message = decypher(filteredStr, key_string, string_size);
        reintroduceSpecialChars(message, specialChars, numSpecialChars);
        printf("Message: %s", message);
        free(key_string);
    }
    else if (choice == 1)
    {
        char *key_string = generateKeyString(ptKey, string_size, key_size);
        char *message = decypher(filteredStr, key_string, string_size);
        reintroduceSpecialChars(message, specialChars, numSpecialChars);
        printf("Message: %s", message);
        free(key_string);
    }
    else
    {
        printf("1 or 2!\n");
    }
    free(cyphertext); free(ptKey); free(filteredStr); free(enKey);
}

void decypherSetup()
{
    char *cyphertext = NULL;
    char *key = NULL;
    size_t size = 0;
    SpecialCharInfo *specialChars;
    int numSpecialChars;

    printf("Enter a cypher: ");
    size_t string_size = getline(&cyphertext, &size, stdin);
    printf("You entered: %s", cyphertext);
    char *filteredStr = filterAndStoreSpecialChars(cyphertext, &specialChars, &numSpecialChars);

    printf("Enter a key: ");
    size_t key_size = getline(&key, &size, stdin);
    printf("You entered: %s", key);

    char *key_string = generateKeyString(key, string_size, key_size);
    char *message = decypher(filteredStr, key_string, string_size);
    reintroduceSpecialChars(message, specialChars, numSpecialChars);
    printf("%s", message);

    free(cyphertext);
    free(key);
    free(key_string);
}

void main()
{
    int choice;
    bool running = true;
    char newline;
    while (running)
    {
        printf("1)Cypher a message with a key\n"
               "2)Decypher message with a key\n"
               "3)Decypher message without key\n\n"
               "Choose an option: ");
        if (scanf("%d", &choice) != 1)
        {
            // Handle invalid input
            printf("Invalid input. Please enter 1, 2 or 3.\n");
            continue;
        }

        while ((newline = getchar()) != '\n' && newline != EOF);

        switch (choice)
        {
        case 1:
            cypherSetup();
            running = false;
            break;
        case 2:
            decypherSetup();
            running = false;
            break;
        case 3:
            kasiski();
            break;
        default:
            printf("Insert 1, 2 ou 3!\n");
            break;
        }
    }
}
