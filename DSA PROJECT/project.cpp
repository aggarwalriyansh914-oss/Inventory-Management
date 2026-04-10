#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;


struct Product {
    int id;
    string name;
    int qty;
    float price;
    int sold;
};


vector<Product> items;// stores inventory


vector<pair<int,int>> cart;// cart store karega
stack<vector<pair<int,int>>> cartUndo;// cart undo 


queue<vector<pair<int,int>>> orders;// orders


stack<vector<Product>> invUndo;// inventory undo


//Add Product
void addProduct(int id, string name, int qty, float price) {
    Product p;

    p.id = id;
    p.name = name;
    p.qty = qty;
    p.price = price;
    p.sold = 0;
    items.push_back(p);
}



int findProduct(int id) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i].id == id)
            return i;
    }
    return -1;
}


//adding to cart
void saveCart() {
    cartUndo.push(cart);
}

void addCart(int id, int q) {
    saveCart();
    cart.push_back({id, q});
    cout << "Added to cart\n";
}

void undoCart() {
    if (!cartUndo.empty()) {
        cart = cartUndo.top();
        cartUndo.pop();
        cout << "Cart undo done\n";
    } else {
        cout << "Nothing to undo\n";
    }
}


//placing order
void placeOrder() {
    if (cart.empty()) {
        cout << "Cart empty\n";
        return;
    }

    orders.push(cart);
    cart.clear();

    cout << "Order placed\n";
}


//bill generation
void processOrder() {
    if (orders.empty()) {
        cout << "No orders\n";
        return;
    }

    invUndo.push(items);

    vector<pair<int,int>> ord = orders.front();
    orders.pop();

    float total = 0;

    cout << "\n*** BILL ***\n";

    for (int i = 0; i < ord.size(); i++) {
        int id = ord[i].first;
        int q = ord[i].second;

        int idx = findProduct(id);

        if (idx != -1 && items[idx].qty >= q) {
            float cost = items[idx].price * q;

            cout << items[idx].name << " x "
                 << q << " = " << cost << endl;

            items[idx].qty -= q;
            items[idx].sold += q;

            total += cost;
        } else {
            cout << "Item not available: " << id << endl;
        }
    }

    cout << "Total = " << total << endl;
}


//undo feature
void undoLast() {
    if (!invUndo.empty()) {
        items = invUndo.top();
        invUndo.pop();
        cout << "Undo successful\n";
    } else {
        cout << "Nothing to undo\n";
    }
}


// searching product by name
void searchName(string name) {
    cout << "\nSearch result:\n";

    for (int i = 0; i < items.size(); i++) {
        if (items[i].name == name) {
            cout << items[i].name
                 << " | Qty: " << items[i].qty << endl;
        }
    }
}


//displaying inventory
void showInventory() {
    if (items.size()<1){
        cout<<endl<<"Please Add a Product into the inventory first."<<endl;
        return;
    }
    cout << "\n--- Inventory ---\n";

    for (int i = 0; i < items.size(); i++) {
        cout << items[i].id << " "
             << items[i].name << " "
             << items[i].qty << " "
             << items[i].price << " "<<endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n*** MENU ***\n";
        cout << "1. Add Product\n";
        cout << "2. Show Inventory\n";
        cout << "3. Add to Cart\n";
        cout << "4. Undo Cart\n";
        cout << "5. Place Order\n";
        cout << "6. Process Order\n";
        cout << "7. Undo Transaction\n";
        cout << "8. Search Product by Name\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, q;
            float price;
            string name;

            cout << "Enter ID | Name | Qty | Price : ";
            cin >> id >> name >> q >> price;

            addProduct(id, name, q, price);
        }

        else if (choice == 2) {
            showInventory();
        }

        else if (choice == 3) {
            int id, q;
            cout << "Enter product ID and quantity: ";
            cin >> id >> q;

            addCart(id, q);
        }

        else if (choice == 4) {
            undoCart();
        }

        else if (choice == 5) {
            placeOrder();
        }

        else if (choice == 6) {
            processOrder();
        }

        else if (choice == 7) {
            undoLast();
        }

        else if (choice == 8) {
            string name;
            cout << "Enter name: ";
            cin >> name;

            searchName(name);
        }

        else if (choice == 0) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
