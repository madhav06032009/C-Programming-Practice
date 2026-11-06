
#include <stdio.h>
#include <stdlib.h>

void receipt(int account, int balance, int amount, int type)
{
    FILE *fp = fopen("receipt.svg", "w");
    if (fp == NULL)
    {
        printf("Receipt file error!\n");
        return;
    }
    fprintf(fp, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"700\" height=\"850\">\n");
    fprintf(fp, "<rect width=\"700\" height=\"850\" fill=\"#101f35\"/>\n");
    fprintf(fp, "<rect x=\"40\" y=\"40\" width=\"620\" height=\"770\" rx=\"30\" fill=\"#1c3452\"/>\n");
    fprintf(fp, "<text x=\"350\" y=\"125\" font-size=\"45\" fill=\"#65e5c0\" text-anchor=\"middle\" font-family=\"Arial\">SMART ATM</text>\n");
    fprintf(fp, "<text x=\"350\" y=\"175\" font-size=\"22\" fill=\"white\" text-anchor=\"middle\" font-family=\"Arial\">TRANSACTION RECEIPT</text>\n");
    fprintf(fp, "<line x1=\"90\" y1=\"210\" x2=\"610\" y2=\"210\" stroke=\"#65e5c0\"/>\n");
    fprintf(fp, "<text x=\"90\" y=\"290\" font-size=\"25\" fill=\"white\" font-family=\"Arial\">Account: XXXX%d</text>\n", account);
    if (type == 1)
        fprintf(fp, "<text x=\"90\" y=\"360\" font-size=\"25\" fill=\"white\" font-family=\"Arial\">Balance Enquiry</text>\n");
    else if (type == 2)
        fprintf(fp, "<text x=\"90\" y=\"360\" font-size=\"25\" fill=\"white\" font-family=\"Arial\">Money Deposit</text>\n");
    else
        fprintf(fp, "<text x=\"90\" y=\"360\" font-size=\"25\" fill=\"white\" font-family=\"Arial\">Money Withdrawal</text>\n");
    fprintf(fp, "<text x=\"90\" y=\"430\" font-size=\"25\" fill=\"white\" font-family=\"Arial\">Amount: Rs. %d</text>\n", amount);
    fprintf(fp, "<text x=\"90\" y=\"520\" font-size=\"25\" fill=\"#65e5c0\" font-family=\"Arial\">AVAILABLE BALANCE</text>\n");
    fprintf(fp, "<text x=\"90\" y=\"590\" font-size=\"55\" fill=\"white\" font-family=\"Arial\">Rs. %d</text>\n", balance);
    fprintf(fp, "<line x1=\"90\" y1=\"650\" x2=\"610\" y2=\"650\" stroke=\"#65e5c0\"/>\n");
    fprintf(fp, "<text x=\"350\" y=\"720\" font-size=\"23\" fill=\"#65e5c0\" text-anchor=\"middle\" font-family=\"Arial\">TRANSACTION SUCCESSFUL</text>\n");
    fprintf(fp, "<text x=\"350\" y=\"765\" font-size=\"18\" fill=\"white\" text-anchor=\"middle\" font-family=\"Arial\">Thank you for using Smart ATM</text>\n");
    fprintf(fp, "</svg>");
    fclose(fp);
    if (system("magick -background none receipt.svg receipt.png") == 0)
    {
        printf("PNG receipt saved successfully!\n");
        system("start \"\" \"receipt.png\"");
    }
    else
        printf("PNG conversion failed. Check ImageMagick installation.\n");
}

int main()
{
    int account = 1001, pin = 1234, acc, password, attempts = 0;
    int choice = 0, balance = 5000, amount;
    int note500 = 20, note200 = 20, note100 = 20;
    int n500, n200, n100, remaining, found, i, j;
    FILE *fp;
    fp = fopen("atm.txt", "r");
    if (fp != NULL)
    {
        if (fscanf(fp, "%d %d %d %d", &balance, &note500, &note200, &note100) != 4 ||
            balance < 0 || balance > 100000 || note500 < 0 || note200 < 0 || note100 < 0)
        {
            printf("Invalid ATM data file!\n");
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
        printf("1. Check Balance\n2. Deposit Money\n3. Withdraw Money\n4. Exit\n");
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
                    return 0;
                if (amount <= 0 || amount % 100 != 0)
                    printf("Invalid amount! Enter multiple of 100.\n");
                else if (amount > 100000 - balance)
                    printf("Deposit limit exceeded!\n");
                else
                {
                    fp = fopen("atm.txt", "w");
                    if (fp == NULL)
                    {
                        printf("File error!\n");
                        break;
                    }
                    if (fprintf(fp, "%d %d %d %d\n", balance + amount, note500, note200, note100) < 0)
                    {
                        fclose(fp);
                        printf("Save failed!\n");
                        return 0;
                    }
                    if (fclose(fp) != 0)
                    {
                        printf("Save failed!\n");
                        return 0;
                    }
                    balance += amount;
                    printf("Deposit Successful!\nUpdated Balance: Rs. %d\n", balance);
                    receipt(account, balance, amount, 2);
                }
                break;
            case 3:
                printf("Enter withdrawal amount: ");
                if (scanf("%d", &amount) != 1)
                    return 0;
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
                    if (!found)
                        printf("Required notes not available!\n");
                    else
                    {
                        fp = fopen("atm.txt", "w");
                        if (fp == NULL)
                        {
                            printf("File error!\n");
                            break;
                        }
                        if (fprintf(fp, "%d %d %d %d\n", balance - amount, note500 - n500, note200 - n200, note100 - n100) < 0)
                        {
                            fclose(fp);
                            printf("Save failed!\n");
                            return 0;
                        }
                        if (fclose(fp) != 0)
                        {
                            printf("Save failed!\n");
                            return 0;
                        }
                        balance -= amount;
                        note500 -= n500;
                        note200 -= n200;
                        note100 -= n100;
                        printf("Withdrawal Successful!\n");
                        printf("500 notes: %d\n200 notes: %d\n100 notes: %d\n", n500, n200, n100);
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
