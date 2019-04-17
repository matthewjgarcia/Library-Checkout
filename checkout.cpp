// Matthew Garcia
// Section 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}
// this function is used to make life easier by checking the cardholders active and has an id
int checkUser(int person, vector<Person*> &myCardholders) {
  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (myCardholders.at(i)->getId()==person)
    {
      if(myCardholders.at(i)->isActive() == false)
      {
        cout << "Card is not active" << endl;
        return 1;
      }
      else
      {
        cout << "Cardholder: " << myCardholders.at(i)->fullName() << endl;
        return 2;
      }
    }
    else if (myCardholders.size() - 1==i)
    {
      cout << "Card ID not found" << endl;
      return 1;
    }
  }
}

//Function to help and make sure the book is valid

int checkBook(int inputBook, vector<Book*> &myBooks) {
  for(int i = 0; i < myBooks.size(); i++)
  {
    if(myBooks.at(i)->getId()==inputBook)
    {
      Person *temp = myBooks.at(i)->getPersonPtr();
      if(temp == 0)
      {
        cout << "Title: " << myBooks.at(i)->getTitle() << endl;
        return 2; // needed to print out the title using helper function
      }
      else
      {
        cout << "The book has been checked out already" << endl;
        return 1;
      }
    }
    else if (myBooks.size() - 1 ==i)
    {
      cout << "Book ID is not found " << endl;
      return 1;
    }
  }
}


// Function to get the book checked out of the library
void BookCheckout(vector<Book*> myBooks, vector<Person*> &myCardholders) {
  int id = 0;
  int inBook = 0;
  int person = 0;
  int book = 0;
  cout << "Please enter the card ID: ";
  cin >> id; // prompt user to enter number and then have them enter
  person = checkUser(id, myCardholders);
  switch(person) // run a switch statement to get the user to check out the book
  {
    case 1:
    return;
    case 2:
    cout << "Please enter the book ID: ";
    cin >> inBook;
    book = checkBook(inBook, myBooks);
    switch(book)
    {
      case 1:
      return;
      case 2:
      for(int j = 0; j < myBooks.size(); j++)
      {
        if(inBook == myBooks.at(j)->getId())
        {
          for(int k = 0; k < myCardholders.size(); k++)
          {
            if(id == myCardholders.at(k)->getId())
            {
              myBooks.at(j)->setPersonPtr(myCardholders.at(k));
              cout << "Rental complete " << endl;
              return;
            }
          }
        }
      }
      default:
      return;
    }
    return;
    default:
    break;
  }
}

void BookReturn(vector<Book *> & myBooks)
{
  int x = 1;
  int bookID;
  cout << "Enter the book ID to return: "; // prompt user for book ID then have them enter the ID
  cin>> bookID;
  for (int i = 0; i < myBooks.size(); i++)
  {
    if (myBooks.at(i)->getId() == bookID)
    {
      x++;
      cout << "Title: " << myBooks.at(i)->getTitle();
      cout << endl;
      myBooks.at(i)->setPersonPtr(nullptr);
      cout << "Return Completed";
      break;
    }
  }
  if(x == 1)
  {
    cout << "Book ID not found";
  }
}

void viewBooks(vector<Book *> &book)
{
  int temp = 1;
  for (int i = 0; i < book.size(); i++)
  {
    if (book.at(i)->getPersonPtr()==nullptr)
    {
      cout << "Book ID: " << book.at(i)->getId() << endl;
      cout << "Title: " << book.at(i)->getTitle() << endl;
      cout << "Author: "<<book.at(i)->getAuthor() << endl;
      cout << "Category: " << book.at(i)->getCategory() << endl;
      temp = 0; //The temp variable will be changed if the if statement runs but It does not happen

    }
    if (temp == 1) // If it does not go through the if statement then there is no avaliable books
    {
      cout << "No avaliable books";
    }
        return;
  }
}

void viewRentals(vector<Book *> &books, vector <Person *> &myCardholders)
{
  int cnt = 0;
  for (size_t x = 0; x < myCardholders.size(); x++)//needed to run the for loop
  {
    for (int i = 0; i < books.size(); i++)
    {
      if (books.at(i)->getPersonPtr()==nullptr)
      {
        cout << "Book ID: " << books.at(i)->getId() << endl;
        cout << "Title: " << books.at(i)->getTitle() << endl;
        cout << "Author: "<<books.at(i)->getAuthor() << endl;
        cout << "Cardholder: "<<myCardholders.at(x)->fullName() << endl;
        cout << "Card ID: " << myCardholders.at(x)->getId() << endl;
        cout << endl;
        cnt++;
      }
    }
  }
  if (cnt == 0)
  {
    cout << "No outstanding rentals"<< endl;
  }
}

void rentalCardholders(vector<Book *> &books, vector<Person*> &myCardholders)
{
  int cnt = 1;
  int person;
  int id;
  cout << "Enter the card ID: ";
  cin >> id;
  person = checkUser(id, myCardholders);
  switch(person)
  {
    case 1:
    return;
    case 2:
    for (int i = 0; i < books.size(); i++)
    {
      if (books.at(i)->getPersonPtr()!=nullptr)
      {
        Person *temp = books.at(i)->getPersonPtr();
        if (temp->getId() == id)
        {
          cout << endl;
          cout << "Book ID: " << books.at(i)->getId() << endl;
          cout << "Title: " << books.at(i)->getTitle() << endl;
          cout << "Author: "<<books.at(i)->getAuthor() << endl;
          cnt++;
        }
      }
    }
    if (cnt == 1) {
      cout << "No books currently checked out";
    }
  }
}



