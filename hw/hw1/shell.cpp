#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
// 分割字符串为单词
std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::string command;
    while (true) {
        // 显示命令提示符
        std::cout << "$ ";
        std::getline(std::cin, command);

        // 退出Shell
        if (command == "exit") {
            break;
        }

        // 分割命令为参数
        std::vector<std::string> args = split(command, ' ');

        // 将参数转换为C风格的数组
        std::vector<char*> cArgs;
        for (const auto& arg : args) {
            cArgs.push_back(const_cast<char*>(arg.c_str()));
        }
        cArgs.push_back(nullptr);

        // 创建子进程并执行命令
        pid_t pid = fork();
        if (pid == 0) {
            // 子进程执行命令
            execvp(cArgs[0], cArgs.data());
            // execvp() 执行失败时输出错误信息
            std::perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // 创建子进程失败
            std::perror("fork");
        } else {
            // 父进程等待子进程结束
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}