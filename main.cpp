#include <iostream>
#include <memory>
using namespace std;

enum class Color {
    red,black
};

class Node {
    Node* parent;
    int key;
    Node* left;
    Node* right;
    Color color;
public:
    explicit Node(Node* p = nullptr, int k = 0, Node* l = nullptr,Node* r = nullptr, Color c = Color::red) :
    parent(p),key(k),left(l),right(r),color(c){};

    void set_parent(Node *parent) {
        this->parent = parent;
    }

    void set_key(int key) {
        this->key = key;
    }

    void set_left(Node *left) {
        this->left = left;
    }

    void set_right(Node *right) {
        this->right = right;
    }

    void set_color(Color color) {
        this->color = color;
    }

    [[nodiscard]] Node* get_parent() const {
        return parent;
    }

    [[nodiscard]] int get_key() const {
        return key;
    }

    [[nodiscard]] Node* get_left() const {
        return left;
    }

    [[nodiscard]] Node* get_right() const {
        return right;
    }

    [[nodiscard]] Color get_color() const {
        return color;
    }

    ~Node() = default;
};

class RedBlackTree {
    Node* root;
    Node* nil;
public:
    RedBlackTree() {
        nil = new Node(nullptr,0,nullptr,nullptr,Color::black);
        nil->set_left(nil);
        nil->set_right(nil);
        nil->set_parent(nil);
        root = nil;
    };

    Node* get_root() const {
        return root;
    }

    Node* get_nil() const {
        return nil;
    }

    void rotateLeft(Node* node) {
        Node* child = node->get_right();
        node->set_right(child->get_left());
        if(node->get_right() != nil)
            node->get_right()->set_parent(node);
        if(node->get_parent() == nil)
            root = child;
        else if(node == node->get_parent()->get_left())
            node->get_parent()->set_left(child);
        else
            node->get_parent()->set_right(child);
        child->set_left(node);
        child -> set_parent(node->get_parent());
        node->set_parent(child);
    }

    void rotateRight(Node* node) {
        Node* child = node->get_left();
        node->set_left(child->get_right());
        if(node->get_left() != nil)
            node->get_left()->set_parent(node);
        if(node->get_parent() == nil)
            root = child;
        else if(node == node->get_parent()->get_left())
            node->get_parent()->set_left(child);
        else
            node->get_parent()->set_right(child);
        child->set_right(node);
        child -> set_parent(node->get_parent());
        node->set_parent(child);
    }

    void Insert(int val) {
        Node* z = new Node(nullptr,val,nil,nil,Color::red);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if(z->get_key() < x->get_key()) {
                x = x->get_left();
            }
            else x = x->get_right();
        }

        z->set_parent(y);

