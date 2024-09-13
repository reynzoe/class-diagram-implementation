#include <iostream>
#include <string>
#include <iomanip>  // Added for tabular formatting
#include <algorithm> // For transform
#include <cctype>    // For tolower

using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_CART_ITEMS = 100;
const int MAX_ORDERS = 100;

class Product {
private:
    string productId;
    string name;
    string description;
    float price;
    int stock;

public:
    Product() : productId(""), name(""), description(""), price(0.0), stock(0) {}

    Product(const string& productId, const string& name, const string& description, float price, int stock)
            : productId(productId), name(name), description(description), price(price), stock(stock) {}

    string getProductId() const { return productId; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    float getPrice() const { return price; }
    int getStock() const { return stock; }

    void updateStock(int quantity) {
        if (stock >= quantity) {
            stock -= quantity;
        } else {
            cout << "Not enough stock available." << endl;
        }
    }

    string getDetail() const {
        return "ID: " + productId + ", Name: " + name + ", Price: $" + to_string(price) + ", Stock: " + to_string(stock);
    }
};

class ShoppingCart {
private:
    string cartId;
    Product cartItems[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int itemCount;

public:
    ShoppingCart() : cartId(""), itemCount(0) {}

    ShoppingCart(const string& cartId) : cartId(cartId), itemCount(0) {}

    void addToCart(Product& product, int quantity) {
        if (itemCount < MAX_CART_ITEMS) {
            cartItems[itemCount] = product;
            quantities[itemCount] = quantity;
            itemCount++;
            cout << "Added " << quantity << " of " << product.getName() << " to the cart." << endl;
            product.updateStock(quantity);
        } else {
            cout << "Cart is full. Cannot add more items." << endl;
        }
    }

    void viewCart() const {
        if (itemCount == 0) {
            cout << "Your shopping cart is empty!" << endl;
            return;
        }

        cout << "Shopping Cart Contents:" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << cartItems[i].getDetail() << ", Quantity: " << quantities[i] << endl;
        }
    }

    void clearCart() {
        itemCount = 0;
        cout << "Shopping cart cleared." << endl;
    }

    Product* getCartItems() { return cartItems; }
    int* getQuantities() { return quantities; }
    int getItemCount() const { return itemCount; }
};

class Order {
private:
    string orderId;
    string orderDate;
    string orderStatus;
    float totalAmount;
    Product orderedProducts[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int orderItemCount;

public:
    Order() : orderId(""), orderDate(""), orderStatus(""), totalAmount(0.0), orderItemCount(0) {}

    Order(const string& orderId, const string& orderDate, const string& orderStatus, float totalAmount)
            : orderId(orderId), orderDate(orderDate), orderStatus(orderStatus), totalAmount(totalAmount), orderItemCount(0) {}

    void placeOrder(ShoppingCart& cart) {
        orderItemCount = cart.getItemCount();
        for (int i = 0; i < orderItemCount; ++i) {
            orderedProducts[i] = cart.getCartItems()[i];
            quantities[i] = cart.getQuantities()[i];
            totalAmount += orderedProducts[i].getPrice() * quantities[i];
        }
        orderStatus = "Placed";
        cout << "Order placed successfully! Order ID: " << orderId << ", Total Amount: $" << totalAmount << endl;
    }

    void viewOrderDetails() const {
        cout << "\nOrder ID: " << orderId << ", Date: " << orderDate << ", Status: " << orderStatus << ", Total Amount: $" << totalAmount << endl;

        // Print table header
        cout << left << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        cout << "----------------------------------------------------------" << endl;

        for (int i = 0; i < orderItemCount; ++i) {
            cout << left << setw(10) << orderedProducts[i].getProductId()
                 << setw(20) << orderedProducts[i].getName()
                 << setw(10) << orderedProducts[i].getPrice()
                 << setw(10) << quantities[i] << endl;
        }
    }
};

class Customer {
private:
    string customerId;
    string customerName;
    string email;
    string address;
    ShoppingCart cart;
    Order orderHistory[MAX_ORDERS];
    int orderCount;

public:
    Customer(const string& customerId, const string& name, const string& email, const string& address)
            : customerId(customerId), customerName(name), email(email), address(address), cart("CART_" + customerId), orderCount(0) {}

    void addToCart(Product& product, int quantity) {
        cart.addToCart(product, quantity);
    }

    void viewCart() const {
        cart.viewCart();
    }

    void placeOrder() {
        if (cart.getItemCount() == 0) {
            cout << "Cart is empty, cannot place an order." << endl;
            return;
        }

        string orderId = "ORD_" + to_string(orderCount + 1);
        Order newOrder(orderId, "2024-09-13", "Placed", 0.0);
        newOrder.placeOrder(cart);
        orderHistory[orderCount++] = newOrder;
        cart.clearCart();
    }

    void viewOrderHistory() const {
        if (orderCount == 0) {
            cout << "No orders have been placed yet." << endl;
            return;
        }

        for (int i = 0; i < orderCount; ++i) {
            orderHistory[i].viewOrderDetails();
        }
    }
};

// Function to convert a string to lowercase
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void displayMenu() {
    cout << "\n--- SAVEWAY ---\n";
    cout << "1. View Products\n";
    cout << "2. View Shopping Cart\n";
    cout << "3. View Orders\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    // Create sample products
    Product products[MAX_PRODUCTS] = {
            Product("P001", "Laptop", "High-performance laptop", 1200.0, 10),
            Product("P002", "Smartphone", "Latest smartphone model", 800.0, 20),
            Product("P003", "Headphones", "Noise-cancelling headphones", 150.0, 30),
            Product("P004", "Tablet", "10-inch tablet", 400.0, 15),
            Product("P005", "Smartwatch", "Fitness smartwatch", 250.0, 25),
            Product("P006", "Wireless Earbuds", "Bluetooth earbuds", 100.0, 40),
            Product("P007", "Monitor", "27-inch 4K monitor", 300.0, 5),
            Product("P008", "Keyboard", "Mechanical gaming keyboard", 80.0, 10),
            Product("P009", "Mouse", "Wireless mouse", 40.0, 20),
            Product("P010", "External Hard Drive", "1TB USB 3.0 hard drive", 60.0, 10)
    };
    int productCount = 10; // Adjust to the actual number of products

    // Create a customer
    Customer customer("C001", "John Doe", "john@example.com", "123 Street, City");

    bool user = true;

    // Main menu loop
    while (user) {
        displayMenu();
        string input;
        getline(cin, input); // Use getline to handle potential multi-word input
        input = toLower(input); // Convert input to lowercase

        if (input == "1" || input == "view products") {
            cout << "\nAvailable Products:\n";
            for (int i = 0; i < productCount; ++i) {
                cout << products[i].getDetail() << endl;
            }
        } else if (input == "2" || input == "view shopping cart") {
            customer.viewCart();
        } else if (input == "3" || input == "view orders") {
            customer.viewOrderHistory();
        } else if (input == "4" || input == "exit") {
            cout << "Exiting program. Goodbye!" << endl;
            user = false;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
