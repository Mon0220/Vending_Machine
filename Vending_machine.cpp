#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;
class Item { 
public:
    string code, name, category;
    double price;
    int stock;

    Item(string c, string n, string cat, double p, int s)
        : code(c), name(n), category(cat), price(p), stock(s) {}
};

class VendingMachine {
private:
    vector<Item> items;

    // Find item by code, return index or -1 if not found
    int findItem(const string& code) const {
        for (int i = 0; i < (int)items.size(); i++)
            if (items[i].code == code) return i;
        return -1;
    }

    // Print pounds (£) nicely
    void money(double x) const {
        cout << "£" << fixed << setprecision(2) << x;
    }

    // Display all items (category shown on each line)
    void menu() const {
        cout << "\n========== VENDING MACHINE ==========\n";
        for (const auto& it : items) {
            cout << it.code << " | " << it.category << " | " << it.name << " | ";
            money(it.price);
            cout << " | Stock: " << it.stock << "\n";
        }
        cout << "Enter item code or Q to quit\n";
        cout << "=====================================\n";
    }

    // Read money in pounds and validate
    double readMoney() const {
        while (true) {
            cout << "Insert money (e.g. 2.50): £";
            double m;
            cin >> m;

            if (cin.fail() || m <= 0) {
                cout << "Invalid amount. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                return m;
            }
        }
    }

public:
    VendingMachine() {
        // code, name, category, price (£), stock
        items.push_back(Item("A1", "Coke",      "Drinks", 2.00, 5));
        items.push_back(Item("A2", "Water",     "Drinks", 1.50, 5));
        items.push_back(Item("A3", "Coffee",    "Drinks", 2.20, 4));
        items.push_back(Item("B1", "Crisps",    "Snacks", 1.80, 6));
        items.push_back(Item("B2", "Chocolate", "Snacks", 1.60, 3));
        items.push_back(Item("B3", "Biscuits",  "Snacks", 1.20, 2));
    }

    void run() {
        while (true) {
            menu();

            cout << "Your choice: ";
            string code;
            cin >> code;

            if (code == "Q" || code == "q") break;

            int i = findItem(code);
            if (i == -1) { cout << "Invalid code.\n"; continue; }
            if (items[i].stock <= 0) { cout << "Out of stock.\n"; continue; }

            cout << "Selected: " << items[i].name << " (";
            money(items[i].price);
            cout << ")\n";

            double paid = readMoney();

            // Small buffer avoids floating-point comparison issues
            if (paid + 1e-9 < items[i].price) {
                cout << "Not enough money. Returning ";
                money(paid);
                cout << "\n";
                continue;
            }

            // Dispense + reduce stock
            items[i].stock--;
            cout << ">>> " << items[i].name << " has been dispensed! <<<\n";

            // Change
            double change = paid - items[i].price;
            cout << "Your change is: ";
            money(change);
            cout << "\n";
        }

        cout << "Thank you!\n";
    }
};

int main() {
    VendingMachine vm;
    vm.run();
    return 0;
}

