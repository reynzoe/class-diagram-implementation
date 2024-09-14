#include <iostream>
#include <iomanip>
#include <algorithm> // for transform

using namespace std;

// Maximum number of products allowed in the shopping cart and orders
const int MAX_PRODUCTS = 100;

// Product class to represent individual products
class Product {
public:
    string id;
    string name;
    double price;

    Product() : id(""), name(""), price(0.0) {}

    Product(string pid, string pname, double pprice) {
        id = pid;
        name = pname;
        price = pprice;
    }
};

// Utility function to convert a string to lowercase
string toLowercase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// ShoppingCart class to manage items in the cart
class ShoppingCart {
public:
    Product cartItems[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    int itemCount;

    ShoppingCart() : itemCount(0) {}

    // Add product to the shopping cart
    void addProductToCart(const Product& product, int quantity) {
        if (itemCount < MAX_PRODUCTS) {
            cartItems[itemCount] = product;
            quantities[itemCount] = quantity;
            itemCount++;
            cout << "Product added successfully!" << endl;
        } else {
            cout << "Cart is full! Cannot add more products." << endl;
        }
    }

    // View shopping cart
    void viewCart() const {
        if (itemCount == 0) {
            cout << "Your shopping cart is empty!" << endl;
            return;
        }
        cout << "Your Shopping Cart:" << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << setw(10) << cartItems[i].id
                 << setw(20) << cartItems[i].name
                 << setw(10) << cartItems[i].price
                 << setw(10) << quantities[i] << endl;
        }
    }

    // Checkout process
    double checkout() const {
        if (itemCount == 0) {
            cout << "Your shopping cart is empty!" << endl;
            return 0;
        }

        double total = 0;
        cout << "Products for Checkout:" << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << setw(10) << cartItems[i].id
                 << setw(20) << cartItems[i].name
                 << setw(10) << cartItems[i].price
                 << setw(10) << quantities[i] << endl;
            total += cartItems[i].price * quantities[i];
        }
        cout << "Total Amount: $" << total << endl;
        return total;
    }

    // Clear the cart after checkout
    void clearCart() {
        itemCount = 0;
    }
};

// Order class to store past orders
class Order {
public:
    string orderId;
    Product orderItems[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    int itemCount;
    double totalAmount;

    Order() : itemCount(0), totalAmount(0) {}

    void setOrder(const string &oid, const Product products[], const int qtys[], int count, double total) {
        orderId = oid;
        for (int i = 0; i < count; ++i) {
            orderItems[i] = products[i];
            quantities[i] = qtys[i];
        }
        itemCount = count;
        totalAmount = total;
    }

    void viewOrderDetails() const {
        cout << "Order ID: " << orderId << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << setw(10) << orderItems[i].id
                 << setw(20) << orderItems[i].name
                 << setw(10) << orderItems[i].price
                 << setw(10) << quantities[i] << endl;
        }
        cout << "Total Amount: $" << totalAmount << endl;
    }
};

// Predefined list of products
Product productList[] = {
        Product("J001", "Air Jordan 1", 150.0),
        Product("N001", "Nike Air Max", 120.0),
        Product("J002", "Air Jordan 4", 200.0),
        Product("N002", "Nike Dunk Low", 130.0)
};
int numProducts = 4;

// Function to display available products
void displayProducts() {
    cout << "Available Products:" << endl;
    cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
    for (int i = 0; i < numProducts; ++i) {
        cout << setw(10) << productList[i].id
             << setw(20) << productList[i].name
             << setw(10) << productList[i].price << endl;
    }
}

int main() {
    ShoppingCart shoppingCart;
    Order orderHistory[MAX_PRODUCTS];
    int orderCount = 0;
    int choice;
    string productId;
    char addMore, checkoutChoice;
    int quantity;

    while (true) {
        cout << "\n------- Menu ------\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit" << endl;
        cout << "-------------------\n";
        cout << "Enter your choice: \n";
        cout << "-------------------\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                displayProducts();
                do {
                    cout << "Enter the ID of the product you want to add to the shopping cart: ";
                    cin >> productId;

                    // Convert user input to lowercase for case-insensitive comparison
                    string lowerProductId = toLowercase(productId);

                    cout << "Enter the quantity: ";
                    cin >> quantity;

                    // Find the product by ID and add it to the shopping cart
                    bool found = false;
                    for (int i = 0; i < numProducts; ++i) {
                        // Convert stored product IDs to lowercase for comparison
                        if (toLowercase(productList[i].id) == lowerProductId) {
                            shoppingCart.addProductToCart(productList[i], quantity);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Product not found!" << endl;
                    }

                    cout << "Do you want to add another product? (Y/N): ";
                    cin >> addMore;
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2: {
                shoppingCart.viewCart();
                cout << "Do you want to check out all the products? (Y/N): ";
                cin >> checkoutChoice;
                if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
                    double total = shoppingCart.checkout();
                    string orderId = "ORD" + to_string(orderCount + 1);
                    orderHistory[orderCount].setOrder(orderId, shoppingCart.cartItems, shoppingCart.quantities, shoppingCart.itemCount, total);
                    orderCount++;
                    shoppingCart.clearCart();
                    cout << "You have successfully checked out the products!" << endl;
                }
                break;
            }
            case 3: {
                if (orderCount == 0) {
                    cout << "No orders found." << endl;
                } else {
                    for (int i = 0; i < orderCount; ++i) {
                        orderHistory[i].viewOrderDetails();
                        cout << "---------------------------------------" << endl;
                    }
                }
                break;
            }
            case 4: {
                cout << "Exiting the program..." << endl;
                return 0;
            }
            default:
                cin.clear();
                cout << "Invalid choice. Please try again." << endl;
                cin.ignore();
        }
    }

    return 0;
}
