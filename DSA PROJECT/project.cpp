// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;

// // Product structure
// struct Product {
//     int id;
//     string name;
//     int quantity;
//     float price;
//     int sales;
//     string expiryDate; // NEW FEATURE
// };

// // Global storage
// vector<Product> inventory;
// vector<pair<int, int>> cart; // for billing

// // Add product
// void addProduct(int id, string name, int qty, float price, string expiry) {
//     Product p;
//     p.id = id;
//     p.name = name;
//     p.quantity = qty;
//     p.price = price;
//     p.sales = 0;
    

//     inventory.push_back(p);
//     cout << "Product added successfully!\n";
// }

// // Search product
// int searchProduct(int id) {
//     for (int i = 0; i < inventory.size(); i++) {
//         if (inventory[i].id == id)
//             return i;
//     }
//     return -1;
// }

// // Sell product (with OUT OF STOCK + EXPIRY CHECK)
// void sellProduct(int id, int qty) {
//     int index = searchProduct(id);

//     if (index == -1) {
//         cout << "Product not found!\n";
//         return;
//     }

//     // OUT OF STOCK
//     if (inventory[index].quantity == 0) {
//         cout << "⚠️ Product OUT OF STOCK!\n";
//         return;
//     }



//     if (inventory[index].quantity >= qty) {
//         inventory[index].quantity -= qty;
//         inventory[index].sales += qty;
//         cout << "Product sold successfully!\n";
//     } else {
//         cout << "Not enough stock!\n";
//     }
// }

// // Add to cart
// void addToCart(int id, int qty) {
//     cart.push_back({id, qty});
//     cout << "Item added to cart!\n";
// }

// // BILL GENERATION
// void generateBill() {
//     float total = 0;
//     cout << "\n------ BILL ------\n";

//     for (auto item : cart) {
//         int index = searchProduct(item.first);

//         if (index != -1) {
//             float cost = inventory[index].price * item.second;
//             cout << inventory[index].name << " x " 
//                  << item.second << " = " << cost << endl;
//             total += cost;

//             // reduce stock
//             inventory[index].quantity -= item.second;
//             inventory[index].sales += item.second;
//         }
//     }

//     cout << "------------------\n";
//     cout << "Total = " << total << endl;
//     cout << "------------------\n";

//     cart.clear();
// }

// // Display inventory
// void displayInventory() {
//     cout << "\n--- Inventory ---\n";
//     for (auto p : inventory) {
//         cout << "ID: " << p.id
//              << " | Name: " << p.name
//              << " | Qty: " << p.quantity
//              << " | Price: " << p.price
//              << " | Expiry: " << p.expiryDate
//              << " | Sales: " << p.sales << endl;
//     }
// }

// // MAIN
// int main() {

//     // Add products (with expiry date)
//     addProduct(101, "Milk", 10, 40, "2026-04-10");
//     addProduct(102, "Rice", 0, 60, "2027-01-01");
//     addProduct(103, "Bread", 5, 30, "2025-12-01");

//     displayInventory();

//     // Try selling OUT OF STOCK product
//     sellProduct(102, 1);

//     // Try selling EXPIRED product
//     sellProduct(103, 1);

//     // Add items to cart
//     addToCart(101, 2);
//     addToCart(103, 1);

//     // Generate bill
//     generateBill();

//     displayInventory();

//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <stack>
// #include <queue>
// using namespace std;

// // product details
// struct Product {
//     int id;
//     string name;
//     int qty;
//     float price;
//     int sold;
// };

// // storage
// vector<Product> items;

// // cart + undo
// vector<pair<int,int>> cart;
// stack<vector<pair<int,int>>> cartUndo;

// // order queue
// queue<vector<pair<int,int>>> orders;

// // undo inventory
// stack<vector<Product>> invUndo;


// // add new product
// void addProduct(int id, string name, int qty, float price) {
//     Product p;
//     p.id = id;
//     p.name = name;
//     p.qty = qty;
//     p.price = price;
//     p.sold = 0;

//     items.push_back(p);
// }

// // find product index
// int findProduct(int id) {
//     for (int i = 0; i < items.size(); i++) {
//         if (items[i].id == id)
//             return i;
//     }
//     return -1;
// }


// // -------- CART --------

// // save state before change
// void saveCart() {
//     cartUndo.push(cart);
// }

// // add item
// void addCart(int id, int q) {
//     saveCart();
//     cart.push_back({id, q});
//     cout << "Added to cart\n";
// }

// // undo last cart change
// void undoCart() {
//     if (!cartUndo.empty()) {
//         cart = cartUndo.top();
//         cartUndo.pop();
//         cout << "Cart undo done\n";
//     } else {
//         cout << "Nothing to undo\n";
//     }
// }


// // -------- ORDER --------

// // place order
// void placeOrder() {
//     if (cart.empty()) {
//         cout << "Cart empty\n";
//         return;
//     }

//     orders.push(cart);
//     cart.clear();

//     cout << "Order placed\n";
// }


// // process order
// void processOrder() {
//     if (orders.empty()) {
//         cout << "No orders\n";
//         return;
//     }

//     invUndo.push(items);

//     auto ord = orders.front();
//     orders.pop();

//     float total = 0;

//     cout << "\n--- BILL ---\n";

//     for (auto x : ord) {
//         int idx = findProduct(x.first);

//         if (idx != -1 && items[idx].qty >= x.second) {
//             float cost = items[idx].price * x.second;

//             cout << items[idx].name << " x "
//                  << x.second << " = " << cost << endl;

//             items[idx].qty -= x.second;
//             items[idx].sold += x.second;

//             total += cost;
//         } else {
//             cout << "Item not available: " << x.first << endl;
//         }
//     }

//     cout << "Total = " << total << endl;
// }


// // undo transaction
// void undoLast() {
//     if (!invUndo.empty()) {
//         items = invUndo.top();
//         invUndo.pop();
//         cout << "Undo successful\n";
//     } else {
//         cout << "Nothing to undo\n";
//     }
// }


// // search by name
// void searchName(string name) {
//     cout << "\nSearch result:\n";

//     for (auto p : items) {
//         if (p.name == name) {
//             cout << p.name << " | Qty: " << p.qty << endl;
//         }
//     }
// }


// // display inventory
// void showInventory() {
//     cout << "\n--- Inventory ---\n";

//     for (auto p : items) {
//         cout << p.id << " "
//              << p.name << " "
//              << p.qty << " "
//              << p.price << " "
//              << p.sold << endl;
//     }
// }


// // -------- MAIN --------

// int main() {

//     addProduct(101, "Milk", 50, 40);
//     addProduct(102, "Rice", 100, 60);
//     addProduct(103, "Sugar", 20, 45);

//     showInventory();

//     addCart(101, 2);
//     addCart(102, 1);

//     undoCart();

//     addCart(103, 3);

//     placeOrder();

//     processOrder();

//     showInventory();

//     undoLast();

//     showInventory();

//     searchName("Milk");

//     return 0;
// }


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