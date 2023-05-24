// Programming Assignment - Burger Ordering //
// Liam Moseley 21008131 //

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


//arrays used later that store set details about burger order that never change//
const string BurgerToppings[6] = { "Cheese", "Salad", "Bacon", "Ketchup", "Mayo", "Extra Burger" };
const float BurgerToppingsPrices[6] = { 0.80f, 0.50f, 1.00f, 0.30f, 0.30f, 1.50f };
const string BurgerSizeArray[3] = { "Small", "Medium", "Large" };
const float BurgerSizeCostArray[3] = { 3.00f,5.50f,7.25f };
const int OrderLength = 7;

//menu options variables//
const int addCreditsOption = 1;
const int orderBurgerOption = 2;
const int recentOrdersOption = 3;
const int exitOption = 0;

//topping options variables//
const int minToppingOption = 0;
const int completeOrderOption = 7;
const int cancelOrderOption = 0;
const int splitDisplayTopping = 3;

//burger size variables//
const int smallBurger = 0;
const int mediumBurger = 1;
const int largeBurger = 2;

//uncategorised variables//
const int maxCreditValue = 1000000;
const int lineLength = 85;
const int maximumDisplayAmount = 15;
const int setPrecisionVariable = 2;

//function to draw a line used mainly in title but saves lines of code//
void DrawLine() 
{
    for (int line = 0; line < lineLength; line++)
    {
        cout << "-";
    }
    cout << endl;
}

//function that draws the title so it can be used over diffirent functions//
void DrawTitle() 
{
    DrawLine();
    //i decided to use a site to make an askii art logo to make the site look better//
    //ill link the site as i didnt copy it i used a generator and made a few changed to format it to visual studio//
    //https://patorjk.com/software/taag/#p=display&h=2&f=Big&t=UCLAN%20BURGER//
    string logo =
        "  _    _  _____  _               _   _    ____  _    _ _____   _____ ______ _____    \n" 
        " | |  | |/ ____ | |        /\\   | \\ | |  |  _ \\| |  | |  __ \\ / ____|  ____|  __ \\  \n"
        " | |  | | |     | |       /  \\  |  \\| |  | |_) | |  | | |__) | |  __| |__  | |__) |  \n"
        " | |  | | |     | |      / /\\ \\ | . ` |  |  _ <  |  | | |  _/| | |_ | __|  |  _  /   \n"
        " | |__| | |____ | |____ / ____ \\| |\\  |  | |_) | |__| | | \\ \\| |__| | |____| | \\ \\   \n"
        "  \\____/ \\_____ |______/_/    \\_\\_| \\_|  |____/ \\____/|_|  \\_\\\\_____|______|_|  \\_\\  \n";
    cout << logo << endl;


        
    DrawLine();
}

//how i add credits. uses basic input and gets what the credits are at the moment using the function and return new credit amount//
float AddCredits(float currentCredits) 
{
    //while loop so i can have repeated inputs for diffirent results//
    bool addingCreditsBool = true;
    bool invalidInput = false;
    while (addingCreditsBool)
    {
        DrawTitle();
        cout << "Current Credits: " << currentCredits << endl;
        cout << "Please enter how many credits you would like to add to your balance: ";
        float creditsAdded = 0.0f;
        cin >> creditsAdded;
        invalidInput = false;

        //input validation//
        if (cin.fail() || creditsAdded < 0)
        {
            cin.clear();
            //i explain this line fully in main//
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Invalid Input" << endl;
            invalidInput = true;
        }

        //this part makes sure the credits dont go over the maximum value if it did the number displays weird to the user//
        else if ((creditsAdded > maxCreditValue || (currentCredits + creditsAdded) >= maxCreditValue) && invalidInput == false)
        {
            system("cls");
            cout << "Too Much To Add" << endl;
        }

        //if user does a valid input add to their total credits and return it to main//
        else if (invalidInput == false)
        {
            currentCredits += creditsAdded;
            system("cls");
            return currentCredits;
        }
    }
}

