#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void cypher(char * message, char * key_string, size_t size){
   // pega um ascii, compara com a message com a chave repetida, substitui os valores  
    char * cypher = NULL;
    cypher = malloc(size);
    for(int i = 0; i < size -1; i++){
        //122 é a última letra do alfabeto em ascii, então subtraio 26 para ir pro começo conforme a tabela de vigenere
        if (((int) key_string[i] - (int) 'a') + (int) message[i] > 122){
            cypher[i] = ((int) key_string[i] - (int) 'a') + (int) message[i] - 26;
        }
        else{
            cypher[i] = ((int) key_string[i] - (int) 'a') + (int) message[i];
        }
    }
    printf("%s\n", cypher);
    free(cypher);
}

void decypher(char * cypher, char * key_string, size_t size){
   // pega um ascii, compara com a string com a chave repetida, substitui os valores  
    char * message = NULL;
    message = malloc(size);
    for(int i = 0; i < size -1; i++){
        //97 é a primeira letra do alfabeto em ascii, então somo 26 para ir pro final conforme a tabela de vigenere
        if ((int) cypher[i] - ((int) key_string[i] - (int) 'a') < 97){
            message[i] = (int) cypher[i] - ((int) key_string[i] - (int) 'a') + 26;
        }
        else{
            message[i] = (int) cypher[i] - ((int) key_string[i] - (int) 'a');
        }
    }
    printf("%s\n", message);
    free(message);
}

char * generate_key_string(char * key, size_t string_size, size_t key_size){
    int i, j;
    char * key_string = NULL;
    key_string = malloc(string_size);
    for(i = 0, j = 0; i < string_size - 1; i++, j++){
        if (j >= key_size - 1){
            j = 0;
        }
        key_string[i] = tolower(key[j]);
    }
    printf("The key string is: %s\n", key_string);
    return key_string;
}

void cypher_menu(){
    char *message = NULL;
    char *key = NULL;
    size_t size = 0;

    printf("Enter a message: ");
    size_t string_size = getline(&message, &size, stdin);
    printf("You entered: %s", message);

    printf("Enter a key: ");
    size_t key_size = getline(&key, &size, stdin);
    printf("You entered: %s", key);
    
    char * key_string = generate_key_string(key, string_size, key_size);
    cypher(message, key_string, string_size);

    free(message); free(key); free(key_string);
}

void trigram(char * cypher, size_t size){
    int matches = 0;
    for(int i = 0; i < size - 1; i++){
        char a = cypher[i];
        char b = cypher[i + 1];
        char c = cypher[i + 2];
        printf("%c%c%c\n", a, b, c);
        for(int j = i + 3; j < size - 3; j++){
            if(cypher[j] == a && cypher[j + 1] == b && cypher[j + 2] == c){
                printf("%c%c%c\n", a, b, c);
                matches++;
            }
        }
    }
    printf("%d\n", matches);
}

void digram(char * cypher, size_t size){
    int matches = 0;
    for(int i = 0; i < size - 1; i++){
        char a = cypher[i];
        char b = cypher[i + 1];
        printf("%c%c\n", a, b);
        for(int j = i + 2; j < size - 2; j++){
            if(cypher[j] == a && cypher[j + 1] == b){
                printf("%c%c\n",a,b);
                matches++;
            }
        }
    }
    printf("%d\n", matches);
}

void kasiski(){
    char *cypher = NULL;
    size_t size = 0;
    printf("Enter a cypher: ");
    size_t string_size = getline(&cypher, &size, stdin);
    printf("You entered: %s", cypher);

    trigram(cypher,string_size);

}

void decypher_menu(){
    char *cypher = NULL;
    char *key = NULL;
    size_t size = 0;

    printf("Enter a cypher: ");
    size_t string_size = getline(&cypher, &size, stdin);
    printf("You entered: %s", cypher);

    printf("Enter a key: ");
    size_t key_size = getline(&key, &size, stdin);
    printf("You entered: %s", key);
    
    char * key_string = generate_key_string(key, string_size, key_size);
    decypher(cypher, key_string, string_size);

    free(cypher); free(key); free(key_string);
}

void main() {
    int choice;
    bool running = true;
    char newline;
    while (running){
        printf("1)Cypher a message with a key\n"
                "2)Decypher message with a key\n"
                "3)Decypher message without key\n\n"
                "Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            // Handle invalid input
            printf("Invalid input. Please enter 1, 2 or 3.\n");
            continue;
        }

        while ((newline = getchar()) != '\n' && newline != EOF);

        switch (choice){
            case 1:
                cypher_menu();
                running = false;
                break;
            case 2:
                decypher_menu();
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
