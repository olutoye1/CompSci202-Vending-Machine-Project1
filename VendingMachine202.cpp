//////////////////////////////////////////////////////
//File: Proj1.cpp **
//Project: CMSC 202 Project 1, Fall 2017 **
//Author: Olutoye Sekiteri**
//Date: 9/28/2017 **
//Section: Wednsday, 7:10-8:00
//E-mail: olutoye1umbc.edu



#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


///////////////////Prototypes///////////////////////
void printWelcome();

int getUserInput();

void getOrders(string itemArray[10], double priceArray[10]);

void viewOrders();
///////////////////////////////////////////////////
int main() {

  const int fileSize = 10; // how big arrays can be

  string itemArray[fileSize]; // array to hold item names

  double priceArray[fileSize]; // array to hols item prices

  int userMenuSelect;    // initailizes user menu selection

  printWelcome();

////////////// reading in file//////////////

  ifstream inputStream;
  inputStream.open("proj1_items.txt");


  string items; /// used to hold the values  for item names and prices
  double prices; ///

  ///spliting by the comma, adds the item name to on array nad the prices to another
  for (int i = 0; i < fileSize; i++){
    getline(inputStream, items,',');
    inputStream >> prices;

    if (inputStream.peek()  == '\n'){
      inputStream.ignore();
    }
    itemArray[i] = items;
    priceArray[i]= prices;
  }

  ////////////////////////////////////////
  ////////////getting user input//////////
  ///do while user doesnt select 3/////
  do{
  userMenuSelect=getUserInput();

    switch(userMenuSelect)
      {
      case 1:
        getOrders(itemArray,priceArray);// calls order function
      break;

      case 2:
        viewOrders();// calls view receipt function
      break;

      case 3: ///exit
      cout<<"Thank you for using th True Grit Snack Bar"<<endl;
      break;
      }
  }while(userMenuSelect!= 3);

  return 0;
}

//-------------------------------------
// Name: printWelcome
// Pre:  none
// Post  prints out greeting
//-------------------------------------
void printWelcome(){
  ////prints welcome message once
  cout<<"The item list was successfully loaded"<<endl;
  cout<<"Welcome to the True Grit Snack Bar"<<endl;


}
//---------------------------------------------------
// Name: viewOrders
// Pre:  none
// Post: Print out receipt vertically
//---------------------------------------------
void viewOrders(){
  //////reads in the text file "receipts.txt" that i created in getOrder function
    string getOrder;
    ifstream openfile("receipts.txt");
    if(openfile.is_open())
      {
        while(! openfile.eof())
          {
            openfile >> getOrder;
            cout << getOrder << endl;
          }
      }
  }


//-----------------------------------------------
// Name: getUserInput
// PreCondition: None
// PostCondition returns user input
//------------------------------------------------
int getUserInput(){

  int u; // user's input

  do {
    ///prints out the selection menu//
      cout<<"What would you like to do:"<<endl;
      cout<<"1. New Order"<<endl;
      cout<<"2. View Receipts"<<endl;
      cout<<"3. Exit"<<endl;

      cin >> u;
  } while(u < 1 || u > 3);

  return u;
}


//------------------------------------------------
// Name: getOrders
// Pre:  takes in the array for price and array for item names
// Post: gets user order,and prints subtotal, tax and total, writes in txt file
//----------------------------------------------------
void getOrders(string iArray[10], double pArray[10])
{
  int uInput1=0;// input for first question
  int uInput2=0;// input for second
  char uInput3;// third
  int quantities[3]; //array to hold the user quantities
  int itemChoice[3]; // array to hold users item name
  int itemCounter=0; // counts how mny items user selecter
  double subtotal=0; // subtotal
  double tax=0;      // tax
  cout<<"                   "<<endl;

  do{

   do{
     // prints out chart header and the whole menu
     cout<<"Number        Item             Price"<<endl;

    for( int i = 0; i < 10; i++){

      cout<< i+1<<"        "<<iArray[i]<<"       $ "<<pArray[i]<<endl;

    }
  cout<<"What would you like to buy?:"<<endl;
  cin>>uInput1;
  }while(uInput1 < 1 || uInput1 > 10);

  itemChoice[itemCounter]=uInput1;

  do {

  cout<<"How many would you like to buy?:"<<endl;
  cin>>uInput2;

  }while(uInput2 < 1);

  quantities[itemCounter]=uInput2;

  subtotal= (subtotal)+(pArray[uInput1-1]*uInput2);//computes subtotals

  itemCounter++;
  if(itemCounter <= 2){
  cout<<"Do you want to add more items?:(y/n)"<<endl;
  cin>>uInput3;
  }
  }while(uInput3 != 'n' && itemCounter < 3);

  tax=(subtotal * .06); // computes tax

    //prints chrt header

    cout<<"Your Order:"<<endl;
    cout<<"Qnty"<<"        "<<"Item"<<"        "<<"Price"<<endl;

    //prints out quantity item name and price for each item
    for(int c = 0; c < itemCounter ; c++){

      cout<<quantities[c]<<"        "<<iArray[itemChoice[c]-1]<<"        "<<pArray[itemChoice[c]-1]<<endl;
        }

    //print totals

    cout<<"Subtotal: "<< subtotal<<endl;
    cout<<"Tax: "<<tax<<endl;
    cout<<"Total: "<<(subtotal+tax)<<endl;
    cout<<"Receipt Written"<<endl;

////////Writing in file///
    ofstream myFile;
    myFile.open("receipts.txt");

    for(int p =0; p < itemCounter ; p++){
      myFile<<quantities[p]<<"        "<<iArray[itemChoice[p]-1]<<"        "<<pArray[itemChoice[p]-1]<<endl;
      ///writes in info with for loop
    }
    myFile<<"Subtotal: "<< subtotal<<endl; ///writes in each line
    myFile<<"Tax: "<<tax<<endl;
    myFile<<"Total: "<<(subtotal+tax)<<endl;
    myFile<<"                  "<<endl;

    myFile.close();
}
