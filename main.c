#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define CONSOLE_WIDTH 168
#define MAX_NAME_LENGTH 50
#define MAX_MENU_ITEMS 50
#define MAX_STAFF 10
#define MAX_ABSENT_DAY 25




typedef struct
{
    char name[MAX_NAME_LENGTH];
    int price;
    int category; //1 food 2 drinks 3 desserts 4 snacks
    char design[100];
    int color ;
    int quantity;
} menuitem;

typedef struct
{
    char name[50];
    int absentdays;
    float salary;
} Staff;

typedef struct
{
    char username[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
} user;


user usersinfo[200];
int maxusers =0;
int userindex ;
char *adminsemails[3] = {"BOSS@gmail.com\n","Boss@gmail.com\n","boss\n"};
char *staffemails[4]= {"Nour\n","Abdulrahman\n","Majed\n","Azzam\n"};

menuitem menu[MAX_MENU_ITEMS];
int menucount =0;

menuitem cart[MAX_MENU_ITEMS];
int cartcount = 0;
int total =0;

Staff staff[MAX_STAFF] =
{
    {"Abdulrahman", 10, 3000},
    {"Azzam", 24, 200}, {"Majed", 5, 4000}, {"Nour", 0, 5000}
};
int staffCount = 4;
int totalSales = 0;
int darkmode = 1;


void clearscreen();

void readd_emails();

void readd_usernames();

void readd_passwords();

void readd_menu_name();

void readd_menu_price();

void readd_menu_category();

void readd_menu_color();

void readd_menu_design();

void clearfile(char filename[MAX_NAME_LENGTH]);

void add_to_users (char info[MAX_NAME_LENGTH], char filename[MAX_NAME_LENGTH]);

void scan_emails();

void scan_menu_names();

void scan_menu_color();

void scan_menu_category();

void scan_menu_price();

void scan_menu_design();

void scan_usernames();

void scan_passwords();

void scan_all();

void centerprint(char text[],int color);

void centerbutton(char text[],int color);

void leftprint(char text[], int color);

void design(char filename[],int color);

void leftdesign(char filename[],int color);

int wrongans(int *choise);

void pre_screen();

void login_screen();

void register_screen();

void firstscreen();

void screens(int choise);

void cartscreen();

void checkoutscreen();

void settings();

void mode();

void Boss_screen();

void menu_edit();

void add_item();

void edit_item();

void remove_item();

void staff_info();

void sales();

void order_email();

void calctotalsales();

void recalactotslsales();

void staff_screen();

void print_orders();

void account();

void change_username();

void change_email();

void change_password();

void delete_user();

void view_userorders();

void color_mode();



void account()
{
    while(1)
    {
        clearscreen();
        int choise;
        design("home_settings.txt",0);
        leftdesign("account.txt", 1);
        centerbutton("1.change your username", 0);
        centerbutton("2.change your password", 0);
        centerbutton("3.change your email", 0);
        centerbutton("4.see last orders", 2);
        design("trash&arrow1.txt", 4);
        centerprint("select:", 0);

        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            change_username();
        case 2 :
            change_password();
        case 3 :
            change_email();
        case 4 :
            view_userorders();
        case 99 :
            delete_user();
        case 0 :
            settings();
        default :
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
        }

    }
}

void add_item()
{
    while(1)
    {
        clearscreen();
        design("layalina.txt",0);
        leftdesign("boss.txt",0);
        char name[MAX_NAME_LENGTH];
        char design1[MAX_NAME_LENGTH];
        int category;
        int price;
        int color;
        int choise;
        int i;
        centerbutton("Menu",2);
        for(i =0; i<menucount; i++)
        {
            char buffer[50];
            sprintf(buffer,"%d. %s            -%d$-",i+1,menu[i].name,menu[i].price);
            centerbutton(buffer,menu[i].color);
        }
        centerbutton("1. Add item",2);
        design("back99.txt", 4);
        centerprint("Select an option : ",0);
        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            centerprint("Set item name : ",0);
            fgets(name,sizeof(name),stdin);
            if(strcmp(name,"99\n")==0) menu_edit();
            name[strcspn(name,"\n")]=0;
            centerprint("Set item price : ",0);
            if(wrongans(&price) ==1)continue;
            if(price == 99) menu_edit();
            if(price <0)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            centerbutton("1.food 2.drinks 3.desserts 4.snacks",0);
            centerprint("Set Item category : ",0);
            if(wrongans(&category) ==1)continue;
            if(category == 99) menu_edit();
            if(category<1||category>4)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            centerbutton("0. Black",0);
            centerbutton("1. Blue",1);
            centerbutton("2. Green",2);
            centerbutton("3. Aqua",3);
            centerbutton("4. Red",4);
            centerbutton("5. Purple",5);
            centerbutton("6. Yellow",6);
            centerprint("Set item color : ",0);
            if(wrongans(&color) ==1)continue;
            if(color == 99) menu_edit();
            if(color >6 || color < 0)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            centerprint("Set item design file : ",0);
            fgets(design1,sizeof(design1),stdin);
            if(strcmp(name,"99\n")==0) menu_edit();
            centerprint("Adding item to menu...",2);
            printf("\n");
            sprintf(menu[menucount].name,"%s",name);
            sprintf(menu[menucount].design,"%s",design1);
            menu[menucount].category = category;
            menu[menucount].color = color;
            menu[menucount].price = price;
            ++menucount;
            Sleep(2000);
            readd_menu_category();
            readd_menu_color();
            readd_menu_design();
            readd_menu_name();
            readd_menu_price();
            centerbutton("Item added successfully",2);
            Sleep(2000);
            continue;
        case 99 :
            menu_edit();
        default :
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
        }

    }
}

void add_to_users (char info[MAX_NAME_LENGTH], char filename[MAX_NAME_LENGTH])
{
    FILE *pf = fopen(filename,"a");
    fprintf(pf,info);
    fclose(pf);
}

