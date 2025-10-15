#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_PLAYERS 100
#define MAX_NAME_LENGTH 50


// using struct to store the data of the players
typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    int AddScore;
    int SubtractScore;
    int MultiScore;
    int DivideScore;
    int isPlayerActive;
    int PlayerTotal;
} Player;


// initialize the players array

Player players[MAX_PLAYERS];
int numPlayers = 0;
int LogIndex = -1;


// to calculate the total score of a player

int calculatePlayerTotal(Player player) {
    return player.AddScore + player.SubtractScore + player.MultiScore + player.DivideScore;
}


// comparing scores of players to sort them in descending order

int comparePlayers(const void *a, const void *b) {
    const Player *playerA = (const Player *)a;
    const Player *playerB = (const Player *)b;
    return (playerB->AddScore + playerB->SubtractScore + playerB->MultiScore + playerB->DivideScore) - (playerA->AddScore + playerA->SubtractScore + playerA->MultiScore + playerA->DivideScore);
}


void displayMainMenu();
void displayLoggedInMenu();
void signUp();
void login();
void arithGame();
void displayLeaderboard();
void removeAccount();
void saveData();
void loadData();
void clrScreen();
void pauseForReading();
void LeadSort();

int main() {
    loadData();

    int choice;
    do {
        clrScreen();

        if (LogIndex == -1) {
            displayMainMenu();
        } else {
            displayLoggedInMenu();
        }
        
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid choice.\n");
            pauseForReading();
            continue;
        }

        switch (choice) {
            case 1:
                if (LogIndex == -1) {
                    signUp();
                } else {
                    arithGame();
                }
                break;
            case 2:
                if (LogIndex == -1) {
                    login();
                } else {
                    LeadSort();
                    displayLeaderboard();
                }
                break;
            case 3:
                if (LogIndex == -1) {
                    printf("Exiting the program. Goodbye!\n");
                    pauseForReading();
                    return 0;
                } else {
                    removeAccount();
                    pauseForReading();
                }
                break;
            case 4:
                if (LogIndex != -1) {
                    LogIndex = -1;
                    printf("Logged out successfully.\n");
                    pauseForReading();
                }
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                pauseForReading();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pauseForReading();
        }
        
    } while (choice != 5);

    saveData();
    return 0;
}

void displayMainMenu() {
    printf("===== Welcome to the Game Menu =====\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Exit\n");
}


// sub-menu for the logged in user

void displayLoggedInMenu() {
    printf("===== Welcome, %s =====\n", players[LogIndex].username);
    printf("1. Arithmetic Game\n");
    printf("2. Leaderboard\n");
    printf("3. Remove Account\n");
    printf("4. Logout\n");
    printf("5. Exit\n");
}


// function to create a new aacount

void signUp() {
    clrScreen();
    printf("===== Sign Up =====\n");

    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    printf("Enter username: ");
    scanf(" %49[^\n]", username); // %49[^\n] allows program to handle spaces

    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(username, players[i].username) == 0 && players[i].isPlayerActive) {
            printf("Username '%s' is already taken. Please choose a different username.\n", username);
            pauseForReading();
            return;
        }
    }

    printf("Enter password: ");
    scanf(" %49[^\n]", password);

    strcpy(players[numPlayers].username, username);
    strcpy(players[numPlayers].password, password);
    players[numPlayers].AddScore = 0;
    players[numPlayers].SubtractScore = 0;
    players[numPlayers].MultiScore = 0;
    players[numPlayers].DivideScore = 0;
    players[numPlayers].isPlayerActive = 1;
    numPlayers++;

    saveData();
    printf("Account created successfully!\n");
    pauseForReading();
}


// login function

void login() {
    clrScreen();
    printf("===== Login =====\n");
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    printf("Enter username: ");
    scanf(" %49[^\n]", username);

    printf("Enter password: ");
    scanf(" %49[^\n]", password);

    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(username, players[i].username) == 0 && strcmp(password, players[i].password) == 0 && players[i].isPlayerActive) {
            LogIndex = i;
            printf("Login successful!\n");
            pauseForReading();
            return;
        }
    }
    printf("Invalid username or password.\n");
    pauseForReading();
}


// arith game function

