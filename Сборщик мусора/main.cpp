#include "TreeTable.h"
#include <iomanip>

int main() {
    setlocale(LC_ALL, "Russian");

    TNode::InitMem(15); 
    std::cout << "���������������� ������ ��� 15 �����\n";
    TNode::PrintFree();

    TreeTable tree;
    std::cout << "\n��������� ��������: 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 65, 75, 85, 90\n";
    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(20);
    tree.Insert(40);
    tree.Insert(60);
    tree.Insert(80);
    tree.Insert(10);
    tree.Insert(25);
    tree.Insert(35);
    tree.Insert(45);
    tree.Insert(65);
    tree.Insert(75);
    tree.Insert(85);
    tree.Insert(90);

    std::cout << "\n������:\n";
    tree.print();

    std::cout << "\n��������� ������:\n";
    TNode::PrintFree();

    std::cout << "\n������� ��������: 30, 70\n";
    //tree.Delete(30);
    tree.Delete(70);

    std::cout << "\n������ ����� ��������:\n";
    tree.print();

    std::cout << "\n��������� ������ ����� ��������:\n";
    TNode::PrintFree();

    std::cout << "\n��������� ������ ������...\n";
    TNode::ClearMem(&tree);
    std::cout << "��������� ������ ����� ������ ������:\n";
    TNode::PrintFree();

    std::cout << "\n������� �������� 55 � 95:\n";
    if (tree.Insert(55)) std::cout << "������� 55 ��������\n";
    if (tree.Insert(95)) std::cout << "������� 95 ��������\n";

    std::cout << "������� �������� 100: ";
    if (!tree.Insert(100)) std::cout << "�� ������� �������� 100 (������ ���������)\n";

    std::cout << "\n�������� ������:\n";
    tree.print();
    std::cout << "�������� ��������� ������:\n";
    TNode::PrintFree();

    return 0;
}

