
# Runs the program for win
./hangman zyxwvutsrqponmlkjihgfedcba < tester.txt > win_output.txt

# Ensures exit code is not 0
if [ $? -ne 0 ]; then
    echo "incorrect win output!"
    rm output.txt
    exit 1
fi

# Ensures differences are not found in win.txt
diff win_output.txt win.txt
if [ $? -eq 0 ]; then
    echo "no differences found in win!"
else
    echo "differences are found in win"
fi

#Cleans up file
rm win_output.txt

#Runs program for lose
./hangman "don't go in empty-handed" < tester.txt > lose_output.txt

# Ensures exit code is not 0
if [ $? -ne 0 ]; then
    echo "incorrect lose output!"
    rm output.txt
    exit 1
fi

diff lose_output.txt lose.txt
if [ $? -eq 0 ]; then
    echo "no differences found in lose!"
else
    echo "differences are found in lose"
fi

# Cleans up file
rm lose_output.txt
exit 0
