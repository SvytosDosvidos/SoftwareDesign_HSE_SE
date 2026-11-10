#include "../include/console_controller.h"

#include<iostream>
#include<format>

void ConsoleController::printCommand() const {
    std::cout << std::format("+{:-^48}+\n", "");
    std::cout << std::format("|{: ^48}|\n", "All command:");
    std::cout << std::format("|{: ^48}|\n", "");
    std::cout << std::format("|{: ^48}|\n", "1 - Instructions for all commands");
    std::cout << std::format("|{: ^48}|\n", "2 - Display of all students in the university");
    std::cout << std::format("|{: ^48}|\n", "3 - Add new student/lecturer/manager in university");
    std::cout << std::format("|{: ^48}|\n", "4 - Instructions on how to add student/lecturer/manager");
    std::cout << std::format("|{: ^48}|\n", "5 - End program");
    std::cout << std::format("+{:-^48}+\n", "");
}