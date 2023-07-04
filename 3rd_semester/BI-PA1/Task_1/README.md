# Task description
    The task is to implement a program that calculates the balance on a bank account. The program processes transactions (deposits, withdrawals) and takes into account interest.

    Assuming that the bank operates in Czech crowns (CZK), it allows customers to deposit and withdraw money, but only one operation is allowed per day. Furthermore, the bank is lenient and allows unlimited overdraft. A positive balance earns interest at the credit interest rate, while a negative balance incurs interest at the debit rate (which may be different). Interest is calculated on a daily basis. The balance and the accrued/charged interest should always be expressed and calculated in whole CZK and haléře. All amounts are rounded towards zero (e.g., an accrued/charged interest of 1.3499 will be processed as 1.34 CZK). The interest for a given day is calculated based on the account balance at midnight, so a deposit or withdrawal will only affect the interest calculation on the following day.

    The program takes as input the values of the credit and debit interest rates as two decimal numbers, representing the daily interest rates in percentage. It is followed by a list of transactions. Each transaction consists of two numbers: the day of the transaction and the amount. The transactions are entered in sorted order, with the day numbers increasing. A positive amount represents a deposit, a negative amount represents a withdrawal, and a zero amount indicates closing the account. The program responds by displaying the final balance and terminates.

    The output of the program is the account balance upon closing. The output format is evident from the examples below. Please ensure to include a newline character ("\n") after each output line.

    If the input is invalid (contains non-numeric or nonsensical values), the program should detect this situation and display an error message. The format of the error message is also shown in the examples below. The program should stop asking for further input upon detecting an error, display the error message, and terminate. Therefore, it is necessary to check for errors immediately after reading each value (do not postpone the input validation until after reading the entire input). The error message should be printed to standard output (do not print it to standard error output).

    Sample program execution:
    Enter the credit interest rate [%]:
    0.01
    Enter the debit interest rate [%]:
    0.1
    Enter the transactions:
    0, 20000
    45, -5000
    100, 10000
    120, 0
    Balance: 25223.27
    Enter the credit interest rate [%]:
    0.02
    Enter the debit interest rate [%]:
    0.4
    Enter the transactions:
    10, 20000
    25, -15000
    45, -10000
    70, 5000
    100, 0
    Balance: -491.27
    Enter the credit interest rate [%]:
    abcd
    Invalid input.
    Enter the credit interest rate [%]:
    0.02
    Enter the debit interest rate [%]:
    0.3
    Enter the transactions:
    5, 2000
    0, 3000
    Invalid input.

    Note:
    The provided sample runs capture the expected output of your program (shown in bold) and the user inputs (shown in regular font). The bold formatting is used only here in the task description to make the output more readable. Your program should display the text without any formatting (without HTML markup).
    The newline character ("\n") is included after the last output line, including any error message.
