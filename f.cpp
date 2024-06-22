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
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.3.1/styles/monokai-sublime.min.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.3.1/highlight.min.js"></script>
    <script>hljs.initHighlightingOnLoad();</script>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #282c34;
            color: #abb2bf;
            margin: 0;
            padding: 0;
        }
        .container {
            max-width: 800px;
            margin: 20px auto;
            padding: 20px;
            background-color: #2c313c;
            border-radius: 5px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);
        }
        h2 {
            color: #61afef;
        }
        pre code {
            font-family: 'Courier New', Courier, monospace;
            font-size: 16px;
            line-height: 1.5;
            padding: 10px;
            border-radius: 5px;
            display: block;
            overflow-x: auto;
            background-color: #2c313c;
            color: #abb2bf;
        }
        .hljs-keyword {
            color: #c678dd;
        }
        .hljs-built_in {
            color: #56b6c2;
        }
        .hljs-type {
            color: #61afef;
        }
        .hljs-literal {
            color: #d19a66;
        }
        .hljs-number {
            color: #d19a66;
        }
        .hljs-string {
            color: #98c379;
        }
        .hljs-comment {
            color: #5c6370;
            font-style: italic;
        }
        .hljs-function {
            color: #61afef;
        }
        .hljs-title {
            color: #e06c75;
        }
        .hljs-params {
            color: #dcdfe4;
        }
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