void Boss_screen()
{
    while(1)
    {
        int choise;
        char buffer[100];
        clearscreen();
        design("layalina.txt",0);
        leftdesign("boss.txt",0);
        design("menu&staff.txt", 6);
        design("sales.txt", 2);
        design("back0.txt", 4);
        centerprint("Select an option : ", 0);
        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            menu_edit();
        case 2 :
            staff_info();
        case 3 :
            sales();
        case 0 :
            mode();
        default :
        {
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
            continue;
        }
        }

    }
}

void clearscreen()
{
    if(darkmode == 0)
    {
        system("cls");
        system("color F0");
    }
    else if(darkmode==1)
    {
        system("cls");
        system("color 0F");
    }
}

void centerbutton(char text[],int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(darkmode == 0)
    {
        SetConsoleTextAttribute(hConsole, 240+color);
    }
    else if (darkmode ==1)
    {
        if(color ==0) color = 15;
        SetConsoleTextAttribute(hConsole,color);
    }
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/2;
    int starlen = length+3;
    printf("%*s+",spaces,"");
    for(int i = 0; i<=starlen; i++)
    {
        printf("=");
    }
    printf("+\n");
    printf("%*s|  %s  |",spaces,"",text);
    printf("\n%*s+",spaces,"");
    for(int i = 0; i<=starlen; i++)
    {
        printf("=");
    }
    printf("+\n\n");
}

void centerprint(char text[],int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(darkmode == 0)
    {
        SetConsoleTextAttribute(hConsole, 240+color);
    }
    else if (darkmode ==1)
    {
        if(color ==0) color = 15;
        SetConsoleTextAttribute(hConsole,color);
    }
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/2;
    printf("%*s%s",spaces,"",text);
}

void cartscreen()
{
    while(1)
    {
        total =0;
        clearscreen();
        design("home_cart.txt", 9);
        leftdesign("cart.txt",2);
        printf("\n\n");
        char buffer[100];
        if(cartcount == 0)
        {
            centerprint("Your Cart Is Empty",4);
            printf("\n");
            design("back0.txt", 4);
            int v;
            centerprint("Select an option : ",0);
            if(wrongans(&v)) continue;
            if(v == 0) firstscreen();
            else {

                    centerprint("    Invalid number!", 4);
                Sleep(700);
                continue;
            }
        }
        else
        {
            centerbutton("your order", 0);
            for(int i =0; i<cartcount; i++)
            {
                sprintf(buffer," (%d) %d x %s = %d$\n",i+1,cart[i].quantity,cart[i].name,cart[i].price*cart[i].quantity);
                centerprint(buffer,0);
                total += cart[i].price*cart[i].quantity;
            }
            char totalmoney[100];
            sprintf(totalmoney,"Total : %d$",total);
            centerprint(totalmoney,0);
        }
        printf("\n");
        design("checkout1.txt", 2);
        design("trash&arrow.txt", 4);
        centerprint("Select an option : ",0);
        int choise;
        if(wrongans(&choise) ==1)continue;
        if(choise ==1) checkoutscreen();
        if(choise == 0)
        {
            firstscreen();
        }
        else if(choise == 99)
        {
            centerprint("Select Item Number :",4);
            int remove;
            if(wrongans(&remove) ==1)continue;
            if (remove <= 0 || remove > cartcount)
            {
                centerprint("    Invalid item number!\n", 4);
                Sleep(700);
                continue;
            }
            remove--;
            total -= cart[remove].price*cart[remove].quantity;
            for (int i = remove; i < cartcount - 1; i++)
            {
                cart[i] = cart[i + 1];
            }
            cartcount--;
            centerprint("    Item removed successfully.\n", 2);
            Sleep(700);
            continue;

        }
        else
        {
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
        }
    }
}

void calctotalsales()
{
    totalSales = 0;
    char getsale[MAX_NAME_LENGTH];
    FILE *pf = fopen("totalsales.txt","r");
    while(fgets(getsale,sizeof(getsale),pf) != NULL)
    {
        totalSales += atoi(getsale);
    }
    fclose(pf);
}

void clearfile(char filename[MAX_NAME_LENGTH])
{
    FILE *pf = fopen(filename,"w");
    fprintf(pf,"");
    fclose(pf);

}

void checkoutscreen()
{
    while(1)
    {
        total=0;
        char address[220];
        int ensure;
        int back_now;
        clearscreen();
        design("home_cart.txt", 1);
        leftdesign("checkout.txt", 2);
        char buffer[100];
        if(cartcount == 0)
        {
            centerprint("Nothing ):",4);
            int v;
            if(wrongans(&v)==1)continue;
            if(v == 0) firstscreen();
        }
        else
        {
            for(int i =0; i<cartcount; i++)
            {
                sprintf(buffer," (%d) %d x %s = %d$\n",i+1,cart[i].quantity,cart[i].name,cart[i].price*cart[i].quantity);
                centerprint(buffer,0);
                total += cart[i].price*cart[i].quantity;
            }
            char totalmoney[100];
            sprintf(totalmoney,"Total : %d$",total);
            centerprint(totalmoney,0);
            printf("\n");
            centerprint("enter your address: ", 0);
            fgets(address,sizeof(address),stdin);
            address[strcspn(address,"\n")] = 0;
            centerprint("enter 1 to ensure the process:", 0);
            if(wrongans(&ensure) ==1) continue;
            if(ensure==1)
            {
                char order[500];
                char emai[MAX_NAME_LENGTH];
                char tota[MAX_NAME_LENGTH];
                char totalsales[MAX_NAME_LENGTH];
                add_to_users("================New Order================\n","orders.txt");
                order_email();
                order_email();
                sprintf(emai,"Username : %s\n",usersinfo[userindex].username);
                add_to_users(emai,"orders.txt");
                order_email();
                for(int i =0; i<cartcount; i++)
                {
                    order_email();
                    sprintf(order," (%d) %d x %s = %d$\n",
                            i+1,
                            cart[i].quantity,cart[i].name,
                            cart[i].price*cart[i].quantity);
                    add_to_users(order,"orders.txt");
                }
                sprintf(tota,"Total : %d$\n\n",total);
                add_to_users(tota,"orders.txt");
                order_email();
                sprintf(totalsales,"%d\n",total);
                add_to_users(totalsales,"totalsales.txt");
                add_to_users(usersinfo[userindex].email,"totalsales_email.txt");
                order_email();
                centerprint("thank you for your order ", 5);
                printf("\n");
                centerprint("the order will arrives in half an hour",0);
                printf("\n");
                design("thank_you.txt", 4);
                design("pressanykey.txt", 4);

                char v[100];
                fgets(v,sizeof(v),stdin);
                calctotalsales();
                cartcount = 0;
                firstscreen();
            }
            else
            {
                centerprint("No Problem Take Your Time (:",2);
                Sleep(1000);
                firstscreen();
            }
        }
    }
}

