#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MASTER 0
#define HORROR 1
#define COMEDY 2
#define FANTASY 3
#define SF 4

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}


int main (int argc, char *argv[]) {
    int  numtasks, rank;
    char buff[1000000];
    char text[1000000];
    char text_recv[1000000];
    char text_final[1000000];
    char recv[1000000];
    int ID = 1;
    char paragraf[1000000];
    size_t len = 0;
    char *line = NULL;
    int lungime;
    int lenght;
    char numefisieriesire[1000000];
    int lungime_fisier;
    FILE *input;
    FILE *output;

    // numefisieriesire = strtok(argv[1], ".");
    // numefisieriesire = strcat(numefisieriesire, ".out");
    lungime_fisier = strlen(argv[1]);
    for (int i = 0; i < lungime_fisier; i++) {
        numefisieriesire[i] = argv[1][i];
    }
    numefisieriesire[lungime_fisier - 3] = 'o';
    numefisieriesire[lungime_fisier - 2] = 'u';
    numefisieriesire[lungime_fisier - 1] = 't';

    // printf("%s\n", numefisieriesire);

    output = fopen(numefisieriesire, "w");

    if ((input = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status status;

    // First process starts the circle.
    if (rank == MASTER) {
        while ((getline(&line, &len, input)) != -1) {
            if (strcmp(line, "horror\n") == 0) {
                strcat(text, buff);
                strcat(text, line);
                while ((getline(&line, &len, input)) != -1) {
                    if (strcmp(line, "\n") == 0) {
                        break;
                    }
                    strcat(text, line);
                }
                lungime = strlen(text);
                MPI_Send(&lungime, 1, MPI_INT, HORROR, 0, MPI_COMM_WORLD);
                MPI_Send(text, lungime, MPI_CHAR, HORROR, 0, MPI_COMM_WORLD);

                MPI_Recv(&lenght, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&text_final, lenght, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                
                fprintf(output, "%s\n", text_final);

                memset(text, 0, lungime);
                memset(text_final, 0, lenght);
            }

            if (strcmp(line, "comedy\n") == 0) {
                strcat(text, buff);
                strcat(text, line);
                while ((getline(&line, &len, input)) != -1) {
                    if (strcmp(line, "\n") == 0) {
                        break;
                    }
                    strcat(text, line);
                }
                lungime = strlen(text);
                MPI_Send(&lungime, 1, MPI_INT, COMEDY, 0, MPI_COMM_WORLD);
                MPI_Send(text, lungime, MPI_CHAR, COMEDY, 0, MPI_COMM_WORLD);

                MPI_Recv(&lenght, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&text_final, lenght, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                
                fprintf(output, "%s\n", text_final);

                memset(text, 0, lungime);
                memset(text_final, 0, lenght);
            }

            if (strcmp(line, "fantasy\n") == 0) {
                strcat(text, buff);
                strcat(text, line);
                while ((getline(&line, &len, input)) != -1) {
                    if (strcmp(line, "\n") == 0) {
                        break;
                    }
                    strcat(text, line);
                }
                lungime = strlen(text);
                MPI_Send(&lungime, 1, MPI_INT, FANTASY, 0, MPI_COMM_WORLD);
                MPI_Send(text, lungime, MPI_CHAR, FANTASY, 0, MPI_COMM_WORLD);

                MPI_Recv(&lenght, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&text_final, lenght, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                
                fprintf(output, "%s\n", text_final);

                memset(text, 0, lungime);
                memset(text_final, 0, lenght);
            }

            if (strcmp(line, "science-fiction\n") == 0) {
                strcat(text, buff);
                strcat(text, line);
                while ((getline(&line, &len, input)) != -1) {
                    if (strcmp(line, "\n") == 0) {
                        break;
                    }
                    strcat(text, line);
                }
                lungime = strlen(text);
                MPI_Send(&lungime, 1, MPI_INT, SF, 0, MPI_COMM_WORLD);
                MPI_Send(text, lungime, MPI_CHAR, SF, 0, MPI_COMM_WORLD);

                MPI_Recv(&lenght, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&text_final, lenght, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                
                fprintf(output, "%s\n", text_final);

                memset(text, 0, lungime);
                memset(text_final, 0, lenght);
            }
        } 
        lungime = -1;
        MPI_Send(&lungime, 1, MPI_INT, HORROR, 0, MPI_COMM_WORLD);
        MPI_Send(&lungime, 1, MPI_INT, COMEDY, 0, MPI_COMM_WORLD);
        MPI_Send(&lungime, 1, MPI_INT, FANTASY, 0, MPI_COMM_WORLD);
        MPI_Send(&lungime, 1, MPI_INT, SF, 0, MPI_COMM_WORLD);

    } else if (rank == HORROR) {
        int lungime;

        while (1) {
            MPI_Recv(&lungime, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            if (lungime == -1) {
                break;
            }
            MPI_Recv(&recv, lungime, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

            char *buffer;
            char newtext[2 * lungime];
            int count;
           
            buffer = strtok(recv, "\n");
            strcat(text_recv, buffer);
            strcat(text_recv, "\n");
            buffer = strtok(NULL, "\n");
            while (buffer != NULL) {
                count = 0;
                for (int i = 0; i < strlen(buffer); i++) {
                    newtext[count] = buffer[i];
                    count++;
                    if (buffer[i] != 'a' && buffer[i] != 'e' && buffer[i] != 'i' &&
                        buffer[i] != 'o' && buffer[i] != 'u' &&
                        buffer[i] != 'A' && buffer[i] != 'E' && buffer[i] != 'I' &&
                        buffer[i] != 'O' && buffer[i] != 'U' && buffer[i] != ' ' &&
                        buffer[i] != '.' && buffer[i] != '!' && buffer[i] != '?' &&
                        buffer[i] != ',') {
                        newtext[count] = tolower(buffer[i]);
                        count++;
                    }
                }
                newtext[count] = '\0';
                strcat(text_recv, newtext); 
                strcat(text_recv, "\n");
                buffer = strtok(NULL, "\n");
            }

            int lenght;
            lenght = strlen(text_recv);
            MPI_Send(&lenght, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
            MPI_Send(&text_recv, lenght, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD);
            memset(text_recv, 0, lenght);
            memset(recv, 0, lenght);
        }

    } else if (rank == COMEDY) {
        int lungime;

        while (1) {
            MPI_Recv(&lungime, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            if (lungime == -1) {
                break;
            }
            MPI_Recv(&recv, lungime, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

            char *buffer;
            char word[1000000];
            int count;
           
            buffer = strtok(recv, "\n");
            strcat(text_recv, buffer);
            strcat(text_recv, "\n");
            buffer = strtok(NULL, "\n");
            while (buffer != NULL) {
                count = 0;
                for (int i = 0; i < strlen(buffer); i++) {
                    if(buffer[i] == ' ') {
                        strcat(text_recv, word);
                        strcat(text_recv, " ");
                        count = -1;
                        memset(word, 0, 1000000);
                    } else if (count % 2 != 0) {
                        word[count] = toupper(buffer[i]);
                    } else {
                        word[count] = buffer[i];
                    }
                    count++;
                }
                if(buffer[strlen(buffer)] == '\0') {
                    strcat(text_recv, word);
                }
                memset(word, 0, 1000000);
                strcat(text_recv, "\n");
                buffer = strtok(NULL, "\n");
            }

            int lenght;
            lenght = strlen(text_recv);
            MPI_Send(&lenght, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
            MPI_Send(&text_recv, lenght, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD);
            memset(text_recv, 0, lenght);
            memset(recv, 0, lenght);
        }

    } else if (rank == FANTASY) {
        int lungime;

        while (1) {
            MPI_Recv(&lungime, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            if (lungime == -1) {
                break;
            }
            MPI_Recv(&recv, lungime, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

            char *buffer;
            char word[1000000];
            int count;
           
            buffer = strtok(recv, "\n");
            strcat(text_recv, buffer);
            strcat(text_recv, "\n");
            buffer = strtok(NULL, "\n");
            while (buffer != NULL) {
                count = 0;
                for (int i = 0; i < strlen(buffer); i++) {
                    if(buffer[i] == ' ') {
                        strcat(text_recv, word);
                        strcat(text_recv, " ");
                        count = -1;
                        memset(word, 0, 1000000);
                    } else if (count == 0) {
                        word[count] = toupper(buffer[i]);
                    } else {
                        word[count] = buffer[i];
                    }
                    count++;
                }
                if(buffer[strlen(buffer)] == '\0') {
                    strcat(text_recv, word);
                }
                memset(word, 0, 1000000);
                strcat(text_recv, "\n");
                buffer = strtok(NULL, "\n");
            }

            int lenght;
            lenght = strlen(text_recv);
            MPI_Send(&lenght, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
            MPI_Send(&text_recv, lenght, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD);
            memset(text_recv, 0, lenght);
            memset(recv, 0, lenght);
        }

    } else if (rank == SF) {
        int lungime;

        while (1) {
            MPI_Recv(&lungime, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            if (lungime == -1) {
                break;
            }
            MPI_Recv(&recv, lungime, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

            char *buffer;
            char word[1000000];
            int count;
            int seven_word;
           
            buffer = strtok(recv, "\n");
            strcat(text_recv, buffer);
            strcat(text_recv, "\n");
            buffer = strtok(NULL, "\n");
            while (buffer != NULL) {
                count = 0;
                seven_word = 1;
                for (int i = 0; i < strlen(buffer); i++) {
                    if(buffer[i] == ' ') {
                        if (seven_word % 7 == 0) {
                            strrev(word);
                        }
                        strcat(text_recv, word);
                        strcat(text_recv, " ");
                        count = -1;
                        seven_word++;
                        memset(word, 0, 1000000);
                    } else {
                        word[count] = buffer[i];
                    }
                    count++;
                }
                if(seven_word % 7 == 0) {
                    strrev(word);
                }
                if(buffer[strlen(buffer)] == '\0') {
                    strcat(text_recv, word);
                }
                memset(word, 0, 1000000);
                strcat(text_recv, "\n");
                buffer = strtok(NULL, "\n");
            }

            int lenght;
            lenght = strlen(text_recv);
            MPI_Send(&lenght, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
            MPI_Send(&text_recv, lenght, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD);
            memset(text_recv, 0, lenght);
            memset(recv, 0, lenght);

        }
    }

    MPI_Finalize();
    fclose(input);
    fclose(output);

}
