/************************************************/
/********** IMPORT/CREATE DEPENDENCIES **********/
/************************************************/





#include <stdlib.h>
#include "resourceManagement.h"

int const STRING_LENGTH = 31;





/******************************************/
/********** PRINT NAMES FUNCTION **********/
/******************************************/





void printNames( ) {

    printf("\nThis solution was completed by:\n");
    printf("Matthew Beck\n");
    printf("N/A\n");
}





/**************************************************/
/********** RESOURCE MANAGEMENT FUNCTION **********/
/**************************************************/
 
 

 
 
void ResourceManagement( char *fileNames[], int testDataSize, double budget ) {



  /********************************/
  /***** CREATE LISTS OF DATA *****/
  /********************************/
  
  
  
  /***** find basic department info *****/


  char deptName[STRING_LENGTH], lineData[STRING_LENGTH], c;
  int i, j;
  double originalBudget = budget, objectPrice;
  FILE *file;
  
  int lenItems, maxLenItems;
  
  struct department { // create a struct to store basic info about a department
  
    int deptID, deptDataSize;
    bool isNext;
    char deptName[STRING_LENGTH];
    
  } departments[testDataSize];
  
  for (i = 0; i < testDataSize; i++) { // find basic info about a department to be used later when assigning said info to an item
  
    lenItems = 0;
    file = fopen(fileNames[i], "r");
    
    if (file != NULL) {
    
      fscanf(file, "%s", departments[i].deptName);
      departments[i].deptID = i;
      
      while (fgets(lineData, STRING_LENGTH, file) != NULL) {
        
          if (lineData[strlen(lineData) - 1] == '\n') {
  
  					lineData[strlen(lineData) - 1] = '\0';
          }
        
          if (lineData != deptName) {
          
            if (lineData[0] != ' ' && lineData[0] != '\r' && lineData[0] != '\t' && lineData[0] != '\n') {
  
              lenItems++;
            }
          }
        }
        
        departments[i].deptDataSize = lenItems / 2;
    }
    
    else {
    
      printf("ERROR: file '%s' is NULL\n", fileNames[i]);
    }
  }
  
  maxLenItems = departments[0].deptDataSize; // find the maximum amount of items a department is requesting to see how many item structs will be needed later
  
  for (i = 0; i < testDataSize; i++) {
  
    if (maxLenItems < departments[i].deptDataSize) {
    
      maxLenItems = departments[i].deptDataSize;
    }
  }
  

  /***** collect items *****/


  typedef struct { // create a struct to store basic information about an item and whether or not it will be accepted
  
    int itemDeptID, itemPosition;
    bool accepted;
    char itemName[STRING_LENGTH], itemDeptName[STRING_LENGTH];
    double itemPrice;
    
  } items;
  
  items allItems[testDataSize][maxLenItems]; // create a 2d array of structs to give each department its own item list
  
  for (i = 0; i < testDataSize; i++) {
  
    for (j = 0; j < maxLenItems; j++) { // completely fill the 2d array of structs will empty data to fill in later
    
      allItems[i][j].itemDeptID = i;
      strcpy(allItems[i][j].itemDeptName, departments[i].deptName);
      allItems[i][j].accepted = true;
      allItems[i][j].itemPosition = j;
      strcpy(allItems[i][j].itemName, " ");
      allItems[i][j].itemPrice = 0;
    }
    
		file = fopen(fileNames[i], "r");

		if (file != NULL) {
   
     j = 0;
     
     fscanf(file, "%s", deptName);

      while ((c = fgetc(file)) != EOF) { // fill a department list with data from its respective file until there is no more data left
        
        if (lineData != deptName) {
        
          fscanf(file, "%s %lf", lineData, &objectPrice);
        
          strcpy(allItems[i][j].itemName, lineData);
          allItems[i][j].itemPrice = objectPrice;
        }
        
        else { // if somehow the program cannot do this, replace the data with an obvious error
         
          strcpy(allItems[i][j].itemName, "ITEM NOT RECIEVED");
          allItems[i][j].itemPrice = 404;
        }
        
        j++;
      }
      
      fclose(file); 
    }
    
    else {
    
      printf("ERROR: file '%s' is NULL\n", fileNames[i]);
    }
    
    for (j = 0; j < maxLenItems; j++) { // if the last item in a list acceidentally duplicated, replace it with a scholarship of value 1000
    
      if (strcmp(allItems[i][j].itemName, allItems[i][j-1].itemName) == 0) {
        
        strcpy(allItems[i][j].itemName, "Scholarship");
        allItems[i][j].itemPrice = 1000;
      }
    }
    
    for (j = 0; j < maxLenItems; j++) { // if an items list has empty data, fill it with scholarships of value 1000
    
      if (allItems[i][j].itemPrice == 0) {
      
        strcpy(allItems[i][j].itemName, "Scholarship");
        allItems[i][j].itemPrice = 1000;
      }
    }
  }
  
  
  
  /************************************/
  /***** SORT ITEMS/UPDATE BUDGET *****/
  /************************************/
  
  
  
  /***** determine which items will be accepted *****/
  
  
  struct remainder { // store the remainder of the budget as a small scholarship
  
    int itemDeptID;
    bool accepted;
    char itemName[STRING_LENGTH], itemDeptName[STRING_LENGTH];
    double itemPrice;
  
  } remainingBudget;
  
  

  for (j = 0; j < maxLenItems; j++) {
    
   for (i = 0; i < testDataSize; i++) {
    
      if (allItems[i][j].itemPosition == j) {
        
        if (allItems[i][j].itemPrice < budget) { // if an item is below budget, accept it and subtract its value
        
          budget = budget - allItems[i][j].itemPrice;
        }
        
        else { // if an item is above budget, reject it
        
          allItems[i][j].accepted = false;
        }
      }
      
      if (i + 1 < testDataSize) { // update which department is next in line
      
        departments[i].isNext = false;
        departments[i + 1].isNext = true;
      }
      
      else { // set the next department in line to position 0 if maximum length reached
      
        departments[i].isNext = false;
        departments[0].isNext = true;
      }
    }
  }
  
  if (budget != 0) {
  
    for (i = 0; i < testDataSize; i++) {
    
      if (departments[i].isNext == true) { // if a department was previously in line, give it the budget
      
        remainingBudget.accepted = true;
        remainingBudget.itemDeptID = i;
        strcpy(remainingBudget.itemDeptName, departments[i].deptName);
        strcpy(remainingBudget.itemName, "Scholarship");
        remainingBudget.itemPrice = budget;
        
        budget = 0;
      }
    }
  }


  
  /******************************/
  /***** PRINT SORTED ITEMS *****/
  /******************************/
  
  
  
  double totalSpent, percentOfBudget;
  char priceStr[STRING_LENGTH];
  
  printf("ITEMS PURCHASED\n----------------------------\n");
    
  for (j = 0; j < maxLenItems; j++) { // print out a full list of all items bought
    
   for (i = 0; i < testDataSize; i++) {
    
      if (allItems[i][j].itemPosition == j) {
        
        if (allItems[i][j].accepted == true) {
        
          sprintf(priceStr, "$%.2lf", allItems[i][j].itemPrice);
          printf("Department of %-30s - %-30s - %20s\n", allItems[i][j].itemDeptName, allItems[i][j].itemName, priceStr);
        }
      }
    }
  }
  
  sprintf(priceStr, "$%.2lf", remainingBudget.itemPrice);
  printf("Department of %-30s - %-30s - %20s\n", remainingBudget.itemDeptName, remainingBudget.itemName, priceStr); // add remaining budget to the list as a scholarship
  
  for (i = 0; i < testDataSize; i++) { // print out each department's item list
  
    totalSpent = 0;
    
    printf("\nDepartment of %s\n", departments[i].deptName);
      
    for (j = 0; j < maxLenItems; j++) {          
      
      if (allItems[i][j].accepted == true) {
        
        totalSpent = totalSpent + allItems[i][j].itemPrice;
      }
    }
    
    if (remainingBudget.itemDeptID == i) { // if a department was previously in next in line before the loop stopped, give it the remainder of the budget as a scholarship
    
        totalSpent = totalSpent + remainingBudget.itemPrice;
    }
    
    percentOfBudget = (totalSpent / originalBudget) * 100;
    
    printf("Total Spent       = $%.2lf\n", totalSpent);
    printf("Percent of Budget = %.2lf\n", percentOfBudget);
    printf("----------------------------\n");
    printf("ITEMS RECIEVED\n");
    
    for (j = 0; j < maxLenItems; j++) {
      
      if (allItems[i][j].accepted == true) {
      
        sprintf(priceStr, "$%.2lf", allItems[i][j].itemPrice);
        printf("%-30s - %20s\n", allItems[i][j].itemName, priceStr);
      }
    }
    
    if (remainingBudget.itemDeptID == i) { // if a department was previously in next in line before the loop stopped, give it the remainder of the budget as a scholarship
    
        sprintf(priceStr, "$%.2lf", remainingBudget.itemPrice);
        printf("%-30s - %20s\n", remainingBudget.itemName, priceStr);
    }
    
    printf("\nITEMS NOT RECIEVED\n");
    
    for (j = 0; j < maxLenItems; j++) {
      
      if (allItems[i][j].accepted == false) {
      
        if (strcmp(allItems[i][j].itemName, "Scholarship") != 0) {
      
          sprintf(priceStr, "$%.2lf", allItems[i][j].itemPrice);
          printf("%-30s - %20s\n", allItems[i][j].itemName, priceStr);
        }
      }
    }
  }
}