void arithGame() {
    clrScreen();
    printf("===== Arithmetic Game =====\n");

    int choice;

    srand(time(NULL));

    do {
        printf("Choose an arithmetic operation:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid choice.\n");
            pauseForReading();
            continue;
        }

        if (choice < 1 || choice > 5) {
            printf("Invalid choice. Please try again.\n");
            pauseForReading();
            continue;
        }

        if (choice == 5) {
            printf("Returning to Main Menu.\n");
            pauseForReading();
            break;
        }

        int numQuestions = 3;
        int operationScore = 0;

        for (int i = 0; i < numQuestions; i++) {
            int num1, num2;
            char operation;

            switch (choice) {
                case 1:
                    operation = '+';
                    num1 = rand() % 20;
                    num2 = rand() % 20;
                    break;
                case 2:
                    operation = '-';
                    num1 = rand() % 20;
                    num2 = rand() % 20;
                    break;
                case 3:
                    operation = '*';
                    num1 = rand() % 10;
                    num2 = rand() % 10;
                    break;
                case 4:
                    operation = '/';
                    
                    do {
                        num1 = rand() % 100;
                        num2 = rand() % 10 + 1; // making sure that the divisor is not 0
                    } while (num1 % num2 != 0); // making sure that the remainder is 0
                    break;
            }

           
            printf("Question %d: %d %c %d = ?\n Your Answer: ", i + 1, num1, operation, num2);

                int userAnswer;
                scanf("%d", &userAnswer); // scan users answer

          
            int correctAnswer;
            switch (operation) {
                case '+':
                    correctAnswer = num1 + num2;
                    break;
                case '-':
                    correctAnswer = num1 - num2;
                    break;
                case '*':
                    correctAnswer = num1 * num2;
                    break;
                case '/':
                    correctAnswer = num1 / num2;
                    break;
            }

           
            if (userAnswer == correctAnswer) {
                printf("Correct!\n");
                operationScore++;
            } else {
                printf("Wrong! The correct answer was %d\n", correctAnswer);
            }
            pauseForReading();
            clrScreen();
        }

        
        switch (choice) {
            case 1:
                players[LogIndex].AddScore += operationScore;
                break;
            case 2:
                players[LogIndex].SubtractScore += operationScore;
                break;
            case 3:
                players[LogIndex].MultiScore += operationScore;
                break;
            case 4:
                players[LogIndex].DivideScore += operationScore;
                break;
        }

       
        players[LogIndex].PlayerTotal = calculatePlayerTotal(players[LogIndex]);

        printf("Set completed. Your Total Score: %d\n", players[LogIndex].PlayerTotal);

    } while (1);

   
    saveData();
}


void displayLeaderboard() {
    clrScreen();
    printf("===== Leaderboard =====\n");
    printf("Rank\tUsername\tAddition\tSubtraction\tMultiplication\tDivision\tTotal\n");
    printf("=======================================================================\n");

   
    Player *activePlayers[MAX_PLAYERS];
    int activePlayersCount = 0;

    
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].isPlayerActive) {
            activePlayers[activePlayersCount++] = &players[i];
        }
    }

   
    qsort(activePlayers, activePlayersCount, sizeof(Player *), comparePlayers);


    // Display leaderboard in sorted order

    for (int rank = 1; rank <= activePlayersCount; rank++) {
        Player *player = activePlayers[rank - 1];

        printf("%d\t%-20s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", rank, player->username, player->AddScore, player->SubtractScore, player->MultiScore, player->DivideScore, calculatePlayerTotal(*player));
    }

    if (activePlayersCount == 0) {
        printf("No active players to display.\n");
    }

    
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}


// funtion to remove account

void removeAccount() {
    clrScreen();
    printf("===== Remove Account =====\n");
    char username[MAX_NAME_LENGTH];

    printf("Enter username to remove: ");
    scanf(" %49[^\n]", username);

    int i;
    for (i = 0; i < numPlayers; i++) {
        if (strcmp(username, players[i].username) == 0 && players[i].isPlayerActive) {
            
            memset(&players[i], 0, sizeof(Player));
            numPlayers--;

            saveData();
            printf("Account '%s' has been removed.\n", username);
            if (LogIndex == i) {
                LogIndex = -1;
            }
            pauseForReading();
            return;
        }
    }
    printf("Account not found or already removed.\n");
    pauseForReading();
}


// save data to file

void saveData() {
    FILE *playersFile = fopen("Players.txt", "a"); // Use "a" for append mode
    if (playersFile == NULL) {
        printf("Error opening Players.txt for writing.\n");
        return;
    }

    // Write the data for the new player (or updated player) at the end of the file
    fprintf(playersFile, "%s %s %d %d %d %d %d\n", 
            players[numPlayers - 1].username, 
            players[numPlayers - 1].password, 
            players[numPlayers - 1].AddScore, 
            players[numPlayers - 1].SubtractScore, 
            players[numPlayers - 1].MultiScore, 
            players[numPlayers - 1].DivideScore, 
            players[numPlayers - 1].isPlayerActive);

    fclose(playersFile);
    printf("Data saved successfully.\n");
}



// upload the data from file to the program

void loadData() {
    FILE *playersFile = fopen("Players.txt", "r");
    if (playersFile == NULL) {
        printf("No existing player data found.\n");
        return;
    }

    numPlayers = 0;
    while (fscanf(playersFile, "%s %s %d %d %d %d %d", players[numPlayers].username, players[numPlayers].password, &players[numPlayers].AddScore, &players[numPlayers].SubtractScore, &players[numPlayers].MultiScore, &players[numPlayers].DivideScore, &players[numPlayers].isPlayerActive) == 7) {
        numPlayers++;
        if (numPlayers >= MAX_PLAYERS) {
            printf("Maximum player limit reached.\n");
            break;
        }
    }

    fclose(playersFile);
    printf("Data loaded successfully.\n");
}


// system("cls"); is unstable so i opted to use special ANSI escape sequence

void clrScreen() {
    printf("\033[2J\033[H");
}


// to give users enough time to read before the program continues

void pauseForReading() {
    sleep(1.5);
}


// sort the leaderboard

void LeadSort() {
    qsort(players, numPlayers, sizeof(Player), comparePlayers);
}