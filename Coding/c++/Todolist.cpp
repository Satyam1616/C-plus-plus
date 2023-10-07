#include <iostream>
#include <vector>

void displayToDoList(const std::vector<std::string>& todoList) {
    std::cout << "To-Do List:\n";
    for (size_t i = 0; i < todoList.size(); ++i) {
        std::cout << i + 1 << ". " << todoList[i] << "\n";
    }
}

int main() {
    std::vector<std::string> todoList;

    char choice;
    do {
        std::cout << "\nMENU:\n";
        std::cout << "1. Add item\n";
        std::cout << "2. Display items\n";
        std::cout << "3. Remove item\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1': {
                std::string newItem;
                std::cout << "Enter the item to add: ";
                std::cin.ignore();  // Clear the input buffer
                std::getline(std::cin, newItem);
                todoList.push_back(newItem);
                break;
            }
            case '2':
                displayToDoList(todoList);
                break;

            case '3': {
                int index;
                std::cout << "Enter the index of the item to remove: ";
                std::cin >> index;
                if (index >= 1 && static_cast<size_t>(index) <= todoList.size()) {
                    todoList.erase(todoList.begin() + index - 1);
                    std::cout << "Item removed.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case '4':
                std::cout << "Exiting the program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '4');

    return 0;
}


