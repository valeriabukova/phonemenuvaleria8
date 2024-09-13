//
//  main.cpp
//  phonemenuvaleria8
//
//  Created by Valeria  Bukova on 13.09.2024.
//

#include <iostream>
///Задание.
///Создайте приложение "Телефонная книга". Необходимо хранить данные об абоненте (ФИО, домашний телефон, рабочий телефон, мобильный телефон, дополнительная информация о контакте) внутри соответствующего класса. Наполните класс переменными-членами, функциями-членами, констру- кторами, реализуйте деструктор. Обязательно необходимо выделять динамически память под ФИО. Предоставьте пользователю возможность добавлять новых абонентов, удалять абонентов, искать абонентов по ФИО, показывать всех абонентов, сохранять информацию в файл и загружать из файла.///
class Contact
{
    char* name;
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char additionalInfo[100];

    
    void copyString(char* dest, const char* src)
    {
        int i = 0;
        while (src[i] != '\0')
        {
            dest[i] = src[i];
            ++i;
        }
        dest[i] = '\0';
    }

    
    int compareString(const char* str1, const char* str2) const
    {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
        {
            ++i;
        }
        return str1[i] - str2[i];
    }

public:
    
    Contact(const char* n = "", const char* home = "", const char* work = "", const char* mobile = "", const char* info = "")
    {
        name = new char[100];
        copyString(name, n);
        copyString(homePhone, home);
        copyString(workPhone, work);
        copyString(mobilePhone, mobile);
        copyString(additionalInfo, info);
    }

    
    ~Contact()
    {
        delete[] name;
    }

   
    void setContact(const char* n, const char* home, const char* work, const char* mobile, const char* info)
    {
        copyString(name, n);
        copyString(homePhone, home);
        copyString(workPhone, work);
        copyString(mobilePhone, mobile);
        copyString(additionalInfo, info);
    }

    
    const char* getName() const
    {
        return name;
    }

    
    void displayContact() const
    {
        std::cout << "Name: " << name << "\n"
                  << "Home Phone: " << homePhone << "\n"
                  << "Work Phone: " << workPhone << "\n"
                  << "Mobile Phone: " << mobilePhone << "\n"
                  << "Additional Info: " << additionalInfo << "\n";
    }

   
    bool compareName(const char* n) const
    {
        return compareString(name, n) == 0;
    }
};

class PhoneBook
{
    Contact* contacts[100];
    int count;

public:
    PhoneBook() : count(0) {}

    ~PhoneBook()
    {
        for (int i = 0; i < count; ++i)
        {
            delete contacts[i];
        }
    }

  
    void addContact()
    {
        char name[100], home[20], work[20], mobile[20], info[100];
        std::cout << "Enter name: ";
        std::cin.ignore();
        std::cin.getline(name, 100);
        std::cout << "Enter home phone: ";
        std::cin.getline(home, 20);
        std::cout << "Enter work phone: ";
        std::cin.getline(work, 20);
        std::cout << "Enter mobile phone: ";
        std::cin.getline(mobile, 20);
        std::cout << "Enter additional info: ";
        std::cin.getline(info, 100);

        contacts[count++] = new Contact(name, home, work, mobile, info);
    }

    
    void deleteContact()
    {
        char name[100];
        std::cout << "Enter name of contact to delete: ";
        std::cin.ignore();
        std::cin.getline(name, 100);

        for (int i = 0; i < count; ++i)
        {
            if (contacts[i]->compareName(name))
            {
                delete contacts[i];
                for (int j = i; j < count - 1; ++j)
                {
                    contacts[j] = contacts[j + 1];
                }
                --count;
                std::cout << "Contact deleted.\n";
                return;
            }
        }
        std::cout << "Contact not found.\n";
    }

   
    void searchContact() const
    {
        char name[100];
        std::cout << "Enter name of contact to search: ";
        std::cin.ignore();
        std::cin.getline(name, 100);

        for (int i = 0; i < count; ++i)
        {
            if (contacts[i]->compareName(name))
            {
                contacts[i]->displayContact();
                return;
            }
        }
        std::cout << "Contact not found.\n";
    }

    
    void displayAll() const
    {
        for (int i = 0; i < count; ++i)
        {
            contacts[i]->displayContact();
            std::cout << "-------------------------\n";
        }
    }
};

int main()
{
    PhoneBook phoneBook;
    int choice;

    do
    {
        std::cout << "\nMenu NotebookPhone:\n"
                  << "1. Add Contact\n"
                  << "2. Delete Contact\n"
                  << "3. Search Contact\n"
                  << "4. Display All Contacts\n"
                  << "0. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1: phoneBook.addContact(); break;
            case 2: phoneBook.deleteContact(); break;
            case 3: phoneBook.searchContact(); break;
            case 4: phoneBook.displayAll(); break;
            case 0: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n";
                
        }
    }
    while (choice != 0);

    return 0;
}
