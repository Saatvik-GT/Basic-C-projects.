#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char name[20];
    int health;
    int maxHealth;
    int energy;
    int maxEnergy;
    int attackPower;
    int defensePower;
    int specialMoves[3];
    char specialMoveNames[3][30];
} Character;


void printGokuArt(void);
void printVegetaArt(void);
void clearScreen(void);
void displayBar(int current, int max, char type);
void printStats(Character *c);
void regenerateEnergy(Character *c);
void attack(Character *attacker, Character *defender);
void specialMove(Character *attacker, Character *defender, int moveIndex);
void playerTurn(Character *player, Character *opponent);
void opponentTurn(Character *opponent, Character *player);

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayBar(int current, int max, char type) {
    printf("[");
    int barWidth = 20;
    int filled = (int)((float)current / max * barWidth);
    
    for (int i = 0; i < barWidth; i++) {
        if (i < filled) {
            printf("%c", type == 'H' ? '*' : '+');
        } else {
            printf(" ");
        }
    }
    printf("] %d/%d", current, max);
}

void printGokuArt() {
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣋⣤⣴⣤⡤⠀⠀⠀⠀⢀⠀⢻⡿⠿⠿⣛\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠔⢀⠋⣠⣶⣿⣷⡄⣼⡷⣼⣧⣀⣉⠈\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⠟⠤⠴⠶⣶⣶⡆⣰⣿⣾⣿⣿⣿⠋⣱⣿⢁⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣮⢅⣿⡟⠻⠍⠛⠵⠋⠉⠉⢺⢡⣿⣟⣉⣩\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠐⢶⠀⠐⠚⠀⠀⢋⡾⣭⣟⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠡⠄⠀⣠⠀⠈⢿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⠿⣶⣴⣿⢏⠀⠀⣿⣮⣭⣻⡿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⠏⢼⣿⣡⣀⡇⢠⣳⣿⣄⣤⣟⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣯⠘⣦⣀⣀⣉⣉⣉⣤⣾⠿⡻⠛⣽⣿⠿⠏\n");
}

void printVegetaArt() {
    printf("⣌⢻⣽⣿⣿⣻⣮⠷⣽⣷⢀⡏⢿⣟⣿⡀⢸⡿⢩⣿⣿⣣⣿⣽⣿⣿⠀⠸⣳\n");
    printf("⢻⢷⣿⣟⢝⡟⠁⢀⢬⣽⣿⣙⣏⣿⣿⠃⣿⢁⣿⡿⠋⠀⠈⠙⣿⣿⡏⣶⣶⡇\n");
    printf("⣷⣵⣽⣿⣷⠀⠀⠘⣛⠛⠊⠻⣞⣼⣿⢰⢇⡾⠋⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣶\n");
    printf("⢽⣿⣿⣿⡻⡆⢠⠀⠘⡄⠀⠀⠘⢷⣿⣼⠏⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣯⣿⠟\n");
    printf("⡈⠫⡻⠁⢝⢿⡾⠀⠀⠐⠀⠀⠀⠀⢻⠁⠀⠀⠀⠀⠀⠀⠠⢶⢋⠝⣿⡿⠟⠁\n");
    printf("⠙⢷⣶⣤⣄⠎⡕⠄⣀⠀⠀⠐⢤⡀⠀⠀⢀⠄⠀⠀⠀⣀⠠⢧⡃⣂⣿⣦⡿⠋\n");
    printf("⠀⠀⠙⣿⣖⠦⣖⡀⠀⢉⣒⡤⣀⠈⢠⠐⢁⡠⡴⢊⡁⠀⣌⢌⢆⡿⠛⠛⠂⠑\n");
    printf("⠀⠀⠒⢺⣿⣷⡆⠤⣀⠉⠀⠒⠋⠍⠈⠨⠭⠙⠒⠀⠀⡰⢄⢾⣿⠖⠒⠀⠀⠀\n");
    printf("⠀⠀⠀⠐⢿⣿⡟⡄⢁⠀⠀⠀⠀⢀⠋⠀⠀⠀⠀⠀⢀⠀⢬⣿⠿⠀⠐⠂⠀⠀\n");
    printf("⠀⠀⠍⢀⡘⢻⣿⣝⢄⡢⡀⠀⠀⢀⠉⡁⠀⠀⢀⣠⣮⣾⣿⠿⣁⣒⠒⠁⠀⠀\n");
}

void printStats(Character *c) {
    printf("\n%s's Status:\n", c->name);
    printf("Health: ");
    displayBar(c->health, c->maxHealth, 'H');
    printf("\nEnergy: ");
    displayBar(c->energy, c->maxEnergy, 'E');
    printf("\nAttack Power: %d\n", c->attackPower);
    printf("Defense Power: %d\n", c->defensePower);
}

