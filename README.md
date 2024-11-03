# Email Spam Filter

This project implements an email spam filter in C. It uses a combination of text preprocessing, efficient data structures, and a Naive Bayes classifier to classify emails as either spam or ham (non-spam). The filter is designed to detect spam keywords, phrases, and patterns efficiently, providing accurate and reliable classification.

## Features

- **Text Preprocessing:** Tokenizes email content, removes stop words, and handles bigrams to enhance spam detection accuracy.
- **Data Structures:**
  - **Bloom Filter:** Quickly checks for spam keywords.
  - **Trie:** Stores and retrieves common spam-related patterns efficiently.
  - **Hash Tables:** Track word frequencies for frequency-based matching.
- **Naive Bayes Classifier:** Calculates spam probabilities based on word occurrences, achieving a balanced trade-off between precision and recall.
- **Flexible Input:** Accepts both CSV datasets for batch classification and individual text files for single email classification.

## Requirements

- **C Compiler** (e.g., `gcc`, `clang`)
- **Dataset Files:** Email datasets (e.g., `emails.csv`, `spam_words.txt`) should be located in the `data` directory.

## How to Run

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/Arunima2305/email-spam-filter
   cd email-spam-filter/src

2. **Compile the Program:**

Compile all source files in the `src` directory, including the necessary modules.

```bash
gcc -o email_spam_filter main.c bloom_filter.c trie.c naive_bayes.c hash_table.c utils.c -lm
```

3. **Run the Program:**

You can run the program in two modes:

- **Batch Mode (CSV Dataset):**
  - The program will load and classify emails from a dataset file (e.g., `emails.csv` in the `data` folder).

    ```bash
    ./email_spam_filter
    ```

- **Single Email Mode (Text File):**
  - To test an individual email, add the email content to `data/email_input.txt` and run the program in this mode. This will classify the single email content as spam or ham.

    ```bash
    ./email_spam_filter
    ```

## User Input

- **For Single Email Classification:**
  - Add the email content (including subject and body) in `data/email_input.txt`.
  - The program will read the content, process it, and display the classification result as either "SPAM" or "HAM".

## Expected Output

- **Model Performance Metrics (Batch Mode):** After classifying the dataset, you will see metrics like:

    ```yaml
    Accuracy: 74.01%
    Precision: 0.59
    ```

- **Classification Result for Single Email (Single Email Mode):**

    ```csharp
    The email is classified as: HAM
    ```

## Example

- **Sample Input Email (in `data/email_input.txt`):**

    ```vbnet
    Subject: re : merit increases
    Vince, I am going to have the team look at the problem...
    ```

- **Output:**

    ```csharp
    The email is classified as: HAM
    ```

## Additional Notes

- **Thresholds:** The spam filter uses specific thresholds for spam detection, which can be adjusted in the code to balance between precision and recall.
- **Stop Words:** Common stop words are removed to reduce noise in the classification process.

## License

This project is licensed under the MIT License. See `LICENSE` for more details.

## Contributing

Contributions are welcome! Feel free to fork the repository, make improvements, and submit a pull request.



