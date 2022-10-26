#include <iostream>
#include <fstream>
#include<list>
#include<vector>
using namespace std;
class ItemInfo {
public:
    int artic, manufacturer;
    double price;
    ItemInfo(double p, int a, int m) : price(p), artic(a), manufacturer(m) {};
};
class Hash
{
    int BUCKET;  
    list<ItemInfo>* table;
public:
    Hash(int b)
    {
        this->BUCKET = b;
        table = new list<ItemInfo>[BUCKET];
    }
    void insertItem(double price, int artic, int manufacturer)
    {
        int index = hashFunction(artic);
        table[index].push_back({ price,artic,manufacturer });
    }

    int hashFunction(int x) {
        return (x % BUCKET);
    }

    void displayHash() {
        for (int i = 0; i < BUCKET; i++) {
            cout << "Ключ в хеш-таблице равен " << i << endl;
            for (auto&& item : table[i]) {
                cout << item.artic << " " << item.price << " " << item.manufacturer << endl;
            }
        }
    };
    void findItem(int value) {
        if (table[hashFunction(value)].empty()) {
            cout << "Такого товара не существует" << endl;
            return;
        }
        for (auto&& item : table[hashFunction(value)]) {
            cout << "Найден товар с артикулом " << item.artic << " ценой в " << item.price << " и производителем " << item.manufacturer << endl;
        }
    }
    ~Hash() {
        delete[] table;
    }
};
class BST {
    double price;
    BST* left, * right,*center;
    int artic, manufacturer;
public:
    static list<BST*> dynamicNodes;
    BST() : price(0), left(NULL),right(NULL),center(NULL),artic(0),manufacturer(0) {};
    BST(double value, int a, int m){
        price = value;
        left = right = center = NULL;
        artic = a;
        manufacturer = m;
    };
    BST* Insert(BST* root, double price,int artic,int man )
    {
        if (!root) {
            BST* item = new BST(price, artic, man);
            dynamicNodes.push_back(item);
            return item;
        }
        if (price > root->price) {
            root->right = Insert(root->right, price,artic,man);
        }
        else if (price < root->price) {
            root->left = Insert(root->left, price,artic,man);
        }
        else {
            root->center = Insert(root->center, price, artic, man);
        }
        return root;
    }
    void Inorder(BST* root)
    {
        if (!root) {
            return;
        }
        Inorder(root->left);
        cout << root->price << endl;
        Inorder(root->right);
    }
    void findItem(BST* root, double value) {
        if (!root) {
            return;
        }
        if (root->price == value) {
            cout << "Найден товар с артикулом " << root->artic << " ценой в " << root->price << " и производителем " << root->manufacturer<< endl;
            findItem(root->center, value);
        }
        if (root->price > value) {
            findItem(root->left, value);
        }
        if (root->price < value) {
            findItem(root->right, value);
        }
    }
};
list<BST*> BST::dynamicNodes;
void f(int) {  };
int main()
{
    std::ifstream file;
    file.open("C:\\Users\\hello\\Desktop\\ads_lab2.dat");
    BST b, * root = NULL;
    Hash h(35129);
    int artic, manufacturer;
    double price;
    int k = 0;
    while (file >> artic) {
        file >> price;
        file >> manufacturer;
        if (k == 0) {
            root = b.Insert(root, price, artic, manufacturer);
        }
        else {
            b.Insert(root, price, artic, manufacturer);
        }
        h.insertItem(price,artic,manufacturer);
        k++;
    };
    b.findItem(root, 588.96);
    cout << "#####################################" << endl;
    h.findItem(1769258);
    for (auto x : BST::dynamicNodes) {
        delete x;
    }
    file.close();
    return 0;
}