        if(y == nil) {
            root = z;
            z->set_parent(nil);
        }
        else if(z->get_key() < y->get_key())
            y->set_left(z);
        else
            y->set_right(z);
        z->set_left(nil);
        z->set_right(nil);
        z->set_color(Color::red);
        Insert_Fixup(z);
    }

    void Insert_Fixup(Node* node) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (node != root && node->get_color() == Color::red && node->get_parent()->get_color() == Color::red) {
            parent = node->get_parent();
            grandparent = parent->get_parent();
            if (parent == grandparent->get_left()) {
                Node* uncle = grandparent->get_right();
                if (uncle != nil && uncle->get_color() == Color::red) {
                    grandparent->set_color(Color::red);
                    parent->set_color(Color::black);
                    uncle->set_color(Color::black);
                    node = grandparent;
                }
                else {
                    if(node == parent->get_right()) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->get_parent();
                    }
                    rotateRight(grandparent);
                    if(parent->get_color() == Color::black) {
                        parent->set_color(Color::red);
                        grandparent->set_color(Color::black);
                    }
                    else {
                        parent -> set_color(Color::black);
                        grandparent->set_color(Color::red);
                    }
                    node = parent;
                }
            }
            else {
                Node* uncle = grandparent->get_left();
                if (uncle != nil && uncle->get_color() == Color::red) {
                    grandparent->set_color(Color::red);
                    parent->set_color(Color::black);
                    uncle->set_color(Color::black);
                    node = grandparent;
                }
                else {
                    if(node == parent->get_left()) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->get_parent();
                    }
                    rotateLeft(grandparent);
                    if(parent->get_color() == Color::black) {
                        parent->set_color(Color::red);
                        grandparent->set_color(Color::black);
                    }
                    else {
                        parent -> set_color(Color::black);
                        grandparent->set_color(Color::red);
                    }
                    node = parent;
                }
            }
        }
        root->set_color(Color::black);
    }

    Node* search_key(int key) {
        Node* node = root;
        while (node != nil && node->get_key() != key) {
            if(key < node->get_key())
                node = node->get_left();
            else
                node = node->get_right();
        }
        return node;
    }

    void transplant(Node* u, Node* v) {
        if(u==v) return;
        if (u->get_parent() == nil)
            root = v;
        else if (u == u->get_parent()->get_left())
            u->get_parent()->set_left(v);
        else
            u->get_parent()->set_right(v);
        if(v != nil)
            v->set_parent(u->get_parent());
    }

    Node* succesor(Node* node) {
        while(node->get_left() != nil)
            node = node->get_left();
        return node;
    }

    void delete_node(int key){
        Node* node = search_key(key);
        if (node == nil) {
            cout<<"Nodul "<<key<<" nu a fost gasit in arbore.";
            return;
        }

        Node* y = node;
        Node* x;
        Color y_original_color = y->get_color();

        if(node->get_left() == nil) {
            x = node->get_right();
            transplant(node,x);
        }
        else if(node->get_right() == nil) {
            x = node->get_left();
            transplant(node,x);
        }
        else {
            y = succesor(node->get_right());
            y_original_color = y->get_color();
            x = y->get_right();

            if(y->get_parent() == node) {
                    x->set_parent(y);
            }
            else
            {
                transplant(y,y->get_right());
                if(y->get_parent()!=node) {
                    y->set_right(node->get_right());
                    if(y->get_right() != nil)
                        y->get_right()->set_parent(y);
                }
            }

            transplant(node,y);
            y->set_left(node->get_left());
            if(y->get_left() != nil)
                y->get_left()->set_parent(y);
            y->set_color(node->get_color());

        }
        delete node;

        if(x!=nil && x == root)
            x->set_parent(nil);

        if(y_original_color == Color::black)
            delete_fixup(x);

        nil->set_parent(nil);
        nil->set_left(nil);
        nil->set_right(nil);


    }

    void delete_fixup(Node* node) {
        while(node != root && node!=nil && node->get_color() == Color::black) {

            if(node == node->get_parent()->get_left()) {
                Node* brother = node->get_parent()->get_right();

                if(brother -> get_color() == Color::red) {
                    brother -> set_color(Color::black);
                    node -> get_parent()->set_color(Color::red);
                    rotateLeft(node->get_parent());
                    brother = node->get_parent()->get_right();
                }

                if((brother->get_left() == nil || brother -> get_left()->get_color() == Color::black) && (brother->get_right() == nil||brother->get_right()->get_color() == Color::black)) {
                    brother->set_color(Color::red);
                    node = node->get_parent();
                }
                else {
                    if(brother -> get_right() == nil || brother -> get_right()->get_color() == Color::black) {
                        if(brother ->get_left() != nil)
                            brother->get_left()->set_color(Color::black);
                        brother->set_color(Color::red);
                        rotateRight(brother);
                        brother=node->get_parent()->get_right();
                    }
                    brother -> set_color(node->get_parent()->get_color());
                    node -> get_parent()->set_color(Color::black);
                    if(brother -> get_right() != nil)
                        brother -> get_right()->set_color(Color::black);
                    rotateLeft(node->get_parent());
                    node = root;
                }
            }
            else {
                Node* brother = node->get_parent()->get_left();

                if(brother -> get_color() == Color::red) {
                    brother -> set_color(Color::black);
                    node -> get_parent()->set_color(Color::red);
                    rotateRight(node->get_parent());
                    brother = node->get_parent()->get_left();
                }

                if((brother->get_right() == nil || brother -> get_right() ->get_color() == Color::black) && (brother -> get_left()==nil || brother ->get_left()->get_color() == Color::black)) {
                    brother ->set_color(Color::red);
                    node = node->get_parent();
                }
                else {
                    if(brother -> get_left() == nil || brother -> get_left()->get_color() == Color::black) {
                        if(brother->get_right() != nil)
                            brother -> get_right()->set_color(Color::black);
                        brother -> set_color(Color::red);
                        rotateLeft(brother);
                        brother=node->get_parent()->get_left();
                    }
                    brother -> set_color(node->get_parent()->get_color());
                    node -> get_parent()->set_color(Color::black);
                    if(brother -> get_left() != nil)
                        brother -> get_left()->set_color(Color::black);
                    rotateRight(node->get_parent());
                    node = root;
                }
            }

        }
        node->set_color(Color::black);

    }



    void inorder(Node* node) {
        if(node == nil) return;
        inorder(node->get_left());
        cout << node->get_key() << " ";
        cout<< (node->get_color() == Color::black ? "Black " : "Red ");
        inorder(node->get_right());
    }

    void print() {
        inorder(root);
        cout<<endl;
    }

    void print_structure(Node* node , int indent = 0) {
        if (node == nil) return;
        print_structure(node->get_right(), indent + 4);
        cout << string(indent, ' ');
        cout << node->get_key() << " (" << (node->get_color() == Color::black ? "Black" : "Red") << ")\n";
        print_structure(node->get_left(), indent + 4);
    }

};

int main() {

    RedBlackTree tree;
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(15);
    tree.Insert(30);
    tree.Insert(25);
    tree.print_structure(tree.get_root());
    cout<<endl<<endl<<endl;
    tree.delete_node(25);
    tree.print_structure(tree.get_root());

    return 0;
}
