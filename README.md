# Inventory Management System (C++)

This is a simple inventory management system that I built using C++ to understand how data structures can be applied in real-world problems.

The program allows managing products, handling customer orders, and generating bills. 
It also includes features like cart management and undo functionality, which makes it closer to how real systems work.

---

## Features

* Add products to inventory
* View all available products
* Add items to cart
* Undo last cart action
* Place order from cart
* Process orders (with bill generation)
* Undo last transaction
* Search product by name

---

## Data Structures Used

This project mainly focuses on using basic data structures:

* **Vector** → for storing inventory and cart
* **Stack** → for undo operations (cart + transactions)
* **Queue** → for order processing (FIFO)

---

## How It Works

1. Products are added to the inventory
2. User can add items to cart
3. Cart can be modified or undone
4. Order is placed and stored in queue
5. Order is processed and bill is generated
6. Inventory updates automatically
7. Undo option is available if something goes wrong

---