void change_username()
{
    while(1)
    {
        clearscreen();
        design("home_settings.txt",0);
        leftdesign("account.txt", 1);
        char confirmpass[MAX_NAME_LENGTH];
        char newusername[MAX_NAME_LENGTH];
        char buffer[MAX_NAME_LENGTH];
        usersinfo[userindex].username[strcspn(usersinfo[userindex].username,"\n")]=0;
        sprintf(buffer,"Current username : %s",usersinfo[userindex].username);
        centerbutton(buffer,4);
        usersinfo[userindex].username[strcspn(usersinfo[userindex].username,"\0")]='\n';
        design("arrow00.txt",4);
        centerprint("Enter your new username :",0);
        fgets(newusername,sizeof(newusername),stdin);
        if(strcmp(newusername,"00\n")==0)account();
        if(strcmp(newusername,"\n")==0)
        {
            centerprint("Invalid username !!",4);
            Sleep(700);
            continue;
        }
        if(strcmp(newusername,usersinfo[userindex].username)==0)
        {
            centerprint("Can't use the same username !",4);
            Sleep(700);
            continue;
        }
        centerprint("Please confirm your password :",0);
        fgets(confirmpass,sizeof(confirmpass),stdin);
        if(strcmp(confirmpass,"00\n")==0)settings();
        if(strcmp(confirmpass,usersinfo[userindex].password)==0)
        {
            sprintf(usersinfo[userindex].username,"%s",newusername);
            readd_usernames();
            centerbutton("Username updated successfully",2);
            Sleep(700);
            firstscreen();
        }
        else
        {
            centerprint("Wrong paswword !",4);
            Sleep(700);
            continue;
        }


    }
}

void change_email()
{
    while(1)
    {
        clearscreen();
        design("home_settings.txt",0);
        leftdesign("account.txt", 1);
        char confirmpass[MAX_NAME_LENGTH];
        char newemail[MAX_NAME_LENGTH];
        char buffer[MAX_NAME_LENGTH];
        int isregistered =0;
        usersinfo[userindex].email[strcspn(usersinfo[userindex].email,"\n")]=0;
        sprintf(buffer,"Current email : %s",usersinfo[userindex].email);
        centerbutton(buffer,4);
        usersinfo[userindex].email[strcspn(usersinfo[userindex].email,"\0")]='\n';
        design("arrow00.txt",4);
        centerprint("Enter your new email :",0);
        fgets(newemail,sizeof(newemail),stdin);
        if(strcmp(newemail,"00\n")==0)account();
        if(strcmp(newemail,"\n")==0)
        {
            centerprint("Invalid email !!",4);
            Sleep(700);
            continue;
        }
        if(strcmp(newemail,usersinfo[userindex].email)==0)
        {
            centerprint("Can't use the same email !",4);
            Sleep(700);
            continue;
        }
        for(int i=0; i<maxusers; i++)
        {
            if(strcmp(newemail,usersinfo[i].email)==0)
            {
                centerprint("Email is already registered !",4);
                Sleep(700);
                isregistered =1;
                break;
            }
        }
        if(isregistered)continue;
        centerprint("Please confirm your password :",0);
        fgets(confirmpass,sizeof(confirmpass),stdin);
        if(strcmp(confirmpass,"00\n")==0)settings();
        if(strcmp(confirmpass,usersinfo[userindex].password)==0)
        {
            sprintf(usersinfo[userindex].email,"%s",newemail);
            readd_emails();
            centerbutton("Email updated successfully",2);
            Sleep(700);
            firstscreen();
        }
        else
        {
            centerprint("Wrong paswword !",4);
            Sleep(700);
            continue;
        }


    }
}

void change_password()
{
    while(1)
    {
        clearscreen();
        design("home_settings.txt",0);
        leftdesign("account.txt", 1);
        char confirmpass[MAX_NAME_LENGTH];
        char newpass[MAX_NAME_LENGTH];
        design("arrow00.txt",4);
        centerprint("Enter your new password :",0);
        fgets(newpass,sizeof(newpass),stdin);
        if(strcmp(newpass,"00\n")==0)settings();
        if(strcmp(newpass,"\n")==0)
        {
            centerprint("Invalid password !!",4);
            Sleep(700);
            continue;
        }
        if(strcmp(newpass,usersinfo[userindex].password)==0)
        {
            centerprint("Can't use the same password !",4);
            Sleep(700);
            continue;
        }
        centerprint("Please confirm your password :",0);
        fgets(confirmpass,sizeof(confirmpass),stdin);
        if(strcmp(confirmpass,"00\n")==0)account();
        if(strcmp(confirmpass,usersinfo[userindex].password)==0)
        {
            sprintf(usersinfo[userindex].password,"%s",newpass);
            readd_passwords();
            centerbutton("Password updated successfully",2);
            Sleep(700);
            firstscreen();
        }
        else
        {
            centerprint("Wrong paswword !",4);
            Sleep(700);
            continue;
        }


    }
}

