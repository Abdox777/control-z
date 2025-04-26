#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>

#define MAX_CART_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_CATEGORIES 5
#define MAX_ITEMS_PER_CATEGORY 10
#define MAX_ART_LENGTH 1000
#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 30

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Item;

typedef struct {
    char name[MAX_NAME_LENGTH];
    const char* items[MAX_ITEMS_PER_CATEGORY];
    float prices[MAX_ITEMS_PER_CATEGORY];
    const char* infoFiles[MAX_ITEMS_PER_CATEGORY];
    const char* categoryArtFile;
    int itemCount;
} MenuCategory;

Item cart[MAX_CART_ITEMS];
int cartCount = 0;

MenuCategory categories[MAX_CATEGORIES];
int categoryCount = 0;

void setWindowSize() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) / 2 + 100, TRUE);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {CONSOLE_WIDTH, CONSOLE_HEIGHT};
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    ShowScrollBar(console, SB_BOTH, FALSE);
}

void clearScreen() {
    system("cls");
    system("color F0");
}

void centerPrint(const char* text) {
    int len = strlen(text);
    int padding = (CONSOLE_WIDTH - len) / 2;
    if (padding < 0) padding = 0;
    printf("%*s%s", padding, "", text);
}

void displayCenteredArt(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char line[256];
        printf("\n");
        while (fgets(line, sizeof(line), file)) {
            centerPrint(line);
        }
        printf("\n");
        fclose(file);
    }
}

void printCenteredBox(const char* text) {
    int len = strlen(text);
    int boxWidth = len + 4;
    int leftPadding = (CONSOLE_WIDTH - boxWidth) / 2;

    printf("\n%*s+", leftPadding, "");
    for (int i = 0; i < boxWidth - 2; i++) printf("-");
    printf("+\n");

    printf("%*s| %s |\n", leftPadding, "", text);

    printf("%*s+", leftPadding, "");
    for (int i = 0; i < boxWidth - 2; i++) printf("-");
    printf("+\n");
}

void checkout();

void addItemToCart(const char* name, float price, int quantity) {
    if (cartCount >= MAX_CART_ITEMS) {
        centerPrint("Cart is full! Cannot add more items.\n");
        return;
    }

    for (int i = 0; i < cartCount; i++) {
        if (strcmp(cart[i].name, name) == 0) {
            cart[i].quantity += quantity;
            centerPrint("Item quantity updated in cart!\n");
            Sleep(1000);
            return;
        }
    }

    strncpy(cart[cartCount].name, name, MAX_NAME_LENGTH - 1);
    cart[cartCount].price = price;
    cart[cartCount].quantity = quantity;
    cartCount++;

    centerPrint("Item added to cart!\n");
    Sleep(1000);
}

