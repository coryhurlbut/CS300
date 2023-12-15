// CS300 Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Cory Hurlbut
//

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// define a structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prereqs;
    Course() {
        courseNumber = "No course number";
        courseTitle = "No course title";
        prereqs = vector<string>();
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node

}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    else {
        // else
        // add Node root and bid
        addNode(root, course);
    }


}

/**
 * Search for a bid
 */
void BinarySearchTree::Search(string courseNumber) {
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root
    Node* currNode = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (currNode != nullptr) {
        // if match found, return current bid
        if (currNode->course.courseNumber == courseNumber) {
            cout << currNode->course.courseNumber << ": " << currNode->course.courseTitle;
            for (int i = 0; i < (int)currNode->course.prereqs.size(); ++i) {
                cout << " | " << currNode->course.prereqs[i];
            }
            cout << endl;
            return;
        }
        // if bid is smaller than current node then traverse left
        if (courseNumber < currNode->course.courseNumber) {
            currNode = currNode->left;
        }// else larger so traverse right
        else {
            currNode = currNode->right;
        }
    }
    cout << "Course not found" << endl;
    return;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (8) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (course.courseNumber < node->course.courseNumber) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        else {
            // else recurse down the left node
            addNode(node->left, course);
        }
    }
    else {// else
     // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        else {//else
         // recurse down the left node
            addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    // FixMe (9): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->course.courseNumber << ": " << node->course.courseTitle;
        for (int i = 0; i < (int)node->course.prereqs.size(); ++i) {
            cout << " | " << node->course.prereqs[i];
        }
        cout << endl;
        //InOder right
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        cout << node->course.courseNumber << ": " << node->course.courseTitle;
        for (int i = 0; i < (int)node->course.prereqs.size(); ++i) {
            cout << " | " << node->course.prereqs[i];
        }
        cout << endl;
    }


}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout << node->course.courseNumber << ": " << node->course.courseTitle;
        for (int i = 0; i < (int)node->course.prereqs.size(); ++i) {
            cout << " | " << node->course.prereqs[i];
        }
        cout << endl;
        //postOrder left
        preOrder(node->left);
        //postOrder right   
        preOrder(node->right);
    }

}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;
    string line;
    vector<string> lines = vector<string>();
    vector<vector<string>> content = vector<vector<string>>();
    
    //Read the file into lines
    ifstream ifile(csvPath.c_str());
    if (ifile.is_open())
    {
        while (ifile.good())
        {
            getline(ifile, line);
            if (line != "")
                lines.push_back(line);
        }
        ifile.close();

        if (lines.size() == 0)
            throw exception("No data in file");
        
    }
    else {
        throw exception("Failed to open file");
    }

    //Parse the lines into usable content
    vector<string>::iterator it = lines.begin();
    for (; it != lines.end(); it++)
    {
        vector<string> row = vector<string>();
        bool quoted = false;
        int tokenStart = 0;
        unsigned int i = 0;

        for (; i != it->length(); i++)
        {
            //Removes 3 weird characters that were prepended on the first record.
            if (i == 0 && it == lines.begin()) {
                tokenStart = tokenStart + 3;
            }
            if (it->at(i) == '"')
                quoted = ((quoted) ? (false) : (true));
            else if (it->at(i) == ',' && !quoted)
            {
                row.push_back(it->substr(tokenStart, i - tokenStart));
                tokenStart = i + 1;
            }
        }
        row.push_back(it->substr(tokenStart, it->length() - tokenStart));

        //Create course and push to bst
        Course course;
        course.courseNumber = row[0];
        course.courseTitle = row[1];
        for (int i = 2; i < (int)row.size(); ++i) {
            course.prereqs.push_back(row[i]);
        }

        // Add course to BST
        bst->Insert(course);
    }
}

int main(int argc, char* argv[]) {
    // Define a timer variable
    clock_t ticks;

    string courseNum;
    //LinkedList* courseLinkedList = new LinkedList();
    //HashTable* courseHashTable = new HashTable();
    BinarySearchTree* courseBST = new BinarySearchTree();

    string CSVPath = "ABCU_Advising_Program_Input.txt";

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << "  1. Load Data Structures" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            try {
                loadCourses(CSVPath, courseBST);
            }
            catch (exception e) {
                cout << "Error loading courses" << endl;
            }
            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:

            ticks = clock();

            courseBST->InOrder();

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 3:
            ticks = clock();
            cout << "Please enter a course number:";
            cin >> courseNum;

            courseBST->Search(courseNum);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        case 9:
            break;
        default:
            cout << choice << " is not a valid option" << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