void color_mode()
{
    while(1)
    {
        clearscreen();
        design("home_settings.txt", 0);
        leftdesign("color_mode0.txt", 1);
        if(darkmode==1)
        {
            design("color_mode2.txt", 0);
            centerbutton("1. Light mode ", 0);
            design("back0.txt", 4);
            centerprint("Select an option : ", 0);
            int v;
            if(wrongans(&v) ==1) continue;
            if(v == 1)
            {
                darkmode =0;
                continue;
            }
            else if(v == 0)settings();
            else
            {
                centerprint("    Invalid Choice !\n", 4);
                Sleep(700);
                continue;
            }
        }
        else if(darkmode == 0)
        {
            design("color_mode1.txt", 0);
            centerbutton("1. Dark mode ", 0);
            design("back0.txt", 4);
            centerprint("Select an option : ", 0);
            int g;
            if(wrongans(&g) ==1) continue; ;
            if(g == 1)
            {
                darkmode=1;
                continue;
            }
            else if(g == 0)settings();
            else
            {
                centerprint("    Invalid Choice !\n", 4);
                Sleep(700);
                continue;
            }
        }

    }

}

void delete_user()
{
    clearscreen();
    design("home_settings.txt",0);
    leftdesign("account.txt", 1);
    char reason[MAX_NAME_LENGTH];
    char confirm[MAX_NAME_LENGTH];
    centerbutton("00.Back",2);
    centerprint("Please tell us why you want to delete your account ): ",4);
    fgets(reason,sizeof(reason),stdin);
    if(strcmp(reason,"00\n")==0)settings();
    centerprint("Press 1 to confirm deletation :",4);
    fgets(confirm,sizeof(confirm),stdin);
    if(strcmp(confirm,"00\n")==0)settings();
    if(strcmp(confirm,"1\n")==0)
    {
        for(int i=userindex; i<maxusers; i++)
        {
            usersinfo[i]=usersinfo[i+1];
        }
        readd_emails();
        readd_passwords();
        readd_usernames();
        centerbutton("GOOD BYE",4);
        exit(0);
    }
    else
    {
        centerprint("Enjoy (:",2);
        Sleep(700);
        firstscreen();
    }


}

void design(char filename[],int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(darkmode == 0)
    {
        SetConsoleTextAttribute(hConsole, 240+color);
    }
    else if (darkmode ==1)
    {
        if(color ==0) color = 15;
        SetConsoleTextAttribute(hConsole,color);
    }
    FILE *pf = fopen(filename,"r");
    char buffer[255];
    while(fgets(buffer,255,pf) != NULL)
    {
        centerprint(buffer,color);
    }
    printf("\n");
}

void edit_item()
{
    while(1)
    {
        clearscreen();
        design("layalina.txt",0);
        leftdesign("boss.txt",0);
        char name[MAX_NAME_LENGTH];
        char design1[MAX_NAME_LENGTH];
        int category;
        int price;
        int color;
        int choise;
        int i;
        centerbutton("Menu",2);
        for(i =0; i<menucount; i++)
        {
            char buffer[50];
            sprintf(buffer,"%d. %s            -%d$-",i+1,menu[i].name,menu[i].price);
            centerbutton(buffer,menu[i].color);
        }
        centerbutton("1. Edit item",2);
        design("back99.txt",4);
        centerprint("Select an option : ",0);
        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            int choise1;
            centerprint("Select item number : ",0);
            if(wrongans(&choise1) ==1)continue;
            if(choise1 == 99) menu_edit();
            if(choise1>menucount || choise1 <1)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            choise1 --;
            centerprint("Set item name : ",0);
            fgets(name,sizeof(name),stdin);
            if(strcmp(name,"99\n")==0) menu_edit();
            name[strcspn(name,"\n")]=0;
            centerprint("Set item price : ",0);
            if(wrongans(&price) ==1)continue;
            if(price == 99) menu_edit();
            if(price <0)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            centerbutton("1.food 2.drinks 3.desserts 4.snacks",0);
            centerprint("Set Item category : ",0);
            if(wrongans(&category) ==1)continue;
            if(category == 99) menu_edit();
            if(category<1||category>4)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            if(darkmode==0)
            {
                centerbutton("0. Black",0);
            }
            else if (darkmode == 1)
            {
                centerbutton("0. white",0);
            }
            centerbutton("1. Blue",1);
            centerbutton("2. Green",2);
            centerbutton("3. Aqua",3);
            centerbutton("4. Red",4);
            centerbutton("5. Purple",5);
            centerbutton("6. Yellow",6);
            centerprint("Set item color : ",0);
            if(wrongans(&color) ==1)continue;
            if(color == 99) menu_edit();
            if(color >6 || color < 0)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            centerprint("Set item design file : ",0);
            fgets(design1,sizeof(design1),stdin);
            if(strcmp(name,"99\n")==0) menu_edit();
            design1[strcspn(design1,"\n")]=0;
            centerprint("Changing item details...",2);
            printf("\n");
            sprintf(menu[choise1].name,"%s",name);
            sprintf(menu[choise1].design,"%s",design1);
            menu[choise1].category = category;
            menu[choise1].color = color;
            menu[choise1].price = price;
            Sleep(2000);
            readd_menu_category();
            readd_menu_color();
            readd_menu_design();
            readd_menu_name();
            readd_menu_price();
            centerbutton("Item edited successfully",2);
            Sleep(2000);
            continue;
        case 99 :
            menu_edit();
        default :
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
        }

    }
}

