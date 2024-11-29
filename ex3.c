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

void avaiableBrands(int days[],int dayCounter,char brands[][BRANDS_NAMES] ) {
    printf("No data for brands ");
    // here i print all the avaiable brands that the user can update
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if(days[i] == dayCounter)
        {
            printf("%s ", &brands[i]);
        }

    }
    printf("\n");
    printf("Please complete the data\n");
}
int brandValid(int carBrand,int days[],int dayCounter)
{
    if (days[carBrand] == dayCounter)
    {
        return 1;
    }
    if (carBrand < 0 || carBrand >= NUM_OF_BRANDS  ) {
        printf("This brand is not valid\n");
        avaiableBrands(days,dayCounter,brands);
        return 0 ;
    }


    return 1;
}



// here i insert the data from the user to the specific car type
void insertData(int dailySalesSum[],int days[],int dayCounter,int carBrand)
{
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        scanf("%d", &dailySalesSum[i]);
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
    int days[NUM_OF_BRANDS] = {0};
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
                int static dayCounter = 0;
                int carBrand=0;
                int dailySalesSum[NUM_OF_BRANDS]={0};
                if(dayCounter < DAYS_IN_YEAR)
                {
                    while (sumBrand < NUM_OF_BRANDS)
                    {
                        avaiableBrands(days, dayCounter,brands);
                        scanf("%d", &carBrand);

                        // i check if the user input is valid
                        while(brandValid(carBrand,days,dayCounter)==0)
                        {
                            scanf("%d",&carBrand);
                        }
                        // here i insert the data from the user to the specific car type
                        insertData(dailySalesSum, days, dayCounter, carBrand);
                        days[carBrand] = dayCounter;
                        // i update the sumBrand
                        sumBrand ++;
                    }
                    sumBrand = 0;

                }
                dayCounter++;
                break;
            }

            case stats:
                break;
            case print:
                break;
            case insights:
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


