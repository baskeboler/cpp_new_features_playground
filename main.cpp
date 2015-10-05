#include <iostream>
#include <array>
#include "addressbook.h"

using namespace std;
AddressBook addresses;

int main()
{
    cout << "Hello World!" << endl;
    unique_ptr<AddressBookEntryBuilder> builder(new AddressBookEntryBuilder());
    auto entry = builder->withAddress("address1")
            ->withEmail("baskeboler@gmail.com")
            ->withName("Victor")
            ->build();

    addresses.addEntry(*entry);

    builder->reset();
    entry = builder->withAddress("address2")
            ->withEmail("rober@gmail.com")
            ->withName("Roberto")
            ->build();


    addresses.addEntry(*entry);
    builder->reset();
    for (int i=0; i < 1000; i++) {
        //entry = AddressBookEntry::create();
        string address = "address" + to_string(i);
        string name = "RandomDude" + to_string(i);
        entry = builder->withAddress(address)
                ->withEmail(name + "@gmail.com")
                ->withName(name)
                ->build();
        addresses.addEntry(*entry);
        builder->reset();
    }

    addresses.printAddressBook();

    auto f = [](const AddressBookEntry& e) {return e.id() < 10;};

    cout << "Calling find()" << endl;
    vector<AddressBookEntry> res = addresses.find(f);
    for (auto const &e: res ) {
        cout << e.toString() << endl;
    }
    return 0;
}