void firstscreen()
{
    int choise;

    while (1)
    {
        clearscreen();
        design("home_home.txt", 9);
        design("food&drinks.txt", 6);
        design("desserts&snaks.txt", 5);
        design("cart&settings.txt", 2);
        design("arrow.txt", 4);
        centerprint("Select an option : ", 0);
        if(wrongans(&choise) ==1)continue;


        switch(choise)
        {
        case 1:
            screens(choise);
        case 2:
            screens(choise);
        case 3:
            screens(choise);
        case 4:
            screens(choise);
        case 5:
            cartscreen();
        case 6:
            settings();
        case 0:
            exit(0);
        default:
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
        }
    }
}

void leftprint(char text[], int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(darkmode == 0)
    {
        SetConsoleTextAttribute(hConsole, 240+color);
    }
    else if (darkmode ==1)
    {
        if(color ==0) color = 15;
        SetConsoleTextAttribute(hConsole,color);
    }
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/20;
    printf("%*s%s",spaces,"",text);
}

void leftdesign(char filename[],int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(darkmode == 0)
    {
        SetConsoleTextAttribute(hConsole, 240+color);
    }
    else if (darkmode ==1)
    {
        if(color ==0) color = 15;
        SetConsoleTextAttribute(hConsole,color);
    }
    FILE *pf = fopen(filename,"r");
    char buffer[255];
    while(fgets(buffer,255,pf) != NULL)
    {
        leftprint(buffer,color);
    }
    printf("\n");
}

void login_screen()
{
    while(1)
    {
        char email[MAX_NAME_LENGTH];
        char targetemail[MAX_NAME_LENGTH];
        char password[MAX_NAME_LENGTH];
        clearscreen();
        leftdesign("layalina.txt", 0);
        design("login.txt", 2);
        printf("\n");
        design("arrow00.txt", 4);
        centerprint("Enter Your Email :",0);
        fgets(email,sizeof(email),stdin);
        if(strcmp(email,"00\n")==0)pre_screen();
        int emailfound =0;
        for(int i=0; i<maxusers; i++)
        {
            if(strcmp(email,usersinfo[i].email)==0)
            {
                emailfound =1;
                userindex =i;
                break;
            }
        }
        if(!emailfound)
        {
            centerprint("INVALID EMAIL !!",4);
            Sleep(700);
            continue;
        }
        centerprint("Enter Your Password :",0);
        fgets(password,sizeof(password),stdin);
        if(strcmp(password,"00\n")==0)pre_screen();
        if(strcmp(password,usersinfo[userindex].password)==0)
        {
            centerprint("Wlcome ",2);
            printf("\n");
            centerprint(usersinfo[userindex].username,2);
            Sleep(700);
            firstscreen();
        }
        else
        {
            centerprint("WRONG PASSWORD !!",4);
            Sleep(700);
            continue;
        }
    }
}

void mode()
{
    while(1)
    {
        int mode_choise;
        clearscreen();
        design("home_settings.txt", 0);
        leftdesign("mode.txt", 1);
        printf("\n");
        design("boss&staff.txt", 0);
        printf("\n");
        design("back0.txt", 4);
        centerprint("Select mode Number :",0);
        if(wrongans(&mode_choise) ==1) continue;
        if(mode_choise==99)delete_user();
        if(mode_choise == 1)
        {
            if((strcmp(usersinfo[userindex].email,adminsemails[0])==0)||(strcmp(usersinfo[userindex].email,adminsemails[1])==0)||(strcmp(usersinfo[userindex].email,adminsemails[2])==0))
            {
                Boss_screen();
            }
            else
            {
                centerprint("You Are Not A Boss !!",4);
                Sleep(3000);
                continue;
            }
        }
        else if(mode_choise == 2)
        {
            if((strcmp(usersinfo[userindex].email,adminsemails[0])==0)
                    ||(strcmp(usersinfo[userindex].email,adminsemails[1])==0)
                    ||(strcmp(usersinfo[userindex].email,adminsemails[2])==0)
                    ||(strcmp(usersinfo[userindex].email,staffemails[0])==0)
                    ||(strcmp(usersinfo[userindex].email,staffemails[1])==0)
                    ||(strcmp(usersinfo[userindex].email,staffemails[2])==0)
                    ||(strcmp(usersinfo[userindex].email,staffemails[3])==0))
            {
                staff_screen();
            }
            else
            {
                centerprint("you are not working here!!!\n", 4);
                Sleep(3000);
                continue;
            }

        }
        else if(mode_choise == 0)
        {
            settings();
        }
        else
        {
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
            continue;
        }
    }
}

void menu_edit()
{
    while(1)
    {
        int choise;
        clearscreen();
        design("layalina.txt", 0);
        leftdesign("boss.txt", 0);
        centerbutton("1. Add items",2);
        centerbutton("2. Edit current items",1);
        centerbutton("3. Remove items",4);
        design("back0.txt", 4);
        centerprint("Select an option : ",0);
        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            add_item();
        case 2 :
            edit_item();
        case 3 :
            remove_item();
        case 0 :
            Boss_screen();
        default :
            centerprint("    Invalid Choice !\n", 4);
        }

    }
}

void order_email()
{
    FILE *pf = fopen("order_email.txt","a");
    fprintf(pf,usersinfo[userindex].email);
    fclose(pf);
}

void print_orders()
{
    char line[MAX_NAME_LENGTH];
    FILE *pf = fopen("orders.txt", "r");
    while(fgets(line,sizeof(line),pf) !=NULL)
    {
        centerprint(line,0);
    }
    fclose(pf);
}

void pre_screen()
{
    while(1)
    {
        clearscreen();
        design("welcome1.txt", 1);
        design("login&signup.txt", 0);
        design("arrow.txt", 4);
        centerprint("Select an option :",0);
        int choise;
        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            login_screen();
        case 2 :
            register_screen();
        case 0 :
            exit(0);
        default:
        {
            centerprint("INVALID CHOISE !!",4);
            Sleep(700);
        }
        }
    }
}

