#include "addressbookentry.h"
#include <sstream>

atomic_int AddressBookEntry::s_nextId;
//atomic_init(&AddressBookEntry::s_nextId, 0);

AddressBookEntry::AddressBookEntry()
{

}

AddressBookEntry *AddressBookEntry::create()
{
    AddressBookEntry *entry = new AddressBookEntry();
    entry->setId(s_nextId.fetch_add(1));
    return entry;
}
string AddressBookEntry::email() const
{
    return m_email;
}

void AddressBookEntry::setEmail(const string &email)
{
    m_email = email;
}
string AddressBookEntry::name() const
{
    return m_name;
}

void AddressBookEntry::setName(const string &name)
{
    m_name = name;
}
string AddressBookEntry::address() const
{
    return m_address;
}

void AddressBookEntry::setAddress(const string &address)
{
    m_address = address;
}
vector<string> AddressBookEntry::phoneNumbers() const
{
    return m_phoneNumbers;
}
void AddressBookEntry::setPhoneNumbers(const vector<string> &phoneNumbers)
{
    m_phoneNumbers = phoneNumbers;
}
int AddressBookEntry::id() const
{
    return m_id;
}

void AddressBookEntry::setId(int id)
{
    m_id = id;
}

string AddressBookEntry::toString() const
{
    stringstream ss;
    ss << "Entry(id=" << id()
       << ", name=" << name()
       << ", address=" << address()
       << ", email=" << email()
       << ")";
    return ss.str();
}







