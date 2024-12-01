/******************
Name:ilay helfgot
ID:212398648
Assignment: ex3
*******************/

#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
//const int addOne = 1, addAll = 2, stats = 3, print = 4, insights = 5, deltas = 6, done = 7;
#define addOne 1
#define addAll 2
#define stats 3
#define print 4
#define insights 5
#define deltas 6
#define done 7

int provideStats(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int totalSales = 0;
    int whatBrand = 0;
    int bestBrand = 0 ;
    int salesType = 0;
    int choice = 0 ;
    int bestType = 0 ;
    int suv=0;
    int sedan=0;
    int coupe=0;
    int gt=0;
    printf("What day would you like to analyze?\n");
    scanf("%d",&choice);
    while (choice < 0 || choice >= DAYS_IN_YEAR||choice >dayCounter)
    {
        printf("Please enter a valid day.\n");
        printf("What day would you like to analyze?\n");
        scanf("%d",&choice);
    }
    printf("In day number %d:\n",choice);
    //here i sum up the total sales of each brand and type for a specific day
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            totalSales= totalSales + cube[choice][i][j];
        }
    }
    //here i sum up how much the best brand had sold
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // i define it here so it will also will reset everytime i move on to the next brand
        int salesBrand = 0 ;
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            salesBrand= salesBrand + cube[choice][i][j];
        }
        if (salesBrand > bestBrand)
        {
            whatBrand = i;
            bestBrand = salesBrand;
        }

    }

    //here i sum up how much the best type had sold
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            salesType= salesType + cube[choice][i][j];
        }

    }
    // here are sum up  sales for each type
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (i==0)
        {
            suv= suv + cube[choice][i][0];
        }
       if (i==1)
       {
           sedan= sedan + cube[choice][i][1];
       }
        if (i==2)
        {
            coupe= coupe + cube[choice][i][2];
        }

        if (i==3)
        {
           gt= gt + cube[choice][i][3];
        }
    }
    // i use array for the total sums of the types so i could check  which is bigger
    int arrType[]={suv,sedan,coupe,gt};
    int bigger =0;
    int bigType=0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
       if (arrType[i]>bigger)
       {
           bigger = arrType[i];
           bigType = i;
       }
    }

    printf("The sales total was %d\n",totalSales);
    printf("The best sold brand with %d sales was ",bestBrand);
    for(int i = 0; i < BRANDS_NAMES; i++)
    {
            printf("%s ", &brands[whatBrand][i]);
    }
    printf("\n");

    printf("The best sold type with %d sales was ",bigger);
    for(int i = 0; i < BRANDS_NAMES; i++)
    {
        printf("%s ", &brands[bigType][i]);
    }
    printf("\n");

}

void avaiableBrands(int days[],int dayCounter,char brands[][BRANDS_NAMES] ) {
    printf("No data for brands ");
    // here i print all the avaiable brands that the user can update
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if(days[i] != dayCounter)
        {
            printf("%s ", brands[i]);
        }

    }

    printf("\nPlease complete the data\n");
}
int brandValid(int carBrand,int days[],int dayCounter)
{

    if (carBrand < 0 || carBrand >= NUM_OF_BRANDS  ) {
        printf("This brand is not valid\n");
        return 0 ;
    }

    if (days[carBrand] == dayCounter)
    {
        printf("This brand is not valid\n");
        return 0;
    }

    return 1;
}



// here i insert the data from the user to the specific car type
void insertData(int dailySalesSum[],int days[],int dayCounter,int carBrand,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        scanf("%d", &dailySalesSum[i]);
    }
    for(int k = 0; k < NUM_OF_TYPES; k++)
    {
        cube[dayCounter][carBrand][k] = dailySalesSum[k];

    }
    // i update the array of brands that represent the last day that that specific brand got updated
    days[carBrand] = dayCounter;
}







void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}


