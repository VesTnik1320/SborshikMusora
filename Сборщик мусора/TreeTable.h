#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

typedef std::string str;

class TreeTable;

struct TNode {
    int key;
    TNode* pLeft;
    TNode* pRight;
    bool isValid;
    bool isAlive;
    static void MarkAlive(TNode* node);

    static struct Mem {
        TNode* pFirst;
        TNode* pLast;
        TNode* pFree;
    } mem;

    static void InitMem(int size = 100) {
        mem.pFirst = new TNode[size];
        mem.pFree = mem.pFirst;
        mem.pLast = mem.pFirst + size - 1;

        for (int i = 0; i < size - 1; i++) {
            mem.pFirst[i].pLeft = &mem.pFirst[i + 1];
            mem.pFirst[i].key = -1;
            mem.pFirst[i].isValid = false;
            mem.pFirst[i].isAlive = false;
        }
        mem.pLast->pLeft = nullptr;
        mem.pLast->key = -1;
        mem.pLast->isValid = false;
        mem.pLast->isAlive = false;
    }

    static void PrintFree() {
        std::cout << "Свободные узлы: ";
        TNode* node = mem.pFree;
        while (node) {
            std::cout << (node - mem.pFirst) << " ";
            node = node->pLeft;
        }
        std::cout << std::endl;
    }

    static void ClearMem(TreeTable* t);

    void* operator new(size_t size) {
        if (mem.pFree == nullptr) {
            throw str("Память закончилась");
        }

        TNode* node = mem.pFree;
        mem.pFree = mem.pFree->pLeft;

        node->pLeft = nullptr;
        node->pRight = nullptr;
        node->isValid = true;
        node->isAlive = false;

        return node;
    }
    void operator delete(void* p) {
        TNode* node = (TNode*)p;
        node->key = -1;
        node->isValid = false;
        node->isAlive = false;
        node->pLeft = mem.pFree;
        mem.pFree = node;
    }
};

TNode::Mem TNode::mem;

class TreeTable {
    TNode* pRoot = nullptr;
    TNode* pCurr = nullptr;
    TNode* pPrev = nullptr;
    std::stack<TNode*> st;
    int level = 0;

public:
    bool Find(int key) {
        pCurr = pRoot;
        pPrev = nullptr;

        while (pCurr != nullptr) {
            if (pCurr->key == key) {
                return true;
            }

            pPrev = pCurr;
            if (key < pCurr->key) {
                pCurr = pCurr->pLeft;
            }
            else {
                pCurr = pCurr->pRight;
            }
        }
        return false;
    }

    bool Insert(int key) {
        if (Find(key)) {
            return false;
        }

        TNode* newNode;
        try {
            newNode = new TNode;
        }
        catch (const str& e) {
            std::cout << e << std::endl;
            return false;
        }

        newNode->key = key;
        newNode->pLeft = nullptr;
        newNode->pRight = nullptr;
        newNode->isValid = true;

        if (pRoot == nullptr) {
            pRoot = newNode;
        }
        else if (key < pPrev->key) {
            pPrev->pLeft = newNode;
        }
        else {
            pPrev->pRight = newNode;
        }

        return true;
    }

    bool Delete(int key) {
        if (!Find(key)) {
            return false;
        }
        if (pPrev == nullptr) {
            DeleteSubtree(pRoot);
        }
        else if (pPrev->pLeft == pCurr) {
            DeleteSubtree(pPrev->pLeft);
        }
        else if (pPrev->pRight == pCurr) {
            DeleteSubtree(pPrev->pRight);
        }
        return true;
    }

    void DeleteSubtree(TNode*& node) {
        if (node == nullptr) return;
        TNode* left = node->pLeft;
        TNode* right = node->pRight;

        delete node;

        node = nullptr;
    }


    void Reset() {
        while (!st.empty()) st.pop();
        pCurr = pRoot;
        while (pCurr && pCurr->pLeft) {
            st.push(pCurr);
            pCurr = pCurr->pLeft;
        }
    }

    bool isEnd() const {
        return pCurr == nullptr;
    }

    void GoNext() {
        if (pCurr->pRight) {
            pCurr = pCurr->pRight;
            while (pCurr->pLeft) {
                st.push(pCurr);
                pCurr = pCurr->pLeft;
            }
        }
        else if (!st.empty()) {
            pCurr = st.top();
            st.pop();
        }
        else {
            pCurr = nullptr;
        }
    }

    TNode* GetCurr() {
        return pCurr;
    }

    void print() {
        printRec(pRoot, "", true);
    }

    void printRec(TNode* node, const std::string& prefix, bool isLeft) {
        if (node == nullptr) return;

        std::cout << prefix;
        std::cout << (isLeft ? "|-- " : "`-- ");
        std::cout << "[" << std::setw(3) << std::setfill('0') << node->key << "] : " << node->key << std::endl;

        printRec(node->pLeft, prefix + (isLeft ? "|   " : "    "), true);
        printRec(node->pRight, prefix + (isLeft ? "|   " : "    "), false);
    }

    friend void TNode::ClearMem(TreeTable* t);
};

void TNode::MarkAlive(TNode* node) {
    if (!node || node->isAlive) return;
    node->isAlive = true;
    MarkAlive(node->pLeft);
    MarkAlive(node->pRight);
}

void TNode::ClearMem(TreeTable* t) {
    for (TNode* node = mem.pFirst; node <= mem.pLast; node++) {
        node->isAlive = false;
    }

    MarkAlive(t->pRoot);

    mem.pFree = nullptr;
    TNode* lastFree = nullptr;

    for (TNode* node = mem.pFirst; node <= mem.pLast; node++) {
        if (!node->isAlive) {
            node->key = -1;
            node->pLeft = nullptr;
            node->pRight = nullptr;
            node->isValid = false;

            if (lastFree) {
                lastFree->pLeft = node;
            }
            else {
                mem.pFree = node;
            }
            lastFree = node;
        }
    }
}