// Tera Parish
// TXP200011

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// structure for node
struct node
{
    string arabic;
    string roman;
    node *next= nullptr;
};

// function prototypes
void createNode(node *&, string);
bool searchArabic(node *, int);
bool searchRoman(node *, string);
node* sortList(node*&, int);
void print2console(node *, int);
void print2file(node *, ofstream&);
// functions from project 1
bool val_arabic(string);
bool val_roman(string);
string toRoman(int);
string toArabic(string);

int main()
{
    node *head=nullptr, *end= nullptr;
    string name_inputFile, line;

    // prompt for file name
    cout <<"Enter the name of the file:";
    cin >> name_inputFile;
    // open the input file
    ifstream inputFile(name_inputFile);
    ofstream outputFile("numbers.txt");

    // check if the file opened successfully
    if(inputFile)
    {
        // read til eof
        while (inputFile>> line)
            createNode(head, line);
    }

    int choice;
    //display the menu
    cout<< "Menu options:\n";
    cout<< "1. search\n";
    cout<< "2. sort\n";
    cout<< "3. exit\n";
    //prompt for choice
    cout<< "Enter your choice of option: ";
    cin >> choice;
    cout<<endl;

    while (choice!=3)
    {
        if (choice==1) //searching
        {
            string searchVal;
            cout<< "Enter a number to be searched: ";
            cin>> searchVal;
            if(isdigit(searchVal[0])) //search for arabic
            {
                int arabicNUM= stoi(searchVal);
                if (searchArabic(head, arabicNUM))
                    cout<< arabicNUM<< " found\n";

                // not in the range of 1 – 4999
                else if (arabicNUM==0)
                    cout<< arabicNUM<< " not found\n";

                else
                    cout<< arabicNUM<< " not found\n";
            }

            else //search for roman
            {
                if (searchRoman(head, searchVal))
                    cout<< searchVal<< " found\n";

                // not in the range of 1 – 4999
                else if (searchVal=="MMMM")
                    cout<< searchVal<< " not found\n";

                else
                    cout<< searchVal<< " not found\n";
            }
        }

        else if (choice ==2) //sorting
        {
            int choice_sort;
            cout<< "How would you like the list sorted by?\n";
            cout<< "1. sort by Roman numeral\n";
            cout<< "2. sort by Arabic numeral\n";
            cin>> choice_sort;

            head= sortList(head, choice_sort);

            //display sorted list to the console
            print2console(head, choice_sort);
        }

        // run til user enter 3 to exit the program
        cout<< "\nMenu options:\n";
        cout<< "1. search\n";
        cout<< "2. sort\n";
        cout<< "3. exit\n";
        cout<< "Enter your choice of option: ";
        cin >> choice;
    }

    cout<< endl;
    // output the sorted list to the console
    // and store the list to a file
    print2file(head, outputFile);

    // close the files
    inputFile.close();
    outputFile.close();
    return 0;
}

bool val_arabic(string arabic)
{
    int a, space=0;

    // if the line is empty, return false
    for (a=0; a<arabic.length();a++)
    {
        if (isspace(arabic[a]))
            space+=1;

        if (space==20)
            return false;
    }

    // if value is not in the range 1- 4999
    for (int index=16; index<21; index++)
    {
        if (isspace(arabic[index-1]) && arabic[index]=='0')
            return false;
    }

    // if value is not in the range 1- 4999
    if (stoi(arabic)>4999)
        return false;

    // if invalid charters, return false
    for (a=0; a<arabic.length();a++)
    {
        if(!isdigit(arabic[a] ) && !isspace(arabic[a]))
            return false;
    }

    return true;
}

bool val_roman(string roman)
{
    int M_count=0;

    for (int r=0; r<roman.length(); r++)
    {
        if (roman[r]=='M')
            M_count++;

        // if character is not M, D, C, L, X, V, I, or space, return false
        if (roman[r] !='M' &&roman[r] !='D' &&roman[r] !='C' &&roman[r] !='L' &&
            roman[r] !='X' &&roman[r] !='V' &&roman[r] !='I' &&!isspace(roman[r]))
            return false;
    }
    // if the value is not in the range 1- 4999
    if (M_count>=4)
        return false;

    return true;
}

string toRoman(int arabic_num)
{
    string Roman;

    // count 1000s, 100s, 10s, n 1s
    int count_1000=arabic_num/1000;
    int count_100= arabic_num%1000/100;
    int count_10= arabic_num%1000%100/10;
    int count_1 = arabic_num%1000%100%10;

    for (int m=1; m<=count_1000; m++)
        Roman+= 'M';

    if(count_100<4)
    {
        for (int c=1; c<=count_100; c++)
            Roman+= 'C';
    }

    if (count_100==4)
        Roman+="CD";

    if (count_100==5)
        Roman+="D";

    if (count_100>5 && count_100<9)
    {
        Roman+="D";
        count_100 -= 5;
        for (int d=1; d<=count_100; d++)
            Roman+= "C";
    }

    if (count_100==9)
        Roman+= "CM";

    if (count_10<4)
    {
        for (int x=1; x<=count_10; x++)
            Roman+= "X";
    }

    if (count_10==4)
        Roman+= "XL";

    if (count_10==5)
        Roman+= "L";

    if (count_10>5 && count_10<9)
    {
        Roman+="L";
        count_10 -= 5;
        for (int l=1; l<=count_10; l++)
            Roman+= "X";
    }

    if (count_10==9)
        Roman+= "XC";

    if (count_1<4)
    {
        for (int i=1; i<=count_1; i++)
            Roman+= 'I';
    }

    if (count_1==4)
        Roman+= "IV";

    if (count_1==5)
        Roman+="V";

    if (count_1>5 && count_1<9)
    {
        Roman+="V";
        count_1 -= 5;
        for (int v=1; v<=count_1; v++)
            Roman+= "I";
    }

    if (count_1==9)
        Roman+= "IX";

    return Roman;
}