int main() {
    int static dayCounter = 0;
    // set a 3d cube of arrays
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // here i Initialize all its values to (-1)s.
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for(int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }

        }
    }
    //this is an array which represent the day which the specific brand still hasnt gotten its info from the user
    int days[NUM_OF_BRANDS] = {-1,-1,-1,-1,-1};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice)
        {
        case addOne:
            {
            int carBrand;
            scanf("%d", &carBrand);
            if (carBrand < 0 || carBrand >= NUM_OF_BRANDS) {
                printf("This brand is not valid\n");
                break;
            }
            int dailySalesSum[NUM_OF_BRANDS]={0};
            for(int i = 0; i < NUM_OF_BRANDS; i++)
            {
                scanf("%d", &dailySalesSum[i]);
            }

            int i = 0;
            while( i < DAYS_IN_YEAR)
            {
                if (cube[i][carBrand][0] == -1)
                {
                    for(int k = 0; k < NUM_OF_TYPES; k++)
                    {
                        cube[i][carBrand][k] = dailySalesSum[k];

                    }
                    days[carBrand] = i;
                    break;
                }
                i++;
            }

            break;
        }

        case addAll:
            {
                // this will let me know when the user has entered the data for all the brands
                int sumBrand=0;
                int carBrand=0;
                int dailySalesSum[NUM_OF_BRANDS]={0};

                if(dayCounter < DAYS_IN_YEAR)
                {
                    while (sumBrand < NUM_OF_BRANDS)
                    {
                        avaiableBrands(days, dayCounter,brands);
                        scanf("%d", &carBrand);

                        while (!brandValid(carBrand, days, dayCounter))
                        {
                            avaiableBrands(dailySalesSum, dayCounter,brands);
                            scanf("%d", &carBrand);
                        }

                        insertData(dailySalesSum, days, dayCounter, carBrand,cube);
                        sumBrand++;

                    }
                    dayCounter++;
                }

                break;
            }

            case stats:
            {
                provideStats(dayCounter,cube);
                break;
            }

            case print:
            {

                printf("*****************************************");

                    for(int k = 0; k < NUM_OF_BRANDS; k++)
                    {
                        printf("Sales for %s:\n ", brands[k]);
                        for(int j = 0; j < dayCounter; j++)
                        {
                            int suv=0;
                            int sedan=0;
                            int coupe=0;
                            int gt=0;
                            suv = cube[j][k][0];
                            sedan= cube[j][k][1];
                            coupe= cube[j][k][2];
                            gt= cube[j][k][3];
                            printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n",j,suv,sedan,coupe,gt);

                        }
                    }
                printf("\n");
                printf("\n");
                printf("****************************************");
                break;
            }
        case insights:
            {
                int bestSeller = 0;
                int currentSeller = 0;
                int whatBrand = 0;
                int bestType =0;
                int whatType = 0;

                // do the whole loop NUM_OF_BRANDS times
                for (int i = 0; i < NUM_OF_BRANDS; i++)
                {
                    currentSeller = 0;

                    // i want to loop until the last updated day by the user
                    for (int day = 0; day < dayCounter; day++)
                    {
                        for (int j = 0; j < NUM_OF_TYPES; j++)
                        {
                            // i store the data for each brand
                            currentSeller =currentSeller+ cube[day][i][j];
                        }
                    }

                    // checking which brand is the best seller by comparing the value to the current highest seller
                    if (currentSeller > bestSeller)
                    {
                        bestSeller = currentSeller;
                        // i want to know which brand at the end is the best seller
                        whatBrand = i;
                    }
                }

                // do the whole loop Num of types times
                for (int i = 0; i < NUM_OF_TYPES; i++)
                {
                    int typeSeller = 0;

                    // i want to loop until the last updated day by the user
                    for (int day = 0; day < dayCounter; day++)
                    {
                        for (int j = 0; j < NUM_OF_BRANDS; j++)
                        {
                            // i store the data for each type
                            typeSeller =typeSeller+ cube[day][j][i];

                        }
                    }
                    // checking which type is the best seller by comparing the value to the current highest seller
                    if (typeSeller > bestType)
                    {
                        bestType = typeSeller;
                        // i want to know which brand at the end is the best seller
                        whatType = i;
                    }

                }
                // print the best-selling brand and its total sales
                printf("The best-selling brand overall is %s: %d sales\n", brands[whatBrand], bestSeller);
                printf("The best-selling type of car is %s: %d sales\n", types[whatType], bestType);
                break;
            }

                break;
            case deltas:
                break;
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