void readd_emails()
{
    clearfile("emails.txt");
    FILE *pf = fopen("emails.txt","a");
    for(int i=0; i<maxusers; i++)
    {
        fprintf(pf,usersinfo[i].email);
    }
    fclose(pf);
}

void readd_usernames()
{
    clearfile("usernames.txt");
    FILE *pf = fopen("usernames.txt","a");
    for(int i=0; i<maxusers; i++)
    {
        fprintf(pf,usersinfo[i].username);
    }
    fclose(pf);
}

void readd_passwords()
{
    clearfile("passwords.txt");
    FILE *pf = fopen("passwords.txt","a");
    for(int i=0; i<maxusers; i++)
    {
        fprintf(pf,usersinfo[i].password);
    }
    fclose(pf);
}

void readd_menu_name()
{
    clearfile("menu_name.txt");
    FILE *pf = fopen("menu_name.txt","a");
    for(int i=0; i<menucount; i++)
    {
        fprintf(pf,"%s\n",menu[i].name);
    }
    fclose(pf);
}

void readd_menu_price()
{
    clearfile("menu_price.txt");
    FILE *pf = fopen("menu_price.txt","a");
    for(int i=0; i<menucount; i++)
    {
        fprintf(pf,"%d\n",menu[i].price);
    }
    fclose(pf);
}

void readd_menu_category()
{
    clearfile("menu_category.txt");
    FILE *pf = fopen("menu_category.txt","a");
    for(int i=0; i<menucount; i++)
    {
        fprintf(pf,"%d\n",menu[i].category);
    }
    fclose(pf);
}

void readd_menu_color()
{
    clearfile("menu_color.txt");
    FILE *pf = fopen("menu_color.txt","a");
    for(int i=0; i<menucount; i++)
    {
        fprintf(pf,"%d\n",menu[i].color);
    }
    fclose(pf);
}

void readd_menu_design()
{
    clearfile("menu_design.txt");
    FILE *pf = fopen("menu_design.txt","a");
    for(int i=0; i<menucount; i++)
    {
        fprintf(pf,"%s\n",menu[i].design);
    }
    fclose(pf);
}

void remove_item()
{
    while(1)
    {
        clearscreen();
        design("layalina.txt",0);
        leftdesign("boss.txt",0);
        int removed;
        int choise;
        centerbutton("Menu",2);
        for(int i =0; i<menucount; i++)
        {
            char buffer[50];
            sprintf(buffer,"%d. %s            -%d$-",i+1,menu[i].name,menu[i].price);
            centerbutton(buffer,menu[i].color);
        }
        centerbutton("1. Remove item",4);
        design("back0.txt",4);
        centerprint("Select an option : ",0);
        if(wrongans(&choise) ==1)continue;
        if(choise ==0) menu_edit();
        if(choise == 1)
        {
            centerprint("Select item number :",0);
            if(wrongans(&removed) ==1)continue;
            if(removed==0)menu_edit();
            if(removed>menucount || removed <1)
            {
                centerprint("Invalid number !",4);
                Sleep(700);
                continue;
            }
            else
            {
                removed--;
                for(int i =removed; i<menucount; i++)
                {
                    menu[i]=menu[i+1];
                }
                menucount--;
                readd_menu_category();
                readd_menu_color();
                readd_menu_design();
                readd_menu_name();
                readd_menu_price();
                centerbutton("Item removed successfully ",4);
                Sleep(2000);
                continue;
            }
        }
        else
        {
            centerprint("Invalid number !",4);
            Sleep(700);
            continue;
        }
    }
}

void recalactotslsales()
{
    FILE *totalsalesf = fopen("totalsales.txt","r");
    FILE *totalsalesemailf = fopen("totalsales_email.txt","r");
    char ifdeletedsale[500]= {};
    char line1[500]= {};
    char line2[500]= {};
    char ifdeletedemail[500]= {};
    while((fgets(line1,sizeof(line1),totalsalesf) !=NULL) && fgets(line2,sizeof(line2),totalsalesemailf) != NULL)
    {
        if(strcmp(line2,usersinfo[userindex].email)!=0)
        {
            strcat(ifdeletedemail,line2);
            strcat(ifdeletedsale,line1);
        }

    }
    fclose(totalsalesemailf);
    fclose(totalsalesf);
    FILE *newtotalsalesf = fopen("totalsales.txt","w");
    FILE *newtotalsalesemailf = fopen("totalsales_email.txt","w");
    fprintf(newtotalsalesemailf,ifdeletedemail);
    fprintf(newtotalsalesf,ifdeletedsale);
    fclose(newtotalsalesemailf);
    fclose(newtotalsalesf);
    calctotalsales();

}

void register_screen()
{
    while(1)
    {
        char username[MAX_NAME_LENGTH];
        char email[MAX_NAME_LENGTH];
        char password[MAX_NAME_LENGTH];

        clearscreen();
        leftdesign("layalina.txt", 0);
        design("signup.txt", 2);
        design("arrow00.txt", 4);
        centerprint("Enter Your username :", 0);
        fgets(username,sizeof(username),stdin);
        if(strcmp(username,"00\n")==0)pre_screen();
        if(strcmp(username,"\n")==0)
        {
            centerprint("Invalid username !!",4);
            Sleep(700);
            continue;
        }
        centerprint("Enter Your email :",0);
        fgets(email,sizeof(email),stdin);
        int isregistered =0;
        for(int i=0; i<maxusers; i++)
        {
            if(strcmp(email,usersinfo[i].email)==0)
            {
                centerprint("Email is already registered !",4);
                Sleep(700);
                isregistered =1;
                break;
            }
        }
        if(isregistered)continue;
        if(strcmp(email,"00\n")==0)pre_screen();
        if(strcmp(email,"\n")==0)
        {
            centerprint("Invalid email !!",4);
            Sleep(700);
            continue;
        }
        centerprint("Enter Your Password :",0);
        fgets(password,sizeof(password),stdin);
        if(strcmp(password,"00\n")==0)pre_screen();
        if(strcmp(password,"\n")==0)
        {
            centerprint("Invalid Password !!",4);
            Sleep(700);
            continue;
        }
        add_to_users(email,"emails.txt");
        add_to_users(username,"usernames.txt");
        add_to_users(password,"passwords.txt");
        centerbutton("Register Done",2);
        Sleep(1000);

        scan_emails();
        scan_passwords();
        scan_usernames();
        login_screen();
    }
}

