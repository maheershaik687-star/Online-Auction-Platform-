#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIDS 100
#define MAX_DAG 100

// ---------------- PLAYER STRUCT ----------------
struct Player {
    int id;
    char name[50];
    struct Player* next;
};

struct Player* playerHead = NULL;

// ---------------- BID STRUCT ----------------
struct Bid {
    int bidID;
    int amount;
    char bidder[50];
};

// ---------------- ITEM STRUCT ----------------
struct Item {
    int id;
    char name[50];

    struct Bid heap[MAX_BIDS]; // Max Heap for bids
    int size;

    int adj[MAX_DAG][MAX_DAG]; // DAG adjacency matrix
    int bidCount;

    struct Item* next;
};

struct Item* head = NULL;

// ---------------- PLAYER FUNCTIONS ----------------
void addPlayer(int id, char name[]) {
    struct Player* newPlayer = (struct Player*)malloc(sizeof(struct Player));
    newPlayer->id = id;
    strcpy(newPlayer->name, name);
    newPlayer->next = NULL;

    if (playerHead == NULL) {
        playerHead = newPlayer;
    } else {
        struct Player* temp = playerHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPlayer;
    }

    printf("Player added successfully!\n");
}

void displayPlayers() {
    struct Player* temp = playerHead;
    if (temp == NULL) {
        printf("No players available!\n");
        return;
    }

    while (temp != NULL) {
        printf("Player ID: %d | Name: %s\n", temp->id, temp->name);
        temp = temp->next;
    }
}

