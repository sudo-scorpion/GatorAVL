#include <iostream>
#include<string>
#include <vector>

using namespace std;

struct TreeNode {
    string NAME;
    int ID;
    TreeNode *left;
    TreeNode *right;

    TreeNode() {
        NAME = " ";
        ID = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(string _name, int _id) {
        NAME = std::move(_name);
        ID = _id;
        left = nullptr;
        right = nullptr;
    }
};

class Student {
public:
    Student();

    int height(TreeNode *_root);

    int balanceFactor(TreeNode *_root);

    static TreeNode *rightRotate(TreeNode *_root);

    static TreeNode *leftRotate(TreeNode *_root);

    TreeNode *insert(TreeNode *_root, TreeNode *newNode);

    static TreeNode *minNode(TreeNode *_root);

    TreeNode *remove(TreeNode *_root, int target);

    TreeNode *search(TreeNode *_root, int target);

    TreeNode *search(TreeNode *_root, const string &target);

    void printInorder(TreeNode *_root);

    void printPreorder(TreeNode *_root);

    void printPostorder(TreeNode *_root);

    void printLevelCount(TreeNode *_root);

    void removeInorder(TreeNode *_root, int n);

    void removeInorderHelper(TreeNode *_root, vector<TreeNode *> &idVec);

    TreeNode *root;
    bool isValid = false;
};

bool isNameValid(const string &data);

bool isIdValid(const string &data);

Student::Student() {
    root = nullptr;
}


int Student::height(TreeNode *_root) {
    if (_root == nullptr)
        return 0;
    return 1 + std::max(height(_root->left), height(_root->right));
}

int Student::balanceFactor(TreeNode *_root) {
    if (_root == nullptr)
        return 0;
    else
        return height(_root->left) - height(_root->right);
}

TreeNode *Student::rightRotate(TreeNode *_root) {
    TreeNode *child = _root->left;
    TreeNode *grandChild = child->right;
    child->right = _root;
    _root->left = grandChild;
    return child;
}

TreeNode *Student::leftRotate(TreeNode *_root) {
    TreeNode *child = _root->right;
    TreeNode *grandChild = child->left;
    child->left = _root;
    _root->right = grandChild;
    return child;
}

TreeNode *Student::insert(TreeNode *_root, TreeNode *newNode) {
    if (_root == nullptr) {
        _root = newNode;
        cout << "successful" << endl;
        return _root;
    } else {
        if (newNode->ID < _root->ID) {
            _root->left = insert(_root->left, newNode);
        } else if (newNode->ID > _root->ID) {
            _root->right = insert(_root->right, newNode);
        } else {
            cout << "unsuccessful" << endl;
            return _root;
        }
    }

    int factor = balanceFactor(_root);
    // Left, Left Rotation
    if (factor > 1 && newNode->ID < _root->left->ID)
        return rightRotate(_root);
    // Right, Right Rotation
    if (factor < -1 && newNode->ID > _root->right->ID)
        return leftRotate(_root);
    // Left, Right Rotation
    if (factor > 1 && newNode->ID > _root->left->ID) {
        _root->left = leftRotate(_root->left);
        return rightRotate(_root);
    }
    // Right, Left Rotation
    if (factor < -1 && newNode->ID < _root->right->ID) {
        _root->right = rightRotate(_root->right);
        return leftRotate(_root);
    }
    return _root;
}

TreeNode *Student::minNode(TreeNode *_root) {
    while (_root->left != nullptr)
        _root = _root->left;
    return _root;
}

TreeNode *Student::remove(TreeNode *_root, int target) {
    if (_root == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    } else if (target < _root->ID)
        _root->left = remove(_root->left, target);
    else if (target > _root->ID)
        _root->right = remove(_root->right, target);

        // case 1: no child
    else if (_root->left == nullptr && _root->right == nullptr) {
        delete _root;
        _root = nullptr;
        cout << "successful" << endl;
        return _root;
    }

        // case 2: one child
    else if (_root->left == nullptr) {
        TreeNode *temp = _root;
        _root = _root->right;
        delete temp;
        cout << "successful" << endl;
        return _root;
    } else if (_root->right == nullptr) {
        TreeNode *temp = _root;
        _root = _root->left;
        delete temp;
        cout << "successful" << endl;
        return _root;
    }
        // case 3: two children
    else {
        TreeNode *temp = minNode(_root->right);
        _root->ID = temp->ID;
        _root->NAME = temp->NAME;
        _root->right = temp->right;
        delete temp;
        cout << "successful" << endl;
        return _root;
    }
    return _root;
}

// search by ID
TreeNode *Student::search(TreeNode *_root, int target) {
    if (_root == nullptr) {
        return _root;
    } else if (_root->ID == target) {
        cout << _root->NAME << endl;
        isValid = true;
        return _root;
    } else if (target < _root->ID)
        return search(_root->left, target);
    else
        return search(_root->right, target);
}

// search by NAME
TreeNode *Student::search(TreeNode *_root, const string &target) {
    if (_root == nullptr) {
        return _root;
    } else if (_root->NAME == target) {
        cout << _root->ID << endl;
        isValid = true;
    }
    search(_root->left, target);
    search(_root->right, target);
    return _root;
}

void Student::printInorder(TreeNode *_root) {
    if (_root != nullptr) {
        printInorder(_root->left);
        if (_root->left)
            cout << ", ";
        cout << _root->NAME;
        if (_root->right)
            cout << ", ";
        printInorder(_root->right);
    }
}

void Student::printPreorder(TreeNode *_root) {
    if (_root != nullptr) {
        cout << _root->NAME;
        if (_root->left)
            cout << ", ";
        printPreorder(_root->left);
        if (_root->right)
            cout << ", ";
        printPreorder(_root->right);
    }
}

void Student::printPostorder(TreeNode *_root) {
    if (_root != nullptr) {
        printPostorder(_root->left);
        if (_root->right)
            cout << ", ";
        printPostorder(_root->right);
        if (_root->left)
            cout << ", ";
        cout << _root->NAME;

    }
}

void Student::printLevelCount(TreeNode *_root) {
    cout << height(_root) << endl;
}

void Student::removeInorder(TreeNode *_root, int n) {
    vector<TreeNode *> idVec;
    removeInorderHelper(_root, idVec);
    remove(root, idVec[n]->ID);
}

void Student::removeInorderHelper(TreeNode *_root, vector<TreeNode *> &idVec) {
    if (_root == nullptr)
        return;
    removeInorderHelper(_root->left, idVec);
    idVec.push_back(_root);
    removeInorderHelper(_root->right, idVec);
}

bool isNameValid(const string &data) {
    for (char i: data) {
        if ((int) i < 65 || ((int) i > 90 &&
                             (int) i < 97) || (int) i > 122) {
            if ((int) i == 32)
                continue;
            return false;
        }
    }
    return true;
}

bool isIdValid(const string &data) {
    int count = 0; // number of digit tracker
    for (char i: data) {
        if ((int) i < 48 || (int) i > 57) {
            if ((int) i == 32)
                continue;
            return false;
        }
        count++;
    }
    if (count != 8)
        return false;
    return true;
}

int main() {
    Student student;
    string idNum;
    string studentName;
    string inputData;
    string command;
    int numOfCommands;
    cin >> numOfCommands;

    for (int i = 0; i < numOfCommands; i++) {
        cin >> command;

        auto *newNode = new TreeNode();

        if (command == "insert") {

            getline(cin, inputData);

            int firstQuote = inputData.find_first_of('"');
            int lastQuote = inputData.find_last_of('"');
            studentName = inputData.substr(firstQuote + 1, lastQuote - 2);
            idNum = inputData.substr(lastQuote + 1, inputData.length() - 1);

            if (!isIdValid(idNum)) {
                cout << "unsuccessful" << endl;
                continue;
            }

            if (studentName.empty()) {
                cout << "unsuccessful" << endl;
                continue;
            }

            if (!isNameValid(studentName)) {
                cout << "unsuccessful" << endl;
                continue;
            }

            newNode->NAME = studentName;
            newNode->ID = stoi(idNum);
            student.root = student.insert(student.root, newNode);

        } else if (command == "remove") {
            string target;
            getline(cin, target);

              if (!isIdValid(target)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            student.root = student.remove(student.root, stoi(target));

        } else if (command == "search") {
            string target;
            getline(cin, target);
            int firstQuote = target.find_first_of('"');
            int lastQuote = target.find_last_of('"');
            if (firstQuote > -1) {
                student.search(student.root, target.substr(firstQuote + 1, lastQuote - 2));
            } else {
                 if (!isIdValid(target)) {
                cout << "unsuccessful" << endl;
                continue;
            }
                student.search(student.root, stoi(target));
            }
            if (!student.isValid)
                cout << "unsuccessful" << endl;
            student.isValid = false;

        } else if (command == "printPreorder") {
            student.printPreorder(student.root);
            cout << endl;

        } else if (command == "printInorder") {
            student.printInorder(student.root);
            cout << endl;

        } else if (command == "printPostorder") {
            student.printPostorder(student.root);
            cout << endl;

        } else if (command == "printLevelCount") {
            student.printLevelCount(student.root);

        } else if (command == "removeInorder") {
            int n; // an index of in order element of tree
            cin >> n;
            student.removeInorder(student.root, n);
        }
    }
    return 0;
}