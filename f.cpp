#include <iostream>
#include <fstream>
#include <string>

std::string escapeHtml(const std::string& unsafe) {
    std::string escaped = unsafe;
    size_t pos = 0;
    while ((pos = escaped.find("&", pos)) != std::string::npos) {
        escaped.replace(pos, 1, "&amp;");
        pos += 5;  // Move past the escaped character
    }
    pos = 0;
    while ((pos = escaped.find("<", pos)) != std::string::npos) {
        escaped.replace(pos, 1, "&lt;");
        pos += 4;  // Move past the escaped character
    }
    pos = 0;
    while ((pos = escaped.find(">", pos)) != std::string::npos) {
        escaped.replace(pos, 1, "&gt;");
        pos += 4;  // Move past the escaped character
    }
    return escaped;
}

std::string generateHtmlOverview(const std::string& cppFileName) {
    std::ifstream inputFile(cppFileName);
    if (!inputFile.is_open()) {
        return "Failed to open file.";
    }

    std::string code;
    std::string line;
    while (std::getline(inputFile, line)) {
        code += escapeHtml(line) + "\n";
    }

    std::string fullHtml = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>C++ Code Overview</title>
    <style>
        /* Add CSS styles for code formatting here */
        body {
    font-family: Consolas, monospace;
    background-color: #1e1e1e;
    color: #d4d4d4;
    margin: 0;
    padding: 0;
}

.container {
    max-width: 800px;
    margin: 20px auto;
    padding: 20px;
    background-color: #252526;
    border-radius: 5px;
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);
}

h2 {
    color: #569cd6;
}

pre {
    background-color: #1e1e1e;
    padding: 10px;
    border-radius: 5px;
    overflow: auto;
    margin-top: 20px;
}

code {
    font-family: Consolas, monospace;
}

.keyword { color: #569cd6; }
.type { color: #4ec9b0; }
.variable { color: #9cdcfe; }
.operator { color: #b5cea8; }
.number { color: #b5cea8; }
.comment { color: #6a9955; font-style: italic; }

        
    </style>
</head>
<body>
    <div class="container">
        <h2>C++ Code Overview</h2>
        <pre><code>)" + code + R"(</code></pre>
    </div>
</body>
</html>)";

    return fullHtml;
}

int main() {
    std::string cppFileName;
    std::cout << "Enter the name of the C++ file: ";
    std::getline(std::cin, cppFileName);

    std::string htmlOverview = generateHtmlOverview(cppFileName);
    std::cout << htmlOverview << std::endl;

    return 0;
}
