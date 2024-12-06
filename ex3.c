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

#define addOne 1
#define addAll 2
#define stats 3
#define print 4
#define insights 5
#define deltas 6
#define done 7




void remainingBrands(int usedBrands[NUM_OF_BRANDS]);
void insertCube(int dailySalesSum[NUM_OF_TYPES],int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int dayCounter,int brand);
void provideStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void bestSellingBrand(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void bestSellingType(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void mostProfitableDay(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void printMenu();


int main()
{
    int  dayCounter = 0;
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
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice)
        {
        case addOne:
            {
                int dailySalesSum[NUM_OF_TYPES] = {0};
                int brand;
                scanf("%d",&brand);
                if(brand >=0 && brand<NUM_OF_BRANDS)
                {
                    insertCube(dailySalesSum,cube,dayCounter,brand);
                }
                else
                {
                    printf("This brand is not valid\n");
                }

                break;
            }

        case addAll:
            {
                int dailySalesSum[NUM_OF_TYPES] = {0};
                int usedBrands[NUM_OF_BRANDS] = {0};
                int counter = NUM_OF_BRANDS;
                int brand;

                printf("No data for brands Toyoga HyunNight Mazduh FolksVegan Key-Yuh\n");
                printf("Please complete the data\n");

                while (counter > 0)
                {
                    scanf("%d", &brand);

                    // Check if the brand is valid and hasn't been used already
                    while (brand < 0 || brand >= NUM_OF_BRANDS || usedBrands[brand] == 1)
                    {
                        printf("This brand is not valid\n");
                        remainingBrands(usedBrands);
                        scanf("%d", &brand);

                    }

                    //i call the function that insert the data to the data cube
                    insertCube(dailySalesSum,cube,dayCounter,brand);
                    // i mark the specific brand as a used brand
                    usedBrands[brand] = 1;
                    // i reduce the counter by 1 because i inserted an data for a brand
                    counter--;

                    // i check if there is still brands that didnt got updated
                    if (counter > 0)
                    {
                      //here i call the function that prints the remaining brands
                      remainingBrands(usedBrands);
                    }

                }
                dayCounter++;
                break;
            }
        case stats:
            {
                int day = 0;

                printf("What day would you like to analyze?\n");
                scanf("%d",&day);
                // here i check if the user typed a valid day to check
                while (day < 1 || day >dayCounter)
                {
                    printf("Please enter a valid day.\n");
                    printf("What day would you like to analyze?\n");
                    scanf("%d",&choice);
                }
                provideStats(cube,day);
                break;
            }

        case print:
            {

                printf("*****************************************\n");

                for(int k = 0; k < NUM_OF_BRANDS; k++)
                {
                    printf("Sales for %s:\n", brands[k]);
                    for(int j = 0; j < dayCounter; j++)
                    {
                        printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n",j+1,cube[j][k][0],cube[j][k][1],cube[j][k][2],cube[j][k][3]);
                    }
                }
                printf("\n");
                printf("\n");
                printf("****************************************\n");
                break;
            }
        case insights:
            {
              //a function that prints the best selling brand
              bestSellingBrand(dayCounter,cube);
              //a function that prints the best selling type
              bestSellingType(dayCounter,cube);
              //a function that prints the most profitable day
              mostProfitableDay(dayCounter,cube);
              break;
            }



        case deltas:
            {
                        for (int j = 0; j < NUM_OF_BRANDS; j++)
                        {
                            int previousDay = 0;
                            int currentDay = 0;
                            float top=0.0;
                            int denominator =dayCounter-1 ;

                            for(int day = 0; day < dayCounter; day++)
                            {
                                currentDay = 0;
                                for(int k = 0; k < NUM_OF_TYPES; k++)
                                {
                                    currentDay =currentDay+cube[day][j][k];

                                }

                                if(day>0)
                                {
                                    top=top+(currentDay-previousDay);
                                }
                                 previousDay=currentDay;

                            }
                            float equation = top/denominator;
                            printf("Brand: %s, Average Delta: %.6f\n",brands[j],equation);

                        }

                        break;
            }

                default:
                    printf("Invalid input\n");
            }
            printMenu();
            scanf("%d", &choice);
        }
        printf("Goodbye!\n");
        return 0;
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



void remainingBrands(int usedBrands[NUM_OF_BRANDS])
{
    printf("No data for brands ");
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // here i check if the current brand (i) is an updated brand or not (if not updated print it)
        if (usedBrands[i] == 0)
        {
            printf("%s ",brands[i]);
        }
    }
    printf("\n");
    printf("Please complete the data\n");
}


void insertCube(int dailySalesSum[NUM_OF_TYPES],int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int dayCounter,int brand)
{
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        scanf("%d", &dailySalesSum[i]);
    }


    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        cube[dayCounter][brand][i] = dailySalesSum[i];
    }

}



void provideStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day)
{
    int valueType =0 ;
    int arrTypes[NUM_OF_TYPES]={0};
    int totalSales = 0;
    int whatBrand = 0;
    int bestBrand = 0 ;
    int bestType = 0 ;
    printf("In day number %d:\n",day );
    //here i sum up the total sales of each brand and type for a specific day
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            totalSales= totalSales + cube[day -1][i][j];
        }
    }
    //here i sum up how much the best brand had sold
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // i define it here so it will also will reset everytime i move on to the next brand
        int totalSalesBrand = 0 ;
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            totalSalesBrand= totalSalesBrand + cube[day-1][i][j];
        }
        if (totalSalesBrand > bestBrand)
        {
            //i want to know in the end of the loop which brand sold the most
            whatBrand = i;
            bestBrand = totalSalesBrand;
        }

    }

    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {

        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            arrTypes[j] = arrTypes[j] + cube[day-1][i][j];
        }

    }
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        if(arrTypes[i]>bestType)
        {
            bestType = arrTypes[i];
            valueType = i;
        }
    }
    printf("The sales total was %d \n", totalSales);
    printf("The best sold brand with %d sales was %s \n",bestBrand,brands[whatBrand]);
    printf("The best sold type with %d sales was %s \n",bestType,types[valueType]);
    printf("\n");


}

void bestSellingBrand(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int bestSeller = 0;
    int whatBrand = 0;

    // do the whole loop NUM_OF_BRANDS times
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        int currentSeller = 0;

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
    // print the best-selling brand and its total sales
    printf("The best-selling brand overall is %s: %d sales\n", brands[whatBrand], bestSeller);
}
void bestSellingType(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int whatType =0;
    int bestSeller = 0;
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
        if (typeSeller > bestSeller)
        {
            bestSeller = typeSeller;
            // i want to know which brand at the end is the best seller
            whatType = i;
        }
    }
    // print the best selling type and its total sales
    printf("The best-selling type of car is %s: %d sales\n", types[whatType], bestSeller);
}
void mostProfitableDay(int dayCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int bestSum =0;
    int bestDay =-1;

    // do the whole loop until i get to the day that wasnt updated already
    for (int j = 0; j < dayCounter; j++)
    {
        int daySum = 0 ;
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            // i want to loop until the last updated day by the user
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                // i sumup all the sales for the specific day
                daySum =daySum+ cube[j][i][k];

            }
        }
        // each time i finish summing up the day i compare it to the best day currently
        if ( daySum> bestSum)
        {
            bestSum = daySum;
            // i want to know which brand at the end is the best seller
            bestDay = j;
        }
    }

    // print the most profitable day and his overall sales
    printf("The most profitable day was day number %d:%dsales$\n",bestDay+1,bestSum);
}
