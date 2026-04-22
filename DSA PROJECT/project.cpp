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


struct CartItem {
    int id;
    int qty;
};


vector<Product> items;// inventory
vector<CartItem> cart;// cart
stack<vector<CartItem>> cartUndo;// undo cart
queue<vector<CartItem>> orders;// order queue
stack<vector<Product>> invUndo;// undo inventory



int findProduct(int id) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i].id == id) {
            return i;
        }
    }
    return -1;
}



void addProduct(int id, string name, int qty, float price) {

    int index = findProduct(id);

    if (index != -1) {
        
        items[index].qty += qty;
        items[index].price = price;

        cout << "Product already exists, quantity updated.\n";
    } 
    else {
        Product p;
        p.id = id;
        p.name = name;
        p.qty = qty;
        p.price = price;
        p.sold = 0;

        items.push_back(p);

        cout << "Product added successfully.\n";
    }
}


void saveCartState() {
    cartUndo.push(cart);
}


void addToCart(int id, int qty) {
    saveCartState();

    CartItem item;
    item.id = id;
    item.qty = qty;

    cart.push_back(item);

    cout << "Item added to cart.\n";
}


void undoCart() {
    if (!cartUndo.empty()) {
        cart = cartUndo.top();
        cartUndo.pop();
        cout << "Cart undo successful.\n";
    } else {
        cout << "Nothing to undo.\n";
    }
}


void placeOrder() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    orders.push(cart);
    cart.clear();

    cout << "Order placed successfully.\n";
}


void processOrder() {

    if (orders.empty()) {
        cout << "No orders to process.\n";
        return;
    }
    invUndo.push(items);

    vector<CartItem> currentOrder = orders.front();
    orders.pop();

    float total = 0;

    cout << "\n**** BILL ****\n";

    for (int i = 0; i < currentOrder.size(); i++) {

        int id = currentOrder[i].id;
        int qty = currentOrder[i].qty;

        int index = findProduct(id);

        if (index != -1 && items[index].qty >= qty) {

            float cost = items[index].price * qty;

            cout << items[index].name << " x "
                 << qty << " = " << cost << endl;

            items[index].qty -= qty;
            items[index].sold += qty;

            total += cost;
        } 
        else {
            cout << "Item not available: " << id << endl;
        }
    }

    cout << "Total = " << total << endl;
}



void undoLastTransaction() {
    if (!invUndo.empty()) {
        items = invUndo.top();
        invUndo.pop();
        cout << "Undo successful.\n";
    } else {
        cout << "Nothing to undo.\n";
    }
}


void searchByName(string name) {

    cout << "\nSearch Results:\n";

    for (int i = 0; i < items.size(); i++) {
        if (items[i].name == name) {
            cout << items[i].name
                 << " | Qty: " << items[i].qty << endl;
        }
    }
}



void showInventory() {

    if (items.empty()) {
        cout << "\nNo products in inventory.\n";
        return;
    }

    cout << "\n*** Inventory ***\n";

    for (int i = 0; i < items.size(); i++) {
        cout << items[i].id << " "
             << items[i].name << " "
             << items[i].qty << " "
             << items[i].price << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Add Product\n";
        cout << "2. Show Inventory\n";
        cout << "3. Add to Cart\n";
        cout << "4. Undo Cart\n";
        cout << "5. Place Order\n";
        cout << "6. Process Order\n";
        cout << "7. Undo Transaction\n";
        cout << "8. Search Product\n";
        cout << "0. Exit\n";

        
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, qty;
            float price;
            string name;

            cout << "Enter ID Name Qty Price: ";
            cin >> id >> name >> qty >> price;

            addProduct(id, name, qty, price);
        }

        else if (choice == 2) {
            showInventory();
        }

        else if (choice == 3) {
            int id, qty;

            cout << "Enter product ID and quantity: ";
            cin >> id >> qty;

            addToCart(id, qty);
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
            undoLastTransaction();
        }

        else if (choice == 8) {
            string name;

            cout << "Enter product name: ";
            cin >> name;

            searchByName(name);
        }

        else if (choice == 0) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