void closeCard(vector<Person *> & card)
{
  int cnt = 1;
  char choice;
  int id;
  cout << "Please enter the card ID: ";
  cin >> id;
  for (int i = 0; i < card.size(); i++)
  {
    if (id == card.at(i)->getId())
    {
      if (card.at(i)->isActive()==true)
      {
        cout << endl;
        cout << "Cardholder: " << card.at(i)->getFirstName() << " " << card.at(i)->getLastName() << endl;
        cout << "Are you sure you want to deactivate card (y/n)? ";
        cin >> choice;
        if (choice == 'y')
        {
          cout << endl;
          card.at(i)->setActive(0);
          cout << "The card ID is deactivated ";
          cnt++;
          break;
        }
        else if (choice == 'n')
        {
          cnt*=2;
          cout << "Thank you";
          break;
        }
      }
      else if (card.at(i)->isActive()==false)
      {
        cnt=0;
        cout << "Cardholder: " << card.at(i)->getFirstName() << " " << card.at(i)->getLastName() << endl;
        cout << "The card ID is already inactive ";
        break;
      }
    }
  }
  if (cnt == 1)
  {
    cout << endl;
    cout << "Card ID not found ";
  }
}



void readBooks(vector<Book *> & books) {
    int bookID;
    string title;
    string author;
    string cat;
    string garbage; // this is needed to store the white space after the get Line is called

    ifstream inFile;
    inFile.open("books.txt");
    while(inFile >> bookID)
    {
      getline(inFile, garbage); // needed otherwise it couts blank space
      getline(inFile, title);
      getline(inFile, author);
      getline(inFile, cat);
      cout << bookID << " " << title << " "  << author << " " << cat;
      Book *bookPtr = new Book(bookID, title, author, cat); // allows the book to push the items to the pointer
      books.push_back(bookPtr);
    }
}

int readPersons(vector<Person *> & myCardholders) {
    int most = 0;
    int cardID;
    bool active;
    string firstName;
    string lastName;

    ifstream f;
    f.open("persons.txt");
    while(f >> cardID >> active >> firstName >> lastName)
    {
      Person *personPtr = new Person(cardID, active, firstName, lastName);
      myCardholders.push_back(personPtr);
    }
    for (int i = 0; i < myCardholders.size(); i++)
    {
      if (most < myCardholders.at(i)->getId())
      (most=myCardholders.at(i)->getId());
    }

    return most+1;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    ifstream f;
    int bookID, cardID;
    f.open("rentals.txt");
    while (f >> bookID >> cardID){

    for (int i = 0; i <myBooks.size(); i++)
    {
      if (bookID == myBooks.at(i)->getId())
      {
        for (int j = 0; j < myCardholders.size(); j++)
        {
          if (cardID == myCardholders.at(j)->getId())
          {
            myBooks.at(i)->setPersonPtr(myCardholders.at(j));
          }
        }
      }
    }
  }
    f.close();
    return;
}

int openCard(vector<Person *> & myCardholders, int nextID)
{
    string f_name;
    string l_name;
    cout << "Please enter the first name " << endl;
    cin >> f_name;
    cout << "Please enter the last name " << endl;
    cin >> l_name;
    for (int i = 0; i < myCardholders.size(); i++)
    {
      if (f_name == myCardholders.at(i)->getFirstName() && l_name == myCardholders.at(i)-> getLastName())
      {
        myCardholders.at(i)-> setActive(1);
        cout << "Card ID " << myCardholders.at(i)->getId() << " active " << endl;
        cout << "Cardholder " << myCardholders.at(i) ->getFirstName() << " " << myCardholders.at(i)->getLastName() << endl;
        return nextID;
      }
      else if(i == myCardholders.size()-1)
      {
        myCardholders.push_back(new Person(nextID, 1, f_name, l_name));
        cout << "Card ID " << myCardholders.at(i+1)->getId() << " active" << endl;
        cout << "Cardholder: " << myCardholders.at(i+1)->getFirstName() << " " <<myCardholders.at(i+1)->getLastName() << endl;
        return nextID + 1;
      }
    }
  }

  void update(vector<Book*>  &myBooks, vector<Person*> &myCardHolders)
  {
    cout << myCardHolders.size();
    ofstream f;
    f.open("persons.txt");

    for(int i = 0; i < myCardHolders.size(); i++)
    {
      f << myCardHolders.at(i)->getId() << " ";
      if(myCardHolders.at(i)->isActive() == true)
      {
        f << "1" << " " << myCardHolders.at(i)->fullName() << endl;
      }
      else
      {
        f << "0" << " " << myCardHolders.at(i)->fullName() << endl;
      }
    }
    f.close();

    f.open("rentals.txt");
    for(int i = 0; i < myBooks.size(); i++)
    {
      if(myBooks.at(i)->getPersonPtr() != nullptr)
      {
        Person *temp = myBooks.at(i)->getPersonPtr();
        f << myBooks.at(i)->getId() << " " << temp->getId() << endl;
      }
    }
    f.close();
  }





int main()
{
    int nextID = 0;
    vector<Book *> books;
    vector<Person *> cardholders;
    nextID= readPersons(cardholders);
    readRentals(books,cardholders);

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
                BookCheckout(books,cardholders);
                break;

            case 2:
                BookReturn(books);
                break;

            case 3:
                viewBooks(books);
                break;

            case 4:
                viewRentals(books, cardholders);
                break;

            case 5:
                rentalCardholders(books,cardholders);
                break;

            case 6:
                nextID=openCard(cardholders, nextID);
                break;

            case 7:
                closeCard(cardholders);
                break;

            case 8:
                update(books,cardholders);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
