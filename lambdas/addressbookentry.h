#ifndef ADDRESSBOOKENTRY_H
#define ADDRESSBOOKENTRY_H

#include <string>
#include <map>
#include <vector>
#include <atomic>
#include <memory>

using namespace std;

class AddressBookEntry
{
public:
    AddressBookEntry();
    static AddressBookEntry* create();

    string email() const;
    void setEmail(const string &email);

    string name() const;
    void setName(const string &name);

    string address() const;
    void setAddress(const string &address);

    vector<string> phoneNumbers() const;

    void setPhoneNumbers(const vector<string> &phoneNumbers);

    int id() const;
    void setId(int id);

    string toString() const;

private:
    int m_id;
    string m_name;
    string m_email;
    string m_address;
    vector<string> m_phoneNumbers;

    static atomic_int s_nextId;

};


class AddressBookEntryBuilder {
public:
    AddressBookEntryBuilder() {
        this->entry = make_shared<AddressBookEntry>(*AddressBookEntry::create());
    }

    AddressBookEntryBuilder* withName(const string& name) {
        this->entry->setName(name);
        return this;
    }

    AddressBookEntryBuilder* withEmail(const string& email) {
        this->entry->setEmail(email);
        return this;
    }

    AddressBookEntryBuilder* withAddress(const string& address) {
        this->entry->setAddress(address);
        return this;
    }

    shared_ptr<AddressBookEntry> build() {
        return entry;
    }

    void reset() {
        this->entry.reset(AddressBookEntry::create());
    }

private:
    shared_ptr<AddressBookEntry> entry;
};
#endif // ADDRESSBOOKENTRY_H
