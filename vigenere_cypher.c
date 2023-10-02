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

// Function to filter special characters and store their positions
char *filterAndStoreSpecialChars(const char *input, SpecialCharInfo **specialChars, int *numSpecialChars)
{
    int len = strlen(input);

    // Allocate memory for filtered string
    char *filteredStr = (char *)malloc((len + 1) * sizeof(char));
    if (filteredStr == NULL)
    {
        // Handle memory allocation error
        return NULL;
    }

    // Initialize variables
    *specialChars = (SpecialCharInfo *)malloc(len * sizeof(SpecialCharInfo));
    if (*specialChars == NULL)
    {
        // Handle memory allocation error
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

// Function to reintroduce special characters
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

char * getText() {
    SpecialCharInfo *specialChars;
    int numSpecialChars;
    FILE *file = fopen("desafio1.txt", "r"); // Replace "your_file.txt" with the path to your file

    char *contents = NULL;
    size_t size = 0;
    char buffer[1024]; // Buffer to read file contents

    while (fgets(buffer, sizeof(buffer), file) != NULL) {

        size_t new_size = size + strlen(buffer) + 2; // +2 for the newline and space
        char *new_contents = (char *)realloc(contents, new_size);

        contents = new_contents;

        strcat(contents, buffer);
        strcat(contents, " "); // Add a space
        size = new_size - 1; // Update the size
    }

    fclose(file);

    // At this point, 'contents' contains the file contents with spaces for new lines
    char *filteredStr = filterAndStoreSpecialChars(contents, &specialChars, &numSpecialChars);

    return filteredStr;
}

int ascii(int x)
{
    return x + 97;
}

/*char * parse_text(char * text,size_t size){
    for (int i = 0; i < size -1; i++){

    }
}
*/

int alphabet(char x)
{
    tolower(x);
    return (int)x - 97;
}

char *cypher(char *message, char *key_string, size_t size)
{
    // pega um ascii, compara com a message com a chave repetida, substitui os valores
    char *cyphertext = NULL;
    cyphertext = malloc(size);
    for (int i = 0; i < size - 1; i++)
    {
        // 122 é a última letra do alfabeto em ascii, então subtraio 26 para ir pro começo conforme a tabela de vigenere
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
    // pega um ascii, compara com a string com a chave repetida, substitui os valores
    char *message = NULL;
    message = malloc(size);
    for (int i = 0; i < size - 1; i++)
    {
        // 97 é a primeira letra do alfabeto em ascii, então somo 26 para ir pro final conforme a tabela de vigenere
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
        // printf("%c%c%c\n", a, b, c);
        for (int j = i + 3; j < size - 3; j++)
        {
            if (cypher[j] == a && cypher[j + 1] == b && cypher[j + 2] == c)
            {
                int distance = j - i;
                printf("%c%c%c Distancia: %d (Divisores:", a, b, c, distance);
                for (int k = 1; k < distance; k++)
                {
                    if (distance % k == 0)
                    {
                        printf(" %d", k);
                    }
                }
                printf(")\n");
                // printf("Distancia entre trigramas: ", distance);
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

    char *key = (char *)malloc(key_size * (sizeof(char)));
    //pt
    /*for (int j = 0; j < key_size; j++)
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
        key[j] = ascii(topthree);
        printf("Key letter %d: %c\n", j + 1, key[j]);
    }*/
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
        key[j] = ascii(topthree);
        printf("Key letter %d: %c\n", j + 1, key[j]);
    }  

    printf("Do you want to edit the key?\n1)sim\n2}não\nEscolha: ");
    int choice = 0;
    char newline;
    scanf("%d", &choice);

    while ((newline = getchar()) != '\n' && newline != EOF);

    if (choice == 1)
    {
        printf("Enter a key: ");
        size_t key_size = getline(&key, &size, stdin);
        printf("You entered: %s", key);
        char *key_string = generateKeyString(key, string_size, key_size);
        char *message = decypher(filteredStr, key_string, string_size);
        reintroduceSpecialChars(message, specialChars, numSpecialChars);
        printf("%s", message);
        free(key_string);
    }
    else if (choice == 2)
    {
        char *key_string = generateKeyString(key, string_size, key_size);
        char *message = decypher(filteredStr, key_string, string_size);
        reintroduceSpecialChars(message, specialChars, numSpecialChars);
        printf("%s", message);
        free(key_string);
    }
    else
    {
        printf("1 ou 2!\n");
    }
    free(cyphertext); free(key); free(filteredStr);
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
            printf("Insira 1, 2 ou 3!\n");
            break;
        }
    }
}
