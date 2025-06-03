#include "TreeTable.h"
#include <iomanip>

int main() {
    setlocale(LC_ALL, "Russian");

    TNode::InitMem(15); 
    std::cout << "Инициализирована память для 15 узлов\n";
    TNode::PrintFree();

    TreeTable tree;
    std::cout << "\nДобавляем элементы: 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 65, 75, 85, 90\n";
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

    std::cout << "\nДерево:\n";
    tree.print();

    std::cout << "\nСостояние памяти:\n";
    TNode::PrintFree();

    std::cout << "\nУдаляем элементы: 30, 70\n";
    //tree.Delete(30);
    tree.Delete(70);

    std::cout << "\nДерево после удаления:\n";
    tree.print();

    std::cout << "\nСостояние памяти после удаления:\n";
    TNode::PrintFree();

    std::cout << "\nЗапускаем сборку мусора...\n";
    TNode::ClearMem(&tree);
    std::cout << "Состояние памяти после сборки мусора:\n";
    TNode::PrintFree();

    std::cout << "\nПробуем добавить 55 и 95:\n";
    if (tree.Insert(55)) std::cout << "Элемент 55 добавлен\n";
    if (tree.Insert(95)) std::cout << "Элемент 95 добавлен\n";

    std::cout << "Пробуем добавить 100: ";
    if (!tree.Insert(100)) std::cout << "Не удалось добавить 100 (память заполнена)\n";

    std::cout << "\nИтоговое дерево:\n";
    tree.print();
    std::cout << "Итоговое состояние памяти:\n";
    TNode::PrintFree();

    return 0;
}

