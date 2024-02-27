#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "resourceManagement.h"

void testData( char *testData[], int testDataSize, double budget, int testNumber );

int main( int argc, char *argv[] )
{
    char *testFiles[] = {
                        "Department-ComputerScience.txt",
                        "Department-Mathematics.txt",
						"Department-Chemistry.txt",
                        "Department-PhysicsAndAstronomy.txt"};
                                                
    int testFilesSize = 4;
    double budget = 41850.00;
		
    printNames( );
	testData( testFiles, testFilesSize, budget, 1 );
	printNames( );

/*     
    if( argc==1 ){
        testData( testData1, testData1Size, 1 );
        testData( testData2, testData2Size, 2 );
    }
    else if( argv[1][0]=='1' ){
        testData( testData1, testData1Size, 1 );
    }
    else if( argv[1][0]=='2' ){
        testData( testData2, testData2Size, 2 );
    } */

    return 0;
}

void testData( char *testData[], int testDataSize, double budget, int testNumber )
{
	char budgetString[21];
    printf( "\n\n------------ START OF TEST #%d ------------\n\n", testNumber );

    //Call ResourceManagement on the inputs 
	sprintf( budgetString, "$%.2lf", budget );
	printf( "TESTING with budget = %20s\n\n", budgetString );
    ResourceManagement( testData, testDataSize, budget );
    printf( "\n" );
    
    printf( "------------ END OF TEST #%d ------------\n", testNumber );
}