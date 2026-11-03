
#include <stdio.h>
void receipt(int account, int balance, int amount, int type)
{
    FILE *fp;
    fp = fopen("receipt.svg", "w");
    if (fp == NULL)
    {
        printf("Receipt could not be created!\n");
        return;
    }
    fprintf(fp, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"600\" height=\"750\">\n");
    fprintf(fp, "<rect width=\"600\" height=\"750\" fill=\"#101f35\"/>\n");
    fprintf(fp, "<rect x=\"40\" y=\"40\" width=\"520\" height=\"670\" rx=\"25\" fill=\"#1c3452\"/>\n");
    fprintf(fp, "<text x=\"300\" y=\"115\" fill=\"#65e5c0\" font-size=\"35\" font-family=\"Arial\" text-anchor=\"middle\">SMART ATM</text>\n");
    fprintf(fp, "<text x=\"300\" y=\"155\" fill=\"white\" font-size=\"18\" font-family=\"Arial\" text-anchor=\"middle\">TRANSACTION RECEIPT</text>\n");
    fprintf(fp, "<line x1=\"80\" y1=\"190\" x2=\"520\" y2=\"190\" stroke=\"#65e5c0\"/>\n");
    fprintf(fp, "<text x=\"80\" y=\"250\" fill=\"white\" font-size=\"22\" font-family=\"Arial\">Account: XXXX%d</text>\n", account);
    if (type == 1)
        fprintf(fp, "<text x=\"80\" y=\"310\" fill=\"white\" font-size=\"22\" font-family=\"Arial\">Transaction: Balance Check</text>\n");
    else if (type == 2)
        fprintf(fp, "<text x=\"80\" y=\"310\" fill=\"white\" font-size=\"22\" font-family=\"Arial\">Transaction: Deposit</text>\n");
    else
        fprintf(fp, "<text x=\"80\" y=\"310\" fill=\"white\" font-size=\"22\" font-family=\"Arial\">Transaction: Withdrawal</text>\n");
    fprintf(fp, "<text x=\"80\" y=\"370\" fill=\"white\" font-size=\"22\" font-family=\"Arial\">Amount: Rs. %d</text>\n", amount);
    fprintf(fp, "<text x=\"80\" y=\"440\" fill=\"#65e5c0\" font-size=\"25\" font-family=\"Arial\">AVAILABLE BALANCE</text>\n");
    fprintf(fp, "<text x=\"80\" y=\"500\" fill=\"white\" font-size=\"45\" font-family=\"Arial\">Rs. %d</text>\n", balance);
    fprintf(fp, "<line x1=\"80\" y1=\"560\" x2=\"520\" y2=\"560\" stroke=\"#65e5c0\"/>\n");
    fprintf(fp, "<text x=\"300\" y=\"625\" fill=\"#65e5c0\" font-size=\"20\" font-family=\"Arial\" text-anchor=\"middle\">Transaction Successful</text>\n");
    fprintf(fp, "<text x=\"300\" y=\"665\" fill=\"white\" font-size=\"16\" font-family=\"Arial\" text-anchor=\"middle\">Thank you for using Smart ATM</text>\n");
    fprintf(fp, "</svg>");
    fclose(fp);
    printf("Receipt saved as receipt.svg\n");
}
int main()
{
    int account = 1001, pin = 1234;
    int acc, password, attempts = 0, choice = 0;
    int balance = 5000, amount;
    int note500 = 20, note200 = 20, note100 = 20;
    int n500, n200, n100, remaining, found, i, j;
    FILE *fp;
    fp = fopen("atm.txt", "r");
    if (fp != NULL)
    {
        if (fscanf(fp, "%d %d %d %d", &balance, &note500, &note200, &note100) != 4)
        {
            printf("Invalid ATM file!\n");
            fclose(fp);
            return 0;
        }
        fclose(fp);
    }
    printf("===== WELCOME TO ATM =====\n");
    printf("Enter Account Number: ");
    if (scanf("%d", &acc) != 1 || acc != account)
    {
        printf("Invalid Account Number!\n");
        return 0;
    }
    while (attempts < 3)
    {
        printf("Enter PIN: ");
        if (scanf("%d", &password) != 1)
        {
            printf("Invalid PIN input!\n");
            return 0;
        }
        if (password == pin)
        {
            printf("Login Successful!\n");
            break;
        }
        attempts++;
        printf("Wrong PIN! Attempts left: %d\n", 3 - attempts);
    }
    if (attempts == 3)
    {
        printf("Account blocked!\n");
        return 0;
    }
    do
    {
        printf("\n===== ATM MENU =====\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 0;
        }
        switch (choice)
        {
            case 1:
                printf("Current Balance: Rs. %d\n", balance);
                receipt(account, balance, 0, 1);
                break;
            case 2:
                printf("Enter deposit amount: ");
                if (scanf("%d", &amount) != 1)
                {
                    printf("Invalid input!\n");
                    return 0;
                }
                if (amount <= 0 || amount % 100 != 0)
                    printf("Invalid amount! Enter multiple of 100.\n");
                else if (amount > 100000 - balance)
                    printf("Deposit limit exceeded!\n");
                else
                {
                    balance = balance + amount;
                    fp = fopen("atm.txt", "w");
                    if (fp == NULL)
                    {
                        balance = balance - amount;
                        printf("File error! Deposit cancelled.\n");
                        break;
                    }
                    fprintf(fp, "%d %d %d %d", balance, note500, note200, note100);
                    fclose(fp);
                    printf("Deposit Successful!\n");
                    printf("Updated Balance: Rs. %d\n", balance);
                    receipt(account, balance, amount, 2);
                }
                break;
            case 3:
                printf("Enter withdrawal amount: ");
                if (scanf("%d", &amount) != 1)
                {
                    printf("Invalid input!\n");
                    return 0;
                }
                if (amount <= 0 || amount % 100 != 0)
                    printf("Invalid amount! Enter multiple of 100.\n");
                else if (amount > balance)
                    printf("Insufficient Balance!\n");
                else
                {
                    found = 0;
                    for (i = note500; i >= 0 && !found; i--)
                    {
                        if (i * 500 > amount)
                            continue;
                        for (j = note200; j >= 0; j--)
                        {
                            remaining = amount - i * 500 - j * 200;
                            if (remaining < 0)
                                continue;
                            if (remaining / 100 <= note100)
                            {
                                n500 = i;
                                n200 = j;
                                n100 = remaining / 100;
                                found = 1;
                                break;
                            }
                        }
                    }
                    if (found == 0)
                        printf("Required notes not available!\n");
                    else
                    {
                        fp = fopen("atm.txt", "w");
                        if (fp == NULL)
                        {
                            printf("File error! Withdrawal cancelled.\n");
                            break;
                        }
                        fprintf(fp, "%d %d %d %d", balance - amount, note500 - n500, note200 - n200, note100 - n100);
                        fclose(fp);
                        balance = balance - amount;
                        note500 = note500 - n500;
                        note200 = note200 - n200;
                        note100 = note100 - n100;
                        printf("Withdrawal Successful!\n");
                        printf("500 notes: %d\n", n500);
                        printf("200 notes: %d\n", n200);
                        printf("100 notes: %d\n", n100);
                        printf("Updated Balance: Rs. %d\n", balance);
                        receipt(account, balance, amount, 3);
                    }
                }
                break;
            case 4:
                printf("Thank you for using ATM!\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 4);
    return 0;
}
