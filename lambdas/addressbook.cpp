#include "addressbook.h"
#include <iostream>

AddressBook::AddressBook()
{

}

void AddressBook::addEntry(const AddressBookEntry &entry)
{
    this->m_entries[entry.id()] = entry;

}

void AddressBook::printAddressBook()
{
    cout << "Printing entries: " << endl;
    for (auto const &entry: m_entries) {
        cout << entry.second.toString() << endl;
    }

}

vector<AddressBookEntry> AddressBook::find(function<bool (const AddressBookEntry &)> func)
{
    vector<AddressBookEntry> result;
    for(auto const& mapEntry : m_entries) {
        if (func(mapEntry.second)) {
            result.push_back(mapEntry.second);
        }
    }
    return result;

}