//gets burger size based off input//
int GetBurgerSize(float credits)
{
    //while loop so i can have repeated inputs for diffirent results//
    bool choosingSize = true;
    while (choosingSize)
    {
        int burgersize = 0;
        bool invalidInput = false;

        DrawTitle();
        cout << "ORDER BURGER Select Size    [Current Balance = " << credits << " credits]" << endl;
        cout << "Please choose from the following options:" << endl
            << "   1. Small   [" << BurgerSizeCostArray[smallBurger] << " credits]" << endl
            << "   2. Medium  [" << BurgerSizeCostArray[mediumBurger] << " credits]" << endl
            << "   3. Large   [" << BurgerSizeCostArray[largeBurger] << " credits]" << endl
            << "   0. Return to Main Menu" << endl;
        DrawLine();

        cout << "Please enter a number: ";
        cin >> burgersize;

        //input validation checks if value entered goes over certain values so it does not try get a value outsode the arrays maximum index//
        if (cin.fail() || burgersize > largeBurger + 1 || burgersize < smallBurger)
        {
            cin.clear();
            //i explain this line fully in main//
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Invalid Input" << endl;
            invalidInput = true;
        }
        //user can exit out of function and as burger size is set to 0 that is whats returned//
        else if (burgersize == exitOption && invalidInput == false)
        {
            system("cls");
            return burgersize;
        }
        //if input is correct returns the burger size based on its index value in the array//
        else if (invalidInput == false)
        {
            system("cls");
            return burgersize;
        }

    }
}

//add topping to burger currently being made, uses arrays to store values needed//
float AddToppings(float credits, int burgerSize)
{
    bool choosingToppingBool = true;
    const int originalToppingLength = 6;
    int currentToppings[originalToppingLength] = { 0,0,0,0,0,0 };
    float costOfBurger = 0.0f;
    costOfBurger = BurgerSizeCostArray[burgerSize - 1];
    bool invalidInput = false;

    //while loop so i can have repeated inputs for diffirent results//
    while (choosingToppingBool)
    {
        int toppingChoice = 0;
        invalidInput = false;

        DrawTitle();
        cout << "Current Credits: " << credits << endl;
        cout << "Current Cost: " << costOfBurger << endl;

        //a for loop that displays all the toppings and prices in a nice formatted way//
        //here i also used iomaip as it allowed me to format how much space was used between whats being displayed//
        //i set a maximum amount of space to be used (15) and put the toppping at the start and price at the end and anything inbetween is blank spaces//
        for (int topping = 0; topping < originalToppingLength; topping++)
        {
            cout << topping + 1 << ". " << BurgerToppings[topping] << setfill(' ') << setw(maximumDisplayAmount - size(BurgerToppings[topping])) << "[" << BurgerToppingsPrices[topping] << " credits]" << endl;
        }

        cout << "7. Complete Order" << endl
             << "0. Cancel Order" << endl;
        DrawLine();

        cout << "You have selected a " << BurgerSizeArray[burgerSize - 1] << " burger" << endl;

        //all this for loop does is split the toppings to give it a nicer display//
        for (int topping = 0; topping < originalToppingLength; topping++)
        {
            if (topping == splitDisplayTopping)
            {
                cout << endl;
            }
            cout << BurgerToppings[topping] << " : " << currentToppings[topping] << "   ";
        }

        cout << endl;
        DrawLine();

        cout << "What topping would you like?" << endl;
        cout << "Enter a number: ";
        cin >> toppingChoice;

        //inpit validation and checking value doesnt go outside the arrays maximum index//
        if (cin.fail() || toppingChoice < cancelOrderOption || toppingChoice > completeOrderOption)
        {
            cin.clear();
            //i explain this line fully in main//
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Invalid Input" << endl;
            invalidInput = true;
        }

        //when a topping is picked it oncreases that specific index in another array which is the users array based on the toppings already chosen//
        //it then adds the price to the cost of the burger//
        else if (toppingChoice < completeOrderOption && toppingChoice > minToppingOption && invalidInput == false)
        {
            currentToppings[toppingChoice - 1]++;
            costOfBurger += BurgerToppingsPrices[toppingChoice - 1];
            system("cls");
        }

        //when complete if user enters 7 the program moves on and breaks out of while loop//
        else if (toppingChoice == completeOrderOption && invalidInput == false)
        {
            system("cls");
            choosingToppingBool = false;
        }

        //if user enters 0 exits the function and return 0//
        else if (toppingChoice == cancelOrderOption && invalidInput == false)
        {
            system("cls");
            return 0;
        }

    }

    return costOfBurger;

}

