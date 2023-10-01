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
    //char * trigram_list = (char *) malloc(size * sizeof(char));
    for(int i = 0; i < size - 1; i++){
        char a = cypher[i];
        char b = cypher[i + 1];
        char c = cypher[i + 2];
        //printf("%c%c%c\n", a, b, c);
        for(int j = i + 3; j < size - 3; j++){
            if(cypher[j] == a && cypher[j + 1] == b && cypher[j + 2] == c){
                int distance = j - i;
                //printf("%c%c%c\n", a, b, c);
                printf("Distancia entre trigramas: %d\n", distance);
            }
        }
    }

}

void trigram_list(char * cypher, size_t size){
    for(int i = 0; i < size - 3; i++){
        char a = cypher[i];
        char b = cypher[i + 1];
        char c = cypher[i + 2];
        //printf("%c%c%c\n", a, b, c);
        for(int j = i + 3; j < size - 3; j++){
            if(cypher[j] == a && cypher[j + 1] == b && cypher[j + 2] == c){
                int distance = j - i;
                printf("%c%c%c Distancia: %d (Divisores:", a, b, c, distance);
                for(int k = 1; k < distance; k++){
                    if (distance % k == 0){
                        printf(" %d", k);
                    }
                }
                printf(")\n");
                //printf("Distancia entre trigramas: ", distance);
            }
        }
    }
    /*for(int i = 0; i < size - 3; i++){
        //if(trigram_list[i] != 0){
            printf("Trigrama: %c%c%c Distancia: %d\n", cypher[i], cypher[i + 1], cypher[i + 2], trigram_list[i]);
        //}
    }*/
}

void kasiski(){
    char *cypher = NULL;
    size_t size = 0;
    int key_size;

    printf("Enter a cypher: ");
    size_t string_size = getline(&cypher, &size, stdin);
    printf("You entered: %s", cypher);

    trigram_list(cypher, string_size);
    printf("What do you think the size of the key is?\nAnswer: ");
    scanf("%d", &key_size);
    printf("Assuming key size %d ...\n", key_size);

    //printa colunas equivalentes a cada letra da chave
    
    for (int i = 0; i < string_size -1; i++){
        if (i % key_size == 0){
            printf("\n ");
        }
        printf(" %c  | ", cypher[i]);
    }
    printf("\n");
    for (int i = 0; i < key_size; i++){
        printf("------");
    }

    printf("\n");

    int letters[21] = {0};
    int frequency[21] = {0};
    for (int i = 0; i < key_size; i++){
        int most_common_letter_quantity = 0;
        int most_common_letter_index = 0;
        for (int j = i; j < string_size -1; j += key_size){
            int matches = 1;
            for (int k = j + key_size; k < string_size -1; k += key_size){
                if (cypher[j] == cypher[k]){
                    matches++;
                    if (matches > most_common_letter_quantity){
                        most_common_letter_quantity = matches;
                        most_common_letter_index = j;
                    }
                }

            }
            
        }
        printf("%d x %c|", most_common_letter_quantity, cypher[most_common_letter_index]);
    }
    printf("\n\n\n");

    double enLetterFrequencies[26] = {
        0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.0697, 0.0015,
        0.0077, 0.0402, 0.0241, 0.0675, 0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906,
        0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007
    };

    double ptletterFrequencies[26] = {
        0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0130, 0.0618, 0.0041,
        0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434,
        0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047
    };
    //divide_cypher(cypher,);
    
    free(cypher);
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