void removeItemFromCart(int index) {
    if (index < 0 || index >= cartCount) {
        centerPrint("Invalid item index!\n");
        return;
    }

    for (int i = index; i < cartCount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartCount--;

    centerPrint("Item removed from cart.\n");
    Sleep(1000);
}

void viewCart() {
    float total = 0;
    clearScreen();
    centerPrint("===== Your Shopping Cart =====\n\n");

    if (cartCount == 0) {
        centerPrint("Your cart is empty.\n");
    } else {
        for (int i = 0; i < cartCount; i++) {
            char buffer[200];
            float itemTotal = cart[i].price * cart[i].quantity;
            sprintf(buffer, "%2d. %-30s $%-6.2f x %-3d = $%-6.2f",
                   i + 1, cart[i].name, cart[i].price, cart[i].quantity, itemTotal);
            centerPrint(buffer);
            printf("\n");
            total += itemTotal;
        }

        centerPrint("----------------------------------------\n");
        char totalText[50];
        sprintf(totalText, "Total: $%.2f", total);
        centerPrint(totalText);
        printf("\n");

        centerPrint("[R] Remove item | [C] Checkout | [B] Back\n");
        centerPrint("Enter choice: ");

        char ch = tolower(getch());
        printf("%c\n", ch);

        if (ch == 'r') {
            int removeIndex;
            centerPrint("Enter item number to remove: ");
            scanf("%d", &removeIndex);
            getchar();
            removeItemFromCart(removeIndex - 1);
        } else if (ch == 'c') {
            checkout();
        }
    }

    centerPrint("Press any key to continue...");
    getch();
}

void checkout() {
    float total = 0;
    clearScreen();
    centerPrint("======= Receipt =======\n\n");

    for (int i = 0; i < cartCount; i++) {
        char buffer[200];
        float itemTotal = cart[i].price * cart[i].quantity;
        sprintf(buffer, "%2d. %-30s $%-6.2f x %-3d = $%-6.2f",
               i + 1, cart[i].name, cart[i].price, cart[i].quantity, itemTotal);
        centerPrint(buffer);
        printf("\n");
        total += itemTotal;
    }

    centerPrint("----------------------------------------\n");
    char totalText[50];
    sprintf(totalText, "Total: $%.2f", total);
    centerPrint(totalText);
    printf("\n");

    centerPrint("Thank you for your order!\n");
    centerPrint("Your food will be ready soon.\n");

    centerPrint("Press any key to exit...");
    getch();
    exit(0);
}

void showCategoryMenu(int categoryIndex) {
    if (categoryIndex < 0 || categoryIndex >= categoryCount) return;

    while (1) {
        clearScreen();

        if (categories[categoryIndex].categoryArtFile != NULL) {
            displayCenteredArt(categories[categoryIndex].categoryArtFile);
        }

        char title[100];
        sprintf(title, "===== %s Menu =====", categories[categoryIndex].name);
        centerPrint(title);
        printf("\n\n");

        for (int i = 0; i < categories[categoryIndex].itemCount; i++) {
            char itemText[100];
            sprintf(itemText, "%2d. %-30s $%-6.2f",
                  i + 1, categories[categoryIndex].items[i],
                  categories[categoryIndex].prices[i]);
            printCenteredBox(itemText);

            if (categories[categoryIndex].infoFiles[i] != NULL) {
                displayCenteredArt(categories[categoryIndex].infoFiles[i]);
            }
        }

        printCenteredBox("0. Back to Main Menu");
        printf("\n");

        centerPrint("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar();

        if (choice == 0) return;

        if (choice > 0 && choice <= categories[categoryIndex].itemCount) {
            centerPrint("Enter quantity: ");
            int qty;
            scanf("%d", &qty);
            getchar();

            if (qty > 0) {
                addItemToCart(categories[categoryIndex].items[choice - 1],
                             categories[categoryIndex].prices[choice - 1], qty);
            } else {
                centerPrint("Quantity must be positive!\n");
                Sleep(1000);
            }
        } else {
            centerPrint("Invalid choice!\n");
            Sleep(1000);
        }
    }
}

void initMenuCategories() {
    // Initialize Food category
    strcpy(categories[0].name, "Food");
    categories[0].items[0] = "Pizza";
    categories[0].prices[0] = 45.0;
    categories[0].infoFiles[0] = "food_pizza.txt";
    categories[0].categoryArtFile = "food_art.txt";

    categories[0].items[1] = "Chicken";
    categories[0].prices[1] = 50.0;
    categories[0].infoFiles[1] = "food_chickn.txt";

    categories[0].items[2] = "Beef";
    categories[0].prices[2] = 80.0;
    categories[0].infoFiles[2] = "food_beef.txt";

    categories[0].itemCount = 3;

    // Initialize Drinks category
    strcpy(categories[1].name, "Drinks");
    categories[1].items[0] = "Coke";
    categories[1].prices[0] = 10.0;
    categories[1].infoFiles[0] = "drinks_cola.txt";
    categories[1].categoryArtFile = "drinks_art.txt";

    categories[1].items[1] = "Pepsi";
    categories[1].prices[1] = 10.0;
    categories[1].infoFiles[1] = "drinks_pepsi.txt";

    categories[1].items[2] = "Water";
    categories[1].prices[2] = 5.0;
    categories[1].infoFiles[2] = "drinks_water.txt";

    categories[1].items[3] = "Orange Juice";
    categories[1].prices[3] = 12.0;
    categories[1].infoFiles[3] = "drinks_orange_juice.txt";

    categories[1].itemCount = 4;

    // Initialize Desserts category
    strcpy(categories[2].name, "Desserts");
    categories[2].items[0] = "Ice Cream";
    categories[2].prices[0] = 20.0;
    categories[2].infoFiles[0] = "desserts_ice_cream.txt";
    categories[2].categoryArtFile = "desserts_art.txt";

    categories[2].items[1] = "Brownie";
    categories[2].prices[1] = 25.0;
    categories[2].infoFiles[1] = "desserts_brownies.txt";

    categories[2].items[2] = "Cheesecake";
    categories[2].prices[2] = 30.0;
    categories[2].infoFiles[2] = "desserts_cheesecake.txt";

    categories[2].itemCount = 3;

    // Initialize Snacks category
    strcpy(categories[3].name, "Snacks");
    categories[3].items[0] = "Fries";
    categories[3].prices[0] = 15.0;
    categories[3].infoFiles[0] = "snacks_fries.txt";
    categories[3].categoryArtFile = "snacks_art.txt";

    categories[3].itemCount = 1;

    categoryCount = 4;
}

void showMainMenu() {
    clearScreen();

    displayCenteredArt("welcome.txt");
    printf("\n");

    for (int i = 0; i < categoryCount; i++) {
        char buffer[50];
        sprintf(buffer, "%d. %s", i + 1, categories[i].name);
        printCenteredBox(buffer);
    }

    printCenteredBox("5. View Cart");
    printCenteredBox("6. Checkout");
    printCenteredBox("7. Exit");
    printf("\n");

    centerPrint("Select an option: ");
}

int main() {
    setWindowSize();
    initMenuCategories();

    while (1) {
        showMainMenu();

        int choice;
        scanf("%d", &choice);
        getchar();

        if (choice >= 1 && choice <= categoryCount) {
            showCategoryMenu(choice - 1);
        } else if (choice == categoryCount + 1) {
            viewCart();
        } else if (choice == categoryCount + 2) {
            checkout();
        } else if (choice == categoryCount + 3) {
            exit(0);
        } else {
            centerPrint("Invalid choice!\n");
            Sleep(1000);
        }
    }

    return 0;
}