//this saves the details to a text file to be displayed later//
void SaveToTextFile(int burgerSize, float costOfBurger)
{
    //also gets a name to be saved also for extra detail//
    string nameOfCustomer;
    DrawTitle();
    cout << "Saving Details..." << endl;
    cout << "Please Enter Your Name: ";
    cin >> nameOfCustomer;

    //uses fstream as this creates a file for me and allows me to save details to it//
    //the "app" means append mode and means im adding to the text file//
    fstream recentOrders("RecentOrders.txt", ios::app);

    //if file is open//
    if (recentOrders)
    {
        //adds all the details in a formatted way
        recentOrders << "Name: " << nameOfCustomer << "\n"
                     << "Burger Size: " << BurgerSizeArray[burgerSize - 1] << "\n"
                     << "Cost of the burger: " << costOfBurger << " Credits" << "\n"
                     << "*************************************" << "\n";
    }

    //if file fails to open gives an error message and doesnt save//
    else if (!recentOrders)
    {
        cout << "ERROR failed to save details... Sorry" << endl;
    }

    //close file after use//
    recentOrders.close();

}

//displays recent orders that are also saved after closing the app//
void DisplayRecentOrders()
{
    system("cls");
    DrawTitle();
    //use fstream again to get the file that orders were saved too//
    fstream recentOrders("RecentOrders.txt");
    string orders;

    //if file is open//
    if (recentOrders.is_open())
    {
        //use a while loop to go through every line in the text document and display it//
        while (getline(recentOrders, orders))
        {
            cout << orders << endl;
        }
        //close file//
        recentOrders.close();
    }
    //if failed to open the file give an error message
    else
    {
        cout << "Failed to open file" << endl;
    }
    system("pause");
    system("cls");
}

//this function check the burger size againts how many credits you have giving diffirent options based on result//
//this fucntion was alot smaller orignally but caused alot of issues when i added input validation so it was made longer and more complicated
float CheckCredits(float costOfBurger, float credits, int burgerSize)
{
    string decision;
    float amountNeeded = 0.0f;
    bool makingDecision = true;
    bool invalidInput = false;

    cout << setiosflags(ios::fixed) << setprecision(setPrecisionVariable) << costOfBurger;

    //if the user doesnt have enough credits it will decline the payment//
    //it also displays how much they need to afford the burger//
    //also starts while loop for multiple times of adding credits and checking credits//
    while(!((credits - costOfBurger) >= 0))
    {
        amountNeeded = costOfBurger - credits;
        invalidInput = false;
        DrawTitle();
        cout << "Credits Declined : Please Insert More Credits" << endl
            << "You need " << amountNeeded << " more to afford your burger" << endl
            << "Would you like to insert credits now? (y/n): ";

        cin >> decision;

        //if the user wants to add more credits it will run the add credits function and the rerun the check credits until they have enough//
        if ((decision == "y" || decision == "Y") && invalidInput == false)
        {
            system("cls");
            credits = AddCredits(credits);
        }

        //if the user doesnt want to pay for the burger it will cancel the order and return their credits back to main//
        else if ((decision == "n" || decision == "N") && invalidInput == false)
        {
            system("cls");
            DrawTitle();
            cout << "Credits Remaining: " << credits << endl;
            cout << "Press Enter for next customer or a new order" << endl;
            system("pause");
            system("cls");
            return credits;
        }

        else
        {
            system("cls");
            cout << "INVALID INPUT" << endl;
        }

    }

    //i read somewhere that comparing floats can be bad so i made it a little longet to avoid this - research more//
    //if the user has enough credits to afford the burger it accepts the credits and removes them from the user//
    system("cls");
    if ((credits - costOfBurger) >= 0)
    {
        DrawTitle();
        credits = credits - costOfBurger;
        cout << "Credits Accepted : Enjoy Your Burger" << endl
            << "Press Enter for next customer or a new order" << endl;
        system("pause");
        system("cls");

        //save details to text file//
        SaveToTextFile(burgerSize, costOfBurger);

        //return credits back to main to be reused//
        return credits;
    }

}