string toArabic(string roman_num)
{
    int sum = 0;
    string to_arabic;

    for (int i = 0; i < roman_num.length(); i++)
    {
        if (roman_num[i] == 'M')
            sum += 1000;

        if (roman_num[i] == 'D')
            sum += 500;

        if (roman_num[i] == 'C')
        {
            if (roman_num[i+1] == 'D')
                sum -= 100;

            else if (roman_num[i+1] == 'M')
                sum -= 100;

            else
                sum += 100;
        }

        if (roman_num[i] == 'L')
            sum += 50;

        if (roman_num[i] == 'X')
        {
            if (roman_num[i+1] == 'L')
                sum -= 10;

            else if (roman_num[i+1] == 'C')
                sum -= 10;

            else
                sum += 10;

        }

        if (roman_num[i] == 'V')
            sum += 5;


        if (roman_num[i] == 'I')
        {
            if (roman_num[i+1] == 'X' || roman_num[i+1] == 'V')
                sum -= 1;

            else
                sum += 1;
        }
    }

    to_arabic= to_string(sum);
    return to_arabic;
}

void createNode(node *&head, string input)
{
    node *data= new node;

    // input is arabic
    if (isdigit(input[0]))
    {
        //check if input is valid
        if (val_arabic(input))
        {
            // convert arabic nums from string to int
            int arabicNum= stoi(input);

            // store values to a node
            data->arabic= input;
            data->roman= toRoman(arabicNum);

            // add new node to the beginning of the list
            data->next= head;
            head= data;
        }
    }

    // input is roman
    else
    {
        // check if input is valid
        if (val_roman(input))
        {
            // store values to a node
            data->arabic= toArabic(input);
            data->roman= input;

            // add new node to the beginning of the list
            data->next= head;
            head= data;
        }
    }
}

bool searchArabic(node *head, int search_arabic)
{
    bool result_arabic= false;
    node *search= head;
    // linear search
    while(search!= nullptr)
    {
        if (stoi(search->arabic) == search_arabic)
            return result_arabic= true;

        search = search->next;
    }
    return result_arabic;
}

bool searchRoman(node *head, string search_roman )
{
    bool result_roman= false;
    node *search= head;
    // linear search
    while(search!= nullptr)
    {
        if ((search->roman) == search_roman)
            return result_roman= true;

        search = search->next;
    }
    return result_roman;
}

//selection sort
node* sortList(node *&head, int sort_choice)
{
    node* min;           // point to the node with min value
    node* prev;          // point to the node before min
    node* prevItem;      // point to the node before current item
    node* sorted= nullptr; // point to the sorted node

    if (sort_choice==1)  //by roman
    {

        // move boundary of unsorted subarray
        for (node* start = head; start!= nullptr; start = sorted->next)
        {
            min = prev = prevItem = nullptr;

            // find the min in unsorted array
            for (node* item = start; item!= nullptr; item = item->next)
            {
                if (min == nullptr || item->roman < min->roman)
                {
                    // update the min node
                    min = item;
                    prev = prevItem;
                }
                prevItem = item;
            }

            // if the min value node is not at the beginning
            if (min != start)
            {
                // swap the head with the min node
                prev->next = min->next;
                min->next = start;

                if (sorted)
                    sorted->next = min;
                else
                    head = min;
            }
            sorted = min;
        }
    }

    else  //by arabic
    {
        for (node* start = head; start!= nullptr; start = sorted->next)
        {
            min = prev = prevItem = nullptr;
            for (node* item = start; item!= nullptr; item = item->next)
            {
                if (min == nullptr || stoi(item->arabic) < stoi(min->arabic))
                {
                    min = item;
                    prev = prevItem;
                }
                prevItem = item;
            }

            if (min != start)
            {
                prev->next = min->next;
                min->next = start;

                if (sorted)
                    sorted->next = min;
                else
                    head = min;
            }
            sorted = min;
        }
    }
    return head;
}

void print2console(node *head, int sort_choice)
{
    node *print=head;

    if (sort_choice==1)  //by roman
    {
        // reach the end of the list
        if(print== nullptr)
            return;

        else
        {
            cout<< print->roman<< endl;
            print2console(print->next, sort_choice);
        }
    }

    else if(sort_choice==2) //by arabic
    {
        // reach the end of the list
        if(print== nullptr)
            return;

        else
        {
            cout<< print->arabic<< endl;
            print2console(print->next, sort_choice);
        }
    }
}

void print2file(node *head, ofstream &out)
{
    node *print=head;

    // reach the end of the list
    if(print== nullptr)
        return;

    else
    {
        string  roman_16= print->roman,
                arabic_4= print->arabic,
                space_roman, space_arabic;

        // fill up the roman field with space
        if (roman_16.length()<16)
        {
            for (int i=0; i< 16-roman_16.length(); i++)
                space_roman.push_back(' ');
        }
        roman_16= roman_16+space_roman;

        // fill up the arabic field with space
        if (arabic_4.length()<4)
        {
            for (int j=0; j<4- arabic_4.length(); j++)
                space_arabic.push_back(' ');
        }
        arabic_4= arabic_4+ space_arabic;

        // format the output
        print->arabic= arabic_4;
        print->roman= roman_16;

        cout<< print->roman<< print->arabic<< endl;
        out<< print->roman<< print->arabic<< endl;
        print2file(print->next, out);
    }
}