void screens(int choise)
{
    while(1)
    {
        int numofshowed=0;
        menuitem showedmenu[MAX_MENU_ITEMS];
        for(int i = 0; i<menucount; i++)
        {
            if(menu[i].category == choise)
            {
                showedmenu[numofshowed] = menu[i];
                numofshowed++;
            }
        }
        clearscreen();
        design("home_menu.txt",0);
        for(int i =0; i<numofshowed; i++)
        {
            char buffer[50];
            sprintf(buffer,"%d. %s            -%d$-",i+1,showedmenu[i].name,showedmenu[i].price);
            centerbutton(buffer, showedmenu[i].color);
            design(showedmenu[i].design,showedmenu[i].color);
        }
        design("back0.txt", 4);
        centerprint("Select an option : ",0);
        int itemnum,qty;
        if(wrongans(&itemnum) ==1)continue;
        if(itemnum ==0)
        {
            firstscreen();
        }
        else if(itemnum<0||(itemnum>numofshowed))
        {
            centerprint("Invalid Choice !\n", 4);
            Sleep(1000);
            continue;
        }
        centerprint("Enter quantity : ",0);
        if(wrongans(&qty) ==1)continue;
        if(qty<=0)
        {
            centerprint("Invalid Choice !\n", 4);
            Sleep(700);
        }
        else
        {
            centerprint("Item added successfully",2);
            Sleep(1000);
            int found = 0;
            for (int i = 0; i < cartcount; i++)
            {
                if (strcmp(cart[i].name, showedmenu[itemnum - 1].name) == 0 )
                {
                    cart[i].quantity += qty;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                showedmenu[itemnum - 1].quantity = qty;
                cart[cartcount] = showedmenu[itemnum - 1];
                cartcount++;
            }


        }
    }
}

void sales()
{
    while(1)
    {
        clearscreen();
        char buffer[220];
        design("layalina.txt",0);
        leftdesign("boss.txt",0);
        centerbutton("last month sales: 53450$", 0);
        centerbutton("last month Restaurant expenses and workers' salaries: 36000$", 4);
        centerbutton("last month profits: 17450$", 2);
        print_orders();
        sprintf(buffer,"Today's sales: %d$", totalSales);
        centerbutton(buffer,2);
        centerbutton("1. Delete orders history",4);
        design("back0.txt", 4);
        centerprint("Select an option : ", 0);
        int v;
        if(wrongans(&v)) continue;
        if(v == 1)
        {
            clearfile("totalsales.txt");
            clearfile("orders.txt");
            clearfile("totalsales_email.txt");
            clearfile("order_email.txt");
            totalSales =0;
            centerbutton("Done",2);
            Sleep(700);
            continue;
        }
        if(v == 0) Boss_screen();
        else
        {
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
            continue;
        }
    }
}

void staff_info()
{
    while(1)
    {
        clearscreen();
        design("layalina.txt",0);
        leftdesign("boss.txt",0);
        char buffer[220];
        centerprint("Staff Summary:", 1);
        printf("\n");
        for (int i = 0; i <staffCount; i++)
        {
            sprintf(buffer, "%s - working days: %d, Salary: %.2f$ ",
                    staff[i].name,
                    25 - staff[i].absentdays,
                    staff[i].salary);
            centerbutton(buffer,1);
        }
        design("back0.txt", 4);
        centerprint("Select an option : ", 0);
        int v;
        if(wrongans(&v)) continue ;
        if(v == 0)Boss_screen();
        else
        {
            centerprint("Invalid Choice !\n", 4);
            Sleep(700);
            continue;
        }
    }
}

void staff_screen()
{

    while(1)
    {
        int staff_number;
        clearscreen();
        design("layalina.txt", 0);
        leftdesign("staff1.txt", 6);
        printf("\n");
        centerbutton("1. Abdulrahman", 0);
        centerbutton("2. Azzam", 0);
        centerbutton("3. Majed", 0);
        centerbutton("4. Nour", 0);
        design("back0.txt",4);
        centerprint("Select an option :",0);
        if(wrongans(&staff_number) ==1) continue;
        if(staff_number==0) mode();
        if(!(staff_number<5 && staff_number>0))
        {
            centerprint("invalid choise",4);
            Sleep(700);
            continue;
        }
        else
        {
            clearscreen();
            design("layalina.txt", 0);
            leftdesign("staff1.txt", 6);
            char buffer[100];
            sprintf(buffer,"welcome %s \n",staff[staff_number-1].name);
            centerbutton(buffer,6);
            sprintf(buffer,"last month you absent: %d \n ", staff[staff_number-1].absentdays);
            centerprint(buffer,0);
            sprintf(buffer,"and you salary: %.2f$ \n", staff[staff_number-1].salary);
            centerprint(buffer,0);
            centerprint("to know you salary for this month enter absent days(0-25):\n ", 0);
            int absent_days;
            centerprint("Select an option :",0);
            if(wrongans(&absent_days) ==1) continue;
            if (absent_days >= 0 && absent_days <= MAX_ABSENT_DAY)
            {
                sprintf(buffer, "your salary for this month:%d$ ", (MAX_ABSENT_DAY - absent_days) * 200);
                centerprint(buffer, 2);
                design("arrow.txt", 4);
                int v;
                if(wrongans(&v) == 1) continue;
                if(v ==0)firstscreen();
            }
            else
            {
                centerprint("  Invalid Choice ! Please enter a value between 0 and 25.\n", 4);
                Sleep(700);
            }
        }

    }
}

void settings()
{
    while(1)
    {
        clearscreen();
        int choise;
        design("home_settings.txt", 0);
        leftdesign("setting.txt", 1);
        design("mode&account.txt", 0);
        design("color_mode01.txt", 0);
        design("back0.txt", 4);

        centerprint("Select an option : ", 0);

        if(wrongans(&choise) ==1)continue;
        switch(choise)
        {
        case 1 :
            mode();
        case 2 :
            account();
        case 3 :
            color_mode();
        case 99 :
            delete_user();
        case 0 :
            firstscreen();
        default :
            centerprint("Invalid Choice !\n", 4);
            Sleep(700);
        }
    }
}

void scan_emails()
{
    FILE *pf = fopen("emails.txt","r");
    int i =0;
    while(fgets(usersinfo[i].email,sizeof(usersinfo[i].email),pf) !=NULL)
    {
        i++;
        maxusers++;
    }
    fclose(pf);
}

void scan_menu_names()
{
    menucount = 0;
    FILE *pf = fopen("menu_name.txt","r");
    int i =0;
    char buffer[MAX_NAME_LENGTH];
    while(fgets(buffer,sizeof(buffer),pf) !=NULL)
    {
        buffer[strcspn(buffer,"\n")] =0;
        sprintf(menu[i].name,"%s",buffer);
        i++;
        menucount++;
    }
    fclose(pf);
}

void scan_usernames()
{
FILE *pf = fopen("usernames.txt","r");
int i =0;
while(fgets(usersinfo[i].username,sizeof(usersinfo[i].username),pf) !=NULL){
    i++;
}
fclose(pf);
}

void scan_menu_color()
{
    char buffer[MAX_NAME_LENGTH];
    FILE *pf = fopen("menu_color.txt","r");
    int i =0;
    while(fgets(buffer,sizeof(buffer),pf) !=NULL)
    {
        menu[i].color = atoi(buffer);
        i++;
    }
    fclose(pf);
}

void scan_menu_category()
{
    char buffer[MAX_NAME_LENGTH];
    FILE *pf = fopen("menu_category.txt","r");
    int i =0;
    while(fgets(buffer,sizeof(buffer),pf) !=NULL)
    {
        menu[i].category = atoi(buffer);
        i++;
    }
    fclose(pf);
}

void scan_menu_price()
{
    char buffer[MAX_NAME_LENGTH];
    FILE *pf = fopen("menu_price.txt","r");
    int i =0;
    while(fgets(buffer,sizeof(buffer),pf) !=NULL)
    {
        menu[i].price = atoi(buffer);
        i++;
    }
    fclose(pf);
}

void scan_menu_design()
{
    FILE *pf = fopen("menu_design.txt","r");
    int i =0;
    char buffer[MAX_NAME_LENGTH];
    while(fgets(buffer,sizeof(buffer),pf) !=NULL)
    {
        buffer[strcspn(buffer,"\n")] =0;
        sprintf(menu[i].design,"%s",buffer);
        i++;
    }
    fclose(pf);
}

void scan_passwords()
{
    FILE *pf = fopen("passwords.txt","r");
    int i =0;
    while(fgets(usersinfo[i].password,sizeof(usersinfo[i].password),pf) !=NULL)
    {
        i++;
    }
    fclose(pf);
}

void scan_all()
{
    scan_emails();
    scan_passwords();
    scan_usernames();
    calctotalsales();
    scan_menu_names();
    scan_menu_category();
    scan_menu_color();
    scan_menu_design();
    scan_menu_price();
}

void view_userorders()
{
    while(1)
    {
        int choise;
        clearscreen();
        design("home_settings.txt",0);
        leftdesign("account.txt", 0);
        centerbutton("Your orders:",2);
        FILE *fileorders = fopen("orders.txt","r");
        FILE *fileemail = fopen("order_email.txt","r");
        char orders[MAX_NAME_LENGTH];
        char email[MAX_NAME_LENGTH];
        char ifdeletedemail[500] = {};
        char ifdeletedorders[500] = {};
        while((fgets(orders,sizeof(orders),fileorders) !=NULL) && fgets(email,sizeof(email),fileemail) != NULL)
        {
            if(strcmp(email,usersinfo[userindex].email)==0)  centerprint(orders,0);
            if(strcmp(email,usersinfo[userindex].email)!=0)
            {
                strcat(ifdeletedemail,email);
                strcat(ifdeletedorders,orders);
            }
        }
        fclose(fileemail);
        fclose(fileorders);
        design("trash&arrow.txt",4);
        centerprint("Select an option : ",0);
        if(wrongans(&choise) ==1)continue;
        if(choise == 0) account();
        if(choise == 1)
        {
            FILE *dfileorders = fopen("orders.txt","w");
            FILE *dfileemail = fopen("order_email.txt","w");
            fprintf(dfileemail,ifdeletedemail);
            fprintf(dfileorders,ifdeletedorders);
            centerbutton("Done",2);
            Sleep(2000);
            fclose(dfileemail);
            fclose(dfileorders);
            recalactotslsales();
            continue;

        }
        else
        {
            centerprint("Invalid number ",4);
            Sleep(700);
            continue;
        }
    }
}

int wrongans(int *choise)
{
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i]; i++)
    {
        if (!isdigit(buffer[i]))
        {
            centerprint("    Invalid input! Please enter numbers only.\n", 4);
            Sleep(700);
            return 1;
        }
    }

    *choise = atoi(buffer);
    return 0;
}


int main()
{
    scan_all();
    pre_screen();

    return 0;
}
//control+z