//main game loop which i used as menu placeholder as this is run first//
int main()
{
    float credits = 0;
    bool runningMainBool = true;
    int userChoice = -1;
    int burgerSize = 0;
    bool invalidInput = false;
    const int ToppingsAmount = 6;
    float costOfBurger = 0.0f;

    //while loop so function can have multiple inputs//
    while (runningMainBool)
    {
        //i was having an issue where when i did an order and returned with no credits it wouldnt return 0 but a large number thats unreadable//
        //i applied this if statement to stop this happening which also made it look like a a feature that doesnt allow too many credits//
        if (credits > maxCreditValue || credits < 0)
        {
            credits = 0;
        }

        DrawTitle();
        cout << "Main Menu" << endl
            << "   1. ADD Credits (current credits: " << fixed << setprecision(setPrecisionVariable) << credits << ")" << endl
            << "   2. Order Burger" << endl
            << "   3. Recent Orders" << endl
            << "   0. EXIT" << endl;
        DrawLine();

        cout << "Enter Choice: ";
        cin >> userChoice;

        //input validation makes sure input isnt above or below the required input or a character//
        if (cin.fail() || userChoice < exitOption || userChoice > recentOrdersOption)
        {
            cin.clear();
            //instead of putting in a single value for the ignore i decided to use this//
            //numeric_limit() combined with max() gets the largest possible value for its type//
            //this means that if the user enters a string size of any size thhis means the ignore will always catch it in one go unlike putting a singular int//
            //this could mitiagte some issues on there input//
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "INVALID INPUT" << endl;
        }

        //runs the add credits function//
        else if (userChoice == addCreditsOption)
        {
            system("cls");
            credits = AddCredits(credits);
        }

        //runs the order burgerSize function//
        else if (userChoice == orderBurgerOption)
        {
            system("cls");
            burgerSize = GetBurgerSize(credits);

            //once they have gotten there burger size it will run this check if the user didnt make a choice on size 0 was returned//
            //if 0 wasnt returned it will carry on//
            if (burgerSize != 0)
            {
                //gets the cost of the burger which is calculated at the end of the addtoppings function//
                costOfBurger = AddToppings(credits, burgerSize);

                //if they cancelled the order 0 is returned and the if statement will be passed if not it will run//
                if (costOfBurger != 0)
                {
                    //this will check if the user has enough credits and change there credits based on if they payed or not//
                    credits = CheckCredits(costOfBurger, credits, burgerSize);
                    system("cls");
                }
            }

        }

        //runs the recent orders function//
        else if (userChoice == recentOrdersOption)
        {
            DisplayRecentOrders();
        }

        //if the user quits it will change the bool running the while loop and the main function will end//
        else if (userChoice == exitOption && invalidInput == false)
        {
            system("cls");
            runningMainBool = !runningMainBool;
        }

    }

    //returns 0 and ends project, returning 0 is apparently a good way to exit the main function and this is the exir code it will recieve - research more//
    return 0;

}