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
            if (match[0] == "{") {
                formattedCode += "\n" + std::string(2 * indentLevel, ' ') + "{";
                ++indentLevel;
            } else if (match[0] == "}") {
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
        body {
            font-family: Consolas, monospace;
            background-color: #1e1e1e;
            color: #d4d4d4;
            margin: 0;
            padding: 20px;
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
            border: 1px solid #3c3c3c;
            border-radius: 5px;
            overflow: auto;
            margin-top: 20px;
        }
        code {
            font-size: 1em;
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
