Program Interface
Your task is to implement the class TextEditorBackend, which represents the backend of a text editor. The required interface:

TextEditorBackend(const std::string& text): Constructor that initializes the editor's content with the given text.

size_t size() const: Number of characters in the text including newlines.

size_t lines() const: Number of lines. An empty text has one line. Each \n character adds a line.

char at(size_t i) const: Returns the i-th character. Allowed range is [0, size()).

void edit(size_t i, char c): Replaces the character at position i with character c. Allowed range is [0, size()).

void insert(size_t i, char c): Inserts character c before the character at position i. Allowed range is [0, size()].

void erase(size_t i): Deletes the character at position i. Allowed range is [0, size()).

size_t line_start(size_t r) const: Returns the start of the r-th line. The \n character is part of the line that it terminates. Allowed range is [0, lines()).

size_t line_length(size_t r) const: Returns the length of the r-th line including the possible \n character at the end. Allowed range is [0, lines()).

size_t char_to_line(size_t i) const: Returns the line number where the i-th character is located. Allowed range is [0, size()).

If a method is called with an argument out of range, it must throw an std::out_of_range exception. The size and lines methods should have constant complexity. Other methods should have logarithmic complexity. The constructor should not be slower than repeated calls to the insert method.