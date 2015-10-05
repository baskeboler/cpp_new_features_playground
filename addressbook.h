#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <map>
#include <vector>
#include <functional>

#include "addressbookentry.h"
using namespace std;

class AddressBook
{
public:
    AddressBook();

    void addEntry(const AddressBookEntry& entry);
    void printAddressBook();

    vector<AddressBookEntry> find(function<bool (const AddressBookEntry&)> func);

private:
    map<int, AddressBookEntry> m_entries;
};


#endif // ADDRESSBOOK_H