int isPlayerExists(char name[]) {
    struct Player* temp = playerHead;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// ---------------- HEAP FUNCTIONS ----------------
void swap(struct Bid* a, struct Bid* b) {
    struct Bid temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct Item* item, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (item->heap[parent].amount < item->heap[index].amount) {
            swap(&item->heap[parent], &item->heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void insertBid(struct Item* item, struct Bid bid) {
    if (item->size >= MAX_BIDS) {
        printf("Maximum bids reached!\n");
        return;
    }

    item->heap[item->size] = bid;
    heapifyUp(item, item->size);
    item->size++;
}

// ---------------- DAG FUNCTIONS ----------------
int dfsCycle(struct Item* item, int v, int visited[], int recStack[]) {
    visited[v] = 1;
    recStack[v] = 1;

    for (int i = 0; i < item->bidCount; i++) {
        if (item->adj[v][i]) {
            if (!visited[i] && dfsCycle(item, i, visited, recStack))
                return 1;
            else if (recStack[i])
                return 1;
        }
    }

    recStack[v] = 0;
    return 0;
}

int hasCycle(struct Item* item) {
    int visited[MAX_DAG] = {0};
    int recStack[MAX_DAG] = {0};

    for (int i = 0; i < item->bidCount; i++) {
        if (!visited[i]) {
            if (dfsCycle(item, i, visited, recStack))
                return 1;
        }
    }
    return 0;
}

void addBidDependency(struct Item* item, int from, int to) {
    item->adj[from][to] = 1;

    if (hasCycle(item)) {
        item->adj[from][to] = 0;
        printf("Dependency creates a cycle! Rejected.\n");
    } else {
        printf("Dependency added successfully.\n");
    }
}

void displayBidDAG(struct Item* item) {
    if (item->bidCount == 0) {
        printf("No bids available for DAG.\n");
        return;
    }

    printf("\nBid Dependency DAG (Adjacency Matrix):\n   ");
    for (int i = 0; i < item->bidCount; i++)
        printf("%d ", item->heap[i].bidID);
    printf("\n");

    for (int i = 0; i < item->bidCount; i++) {
        printf("%d ", item->heap[i].bidID);
        for (int j = 0; j < item->bidCount; j++) {
            printf("%d ", item->adj[i][j]);
        }
        printf("\n");
    }
}

// ---------------- ITEM FUNCTIONS ----------------
struct Item* findItem(int id) {
    struct Item* temp = head;
    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void addItem(int id, char name[]) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->size = 0;
    newItem->bidCount = 0;
    newItem->next = NULL;

    for (int i = 0; i < MAX_DAG; i++)
        for (int j = 0; j < MAX_DAG; j++)
            newItem->adj[i][j] = 0;

    if (head == NULL) {
        head = newItem;
    } else {
        struct Item* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newItem;
    }

    printf("Item added successfully!\n");
}

void displayItems() {
    struct Item* temp = head;

    if (temp == NULL) {
        printf("No items available!\n");
        return;
    }

    while (temp != NULL) {
        printf("\nItem ID: %d | Name: %s", temp->id, temp->name);

        if (temp->size > 0) {
            printf(" | Highest Bid: %d by %s",
                   temp->heap[0].amount,
                   temp->heap[0].bidder);
        } else {
            printf(" | No bids yet");
        }

        printf("\n");
        temp = temp->next;
    }
}

// ---------------- AUCTION FUNCTIONS ----------------
void placeBid(int itemId, char bidder[], int amount) {
    if (!isPlayerExists(bidder)) {
        printf("Player not registered!\n");
        return;
    }

    struct Item* item = findItem(itemId);
    if (item == NULL) {
        printf("Item not found!\n");
        return;
    }

    struct Bid bid;
    bid.bidID = item->bidCount + 1;
    bid.amount = amount;
    strcpy(bid.bidder, bidder);

    insertBid(item, bid);

    // Initialize DAG node
    for (int i = 0; i < MAX_DAG; i++) {
        item->adj[item->bidCount][i] = 0;
        item->adj[i][item->bidCount] = 0;
    }

    item->bidCount++;

    // Add dependency
    if (item->bidCount > 1) {
        int dep;
        printf("Enter Bid ID this bid depends on (0 for none): ");
        scanf("%d", &dep);

        if (dep > 0 && dep <= item->bidCount - 1) {
            addBidDependency(item, dep - 1, item->bidCount - 1);
        }
    }

    printf("Bid placed successfully! Bid ID: %d\n", bid.bidID);
}

void showHighestBid(int id) {
    struct Item* item = findItem(id);

    if (item == NULL) {
        printf("Item not found!\n");
        return;
    }

    if (item->size == 0) {
        printf("No bids available!\n");
        return;
    }

    printf("\nHighest Bid for %s:\n", item->name);
    printf("Amount: %d | Bidder: %s\n",
           item->heap[0].amount,
           item->heap[0].bidder);
}

// ---------------- FILE HANDLING ----------------
void saveToFile() {
    FILE* fp = fopen("auction.txt", "w");
    if (!fp) {
        printf("File error!\n");
        return;
    }

    struct Item* temp = head;
    while (temp != NULL) {
        fprintf(fp, "Item ID: %d Name: %s Highest Bid: %d\n",
                temp->id,
                temp->name,
                temp->size ? temp->heap[0].amount : 0);
        temp = temp->next;
    }

    fclose(fp);
    printf("Data saved to auction.txt\n");
}

// ---------------- DISPLAY ALL DETAILS ----------------
void displayAll() {
    struct Item* temp;

    printf("\n========== ALL AUCTION DETAILS ==========\n");

    printf("\n----- PLAYERS -----\n");
    displayPlayers();

    printf("\n----- ITEMS -----\n");
    displayItems();

    printf("\n----- HIGHEST BIDS -----\n");
    temp = head;
    if (temp == NULL) {
        printf("No items available!\n");
    } else {
        while (temp != NULL) {
            if (temp->size > 0) {
                printf("Item: %s | Highest Bid: %d by %s\n",
                       temp->name,
                       temp->heap[0].amount,
                       temp->heap[0].bidder);
            } else {
                printf("Item: %s | No bids yet\n", temp->name);
            }
            temp = temp->next;
        }
    }

    printf("\n----- BID DEPENDENCY DAG -----\n");
    temp = head;
    if (temp == NULL) {
        printf("No items available!\n");
    } else {
        while (temp != NULL) {
            printf("\nItem ID: %d | Name: %s\n",
                   temp->id, temp->name);
            displayBidDAG(temp);
            temp = temp->next;
        }
    }

    printf("\n==========================================\n");
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    int choice, id, amount, itemId;
    char name[50], bidder[50];

    while (1) {
        printf("\n===== ONLINE AUCTION SYSTEM =====\n");
        printf("1. Add Player\n");
        printf("2. Display Players\n");
        printf("3. Add Item\n");
        printf("4. Display Items\n");
        printf("5. Place Bid\n");
        printf("6. Show Highest Bid\n");
        printf("7. Save to File\n");
        printf("8. Display Bid Dependency DAG\n");
        printf("9. Display All Details\n");
        printf("10. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Player ID: ");
                scanf("%d", &id);
                printf("Enter Player Name: ");
                scanf("%s", name);
                addPlayer(id, name);
                break;

            case 2:
                displayPlayers();
                break;

            case 3:
                printf("Enter Item ID: ");
                scanf("%d", &id);
                printf("Enter Item Name: ");
                scanf("%s", name);
                addItem(id, name);
                break;

            case 4:
                displayItems();
                break;

            case 5:
                printf("Enter Item ID: ");
                scanf("%d", &itemId);
                printf("Enter Bidder Name: ");
                scanf("%s", bidder);
                printf("Enter Bid Amount: ");
                scanf("%d", &amount);
                placeBid(itemId, bidder, amount);
                break;

            case 6:
                printf("Enter Item ID: ");
                scanf("%d", &id);
                showHighestBid(id);
                break;

            case 7:
                saveToFile();
                break;

            case 8: {
                printf("Enter Item ID: ");
                scanf("%d", &id);
                struct Item* item = findItem(id);
                if (item)
                    displayBidDAG(item);
                else
                    printf("Item not found!\n");
                break;
            }

            case 9:
                displayAll();
                break;

            case 10:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}