void regenerateEnergy(Character *c) {
    c->energy += 15;
    if (c->energy > c->maxEnergy) {
        c->energy = c->maxEnergy;
    }
}

void attack(Character *attacker, Character *defender) {
    int damage = attacker->attackPower - defender->defensePower;
    damage += (rand() % 5) - 2;
    
    if (damage > 0) {
        defender->health -= damage;
        printf("\n* %s attacks %s for %d damage!\n", attacker->name, defender->name, damage);
    } else {
        printf("\n# %s's attack was blocked by %s's defense!\n", attacker->name, defender->name);
    }
    
    regenerateEnergy(attacker);
}

void specialMove(Character *attacker, Character *defender, int moveIndex) {
    int energyCost = 30 + (moveIndex * 10);
    
    if (attacker->energy >= energyCost) {
        int damage = attacker->specialMoves[moveIndex] - defender->defensePower;
        damage += (rand() % 8) - 3;
        attacker->energy -= energyCost;
        
        if (damage > 0) {
            defender->health -= damage;
            printf("\n+ %s uses %s on %s for %d damage!\n", 
                   attacker->name, 
                   attacker->specialMoveNames[moveIndex], 
                   defender->name, 
                   damage);
        } else {
            printf("\n# %s's %s was blocked!\n", 
                   attacker->name, 
                   attacker->specialMoveNames[moveIndex]);
        }
    } else {
        printf("\nX %s doesn't have enough energy for %s!\n", 
               attacker->name, 
               attacker->specialMoveNames[moveIndex]);
    }
}

void playerTurn(Character *player, Character *opponent) {
    int choice;
    printf("\nChoose an action:\n");
    printf("1. Attack\n");
    printf("2. %s (30 Energy)\n", player->specialMoveNames[0]);
    printf("3. %s (40 Energy)\n", player->specialMoveNames[1]);
    printf("4. %s (50 Energy)\n", player->specialMoveNames[2]);
    printf("5. Defend\n");
    printf("Enter your choice (1-5): ");
    
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            attack(player, opponent);
            break;
        case 2:
        case 3:
        case 4:
            specialMove(player, opponent, choice - 2);
            break;
        case 5:
            printf("\n# %s takes a defensive stance!\n", player->name);
            player->defensePower += 8;
            regenerateEnergy(player);
            break;
        default:
            printf("Invalid choice, turn skipped.\n");
            break;
    }
}

void opponentTurn(Character *opponent, Character *player) {
    int action;
    
    if (opponent->health < opponent->maxHealth / 3) {
        action = (rand() % 100 < 70) ? rand() % 3 + 2 : 1;
    } else if (opponent->energy > 80) {
        action = rand() % 3 + 2;
    } else {
        action = rand() % 5 + 1;
    }
    
    switch (action) {
        case 1:
            attack(opponent, player);
            break;
        case 2:
        case 3:
        case 4:
            specialMove(opponent, player, action - 2);
            break;
        case 5:
            printf("\n# %s takes a defensive stance!\n", opponent->name);
            opponent->defensePower += 8;
            regenerateEnergy(opponent);
            break;
    }
}

int main() {
    srand(time(NULL));
    
    Character goku = {
        "Goku",
        100, 100,
        100, 100,
        20, 10,
        {25, 35, 45},
        {"Kamehameha", "Spirit Bomb", "Ultra Instinct"}
    };
    
    Character vegeta = {
        "Vegeta",
        100, 100,
        100, 100,
        18, 12,
        {28, 38, 42},
        {"Galick Gun", "Final Flash", "Final Explosion"}
    };
    
    int turn = 0;
    
    printf("Dragon Ball Z Battle Simulator!\n");
    printf("Goku vs Vegeta\n");
    sleep(2);
    
    while (goku.health > 0 && vegeta.health > 0) {
        clearScreen();
        printf("\nRound %d\n", turn + 1);
        printf("----------------------------------------\n");
        
        if (turn % 2 == 0) {
            printGokuArt();
            printStats(&goku);
            printStats(&vegeta);
            printf("\nYour turn (Goku)!\n");
            playerTurn(&goku, &vegeta);
        } else {
            printVegetaArt();
            printStats(&vegeta);
            printStats(&goku);
            printf("\nVegeta's turn!\n");
            opponentTurn(&vegeta, &goku);
        }
        
        goku.defensePower = 10;
        vegeta.defensePower = 12;
        
        turn++;
        sleep(2);
    }
    
    clearScreen();
    printf("\n=== Battle Result ===\n");
    printf("----------------------------------------\n");
    if (goku.health <= 0) {
        printVegetaArt();
        printf("\nVegeta wins! The Prince of All Saiyans triumphs!\n");
    } else {
        printGokuArt();
        printf("\nGoku wins! Earth's greatest hero prevails!\n");
    }
    
    return 0;
}