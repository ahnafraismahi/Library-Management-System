
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;

class Library
{
    int BookId;
    char Title[20];
    char Author[20];
    char Category[20];
    int Pages;
    float Edition;

public:
    // Accessor functions
    int getID()
    {
        return BookId;
    }
    char* getTitle()
    {
        return Title;
    }
    char* getAuthor()
    {
        return Author;
    }
    char* getCategory()
    {
        return Category;
    }
    float getEdition()
    {
        return Edition;
    }

    // Default constructor
    Library()
    {
        BookId = 0;
        strcpy(Title, "");
        strcpy(Author, "");
        strcpy(Category, "");
        Pages = 0;
        Edition = 0;
    }

    void getBook();
    void showBook();
    static void header();
    void listView();
};

void Library::getBook()
{
    cout << "\tEnter Book Id: ";
    cin >> BookId;
    cout << "\tEnter Book Title: ";
    cin.ignore();
    cin.getline(Title, 20);
    cout << "\tEnter Book Author: ";
    cin.getline(Author, 20);
    cout << "\tEnter Book Category: ";
    cin.getline(Category, 20);
    cout << "\tEnter No of pages: ";
    cin >> Pages;
    cout << "\tEnter date of Edition: ";
    cin >> Edition;
    cout << endl;
}

void Library::showBook()
{
    cout << endl;
    cout << "Book Id: " << BookId << endl;
    cout << "Book Title: " << Title << endl;
    cout << "Author Name: " << Author << endl;
    cout << "Category: " << Category << endl;
    cout << "No of Pages: " << Pages << endl;
    cout << "Edition: " << Edition << endl;
}

void Library::header()
{
    cout.setf(ios::left);
    cout << setw(5) << "I.D."
         << setw(20) << "Book Title"
         << setw(20) << "Book Author"
         << setw(15) << "Category"
         << setw(6) << "Pages"
         << setw(6) << "Edition" << endl;

    for (int i = 1; i <= 72; i++)
    {
        cout << "=";
    }
    cout << endl;
}

void Library::listView()
{
    cout.setf(ios::left);
    cout << setw(5) << BookId
         << setw(20) << Title
         << setw(20) << Author
         << setw(15) << Category
         << setw(6) << Pages
         << setw(6) << Edition << endl;
}

void drawline(char);
void heading();
void menu();
void searchMenu();
void addBook();
void displayBooks();
void searchById();
void searchByTitle();
void searchByCategory();
void searchByAuthor();
void dispose();
void modify();
void displayDisposed();

void drawline(char ch)
{
    for (int i = 1; i < 80; i++)
    {
        cout << ch;
    }
    cout << endl;
}

void heading()
{
    drawline('+');
    cout << "\t\t LIBRARY MANAGEMENT SYSTEM\n";
    drawline('+');
}

void addBook()
{
    ofstream fout;
    fout.open("books.dat", ios::app);
    Library l;
    l.getBook();
    fout.write((char*)&l, sizeof(l));
    cout << "Book data saved in file." << endl;
    fout.close();
}

void displayBooks()
{
    ifstream fin("books.dat");
    int rec = 0;
    Library l;
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (rec < 1)
            l.header();
        l.listView();
        rec++;
    }
    fin.close();
    cout << "\nTotal " << rec << " records in file." << endl;
}

void searchById()
{
    int n, flag = 0;
    ifstream fin("books.dat");
    Library l;
    cout << "Enter Book Id: ";
    cin >> n;
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (n == l.getID())
        {
            l.showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Id " << n << " not available." << endl;
}

void searchByTitle()
{
    int flag = 0;
    char title[20];
    ifstream fin("books.dat");
    Library l;
    cout << "Enter Book Title: ";
    cin.ignore();
    cin.getline(title, 20);
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (strcmpi(title, l.getTitle()) == 0)
        {
            l.showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with title " << title << " not available." << endl;
}

void searchByCategory()
{
    int flag = 0, rec = 0;
    char cat[20];
    ifstream fin("books.dat");
    Library l;
    cout << "Enter Book Category: ";
    cin.ignore();
    cin.getline(cat, 20);
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (strcmpi(cat, l.getCategory()) == 0)
        {
            if (rec < 1)
                l.header();
            l.listView();
            flag++;
            rec++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with category " << cat << " not available." << endl;
}

void searchByAuthor()
{
    int flag = 0, rec = 0;
    char aut[20];
    ifstream fin("books.dat");
    Library l;
    cout << "Enter Book Author: ";
    cin.ignore();
    cin.getline(aut, 20);
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (strcmpi(aut, l.getAuthor()) == 0)
        {
            if (rec < 1)
                l.header();
            l.listView();
            flag++;
            rec++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Author " << aut << " not available." << endl;
}

void dispose()
{
    int n, flag = 0;
    ifstream fin("books.dat");
    ofstream fout("dispose.txt", ios::out);
    Library l;
    cout << "Enter Book Id: ";
    cin >> n;
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (n == l.getID())
        {
            l.showBook();
            flag++;
        }
        else
        {
            fout.write((char*)&l, sizeof(l));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "Book with Id " << n << " not available." << endl;
    else
        cout << "Book with Id " << n << " disposed." << endl;
}

void modify()
{
    int n, pos, flag = 0;
    fstream fin("books.dat", ios::in | ios::out);
    Library l;
    cout << "Enter Book Id: ";
    cin >> n;
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (n == l.getID())
        {
            pos = fin.tellg();
            cout << "Following data will be edited:" << endl;
            l.showBook();
            flag++;
            fin.seekg(pos - sizeof(l));
            l.getBook();
            fin.write((char*)&l, sizeof(l));
            cout << "Data modified successfully." << endl;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Id " << n << " not available." << endl;
}

void displayDisposed()
{
    ifstream fin("dispose.txt");
    int rec = 0;
    Library l;
    while (fin.read((char*)&l, sizeof(l)))
    {
        if (rec < 1)
            l.header();
        l.listView();
        rec++;
    }
    fin.close();
    cout << "\nTotal " << rec << " records disposed off file." << endl;
}

void menu()
{
    int ch;
    do
    {
        system("cls");
        heading();
        cout << "0. EXIT" << endl;
        cout << "1. ADD New BOOK" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Search Books" << endl;
        cout << "4. Dispose Off Books" << endl;
        cout << "5. Modify Details" << endl;
        cout << "6. List of Disposed Books" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        system("cls");
        heading();
        switch (ch)
        {
        case 1:
            system("color 5E");
            addBook();
            break;
        case 2:
            system("color 5F");
            displayBooks();
            break;
        case 3:
            system("color 6E");
            searchMenu();
            break;
        case 4:
            system("color 6F");
            dispose();
            break;
        case 5:
            system("color 4E");
            modify();
            break;
        case 6:
            system("color 4F");
            displayDisposed();
            break;
        }
        system("pause");
    } while (ch != 0);
}

void searchMenu()
{
    int ch;
    do
    {
        system("cls");
        heading();
        cout << "Book search options" << endl;
        cout << "0. Back" << endl;
        cout << "1. By Id" << endl;
        cout << "2. By Title" << endl;
        cout << "3. By Category" << endl;
        cout << "4. By Author" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        system("cls");
        heading();
        switch (ch)
        {
        case 1:
            system("color 5E");
            searchById();
            break;
        case 2:
            system("color 6E");
            searchByTitle();
            break;
        case 3:
            system("color 5F");
            searchByCategory();
            break;
        case 4:
            system("color 6F");
            searchByAuthor();
            break;
        default:
            cout << "\a";
        }
        system("pause");
    } while (ch != 0);
}

int main()
{
    menu();
    return 0;
}
