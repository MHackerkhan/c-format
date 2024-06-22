#include <iostream>
#include <string>
#include <regex>

std::string escapeHtml(const std::string& unsafe) {
    std::string escaped = unsafe;
    std::regex_replace(escaped, std::regex("&"), "&amp;");
    std::regex_replace(escaped, std::regex("<"), "&lt;");
    std::regex_replace(escaped, std::regex(">"), "&gt;");
    std::regex_replace(escaped, std::regex("\""), "&quot;");
    std::regex_replace(escaped, std::regex("'"), "&#039;");
    return escaped;
}

std::string formatCppCode(const std::string& input) {
    // Simulated formatting - indent with two spaces
    std::string formattedCode;
    int indentLevel = 0;
    std::regex pattern(R"((\{|\}))");
    std::smatch match;

    for (char c : input) {
        if (std::regex_search(std::string(1, c), match, pattern)) {
            if (match[0].str() == "{") {
                formattedCode += "\n" + std::string(2 * indentLevel, ' ') + "{";
                ++indentLevel;
            } else if (match[0].str() == "}") {
                --indentLevel;
                formattedCode += "\n" + std::string(2 * indentLevel, ' ') + "}";
            }
        } else {
            formattedCode += c;
        }
    }

    return formattedCode;
}

std::string generateHTML(const std::string& input) {
    std::string formattedCode = formatCppCode(input);
    std::string escapedCode = escapeHtml(formattedCode);

    std::string fullHTML = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Formatted Code</title>
    <style>
        /* Add CSS styles for code formatting here */
    </style>
</head>
<body>
    <div class="container">
        <h2>Formatted Code</h2>
        <pre><code>)" + escapedCode + R"(</code></pre>
    </div>
</body>
</html>)";

    return fullHTML;
}

int main() {
    std::cout << "Enter your C++ code:\n";
    std::string input;
    std::getline(std::cin, input);

    std::string htmlOutput = generateHTML(input);
    std::cout << htmlOutput << std::endl;

    return 0;
}
