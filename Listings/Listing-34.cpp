#include "Listing-33.h"

#include <string.h>

struct DBRecord // (1)
{
    char firstName[50];
    char lastName[50];
};

bool CompareByFirstName(const DBRecord& rec1, const DBRecord& rec2) // (2)
{
    return strcmp(rec1.firstName, rec2.firstName) < 0;
}

bool CompareByLastName(const DBRecord& rec1, const DBRecord& rec2) // (3)
{
    return strcmp(rec1.lastName, rec2.lastName) < 0;
}

class SortRules // (4)
{
public:
    enum { SORT_ASC = 1, SORT_DESC = 2 } sortDirect; // (5)
    enum { SORT_FIRST_NAME = 1, SORT_LAST_NAME = 2 } sortWhat; // (6)

    bool operator () (const DBRecord& rec1, const DBRecord& rec2) const // (7)
    {
        if (sortDirect == SORT_ASC)
        {
            if (sortWhat == SORT_FIRST_NAME)
            {
                return strcmp(rec1.firstName, rec2.firstName) < 0;
            }
            else
            {
                return strcmp(rec1.lastName, rec2.lastName) < 0;
            }
        }
        else
        {
            if (sortWhat == SORT_FIRST_NAME)
            {
                return strcmp(rec1.firstName, rec2.firstName) > 0;
            }
            else
            {
                return strcmp(rec1.lastName, rec2.lastName) > 0;
            }
        }
    }
};

int main()
{
    DBRecord dbRecArray[10]; // (8)
    //Read from database

    sort_bubble(dbRecArray, 10, CompareByFirstName);  // (9)
    sort_bubble(dbRecArray, 10, CompareByLastName);   // (10)

    sort_bubble(dbRecArray, 10, [](const DBRecord& rec1, const DBRecord& rec2) // (11)
        {
            return strcmp(rec1.firstName, rec2.firstName) < 0;
        });
    sort_bubble(dbRecArray, 10, [](const DBRecord& rec1, const DBRecord& rec2) // (12)
        {
            return strcmp(rec1.lastName, rec2.lastName) < 0;
        });

    SortRules rules; // (13)
    rules.sortWhat = SortRules::SORT_LAST_NAME; // (14)
    rules.sortDirect = SortRules::SORT_ASC;               // (15)
    sort_bubble(dbRecArray, 10, rules); // (16)
}
